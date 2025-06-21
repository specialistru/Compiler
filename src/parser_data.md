## ✅ Поддерживаемые конструкции DATA

| Имя файла                   | Конструкция                    | Пример                            | Поддерживается | Комментарий                                     |
| --------------------------- | ------------------------------ | --------------------------------- | -------------- | ----------------------------------------------- |
| parser_data_identifier.c    | Обработка идентификаторов      | `my_var`                          | ✅ Готово      | Проверка и возврат идентификатора               |
| parser_data_type.c          | Разбор конструкции TYPE        | `TYPE string`                     | ✅ Готово      | Поддерживается простая обработка                |
| parser_data_declaration.c   | Основное объявление DATA и др. | `DATA my_var TYPE string.`        | ✅ Готово      | Полная поддержка объявления                     |
| parser_data_constants.c     | Объявление CONSTANTS           | `CONSTANTS pi TYPE p VALUE 3.14.` | 🔲 Частично    | Нет поддержки VALUE и дополнительных параметров |
| parser_data_types.c         | Объявление TYPES               | `TYPES ty_str TYPE string.`       | ✅ Готово      | Простая поддержка типов                         |
| parser_data_field_symbols.c | Объявление FIELD-SYMBOLS       | `FIELD-SYMBOLS <fs> TYPE any.`    | 🔲 Частично    | Не реализована проверка типа и использования    |
| parser_data_parameters.c    | Объявление PARAMETERS          | `PARAMETERS p_name TYPE string.`  | ✅ Готово      | Простая обработка параметров                    |
| parser_data_type_complex.c  | Сложные типы и структуры       | `TYPES ty_struct TYPE STRUCTURE.` | ❌ Не готово   | Отсутствует поддержка структур и сложных типов  |
