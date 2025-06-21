// parser_if_end.c
#include "parser_if_end.h"
#include "parser.h"

bool parse_if_end(parser_t* parser) {
    if (parser_match_keyword(parser, "ENDIF")) {
        return true;
    }
    parser_error(parser, "Ожидался ENDIF для завершения конструкции IF");
    return false;
}
