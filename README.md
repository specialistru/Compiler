# Compiler

## Этап 1: Архитектура и базовые модули

### 1.1. Модуль лексера (lexer)

* Поддержка полного набора лексем ABAP (ключевые слова, идентификаторы, литералы, операторы)
* Поддержка многострочных комментариев, строк, спецсимволов
* Учёт юникода и локализации (UTF-8)

### 1.2. Модуль парсера (parser)

* Рекурсивный нисходящий парсер или парсер на основе грамматики (LL(1) или LALR)
* Поддержка всего синтаксиса ABAP:

  * Операторы: IF, CASE, LOOP, WHILE, DO, PERFORM, FUNCTION CALL
  * Определения: DATA, TYPES, CONSTANTS, CLASS, INTERFACE
  * Управление блоками (BEGIN, END)
* Полный AST с узлами для каждого типа конструкции

### 1.3. Семантический анализ (semantic)

* Система областей видимости (глобальная, локальная, блоки)
* Таблица символов с типами, проверка объявлений и использований
* Проверка типов (статическая типизация), совместимость типов
* Проверка объявлений процедур, функций, методов
* Поддержка пользовательских типов (структуры, таблицы, классы)

---

## Этап 2: Промежуточное представление (IR) и генерация кода

### 2.1. Разработка IR

* Создание представления в виде байткода или трёхадресного кода
* Поддержка выражений, вызовов функций, условий, циклов
* Стек вызовов, управление локальными переменными и параметрами

### 2.2. Генератор IR

* Преобразование AST в IR
* Поддержка сложных конструкций (циклы, условия, вызовы)
* Обработка рекурсии

---

## Этап 3: Оптимизации

### 3.1. Простые оптимизации

* Устранение мёртвого кода
* Константное свёртывание
* Инлайнинг функций

### 3.2. Продвинутые оптимизации

* Алгебраические преобразования
* Оптимизация циклов (распараллеливание, разворачивание)
* Управление регистрами / памятью

---

## Этап 4: Интерпретатор и/или JIT-компилятор

### 4.1. Интерпретатор IR

* Исполнение байткода с поддержкой стековой машины
* Поддержка рекурсии, параметров функций, локальных переменных

### 4.2. JIT-компиляция (по желанию)

* Генерация машинного кода из IR для ускорения исполнения

---

## Этап 5: Среда выполнения ABAP

* Работа с базами данных через OpenSQL API
* Поддержка внутренних таблиц, классов, событий, модулей
* Управление ошибками, исключениями, транзакциями
* Поддержка параллелизма (блокировки, синхронизация)

---

## Этап 6: Инструменты и поддержка разработчиков

* Отладчик с точками останова, пошаговым выполнением
* Профилировщик
* Система логирования и трассировки
* Поддержка интеграции с SAP GUI / SAP Fiori (если нужно)

---

# Разбиение по модулям проекта

| Модуль               | Задачи и структуры данных                                                   |
| -------------------- | --------------------------------------------------------------------------- |
| lexer.c/h            | Лексемы, позиция, буфер, функции для разбора исходника                      |
| parser.c/h           | AST узлы, грамматика, синтаксический анализатор                             |
| semantic.c/h         | Семантический анализ: Таблицы символов, области видимости, типы, проверка   |
| ast.c/h              | Узлы AST, функции построения и обхода                                       |
| ir.c/h               | Структуры IR инструкций, управление списком инструкций                      |
| ir_generator.c/h     | Трансляция AST в IR (генерация IR и его хранение)                           |
| optimizer.c/h        | Алгоритмы оптимизации IR                                                    |
| interpreter.c/h      | Стек вызовов, регистры, исполнение инструкций интерпретатор IR              |
| parameters.c/h       | инфраструктура.                                                             |
| perform.c/h          | инфраструктура.                                                             |
| jit\_compiler (опц.) | Генерация машинного кода из IR                                              |
| runtime              | Реализация стандартной библиотеки ABAP, базы, таблицы, объекты              |
| error_handling.c/h   | Обработка ошибок, исключений                                                |
| tools/debugger       | Отладка, профилирование                                                     |
| tests/               | тестирование всех компонентов вместе.                                       |
| examples/            | демонстрация параметров и perform.                                          |
| Makefile             | сборка всего проекта.                                                       |


Вот **общая структура каталогов проекта `Compiler/`** с учётом всех перечисленных файлов и логики из предыдущего этапа проектирования:

---

## 📁 `Compiler/` — Корневая директория проекта

```
Compiler/
├── build/                  # Сборка и артефакты
├── bin/                    # Скомпилированные бинарники
├── lib/                    # Внешние зависимости (при необходимости)
├── include/                # Общие заголовочные файлы
│   ├── common.h
│   ├── config.h
│   ├── error.h
│   ├── utf8.h
│   └── ...
├── docs/                   # Документация проекта
│   ├── architecture.md
│   ├── grammar.md
│   ├── ir_spec.md
│   └── build.md
├── examples/               # Примеры ABAP-программ
├── tests/                  # Юнит-тесты и интеграционные тесты
│   └── lexer_test.c
├── src/                    # Основной исходный код
│   ├── core/
│   │   ├── main.c
│   │   └── config.c
│   ├── lexer/
│   │   ├── lexer.c
│   │   ├── token.c
│   │   └── token_stream.c
│   ├── parser/
│   │   ├── ast.c
│   │   ├── parser.c
│   │   ├── grammar.abnf
│   │   ├── if/
│   │   │   ├── simple.c
│   │   │   ├── nested.c
│   │   │   ├── elseif.c
│   │   │   ├── else.c
│   │   │   ├── endif.c
│   │   │   ├── logical_ops.c
│   │   │   ├── not.c
│   │   │   ├── bracketed.c
│   │   │   ├── errors.c
│   │   │   ├── multilevel_elseif_else.c
│   │   │   ├── deep_elseif.c
│   │   │   ├── complex_conditions.c
│   │   │   ├── body.c
│   │   │   └── complex_body.c
│   │   ├── perform/
│   │   │   ├── simple.c
│   │   │   ├── nested.c
│   │   │   ├── logical_ops.c
│   │   │   ├── and_or.c
│   │   │   ├── not.c
│   │   │   ├── elseif.c
│   │   │   ├── else.c
│   │   │   ├── bracketed.c
│   │   │   ├── complex.c
│   │   │   └── errors.c
│   │   ├── call_function/
│   │   │   ├── simple.c
│   │   │   ├── dynamic.c
│   │   │   ├── exceptions.c
│   │   │   ├── bracketed.c
│   │   │   └── complex.c
│   │   ├── class/
│   │   │   ├── def.c
│   │   │   ├── attributes.c
│   │   │   ├── interface.c
│   │   │   ├── method_def.c
│   │   │   ├── method_impl.c
│   │   │   ├── simple.c
│   │   │   ├── visibility.c
│   │   │   ├── implementation.c
│   │   │   ├── endinterface.c
│   │   │   ├── endclass.c
│   │   │   └── errors.c
│   │   ├── method/
│   │   │   ├── definition.c
│   │   │   ├── implementation.c
│   │   │   ├── visibility.c
│   │   │   └── error.c
│   │   ├── loop/
│   │   │   ├── loop.c
│   │   │   ├── do.c
│   │   │   ├── while.c
│   │   │   └── other_construct.c
│   │   ├── expression/
│   │   │   ├── literal.c
│   │   │   ├── identifier.c
│   │   │   ├── operator.c
│   │   │   ├── variable.c
│   │   │   ├── bracket.c
│   │   │   ├── function_call.c
│   │   │   ├── ternary.c
│   │   │   ├── conditional.c
│   │   │   ├── assignment.c
│   │   │   ├── array_access.c
│   │   │   ├── logical.c
│   │   │   └── complex.c
│   │   ├── assignment/
│   │   │   ├── simple.c
│   │   │   ├── chain.c
│   │   │   └── complex.c
│   │   ├── form/
│   │   │   ├── simple.c
│   │   │   ├── complex.c
│   │   │   └── syntax_error.c
│   │   ├── module/
│   │   │   ├── simple.c
│   │   │   ├── complex.c
│   │   │   └── chain_and_field.c
│   │   ├── try/
│   │   │   ├── simple.c
│   │   │   ├── catch.c
│   │   │   ├── cleanup.c
│   │   │   ├── nested.c
│   │   │   └── errors.c
│   │   ├── select/
│   │   │   ├── simple.c
│   │   │   ├── into_table.c
│   │   │   ├── join.c
│   │   │   ├── where.c
│   │   │   └── endselect.c
│   │   ├── table_ops/
│   │   │   ├── append.c
│   │   │   ├── insert.c
│   │   │   ├── delete.c
│   │   │   ├── modify.c
│   │   │   ├── read.c
│   │   │   └── sort.c
│   │   ├── declarations/
│   │   │   ├── data.c
│   │   │   ├── constants.c
│   │   │   ├── parameters.c
│   │   │   ├── types.c
│   │   │   ├── field_symbols.c
│   │   │   ├── select_options.c
│   │   │   └── ranges.c
│   │   ├── control/
│   │   │   ├── exit.c
│   │   │   ├── continue.c
│   │   │   ├── check.c
│   │   │   ├── return.c
│   │   │   └── auth_check.c
│   │   ├── special/
│   │   │   ├── export_import.c
│   │   │   ├── memory_id.c
│   │   │   ├── set_get_parameter.c
│   │   │   ├── free_create_object.c
│   │   │   ├── authority_check.c
│   │   │   └── message.c
│   ├── semantic/
│   │   ├── semantic_analyzer.c
│   │   ├── symbol_table.c
│   │   └── type_checker.c
│   ├── ir/
│   │   ├── ir.c
│   │   └── ir_generator.c
│   ├── opt/
│   │   ├── optimizer.c
│   │   ├── dead_code_elim.c
│   │   ├── const_fold.c
│   │   ├── inlining.c
│   │   └── loop_opt.c
│   ├── vm/
│   │   ├── vm.c
│   │   ├── call_stack.c
│   │   └── jit.c          # по желанию
│   ├── runtime/
│   │   ├── sql_api.c
│   │   ├── internal_tables.c
│   │   ├── objects.c
│   │   ├── exceptions.c
│   │   └── threads.c
│   └── tools/
│       ├── debugger.c
│       ├── profiler.c
│       ├── logger.c
│       └── trace.c
```


Отлично — вот **полный и исчерпывающий список всех исходных файлов проекта ABAP-компилятора на языке C**, включая:

1. Все твои ранее перечисленные `.c`-файлы
2. Структуру модулей компилятора: `lexer`, `parser`, `semantic`, `ir`, `opt`, `vm`, `runtime`, `tools`
3. Недостающие, но необходимые файлы: AST, диагностика, CLI, стандартная библиотека, конфигурация, токены и т.д.
4. Заголовочные `.h`-файлы, которые обеспечивают модульность

---

### 📁 `Compiler/` — Корневая директория

---

#### 📁 `include/` — Заголовочные файлы

```
include/
├── common.h
├── config.h
├── error.h
├── utf8.h
├── token.h
├── ast.h
├── parser.h
├── lexer.h
├── ir.h
├── optimizer.h
├── vm.h
├── runtime.h
├── symbol_table.h
├── type_checker.h
├── diagnostics.h
├── logger.h
├── debug.h
├── abap_keywords.h
├── stdlib.h
├── cli.h
```

---

#### 📁 `src/core/` — Точка входа, конфигурация

```
core/
├── main.c              # CLI интерфейс: принимает путь к файлу ABAP
├── config.c            # Чтение конфигурационных флагов компилятора
├── cli.c               # Обработка параметров командной строки
```

---

#### 📁 `src/lexer/` — Лексический анализатор

```
lexer/
├── lexer.c             # Разбор входного текста в токены
├── token.c             # Структура и типизация токенов
├── token_stream.c      # Буферизация токенов, lookahead и откат
```

---

#### 📁 `src/parser/` — Парсер и модули синтаксического анализа

```
parser/
├── parser.c            # Центральный LL(1) или рекурсивный парсер
├── ast.c               # Создание узлов AST
├── ast_visitor.c       # Обход дерева AST (для отладки, IR, вывода)

├── if/
│   ├── simple.c  nested.c  elseif.c  else.c  endif.c
│   ├── logical_ops.c  not.c  bracketed.c  errors.c
│   ├── multilevel_elseif_else.c  deep_elseif.c
│   ├── complex_conditions.c  body.c  complex_body.c

├── perform/
│   ├── simple.c  nested.c  logical_ops.c  and_or.c
│   ├── not.c  elseif.c  else.c  bracketed.c  complex.c  errors.c

├── call_function/
│   ├── simple.c  dynamic.c  exceptions.c  bracketed.c  complex.c

├── class/
│   ├── def.c  attributes.c  interface.c  method_def.c
│   ├── method_impl.c  simple.c  visibility.c  implementation.c
│   ├── endinterface.c  endclass.c  errors.c

├── method/
│   ├── definition.c  implementation.c  visibility.c  error.c

├── loop/
│   ├── loop.c  do.c  while.c  other_construct.c

├── expression/
│   ├── literal.c  identifier.c  operator.c  variable.c
│   ├── bracket.c  function_call.c  ternary.c  conditional.c
│   ├── assignment.c  array_access.c  logical.c  complex.c

├── assignment/
│   ├── simple.c  chain.c  complex.c

├── form/
│   ├── simple.c  complex.c  syntax_error.c

├── module/
│   ├── simple.c  complex.c  chain_and_field.c

├── try/
│   ├── simple.c  catch.c  cleanup.c  nested.c  errors.c

├── select/
│   ├── simple.c  into_table.c  join.c  where.c  endselect.c

├── table_ops/
│   ├── append.c  insert.c  delete.c  modify.c  read.c  sort.c

├── declarations/
│   ├── data.c  constants.c  parameters.c  types.c
│   ├── field_symbols.c  select_options.c  ranges.c

├── control/
│   ├── exit.c  continue.c  check.c  return.c  auth_check.c

├── special/
│   ├── export_import.c  memory_id.c  set_get_parameter.c
│   ├── free_create_object.c  authority_check.c  message.c
```

---

#### 📁 `src/semantic/` — Семантический анализ

```
semantic/
├── semantic_analyzer.c     # Анализ всех узлов AST
├── symbol_table.c          # Иерархия областей видимости
├── type_checker.c          # Проверка типовой совместимости
```

---

#### 📁 `src/ir/` — Промежуточное представление

```
ir/
├── ir.c                    # Структура IR-команд
├── ir_generator.c          # Генерация IR из AST
```

---

#### 📁 `src/opt/` — Оптимизации IR

```
opt/
├── optimizer.c             # Центральная точка управления оптимизациями
├── dead_code_elim.c        # Удаление мёртвого кода
├── const_fold.c            # Константное свёртывание
├── inlining.c              # Инлайнинг функций
├── loop_opt.c              # Оптимизация циклов
```

---

#### 📁 `src/vm/` — Интерпретатор и стековая VM

```
vm/
├── vm.c                    # Исполнение IR
├── call_stack.c            # Управление вызовами и локальными переменными
├── jit.c                   # JIT-компиляция (по желанию)
```

---

#### 📁 `src/runtime/` — Среда выполнения ABAP

```
runtime/
├── sql_api.c               # Поддержка OpenSQL (SELECT, INSERT, ...)
├── internal_tables.c       # Реализация табличных операций
├── objects.c               # Работа с объектами и классами
├── exceptions.c            # Исключения, TRY-CATCH
├── threads.c               # Параллелизм, блокировки
```

---

#### 📁 `src/tools/` — Инструменты разработчика

```
tools/
├── debugger.c              # Пошаговое выполнение, breakpoints
├── profiler.c              # Сбор статистики по IR
├── logger.c                # Логирование событий
├── trace.c                 # Подробная трассировка IR
```

---

#### 📁 `tests/` — Тесты

```
tests/
├── lexer_test.c
├── parser_test.c
├── semantic_test.c
├── ir_test.c
├── vm_test.c
├── regression/
│   ├── test_if.abap
│   ├── test_perform.abap
│   ├── test_sql.abap
```

---

#### 📁 `examples/`

```
examples/
├── hello_world.abap
├── nested_if.abap
├── loop_select.abap
├── classes.abap
```

---

#### 📁 `docs/`

```
docs/
├── architecture.md
├── grammar.md
├── ir_spec.md
├── build.md
├── optimization.md
```

---

## 📦 Количество исходников:

* `.c` файлов: **более 160**
* `.h` файлов: \~**20-30**
* Всего: \~**200 файлов** — реалистичный размер для компилятора среднего уровня сложности.
