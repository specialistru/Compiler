## ✅ **Общая структура каталогов**

```


```
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

```
Compiler/
│
├── include/                     # Заголовочные файлы (.h)
│   ├── parser_data.h
│   ├── parser_perform.h
│   ├── parser_call.h
│   ├── parser_class.h
│   ├── parser_method.h
│   ├── parser_loop.h
│   ├── parser_expression.h
│   └── parser_common.h           # Общие типы, структуры, утилиты
│
├── src/                          # Исходные файлы (.c)
│   ├── data/                     ## Конструкция DATA
│   │   ├── parser_data_value_assignment.c
│   │   ├── parser_data_initialization.c
│   │   ├── parser_data_complex_types.c
│   │   ├── parser_data_constants_value.c
│   │   ├── parser_data_parameters.c
│   │   ├── parser_data_field_symbols.c
│   │   ├── parser_data_select_options.c
│   │   ├── parser_data_ranges.c
│   │
│   ├── perform/
│   │   ├── parser_perform_nested.c
│   │   ├── parser_perform_logical_ops.c
│   │   ├── parser_perform_syntax_error.c
│   │   ├── parser_perform_complex.c
│   │   ├── parser_perform_and_or.c
│   │   ├── parser_perform_errors.c
│   │   ├── parser_perform_elseif.c
│   │   ├── parser_perform_else.c
│   │   ├── parser_perform_not.c
│   │   ├── parser_perform_bracketed.c
│   │   ├── parser_perform_deep_nested.c
│   │   ├── parser_perform_complex_body.c
│   │
│   ├── call/
│   │   ├── parser_call_complex.c
│   │   ├── parser_call_dynamic.c
│   │   ├── parser_call_exceptions.c
│   │   ├── parser_call_bracketed.c
│   │
│   ├── class/
│   │   ├── parser_class_attributes.c
│   │   ├── parser_class_def.c
│   │   ├── parser_class_definition.c
│   │   ├── parser_class_end.c
│   │   ├── parser_class_endclass.c
│   │   ├── parser_class_endinterface.c
│   │   ├── parser_class_errors.c
│   │   ├── parser_class_implementation.c
│   │   ├── parser_class_interface.c
│   │   ├── parser_class_method.c
│   │   ├── parser_class_method_def.c
│   │   ├── parser_class_method_definition.c
│   │   ├── parser_class_method_impl.c
│   │   ├── parser_class_simple.c
│   │   ├── parser_class_visibility.c
│   │
│   ├── method/
│   │   ├── parser_method_definition.c
│   │   ├── parser_method_error.c
│   │   ├── parser_method_implementation.c
│   │   ├── parser_method_visibility.c
│   │
│   ├── loop/
│   │   ├── parser_loop_loop.c
│   │   ├── parser_loop_other_construct.c
│   │   ├── parser_loop.c
│   │
│   ├── expression/
│   │   ├── parser_expression_function.c
│   │   ├── parser_expression_logical.c
│   │   ├── parser_expression_function_call.c
│   │   ├── parser_expression_literal.c
│   │   ├── parser_expression_identifier.c
│   │   ├── parser_expression_ternary.c
│   │   ├── parser_expression_operator.c
│   │   ├── parser_expression_variable.c
│   │   ├── parser_expression_bracket.c
│   │   ├── parser_expression_complex.c
│   │   ├── parser_expression_conditional.c
│   │   ├── parser_expression_assignment.c
│   │   ├── parser_expression_array_access.c
│   │   ├── parser_expression.c
│   │
│   ├── parser_perform.c
│   ├── parser_data.c
│   ├── parser_call.c
│   ├── parser_class.c
│   ├── parser_method.c
│   ├── parser_loop.c
│   ├── parser_expression.c
│
├── tests/                       # Тесты для различных модулей
│   ├── test_parser_data.c
│   ├── test_parser_perform.c
│   ├── test_parser_call.c
│   ├── test_parser_class.c
│   ├── test_parser_method.c
│   ├── test_parser_loop.c
│   ├── test_parser_expression.c
│   └── ...
│
├── docs/                        # Документация
│   ├── design.md
│   ├── api.md
│   └── usage.md
│
├── build/                       # Каталог сборки (output)
│
├── Makefile                    # Файл сборки (или CMakeLists.txt)
├── README.md

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
