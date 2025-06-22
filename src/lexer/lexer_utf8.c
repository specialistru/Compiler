#include "lexer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

// Инициализация лексера
void lexer_init(Lexer *lexer, const char *source) {
    lexer->source = source;
    lexer->length = (int)strlen(source);
    lexer->pos = 0;
    lexer->line = 1;
    lexer->col = 1;
}

// Освобождение памяти токена
void lexer_free_token(Token *token) {
    if (token->lexeme) {
        free(token->lexeme);
        token->lexeme = NULL;
    }
}

// Проверка начала идентификатора UTF-8
int is_utf8_identifier_start(int32_t cp) {
    utf8proc_category_t cat = utf8proc_category(cp);
    return (cat == UTF8PROC_CATEGORY_LU || // Uppercase letter
            cat == UTF8PROC_CATEGORY_LL || // Lowercase letter
            cat == UTF8PROC_CATEGORY_LT || // Titlecase letter
            cat == UTF8PROC_CATEGORY_LM || // Modifier letter
            cat == UTF8PROC_CATEGORY_LO || // Other letter
            cp == '_');                    // Подчеркивание разрешено в начале
}

// Проверка продолжения идентификатора UTF-8
int is_utf8_identifier_continue(int32_t cp) {
    utf8proc_category_t cat = utf8proc_category(cp);
    return (is_utf8_identifier_start(cp) ||
            cat == UTF8PROC_CATEGORY_ND ||  // Decimal number
            cat == UTF8PROC_CATEGORY_PC);   // Connector punctuation (например, подчеркивание)
}

// Вспомогательная функция для чтения одного UTF-8 символа
// Возвращает количество байт в символе, либо 0 если ошибка
int utf8proc_iterate(const uint8_t *str, int32_t strlen, int32_t *codepoint) {
    // Вызов utf8proc
    int result = utf8proc_iterate(str, strlen, codepoint);
    if (result <= 0) {
        // Ошибка кодировки, считаем один байт как символ
        *codepoint = (int32_t)(*str);
        return 1;
    }
    return result;
}

// Пропуск пробелов и табуляции
static void skip_whitespace(Lexer *lexer) {
    while (lexer->pos < lexer->length) {
        char c = lexer->source[lexer->pos];
        if (c == ' ' || c == '\t') {
            lexer->pos++;
            lexer->col++;
        } else if (c == '\n' || c == '\r') {
            lexer->pos++;
            lexer->line++;
            lexer->col = 1;
            // Если \r\n - пропускаем вторую часть
            if (lexer->pos < lexer->length && lexer->source[lexer->pos] == '\n') {
                lexer->pos++;
            }
        } else {
            break;
        }
    }
}

// Чтение идентификатора или ключевого слова
static Token lex_identifier(Lexer *lexer) {
    Token token;
    token.type = TOKEN_IDENTIFIER;
    token.line = lexer->line;
    token.col = lexer->col;
    int start_pos = lexer->pos;

    int32_t cp;
    int bytes = utf8proc_iterate((uint8_t*)&lexer->source[lexer->pos], lexer->length - lexer->pos, &cp);
    if (!is_utf8_identifier_start(cp)) {
        token.type = TOKEN_UNKNOWN;
        token.lexeme = strndup(&lexer->source[lexer->pos], 1);
        lexer->pos++;
        lexer->col++;
        return token;
    }

    lexer->pos += bytes;
    lexer->col++;

    while (lexer->pos < lexer->length) {
        int next_bytes = utf8proc_iterate((uint8_t*)&lexer->source[lexer->pos], lexer->length - lexer->pos, &cp);
        if (!is_utf8_identifier_continue(cp)) break;
        lexer->pos += next_bytes;
        lexer->col++;
    }

    int len = lexer->pos - start_pos;
    token.lexeme = strndup(&lexer->source[start_pos], len);

    return token;
}

// Чтение числа (целое или с плавающей точкой)
static Token lex_number(Lexer *lexer) {
    Token token;
    token.type = TOKEN_NUMBER;
    token.line = lexer->line;
    token.col = lexer->col;

    int start_pos = lexer->pos;
    int has_dot = 0;
    int has_exp = 0;

    while (lexer->pos < lexer->length) {
        char c = lexer->source[lexer->pos];
        if (isdigit(c)) {
            lexer->pos++;
            lexer->col++;
        } else if (c == '.' && !has_dot) {
            has_dot = 1;
            lexer->pos++;
            lexer->col++;
        } else if ((c == 'E' || c == 'e') && !has_exp) {
            has_exp = 1;
            lexer->pos++;
            lexer->col++;
            // Может быть знак + или -
            if (lexer->pos < lexer->length) {
                char next_c = lexer->source[lexer->pos];
                if (next_c == '+' || next_c == '-') {
                    lexer->pos++;
                    lexer->col++;
                }
            }
        } else {
            break;
        }
    }

    int len = lexer->pos - start_pos;
    token.lexeme = strndup(&lexer->source[start_pos], len);

    return token;
}

// Чтение строки в одинарных кавычках с экранированием ''
static Token lex_string(Lexer *lexer) {
    Token token;
    token.type = TOKEN_STRING;
    token.line = lexer->line;
    token.col = lexer->col;

    lexer->pos++; // пропускаем начальный '
    lexer->col++;

    int start_pos = lexer->pos;
    char *buffer = malloc(MAX_LEXEME_LEN);
    if (!buffer) {
        perror("malloc");
        exit(1);
    }
    int buf_idx = 0;

    while (lexer->pos < lexer->length) {
        char c = lexer->source[lexer->pos];

        // Конец строки
        if (c == '\'') {
            // Проверяем двойные одинарные кавычки ''
            if (lexer->pos + 1 < lexer->length && lexer->source[lexer->pos + 1] == '\'') {
                buffer[buf_idx++] = '\'';
                lexer->pos += 2;
                lexer->col += 2;
            } else {
                lexer->pos++;
                lexer->col++;
                break;
            }
        } else {
            buffer[buf_idx++] = c;
            lexer->pos++;
            lexer->col++;
            if (buf_idx >= MAX_LEXEME_LEN - 1) break;
        }
    }

    buffer[buf_idx] = '\0';
    token.lexeme = buffer;
    return token;
}

// Чтение комментария
static Token lex_comment(Lexer *lexer) {
    Token token;
    token.type = TOKEN_COMMENT;
    token.line = lexer->line;
    token.col = lexer->col;

    int start_pos = lexer->pos;

    while (lexer->pos < lexer->length) {
        char c = lexer->source[lexer->pos];
        if (c == '\n' || c == '\r') break;
        lexer->pos++;
        lexer->col++;
    }

    int len = lexer->pos - start_pos;
    token.lexeme = strndup(&lexer->source[start_pos], len);

    return token;
}

// Чтение оператора или символа (один или два символа)
static Token lex_operator_or_symbol(Lexer *lexer) {
    Token token;
    token.type = TOKEN_OPERATOR;
    token.line = lexer->line;
    token.col = lexer->col;

    char c = lexer->source[lexer->pos];
    char next_c = (lexer->pos + 1 < lexer->length) ? lexer->source[lexer->pos + 1] : 0;

    // Список операторов с 2 символами, которые используются в ABAP
    if ((c == '-' && next_c == '>') ||
        (c == '=' && next_c == '>') ||
        (c == '<' && next_c == '>') ||
        (c == '<' && next_c == '=') ||
        (c == '>' && next_c == '=')) {

        token.lexeme = (char*)malloc(3);
        token.lexeme[0] = c;
        token.lexeme[1] = next_c;
        token.lexeme[2] = '\0';

        lexer->pos += 2;
        lexer->col += 2;
    } else {
        // Однобайтовый оператор/символ
        token.lexeme = (char*)malloc(2);
        token.lexeme[0] = c;
        token.lexeme[1] = '\0';

        lexer->pos++;
        lexer->col++;
    }

    return token;
}

// Основная функция получения следующего токена
Token lexer_next_token(Lexer *lexer) {
    skip_whitespace(lexer);

    if (lexer->pos >= lexer->length) {
        Token eof = { TOKEN_EOF, NULL, lexer->line, lexer->col };
        return eof;
    }

    char c = lexer->source[lexer->pos];

    // Комментарии: строка начинается с * или "
    if (c == '*' || c == '"') {
        return lex_comment(lexer);
    }

    // Строки
    if (c == '\'') {
        return lex_string(lexer);
    }

    // Числа (начинаются с цифры)
    if (isdigit(c)) {
        return lex_number(lexer);
    }

    // Идентификаторы и ключевые слова (начинаются с UTF-8 буквы или _)
    int32_t cp;
    int bytes = utf8proc_iterate((uint8_t*)&lexer->source[lexer->pos], lexer->length - lexer->pos, &cp);
    if (is_utf8_identifier_start(cp)) {
        return lex_identifier(lexer);
    }

    // Операторы и символы
    return lex_operator_or_symbol(lexer);
}
