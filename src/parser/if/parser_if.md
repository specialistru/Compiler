## ✅ Поддерживаемые конструкции IF

| Имя файла                          | Конструкция                                                   | Пример                                           | Поддерживается |
| ---------------------------------- | ------------------------------------------------------------- | ------------------------------------------------ | -------------- |
| parser_if_simple_condition.c       | Простое условие IF                                            | `IF x = 1. WRITE x. ENDIF.`                      | ✅ Готово      |
| parser_if_nested.c                 | Вложенный IF                                                  | `IF x = 1. IF y = 2. WRITE y. ENDIF. ENDIF.`     | ✅ Готово      |
| parser_if_elseif.c                 | ELSEIF                                                        | `IF x = 1. ELSEIF y = 2. ENDIF.`                 | ✅ Готово      |
| parser_if_else.c                   | ELSE                                                          | `IF x = 1. ELSE. WRITE 'Else'. ENDIF.`           | ✅ Готово      |
| parser_if_endif.c                  | ENDIF                                                         | Завершение блока                                 | ✅ Готово      |
| parser_if_logical_ops.c            | Логические операции в условиях                                | `IF x = 1 AND y = 2 OR z = 3.`                   | ✅ Готово      |
| parser_if_not.c                    | Логический оператор NOT                                       | `IF NOT x = 1.`                                  | ✅ Готово      |
| parser_if_syntax_error.c           | Обработка синтаксических ошибок                               | `IF x == .` → ошибка                             | ✅ Готово      |
| parser_if_complex_conditions.c     | Сложные условия с использованием AND/OR, скобок               | `IF (x = 1 AND y = 2) OR z = 3.`                 | 🔲 Частично    |
| parser_if_multilevel_elseif_else.c | Многоуровневые ELSEIF/ELSE                                    | `IF x=1. ELSEIF y=2. ELSEIF z=3. ELSE. ENDIF.`   | 🔲 Частично    |
| parser_if_body.c                   | Тело IF/ELSE с произвольными инструкциями                     | `IF cond. WRITE: 'OK'. ENDIF.`                   | ✅ Готово      |
| parser_if_simple.c                 | Основной парсер IF (объединение простых случаев)              | `IF x = 1. ... ENDIF.`                           | ✅ Готово      |
| parser_if_end.c                    | Завершение блока IF                                           | Завершение конструкции IF                        | ✅ Готово      |
| parser_if_and_or.c                 | Логические операторы AND / OR                                 | `IF a = 1 AND b = 2 OR c = 3.`                   | ✅ Готово      |
| parser_if_bracketed.c              | Условия с вложенными скобками                                 | `IF (x = 1 OR (y = 2 AND z = 3)).`               | 🔲 Частично    |
| parser_if_errors.c                 | Обработка синтаксических ошибок IF                            | `IF x ==.` → ошибка                              | ✅ Готово      |
| parser_if_deep_elseif.c            | Глубокие многоуровневые ELSEIF                                | `IF x=1. ELSEIF y=2. ELSEIF z=3. ELSE. ENDIF.`   | 🔲 Частично    |
| parser_if_complex_body.c           | Тело IF с комплексными инструкциями (DATA, CALL, LOOP и т.п.) | `IF x = 1. DATA y TYPE i. CALL METHOD z. ENDIF.` | 🔲 Частично    |

