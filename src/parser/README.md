## ✅ **Общая структура каталогов**

```
src/parser/
│
├── parser.h                         # Главный интерфейс парсера
├── parser.c                         # Основной управляющий код
│
├── parser_data.c / .h              ## Конструкция DATA
├── parser_if.c / .h                ## Конструкция IF / ELSE / ENDIF
├── parser_perform.c / .h           ## PERFORM
├── parser_call_function.c / .h     ## CALL FUNCTION
├── parser_class.c / .h             ## CLASS / ENDCLASS
├── parser_method.c / .h            ## METHOD / ENDMETHOD
├── parser_loop.c / .h              ## LOOP, ENDLOOP, LOOP AT, SELECT, etc.
├── parser_expression.c / .h        ## Выражения
├── parser_assignment.c / .h        # Присваивания
├── parser_form.c / .h              # FORM / ENDFORM
├── parser_module.c / .h            # MODULE / ENDMODULE
├── parser_try.c / .h               # TRY / CATCH / ENDTRY
├── parser_select.c / .h            # SELECT / SELECT SINGLE
├── parser_table_ops.c / .h         # READ/INSERT/MODIFY/DELETE TABLE
├── parser_declarations.c / .h      # PARAMETERS, TYPES, CONSTANTS, FIELD-SYMBOLS, etc.
├── parser_control.c / .h           # CASE, DO, WHILE, CHECK, CONTINUE, EXIT
├── parser_special.c / .h           # AUTHORITY-CHECK, SET PARAMETER, GET PARAMETER
```

## ✅ План поэтапной реализации

| Конструкция            | Файл                     | Статус | Комментарий                   |
| ---------------------- | ------------------------ | ------ | ----------------------------- |
| DATA                   | parser_data.c/h          | ✅    | Готово                        |
| IF / ELSE / ENDIF      | parser_if.c/h            | ✅    | Готово                        |
| PERFORM                | parser_perform.c/h       | ❌    | Требуется реализация          |
| CALL FUNCTION          | parser_call_function.c/h | ❌    | Требуется реализация          |
| CLASS / ENDCLASS       | parser_class.c/h         | 🔲    | Частично                      |
| METHOD / ENDMETHOD     | parser_method.c/h        | ❌    | Нужно выделить методы         |
| LOOP / SELECT          | parser_loop.c/h          | 🔲    | Только LOOP AT                |
| ASSIGNMENTS (=)        | parser_assignment.c/h    | ✅    | Готово                        |
| EXPRESSIONS            | parser_expression.c/h    | ✅    | Базовые выражения реализованы |
| FORM / ENDFORM         | parser_form.c/h          | ❌    | Требуется реализация          |
| MODULE / ENDMODULE     | parser_module.c/h        | 🔲    | Частично                      |
| TRY / CATCH / ENDTRY   | parser_try.c/h           | ❌    | Не реализовано                |
| READ / INSERT / TABLES | parser_table_ops.c/h     | ❌    | Не реализовано                |
| DECLARATIONS           | parser_declarations.c/h  | 🔲    | Только TYPES реализовано      |
| CONTROL STRUCTURES     | parser_control.c/h       | 🔲    | Только IF-ELSE                |
| SPECIAL                | parser_special.c/h       | ❌    | Не реализовано                |

### ✅ ЭТАПЫ РЕАЛИЗАЦИИ КОНСТРУКЦИЙ ABAP-ПАРСЕРА:

#### 1. **parser\_data.c/h**

* Обработка `DATA`, `CONSTANTS`, `TYPES`, `FIELD-SYMBOLS`
* Парсинг: `DATA var TYPE i.`
* Поддержка сложных типов (таблицы, структуры)

#### 2. **parser\_if.c/h**

* Конструкции: `IF`, `ELSEIF`, `ELSE`, `ENDIF`
* Вложенные условия и логика выражений

#### 3. **parser\_perform.c/h**

* Поддержка `PERFORM ... USING`, `CHANGING`
* Связь с `FORM`, `ENDFORM`

#### 4. **parser\_call.c/h**

* `CALL FUNCTION`, `CALL METHOD`, `RAISING`, `EXPORTING`, `IMPORTING`

#### 5. **parser\_class.c/h**

* Поддержка: `CLASS`, `METHOD`, `ENDCLASS`, `ENDMETHOD`
* Связь с объектной моделью и символической таблицей

#### 6. **parser\_select.c/h**

* `SELECT`, `SELECT SINGLE`, `LOOP AT`, `READ TABLE`
* Работа с выражениями `WHERE`, `INTO`, `FIELDS`

#### 7. **parser\_loop.c/h**

* `DO`, `WHILE`, `LOOP`, `ENDLOOP`
* `EXIT`, `CONTINUE`, `CHECK`

#### 8. **parser\_try.c/h**

* `TRY`, `CATCH`, `ENDTRY`, `CLEANUP`
* Проверка исключений

#### 9. **parser\_expr.c/h**

* Парсинг выражений (`a + b`, `x = y * z`)
* Унарные, бинарные, логические, сравнения

#### 10. **parser\_special.c/h**

* `EXPORT`, `IMPORT`, `SET PARAMETER`, `GET PARAMETER`
* `AUTHORITY-CHECK`, `MEMORY ID`
