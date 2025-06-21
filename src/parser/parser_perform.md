## ✅ Поддерживаемые конструкции PERFORM

| Имя файла                 | Конструкция                                          | Пример                                         | Поддерживается | Комментарий                                              |
| ------------------------- | ---------------------------------------------------- | ---------------------------------------------- | -------------- | -------------------------------------------------------- |
| parser_perform_simple.c   | Простое выполнение PERFORM                           | `PERFORM subroutine.`                          | ✅             | Полная поддержка простой формы PERFORM                   |
| parser_perform_using.c    | PERFORM ... USING                                    | `PERFORM subroutine USING var1 var2.`          | ✅             | Поддержка передачи параметров USING                      |
| parser_perform_tables.c   | PERFORM ... TABLES                                   | `PERFORM subroutine TABLES itab.`              | ✅             | Обработка передачи таблиц                                |
| parser_perform_changing.c | PERFORM ... CHANGING                                 | `PERFORM subroutine CHANGING var.`             | ✅             | Поддержка передачи параметров CHANGING                   |
| parser_perform_errors.c   | Обработка ошибок                                     | N/A                                            | ✅             | Вывод и обработка ошибок при парсинге                    |
| parser_perform_complex.c  | Сложные конструкции PERFORM (WITH, returning и т.п.) | `PERFORM subroutine WITH param RETURNING var.` | 🔲             | Частичная поддержка, требует доработки сложных вариантов |
| parser_perform_nested.c   | Вложенные вызовы PERFORM                             | Вложенный вызов в теле другого PERFORM         | 🔲             | Частично поддерживается, нужна доработка                 |
