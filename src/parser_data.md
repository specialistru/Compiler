## ✅ Поддерживаемые конструкции DATA

| Имя файла                      | Конструкция      | Пример                              | Поддерживается | Комментарий                              |
| ------------------------------ | ---------------- | ----------------------------------- | -------------- | ---------------------------------------- |
| parser_data_data.c             | DATA             | DATA lv_var TYPE i.                 | ✅             | Полная поддержка объявления переменных   |
| parser_data_constants.c        | CONSTANTS        | CONSTANTS pi TYPE p VALUE 3.14.     | ✅             | Полная поддержка объявления констант     |
| parser_data_parameters.c       | PARAMETERS       | PARAMETERS p_matnr TYPE matnr.      | ✅             | Полная поддержка параметров              |
| parser_data_field_symbols.c    | FIELD-SYMBOLS    | FIELD-SYMBOLS <fs>.                 | ✅             | Полная поддержка указателей              |
| parser_data_types.c            | TYPES            | TYPES ty_tab TYPE STANDARD TABLE.   | ✅             | Полная поддержка определения типов       |
| parser_data_select_options.c   | SELECT-OPTIONS   | SELECT-OPTIONS so_matnr FOR matnr.  | ✅             | Поддержка базовая, без сложных опций     |
| parser_data_ranges.c           | RANGES           | RANGES r_matnr FOR matnr.           | ✅             | Поддержка базовая                        |
| parser_data_value_assignment.c | VALUE assignment | DATA lv_var TYPE i VALUE 10.        | ✅             | Поддержка присвоения значения            |
| parser_data_initialization.c   | INITIALIZATION   | DATA lv_var TYPE i INIT 0.          | ✅             | Поддержка инициализации                  |
| parser_data_complex_types.c    | COMPLEX TYPES    | TYPES ty_tab TYPE TABLE OF ty_line. | 🔲             | Частичная поддержка, нет парсинга полей  |
| parser_data_constants_value.c  | CONSTANTS value  | CONSTANTS pi TYPE p VALUE 3.14.     | ✅             | Поддержка присвоения значений константам |
