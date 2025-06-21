#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

// Вспомогательная функция для сравнения токена с ожидаемым значением
static void check_token(Token *token, token_type_t expected_type, const char *expected_lexeme, int expected_line, int expected_col) {
    if (token->type != expected_type) {
        fprintf(stderr, "Ошибка: ожидаемый тип токена %d, получен %d\n", expected_type, token->type);
        exit(1);
    }
    if (expected_lexeme != NULL) {
        if (token->lexeme == NULL || strcmp(token->lexeme, expected_lexeme) != 0) {
            fprintf(stderr, "Ошибка: ожидаемый лексем \"%s\", получен \"%s\"\n",
                    expected_lexeme,
                    token->lexeme ? token->lexeme : "(NULL)");
            exit(1);
        }
    }
    if (token->line != expected_line || token->col != expected_col) {
        fprintf(stderr, "Ошибка: ожидаемые позиция %d:%d, получена %d:%d\n",
                expected_line, expected_col, token->line, token->col);
        exit(1);
    }
}

// Основная функция теста
int main() {
    const char *source =
        "* Комментарий в ABAP\n"
        "DATA lv_имя TYPE string.\n"
        "lv_имя = 'Привет''мир'.\n"
        "WRITE: / lv_имя.\n"
        "IF lv_имя = 'Привет'.\n"
        "  WRITE 'Приветствие'.\n"
        "ENDIF.\n"
        "DO 10 TIMES.\n"
        "  WRITE 'Loop'.\n"
        "ENDDO.\n";

    Lexer lexer;
    lexer_init(&lexer, source);

    Token token;
    int count = 0;

    while (1) {
        token = lexer_next_token(&lexer);
        if (token.type == TOKEN_EOF) {
            lexer_free_token(&token);
            break;
        }
        switch(count) {
            case 0: // Комментарий
                check_token(&token, TOKEN_COMMENT, "* Комментарий в ABAP", 1, 1);
                break;
            case 1: // DATA
                check_token(&token, TOKEN_IDENTIFIER, "DATA", 2, 1);
                break;
            case 2: // lv_имя
                check_token(&token, TOKEN_IDENTIFIER, "lv_имя", 2, 6);
                break;
            case 3: // TYPE
                check_token(&token, TOKEN_IDENTIFIER, "TYPE", 2, 13);
                break;
            case 4: // string
                check_token(&token, TOKEN_IDENTIFIER, "string", 2, 18);
                break;
            case 5: // .
                check_token(&token, TOKEN_OPERATOR, ".", 2, 24);
                break;
            case 6: // lv_имя
                check_token(&token, TOKEN_IDENTIFIER, "lv_имя", 3, 1);
                break;
            case 7: // =
                check_token(&token, TOKEN_OPERATOR, "=", 3, 7);
                break;
            case 8: // строка с экранированием
                check_token(&token, TOKEN_STRING, "Привет'мир", 3, 9);
                break;
            case 9: // .
                check_token(&token, TOKEN_OPERATOR, ".", 3, 22);
                break;
            case 10: // WRITE
                check_token(&token, TOKEN_IDENTIFIER, "WRITE", 4, 1);
                break;
            case 11: // :
                check_token(&token, TOKEN_OPERATOR, ":", 4, 6);
                break;
            case 12: // /
                check_token(&token, TOKEN_OPERATOR, "/", 4, 8);
                break;
            case 13: // lv_имя
                check_token(&token, TOKEN_IDENTIFIER, "lv_имя", 4, 10);
                break;
            case 14: // .
                check_token(&token, TOKEN_OPERATOR, ".", 4, 16);
                break;
            case 15: // IF
                check_token(&token, TOKEN_IDENTIFIER, "IF", 5, 1);
                break;
            case 16: // lv_имя
                check_token(&token, TOKEN_IDENTIFIER, "lv_имя", 5, 4);
                break;
            case 17: // =
                check_token(&token, TOKEN_OPERATOR, "=", 5, 10);
                break;
            case 18: // строка
                check_token(&token, TOKEN_STRING, "Привет", 5, 12);
                break;
            case 19: // .
                check_token(&token, TOKEN_OPERATOR, ".", 5, 21);
                break;
            case 20: // WRITE
                check_token(&token, TOKEN_IDENTIFIER, "WRITE", 6, 3);
                break;
            case 21: // строка
                check_token(&token, TOKEN_STRING, "Приветствие", 6, 9);
                break;
            case 22: // .
                check_token(&token, TOKEN_OPERATOR, ".", 6, 22);
                break;
            case 23: // ENDIF
                check_token(&token, TOKEN_IDENTIFIER, "ENDIF", 7, 1);
                break;
            case 24: // .
                check_token(&token, TOKEN_OPERATOR, ".", 7, 6);
                break;
            case 25: // DO
                check_token(&token, TOKEN_IDENTIFIER, "DO", 8, 1);
                break;
            case 26: // число
                check_token(&token, TOKEN_NUMBER, "10", 8, 4);
                break;
            case 27: // TIMES
                check_token(&token, TOKEN_IDENTIFIER, "TIMES", 8, 7);
                break;
            case 28: // .
                check_token(&token, TOKEN_OPERATOR, ".", 8, 12);
                break;
            case 29: // WRITE
                check_token(&token, TOKEN_IDENTIFIER, "WRITE", 9, 3);
                break;
            case 30: // строка
                check_token(&token, TOKEN_STRING, "Loop", 9, 9);
                break;
            case 31: // .
                check_token(&token, TOKEN_OPERATOR, ".", 9, 15);
                break;
            case 32: // ENDDO
                check_token(&token, TOKEN_IDENTIFIER, "ENDDO", 10, 1);
                break;
            case 33: // .
                check_token(&token, TOKEN_OPERATOR, ".", 10, 6);
                break;
            default:
                fprintf(stderr, "Ошибка: неожидаемый токен номер %d\n", count);
                exit(1);
        }
        lexer_free_token(&token);
        count++;
    }

    printf("Все тесты пройдены успешно!\n");
    return 0;
}
