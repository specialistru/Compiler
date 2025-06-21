## ✅ Поддерживаемые конструкции PERFORM

| Имя файла                     | Конструкция                   | Пример                       | Поддерживается | Комментарий                           |
| ----------------------------- | ----------------------------- | ---------------------------- | -------------- | ------------------------------------- |
| parser_perform_nested.c       | Вложенный PERFORM             | `PERFORM subroutine.`        | 🔲 Частично    | Требуется доработка вложенных вызовов |
| parser_perform_logical_ops.c  | Логические операции в PERFORM | `PERFORM ... AND ... OR ...` | 🔲 Частично    | Частичная поддержка AND/OR            |
| parser_perform_syntax_error.c | Ошибки синтаксиса PERFORM     | `PERFORM missing_dot`        | ✅ Готово      | Обработка базовых ошибок              |
| parser_perform_complex.c      | Сложные конструкции PERFORM   | `PERFORM ... USING ...`      | 🔲 Частично    | Требуется доработка сложных вызовов   |
| parser_perform_and_or.c       | Логические операторы AND/OR   | `PERFORM ... AND ... OR ...` | 🔲 Частично    | Частичная поддержка                   |
| parser_perform_errors.c       | Обработка ошибок PERFORM      | `PERFORM invalid_syntax.`    | ✅ Готово      | Базовые ошибки парсинга               |
| parser_perform_elseif.c       | Ветка ELSEIF в PERFORM        | `PERFORM ... ELSEIF ...`     | ❌ Не готово   | Не реализовано                        |
| parser_perform_else.c         | Ветка ELSE в PERFORM          | `PERFORM ... ELSE ...`       | ❌ Не готово   | Не реализовано                        |
| parser_perform_not.c          | Логический оператор NOT       | `PERFORM NOT condition.`     | 🔲 Частично    | Частичная реализация                  |
| parser_perform_bracketed.c    | Условия в скобках             | `PERFORM (condition).`       | 🔲 Частично    | Нужно улучшить разбор скобок          |
| parser_perform_deep_nested.c  | Глубоко вложенный PERFORM     | Многоуровневый вызов         | ❌ Не готово   | Не реализовано                        |
| parser_perform_complex_body.c | Сложное тело PERFORM          | Много инструкций внутри      | 🔲 Частично    | Требуется доработка                   |
