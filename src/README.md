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

