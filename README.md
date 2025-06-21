# Compiler

- lexer.c/h — лексер ABAP-like.   
- parser.c/h — простой парсер с AST.   
- ast.c/h — структура AST с освобождением.   
- semantic.c/h — семантический анализ (проверки).   
- ir.c/h, ir_generator.c/h — генерация IR и его хранение.   
- optimizer.c/h — заглушка для оптимизаций.   
- interpreter.c/h — интерпретатор IR.   
- parameters.c/h, perform.c/h, error_handling.c/h — инфраструктура.   
- tests/ — тестирование всех компонентов вместе.   
- examples/ — демонстрация параметров и perform.   
- Makefile — сборка всего проекта.   
