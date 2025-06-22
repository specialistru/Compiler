| Имя файла                           | Конструкция               | Пример                       | Поддерживается | Комментарий                                           |
| ----------------------------------- | ------------------------- | ---------------------------- | -------------- | ----------------------------------------------------- |
| parser\_class\_attributes.c         | Атрибуты класса           | `CLASS attr ... ENDCLASS`    | ✅              | Полная реализация атрибутов класса                    |
| parser\_class\_def.c                | Определение класса        | `CLASS ... ENDCLASS`         | ✅              | Базовый парсер определения класса                     |
| parser\_class\_definition.c         | Полное определение класса | `CLASS ... ENDCLASS`         | ✅              | Полный разбор класса с методами и атрибутами          |
| parser\_class\_end.c                | Конец класса              | `ENDCLASS`                   | ✅              | Обработка окончания класса                            |
| parser\_class\_endclass.c           | Конец класса (ENDCLASS)   | `ENDCLASS`                   | ✅              | Аналогично parser\_class\_end.c                       |
| parser\_class\_endinterface.c       | Конец интерфейса          | `ENDINTERFACE`               | ✅              | Парсинг окончания интерфейса                          |
| parser\_class\_errors.c             | Ошибки парсинга класса    | Ошибки в синтаксисе          | ✅              | Обработка и вывод ошибок                              |
| parser\_class\_implementation.c     | Реализация класса         | `IMPLEMENTATION ...`         | 🔲 Частично    | Нужно доработать поддержку методов реализации         |
| parser\_class\_interface.c          | Интерфейс класса          | `INTERFACE ... ENDINTERFACE` | ✅              | Полная поддержка интерфейсов                          |
| parser\_class\_method.c             | Метод класса              | `METHOD ... ENDMETHOD`       | ✅              | Парсинг определения метода                            |
| parser\_class\_method\_def.c        | Определение метода        | `METHOD ... ENDMETHOD`       | ✅              | Дублирует parser\_class\_method.c, требует унификации |
| parser\_class\_method\_definition.c | Определение метода        | `METHOD ... ENDMETHOD`       | ✅              | Аналогично предыдущему                                |
| parser\_class\_method\_impl.c       | Реализация метода         | `METHOD ... ENDMETHOD`       | 🔲 Частично    | Требуется доработка тела метода                       |
| parser\_class\_simple.c             | Простые конструкции       | `CLASS ... ENDCLASS`         | ✅              | Поддержка простых деклараций                          |
| parser\_class\_visibility.c         | Видимость членов          | `PUBLIC`, `PRIVATE`          | ✅              | Полная поддержка модификаторов видимости              |
