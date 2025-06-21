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

| Конструкция      | Файл реализован?                    | Комментарий                                    |
| ---------------- | ----------------------------------- | ---------------------------------------------- |
| DATA             | ✅ parser\_data\_data.c              | Объявление переменной реализовано              |
| CONSTANTS        | ✅ parser\_data\_constants.c         | Объявление константы реализовано               |
| PARAMETERS       | ✅ parser\_data\_parameters.c        | Объявление параметров реализовано              |
| FIELD-SYMBOLS    | ✅ parser\_data\_field\_symbols.c    | Объявление указателей реализовано              |
| TYPES            | ✅ parser\_data\_types.c             | Определение пользовательских типов реализовано |
| SELECT-OPTIONS   | ✅ parser\_data\_select\_options.c   | Специальный тип диапазона выбора реализован    |
| RANGES           | ✅ parser\_data\_ranges.c            | Определение диапазона значений реализовано     |
| VALUE assignment | ✅ parser\_data\_value\_assignment.c | Присвоение значения при объявлении реализовано |
| INITIALIZATION   | ✅ parser\_data\_initialization.c    | Инициализация переменных реализовано           |
| COMPLEX TYPES    | ✅ parser\_data\_complex\_types.c    | Таблицы, структуры реализованы                 |
| CONSTANTS value  | ✅ parser\_data\_constants\_value.c  | Значения для констант реализованы              |
