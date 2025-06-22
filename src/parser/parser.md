| Имя файла                               | Module         | Конструкция                   | Пример                                          | Статус | Комментарий                              |
| --------------------------------------- | -------------- | ----------------------------- | ----------------------------------------------- | ------ | ---------------------------------------- |
| parser\_if\_simple.c                    | if             | Простое IF                    | `IF a = 1. ENDIF.`                              | ✅      | Базовый разбор конструкции работает      |
| parser\_if\_nested.c                    | if             | Вложенный IF                  | `IF … IF … ENDIF ENDIF.`                        | 🔲     | Поддержка частично, нужна глубина        |
| parser\_if\_elseif.c                    | if             | ELSEIF                        | `IF … ELSEIF … ENDIF.`                          | ✅      | Корректная обработка                     |
| parser\_if\_else.c                      | if             | ELSE                          | `IF … ELSE … ENDIF.`                            | ✅      | Ветка ELSE корректна                     |
| parser\_if\_endif.c                     | if             | ENDIF                         | Завершение блока IF                             | ✅      | Правильно закрывает                      |
| parser\_if\_logical\_ops.c              | if             | AND/OR                        | `IF a = 1 AND b = 2.`                           | ✅      | Логические операции поддерживаются       |
| parser\_if\_not.c                       | if             | NOT                           | `IF NOT a = 1.`                                 | ✅      | Унарный NOT реализован                   |
| parser\_if\_bracketed.c                 | if             | Скобки                        | `IF (a = 1).`                                   | ✅      | Парсит группировку                       |
| parser\_if\_errors.c                    | if             | Ошибки IF                     | `IF a .`                                        | ✅      | Обнаруживает ошибки                      |
| parser\_if\_multilevel\_elseif\_else.c  | if             | Много ELSEIF/ELSE             | Несколько веток                                 | 🔲     | Ограниченная поддержка                   |
| parser\_perform\_simple.c               | perform        | Простое PERFORM               | `PERFORM subroutine.`                           | ✅      | Работает                                 |
| parser\_perform\_nested.c               | perform        | Вложенные PERFORM             | `PERFORM a. PERFORM b.`                         | 🔲     | Частичная поддержка                      |
| parser\_perform\_logical\_ops.c         | perform        | AND/OR условия внутри PERFORM | `PERFORM sub IF a AND b.`                       | 🔲     | Надо доработать                          |
| parser\_perform\_else.c                 | perform        | ELSE                          | `PERFORM sub ELSE.`                             | ❌      | Не реализовано                           |
| parser\_call\_function\_simple.c        | call\_function | Базовый CALL FUNCTION         | `CALL FUNCTION 'BAPI_USER_GET'.`                | ✅      | Работает                                 |
| parser\_call\_function\_dynamic.c       | call\_function | Динамический вызов            | `CALL FUNCTION lv_name.`                        | 🔲     | Частичная поддержка                      |
| parser\_call\_function\_exceptions.c    | call\_function | EXCEPTIONS / CATCH            | `CALL FUNCTION … EXCEPTIONS.`                   | 🔲     | Только базовая обработка                 |
| parser\_call\_function\_bracketed.c     | call\_function | Скобки параметров             | `CALL FUNCTION … EXPORTING ...).`               | 🔲     | Нужно учесть скобки                      |
| parser\_class\_def.c                    | class          | Описание класса               | `CLASS zcl_my DEFINITION.`                      | 🔲     | Добавить парсинг интерфейсов             |
| parser\_class\_method\_def.c            | class          | METHOD DEFINITION             | \`METHODS do\_it.”                              | 🔲     | Параметры метода не обрабатываются       |
| parser\_class\_interface.c              | class          | INTERFACE                     | \`INTERFACE lif\_m.”                            | 🔲     | Недостаёт закрытия/interface             |
| parser\_class\_visibility.c             | class          | PUBLIC/PROTECTED              | `PUBLIC SECTION.`                               | 🔲     | Не вся видимость обрабатывается          |
| parser\_class\_errors.c                 | class          | Ошибки при парсинге классов   | `CLASS zcl DEFINITION ENDCLASS.`                | 🔲     | Логика ошибок не завершена               |
| parser\_method\_definition.c            | method         | METHOD … ENDMETHOD            | `METHOD do_it. ENDMETHOD.`                      | ✅      | Базовая поддержка метода                 |
| parser\_method\_implementation.c        | method         | Реализация метода             | `METHOD do_it. … ENDMETHOD.`                    | 🔲     | Не все тела методов поддерживаются       |
| parser\_method\_visibility.c            | method         | PRIVATE/PUBLIC секции         | `PRIVATE SECTION.`                              | 🔲     | Частичная поддержка                      |
| parser\_method\_error.c                 | method         | Ошибки метода                 | `METHOD …` без END                              | 🔲     | Ошибки не детализированы                 |
| parser\_loop\_loop.c                    | loop           | LOOP AT itab … ENDLOOP        | `LOOP AT itab.`                                 | ✅      | Работает                                 |
| parser\_loop\_do.c                      | loop           | DO … ENDDO                    | `DO 10 TIMES.`                                  | 🔲     | Частично, нужна поддержка BREAK/CONTINUE |
| parser\_loop\_while.c                   | loop           | WHILE … ENDWHILE              | \`WHILE a < 10.”                                | 🔲     | Логические проверки частично             |
| parser\_loop\_other\_construct.c        | loop           | EXIT/CONTINUE внутри LOOP     | `CONTINUE.`                                     | 🔲     | Нужно интеграция                         |
| parser\_expression\_literal.c           | expression     | Литералы                      | `lv = 'text'.`                                  | ✅      | Работает                                 |
| parser\_expression\_identifier.c        | expression     | Идентификаторы                | `lv = lv2.`                                     | ✅      | Работает                                 |
| parser\_expression\_operator.c          | expression     | +, -, \*, /                   | `a + b * c.`                                    | ✅      | Работает                                 |
| parser\_expression\_variable.c          | expression     | Переменные                    | \`obj-field = 1.”                               | ✅      | Работает                                 |
| parser\_expression\_bracket.c           | expression     | Скобки                        | \`(a + b) \* c.”                                | ✅      | Работает                                 |
| parser\_expression\_function\_call.c    | expression     | Вызов функции                 | `func(a, b).`                                   | ✅      | Работает                                 |
| parser\_expression\_ternary.c           | expression     | Тернарный оператор            | \`flag = a ? b : c.”                            | ✅      | Работает                                 |
| parser\_expression\_conditional.c       | expression     | Логическая условность         | `a = COND #( WHEN flag = abap_true THEN 'X' ).` | ✅      | Работает                                 |
| parser\_expression\_assignment.c        | expression     | Присваивание в выражении      | \`a = b = c.”                                   | ✅      | Работает                                 |
| parser\_expression\_array\_access.c     | expression     | Доступ к элементам массива    | \`itab\[ i ] = val.”                            | ✅      | Работает                                 |
| parser\_assignment\_simple.c            | assignment     | Простое присвоение            | \`a = 1.”                                       | ✅      | Работает                                 |
| parser\_assignment\_chain.c             | assignment     | Цепочка присвоений            | \`a = b = 2.”                                   | 🔲     | Нужен рекурсивный разбор                 |
| parser\_assignment\_complex.c           | assignment     | Сложное присвоение            | \`obj-field = func( ).”                         | 🔲     | Нужно обработать поля и функции          |
| parser\_form\_simple.c                  | form           | FORM … ENDFORM                | `FORM sub. ENDFORM.`                            | 🔲     | Без параметров и RETURN                  |
| parser\_form\_complex.c                 | form           | FORM с USING/CHANGING         | \`FORM sub USING par1 par2.”                    | 🔲     | Нужно обработать сигнатуру               |
| parser\_form\_syntax\_error.c           | form           | Ошибки в FORM                 | `FORM sub USING .`                              | 🔲     | Ограниченный разбор ошибок               |
| parser\_module\_simple.c                | module         | MODULE / ENDMODULE            | `MODULE sub OUTPUT.`                            | 🔲     | Без PROCESS/CHAIN                        |
| parser\_module\_complex.c               | module         | MODULE с CHAIN/FIELD          | `MODULE sub INPUT PROCESS BEFORE OUTPUT.`       | 🔲     | Не всё покрыто                           |
| parser\_module\_chain\_and\_field.c     | module         | MODULE … CHAIN                | \`MODULE sub CHAIN field OF screen.”            | 🔲     | Частичная поддержка                      |
| parser\_try\_simple.c                   | try            | TRY / ENDTRY                  | `TRY. ENDTRY.`                                  | 🔲     | Нет CATCH                                |
| parser\_try\_catch.c                    | try            | CATCH                         | \`TRY. CATCH cx. ENDTRY.”                       | 🔲     | Без BODY CATCH                           |
| parser\_try\_cleanup.c                  | try            | CLEANUP                       | \`TRY. CLEANUP.”                                | 🔲     | Отсутствует                              |
| parser\_try\_nested.c                   | try            | Вложенные TRY                 | \`TRY. TRY. ... ENDTRY ENDTRY.”                 | 🔲     | Частичная реализация                     |
| parser\_try\_errors.c                   | try            | Ошибки в TRY                  | \`TRY CATCH.”                                   | 🔲     | Частичная                                |
| parser\_select\_simple.c                | select         | SELECT / ENDSELECT            | \`SELECT \* FROM mara INTO TABLE itab.”         | ✅      | Работает                                 |
| parser\_select\_into\_table.c           | select         | SELECT … INTO TABLE           | \`SELECT single\_field INTO wa.”                | ✅      | Поддерживается                           |
| parser\_select\_join.c                  | select         | INNER JOIN в SELECT           | `SELECT ... FROM a INNER JOIN b ON ...`         | 🔲     | Частичная поддержка                      |
| parser\_select\_where.c                 | select         | WHERE в SELECT                | `SELECT ... WHERE a = 'X'.`                     | ✅      | Работает                                 |
| parser\_select\_endselect.c             | select         | ENDSELECT                     | `ENDSELECT.`                                    | ✅      | Работает                                 |
| parser\_table\_ops\_append.c            | table\_ops     | APPEND                        | \`APPEND wa TO itab.”                           | 🔲     | Только базовая логика                    |
| parser\_table\_ops\_insert.c            | table\_ops     | INSERT                        | \`INSERT wa INTO TABLE itab.”                   | 🔲     | Не реализовано                           |
| parser\_table\_ops\_delete.c            | table\_ops     | DELETE                        | \`DELETE itab INDEX 1.”                         | 🔲     | Не реализовано                           |
| parser\_table\_ops\_modify.c            | table\_ops     | MODIFY                        | \`MODIFY itab FROM wa INDEX 1.”                 | 🔲     | Не реализовано                           |
| parser\_table\_ops\_read.c              | table\_ops     | READ TABLE                    | \`READ TABLE itab INDEX 1 INTO wa.”             | 🔲     | Не реализовано                           |
| parser\_table\_ops\_sort.c              | table\_ops     | SORT TABLE                    | `SORT itab BY field.`                           | 🔲     | Не реализовано                           |
| parser\_declarations\_data.c            | declarations   | DATA                          | `DATA lv TYPE i.`                               | ✅      | Работает                                 |
| parser\_declarations\_constants.c       | declarations   | CONSTANTS                     | `CONSTANTS c VALUE 'X'.`                        | 🔲     | VALUE не всегда производится             |
| parser\_declarations\_parameters.c      | declarations   | PARAMETERS                    | `PARAMETERS p TYPE i.`                          | ✅      | Работает                                 |
| parser\_declarations\_types.c           | declarations   | TYPES                         | \`TYPES: BEGIN OF ty, field TYPE i.”            | 🔲     | Структуры/таблицы не покрыты             |
| parser\_declarations\_field\_symbols.c  | declarations   | FIELD-SYMBOLS                 | `FIELD-SYMBOLS <fs>.`                           | ✅      | Работает                                 |
| parser\_declarations\_select\_options.c | declarations   | SELECT-OPTIONS                | \`SELECT-OPTIONS so FOR table.”                 | ✅      | Работает                                 |
| parser\_declarations\_ranges.c          | declarations   | RANGES                        | \`RANGES r FOR field.”                          | ✅      | Работает                                 |
| parser\_control\_exit.c                 | control        | EXIT                          | `EXIT.`                                         | ✅      | Работает                                 |
| parser\_control\_continue.c             | control        | CONTINUE                      | `CONTINUE.`                                     | ✅      | Работает                                 |
| parser\_control\_check.c                | control        | CHECK                         | `CHECK a = 1.`                                  | ✅      | Работает                                 |
| parser\_control\_return.c               | control        | RETURN                        | `RETURN.`                                       | ✅      | Работает                                 |
| parser\_control\_auth\_check.c          | control        | AUTHORITY-CHECK               | `AUTHORITY-CHECK OBJECT obj.`                   | 🔲     | Частично реализовано                     |
| parser\_special\_export\_import.c       | special        | EXPORT / IMPORT MEMORY        | \`EXPORT val TO MEMORY ID id.”                  | ✅      | Работает                                 |
| parser\_special\_memory\_id.c           | special        | MEMORY-ID                     | \`EXPORT ... TO MEMORY ID id.”                  | ✅      | Работает                                 |
| parser\_special\_set\_get\_parameter.c  | special        | SET/GET PARAMETER             | `SET PARAMETER ID 'A' FIELD lv.`                | ✅      | Работает                                 |
| parser\_special\_free\_create\_object.c | special        | CREATE OBJECT / FREE          | `CREATE OBJECT obj. FREE obj.`                  | ✅      | Работает                                 |
| parser\_special\_authority\_check.c     | special        | AUTHORITY-CHECK               | `AUTHORITY-CHECK OBJECT obj.`                   | ✅      | Работает                                 |
| parser\_special\_message.c              | special        | MESSAGE                       | `MESSAGE 'Msg' TYPE 'S'.`                       | ✅      | Работает                                 |

