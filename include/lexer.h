#ifndef LEXER_H
#define LEXER_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
// Подключаем utf8proc для Unicode-анализа
#include <utf8proc.h>

// Максимальная длина лексемы (при необходимости можно увеличить)
#define MAX_LEXEME_LEN 256

// Тип токена (дополнить по мере необходимости)
typedef enum {
    TOKEN_UNKNOWN = 0,
    TOKEN_EOF,
    TOKEN_IDENTIFIER,
    TOKEN_KEYWORD,
    TOKEN_NUMBER,
    TOKEN_STRING,
    TOKEN_OPERATOR,
    TOKEN_COMMENT,
    TOKEN_SYMBOL,
    // ... добавить остальные токены ABAP
} token_type_t;

// Структура токена
typedef struct {
    token_type_t type;
    char *lexeme;        // динамически выделенная строка с текстом токена
    int line;            // номер строки
    int column;          // номер колонки
} Token_t;

typedef struct {
    const char* source;
    size_t pos;
    int line;
    int column;
} lexer_t;

// Структура лексера
typedef struct {
    const char *source;  // исходный код
    int length;          // длина исходного кода
    size_t pos;          // текущая позиция в исходном коде (байты)
    int line;            // текущая строка
    int column;          // текущая колонка
} Lexer_t;

// Инициализация лексера
void lexer_init(Lexer *lexer, const char *source);

// Получить следующий токен
Token_t lexer_next_token(Lexer *lexer);

// Очистка памяти токена
void lexer_free_token(Token *token);

// Проверка начала идентификатора UTF-8
int is_utf8_identifier_start(int32_t codepoint);

// Проверка продолжения идентификатора UTF-8
int is_utf8_identifier_continue(int32_t codepoint);

// Функция итерации по utf8-символам
int utf8proc_iterate(const uint8_t *str, int32_t strlen, int32_t *codepoint);

#endif // LEXER_H
