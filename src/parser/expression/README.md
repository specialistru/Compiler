| Имя файла                            | Конструкция              | Пример                          | Поддерживается | Комментарий                                     |
| ------------------------------------ | ------------------------ | ------------------------------- | -------------- | ----------------------------------------------- |
| parser\_expression\_arithmetic.c     | Арифметические выражения | `a + b * c`                     | ✅ Готово       | Полная поддержка                                |
| parser\_expression\_logical.c        | Логические выражения     | `a AND b OR NOT c`              | 🔲 Частично    | Требуется доработка                             |
| parser\_expression\_function\_call.c | Вызовы функций           | `func(a, b)`                    | ✅ Готово       | Полностью реализовано                           |
| parser\_expression\_literal.c        | Литералы (числа, строки) | `"Hello"`, `123`                | ✅ Готово       |                                                 |
| parser\_expression\_identifier.c     | Идентификаторы           | `variableName`                  | ✅ Готово       |                                                 |
| parser\_expression\_bracketed.c      | Выражения в скобках      | `(a + b) * c`                   | ❌ Не готово    | Требуется полная реализация                     |
| parser\_expression\_unary.c          | Унарные операции         | `-a`, `NOT b`                   | 🔲 Частично    | Нужно доработать                                |
| parser\_expression\_comparison.c     | Операции сравнения       | `a = b`, `x <> y`               | ✅ Готово       |                                                 |
| parser\_expression\_ternary.c        | Тернарные выражения      | `cond ? expr1 : expr2`          | ❌ Не готово    | Реализация отсутствует                          |
| parser\_expression\_function.c       | Вызов функции            | `func_name(arg1, arg2)`         | ✅              | Полная реализация, парсит функцию с аргументами |
| parser\_expression\_operator.c       | Операторы (арифметика)   | `a + b * c`                     | ✅              | Полноценный разбор операций                     |
| parser\_expression\_variable.c       | Переменные               | `var_name`                      | ✅              | Поддерживается идентификация переменных         |
| parser\_expression\_bracket.c        | Скобочные выражения      | `(a + b)`                       | ✅              | Корректно парсит выражения в скобках            |
| parser\_expression\_complex.c        | Сложные выражения        | Комбинации операторов и функций | 🔲             | Частичная реализация, требует доработки         |
| parser\_expression\_conditional.c    | Тернарный оператор       | `cond ? trueVal : falseVal`     | ❌              | Пока не реализовано                             |
| parser\_expression\_assignment.c     | Присвоение               | `a = 5`                         | ✅              | Реализовано, корректно парсит присвоения        |
| parser\_expression\_array\_access.c  | Обращение к массивам     | `arr[index]`                    | 🔲             | Частичная поддержка, нужна доработка            |
