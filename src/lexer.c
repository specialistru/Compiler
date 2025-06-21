#include "lexer.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_TOKEN_SIZE 512

// Ключевые слова ABAP (с учётом твоего списка)
static const char* keywords[] = {
    // 1. Объявление данных
    "DATA", "CONSTANTS", "TYPES", "PARAMETERS", "SELECT-OPTIONS",
    "TABLES", "FIELD-SYMBOLS", "RANGES", "FIELD-GROUPS",

    // 2. Управление потоком
    "IF", "ELSE", "ELSEIF", "ENDIF", "CASE", "WHEN", "OTHERWISE", "ENDCASE",
    "DO", "WHILE", "ENDDO", "LOOP", "ENDLOOP", "EXIT", "CONTINUE", "CHECK", "RETURN",

    // 3. Операторы обработки
    "MOVE", "MOVE-CORRESPONDING", "CLEAR", "REFRESH", "APPEND", "DELETE", "INSERT",
    "MODIFY", "READ", "SORT", "COLLECT", "TRANSFER",

    // 4. Операторы вызова
    "CALL", "FUNCTION", "PERFORM", "CALL", "METHOD", "EXEC", "SQL", "SUBMIT",
    "WAIT", "MESSAGE", "RAISE",

    // 5. Работа с таблицами
    "OPEN", "CURSOR", "FETCH", "CLOSE", "SELECT", "SINGLE", "ENDSELECT",
    "MODIFY", "TABLE", "LOOP", "AT", "READ", "DELETE", "INSERT",

    // 6. Операторы обработки исключений
    "TRY", "CATCH", "CLEANUP", "ENDTRY", "MESSAGE", "RAISE", "EXCEPTION",

    // 7. Определение программных объектов
    "REPORT", "PROGRAM", "FUNCTION-POOL", "FUNCTION", "FORM", "CLASS",
    "INTERFACE", "METHOD", "ENDCLASS", "ENDINTERFACE",

    // 8. Модульные операторы (повторяются, но важно для разбора)
    "PERFORM", "SUBMIT", "CALL", "FUNCTION", "CALL", "METHOD", "RETURN",

    // 9. Ключевые слова структуры
    "STRUCTURE", "TABLE", "TYPE", "OCCURS", "WITH", "HEADER", "LINE",
    "LIKE", "CONSTANTS", "INITIALIZATION", "AT", "SELECTION-SCREEN",

    // 10. Специальные
    "EXPORT", "IMPORT", "MEMORY", "ID", "SET", "PARAMETER", "GET",
    "AUTHORITY-CHECK", "NEW", "FREE", "REF", "TO", "CREATE", "OBJECT", "FREE", "OBJECT",

    NULL
};

// Прототип для проверки ключевого слова (возвращает true если keyword)
static bool is_keyword(const char* str) {
    for (int i = 0; keywords[i] != NULL; i++) {
        if (strcasecmp(str, keywords[i]) == 0) return true;
    }
    return false;
}

void lexer_init(lexer_t* lexer, const char* source) {
    lexer->source = source;
    lexer->pos = 0;
    lexer->line = 1;
    lexer->column = 1;
}

static char peek(lexer_t* lexer) {
    return lexer->source[lexer->pos];
}

static char peek_next(lexer_t* lexer) {
    return lexer->source[lexer->pos + 1];
}

static char advance(lexer_t* lexer) {
    char c = lexer->source[lexer->pos++];
    if (c == '\n') {
        lexer->line++;
        lexer->column = 1;
    } else {
        lexer->column++;
    }
    return c;
}

static void skip_whitespace(lexer_t* lexer) {
    while (isspace(peek(lexer))) {
        advance(lexer);
    }
}

static token_t make_token(token_type_t type, const char* start, size_t len, int line, int col) {
    char* lexeme = (char*)malloc(len + 1);
    if (!lexeme) {
        fprintf(stderr, "[LEXER ERROR] malloc failed\n");
        exit(EXIT_FAILURE);
    }
    strncpy(lexeme, start, len);
    lexeme[len] = '\0';
    return (token_t){ type, lexeme, line, col };
}

void lexer_free_token(token_t* token) {
    if (token->lexeme) {
        free(token->lexeme);
        token->lexeme = NULL;
    }
}

token_t lexer_next_token(lexer_t* lexer) {
    skip_whitespace(lexer);

    int line = lexer->line;
    int col = lexer->column;
    char c = peek(lexer);

    if (c == '\0') return make_token(TOKEN_EOF, "", 0, line, col);

    // Комментарии (строки начинаются с * или ")
    if (c == '*' || c == '"') {
        while (peek(lexer) != '\n' && peek(lexer) != '\0') advance(lexer);
        return lexer_next_token(lexer); // пропускаем комментарий
    }

    // Идентификаторы / ключевые слова (учитываем дефисы для ABAP, например MOVE-CORRESPONDING)
    if (isalpha(c) || c == '_') {
        const char* start = &lexer->source[lexer->pos];
        size_t len = 0;
        while (isalnum(peek(lexer)) || peek(lexer) == '_' || peek(lexer) == '-') {
            advance(lexer);
            len++;
        }
        // Проверяем ключевые слова (вверхний регистр)
        char* tmp = (char*)malloc(len + 1);
        strncpy(tmp, start, len);
        tmp[len] = '\0';

        // ABAP ключевые слова чувствительны к дефисам
        // Приводим к верхнему регистру для сравнения
        for (size_t i = 0; i < len; i++) tmp[i] = toupper((unsigned char)tmp[i]);

        token_type_t type = is_keyword(tmp) ? TOKEN_KEYWORD : TOKEN_IDENTIFIER;
        token_t token = make_token(type, start, len, line, col);
        free(tmp);
        return token;
    }

    // Числа (целые, десятичные, с экспонентой)
    if (isdigit(c)) {
        const char* start = &lexer->source[lexer->pos];
        bool dot_found = false;
        size_t len = 0;
        while (isdigit(peek(lexer)) || (!dot_found && peek(lexer) == '.')) {
            if (peek(lexer) == '.') dot_found = true;
            advance(lexer);
            len++;
        }
        if (tolower(peek(lexer)) == 'e') {
            advance(lexer);
            len++;
            if (peek(lexer) == '+' || peek(lexer) == '-') {
                advance(lexer);
                len++;
            }
            while (isdigit(peek(lexer))) {
                advance(lexer);
                len++;
            }
        }
        return make_token(TOKEN_NUMBER, start, len, line, col);
    }

    // Строки в одинарных кавычках (учитываем двойные кавычки как экранирование)
    if (c == '\'') {
        advance(lexer); // пропускаем начальную кавычку
        const char* start = &lexer->source[lexer->pos];
        size_t len = 0;
        while (peek(lexer) != '\0') {
            if (peek(lexer) == '\'' && peek_next(lexer) == '\'') {
                advance(lexer); // двойная кавычка - экранирование
                advance(lexer);
                len++;
            } else if (peek(lexer) == '\'') {
                break;
            } else {
                advance(lexer);
                len++;
            }
        }
        advance(lexer); // закрывающая кавычка
        return make_token(TOKEN_STRING, start, len, line, col);
    }

    // Операторы с двумя символами (=>, ->, <>, <=, >=)
    if (c == '=' && peek_next(lexer) == '>') {
        advance(lexer); advance(lexer);
        return make_token(TOKEN_OPERATOR, "=>", 2, line, col);
    }
    if (c == '-' && peek_next(lexer) == '>') {
        advance(lexer); advance(lexer);
        return make_token(TOKEN_OPERATOR, "->", 2, line, col);
    }
    if (c == '<' && peek_next(lexer) == '>') {
        advance(lexer); advance(lexer);
        return make_token(TOKEN_OPERATOR, "<>", 2, line, col);
    }
    if ((c == '<' || c == '>') && peek_next(lexer) == '=') {
        char op[3] = { c, '=', '\0' };
        advance(lexer); advance(lexer);
        return make_token(TOKEN_OPERATOR, op, 2, line, col);
    }

    // Операторы с одним символом и символы
    if (strchr("+-*/=()[],.;:", c)) {
        advance(lexer);
        return make_token(TOKEN_SYMBOL, &lexer->source[lexer->pos - 1], 1, line, col);
    }

    // Неизвестный символ
    fprintf(stderr, "[LEXER ERROR] Unknown character '%c' at %d:%d\n", c, line, col);
    advance(lexer);
    return make_token(TOKEN_UNKNOWN, &lexer->source[lexer->pos - 1], 1, line, col);
}
