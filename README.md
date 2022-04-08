# Алгебра полиномов

__Цель данной работы__  — разработать программную систему, позволяющую выполнять алгебраические операции над полиномами от трёх переменных.

* Объектом работы является полином от трёх переменных, степени которых не превышают десять.
* У каждого полинома имеется уникальное имя.
* Полиномы хранятся в шести таблицах:
  - Неупорядоченные на массиве и на списке.
  - Упорядоченные на массиве и дереве поиска.
  - Два вида хеш-таблиц.
* Пользователь работает с одной таблицей, которую выбрал до этого. Изменение данной таблицы влечёт за собой изменение остальных.
* Работа с таблицей позволяет выполнить операции:
  - Добавления элемента.
  - Поиска элемента.
  - Удаления элемента.
* Программа должна предоставлять возможность выполнения алгебраических операций над полиномами:
  - Сумма полиномов.
  - Разность полиномов.
  - Произведение полиномов.
  - Нахождение первообразной.
  - Вычисление производной.
  - Вычисление значения в точке.

## Основные объекты
* Моном:
  * Хранит коэффициент и степень.
  * Предоставляет возможность вычисления значения в точке, нахождения первообразной и производной, поиска суммы, разности, произведения и частного двух мономов.
* Полином:
  * Хранит список мономов, входящих в полином.
  * Предоставляет возможность вычисления значения в точке, нахождения первообразной и производной, поиска суммы, разности, произведения и частного двух полиномов.
* Объект полинома:
  * Хранит полином, его строковое представление и название.
* Постфиксная форма:
  * Хранит инфиксное и постфиксное представления, набор лексем.
  * Позволяет реализовать алгоритм перевода в постфиксное представление и выполнить вычисление арифметического выражения по нему.
* Объект, содержащий основные операции:
  * Хранит строковое представление названия операции, её приоритет и арность.

* [Стек.][stack]
* [Связный список.][list]
* Дерево поиска.
* Неупорядоченная таблица на массиве.
  * Хранит массив указателей на объект полинома.
  * Предоставляет возможность добавления, удаления и поиска объектов полинома.
* Неупорядоченная таблица на списке.
  * Хранит список указателей на объект полинома.
  * Предоставляет возможность добавления, удаления и поиска объектов полинома.
* Упорядоченная таблица на массиве.
  * Хранит упорядоченный по ключам (названиям) массив указателей на объект полинома.
  * Предоставляет возможность добавления, удаления и поиска объектов полинома.
* Упорядоченная таблица на дереве поиска.
  * Предоставляет возможность добавления, удаления и поиска объектов полинома.
* Хеш-таблица с открытой адресацией.
  * Хранит массив структур Bucket, хранящий значение флага 'удалён' и указатель на объект полинома.
  * Предоставляет возможность добавления, удаления и поиска объектов полинома.
* Хеш-таблица с цепочками.
  * Предоставляет возможность добавления, удаления и поиска объектов полинома.

## Основные алгоритмы

### Добавление элемента:

#### 1. В неупорядоченную таблицу на списке:

1. По переданному ключу ищем полином:
   1. Если полином с данным именем найден, то алгоритм прекращает свою работу без добавления элемента.
   2. Если полином с данным именем не найден, то алгоритм продолжает свою работу.
2. Создаем звено и заполняем его данными.
3. Добавляем созданное звено в начало списка.

#### 2. В неупорядоченную таблицу на массиве:

1. По переданному ключу ищем полином:
   1. Если полином с данным именем найден, то алгоритм прекращает свою работу без добавления элемента.
   2. Если полином с данным именем не найден, то алгоритм продолжает свою работу.
2. В первую свободную ячейку записываем указатель на объект полинома.

#### 3. В упорядоченную таблицу на массиве:

   Производим бинарный поиск ключа по упорядоченноу массиву:
   1. Если ключ был найден, то завершаем работу алгоритма без добавления элемента. 
   2. Если ключ не был найден, то в зависимости от того, в какую сторону перед выходом из поиска смещались правая и левая границы производим вставку. Если последней смещалась левая границы, то смещаем все элементы на одну клетку вправо, начиная с индекса левой границы, а затем производим вставку элемента по этому индексу. Если последней смещалась правая граница, то производим аналогичные действия только для индекса правой границы.

#### 4. В хеш-таблицу с открытой адресацией:

Вычисляем хеш по ключу переданного элемента:
   1. Если ячейка по данному хешу уже инициализирована, то проверяем элемент с хеш равным текущий хеш + шаг % размер таблицы (значение шага вычисляем на моменте создания таблицы).
   2. Если ячейка по данному хешу не инициализирована или элемент в ней был удалён, то вставляем переданный элемент.

#### 5. В хеш-таблицу, реализованную методом цепочек:

Вычисляем хеш по ключу переданного элемента:
   1. Если ячейка по данному хешу уже инициализирована и запускаем операцию поиска, чтобы проверить ключ на уникальность. Если ключ оказался уникальным, то вставлям переданный элемент в начало списка и завершаем работу, если нет, то также завершаем работу алгоритма, но без добавления элемента.
   2. Если ячейка по данному хешу не инициализирована, то вставляем переданный элемент в данную ячейку.

### Удаление элемента:

#### 1. В неупорядоченой таблице на списке:

1. По переданному ключу ищем полином, который нужно удалить.
2. Удаляем полином из списка, используя обычный алгоритм удаления работы со списками.

#### 2. В неупорядоченной таблице на массиве:

1. По переданному ключу ищем полином, который нужно удалить.
2. Если полином найден, то на его место записывается последний.
3. Если полином не найден, то алгоритм прекращает свою работу.

#### 3. В упорядоченную таблицу на массиве:

   Производим бинарный поиск ключа по упорядоченноу массиву:
   1. Если ключ был найден, то производим перезаписывание элементов на одну ячейку влево с конца массива до индекса найденного элемента. 
   2. Если ключ не был найден, то завершаем работу алгоритма без удаления элемента.

#### 4. В хеш-таблице с открытой адресацией:

1. Вычисляем хеш по переданному ключу:
   1. Если значение ключа в ячейке равно переданному, то выставляем в ячейке флаг 'удалён'.
   2. Если значение не совпало, то продолжаем проверять элементы с хеш равным текущий хеш + шаг % размер таблицы (значение шага вычисляем на моменте создания таблицы), пока не встретим удалённый, или не инициализированный элемент, или не повторим операцию кол-во раз равное размеру таблицы (пройдём все элементы).
2. Если элемент с данным ключом найден, то выставляем эдементу флаг 'удалён'
3. Если элемент с данным ключом не найден, то выход из функции.

#### 5. В хеш-таблице, реализованной методом цепочек:

   Вычисляем хеш по переданному ключу:
      1. Если ячейка по данному хешу не инициализирована, значит, данного ключа нет в таблице, завершаем работу алгоритма.
      2. Если ячейка оказалась инициализированной, то производим поиск ключа по таблице. Если нашли переданный ключ, то удаляем элемент из списка и завершаем работу алгоритма. Если переданный ключ не был найден, то завершаем работу алгоритма без удаления.

### Поиск элемента:

#### 1. В неупорядоченной таблице на списке:

1. Запоминаем указатель на первое звено списка.
2. Пока не дошли до конца списка, сравниваем имя объекта полинома и переданный ключ:
   1. Если они равны, мы нашли нужный полином. Алгоритм прекращает свою работу.
   2. Если они не равны, переставляем указатель на следующее звено списка. Повторяем пункт 2.
3. Если дошли до конца списка и не нашли полином, то возвращаем признак отсутствия элемента. Алгоритм прекращает свою работу.

#### 2. В неупорядоченной таблице на массиве:

1. Пока не дошли до конца массива, сравниваем имя объекта полинома и переданный ключ:
   1. Если они равны, мы нашли нужный полином. Алгоритм прекращает свою работу.
   2. Если они не равны, то продолжаем идти по массиву.
2. Если дошли до конца массива и не нашли полином, то возвращаем признак отсутствия элемента. Алгоритм прекращает свою работу.

#### 3. В упорядоченную таблицу на массиве:

   Производим бинарный поиск по ключу. В случае, если ключ был найден, то возвращаем указатель на найденный элемент, если же не был найден, то возвращаем нулевой указатель.

#### 4. В хеш-таблице с открытой адресацией:

1. Вычисляем хеш по переданному ключу:
   1. Если значение ключа в ячейке равно переданному, то возвращаем указатель на текущий элемент.
   2. Если значение не совпало, то продолжаем проверять элементы с хеш равным текущий хеш + шаг % размер таблицы (значение шага вычисляем на моменте создания таблицы), пока не встретим удалённый, или не инициализированный элемент, или не повторим операцию кол-во раз равное размеру таблицы (пройдём все элементы).
2. Если элемент не был найден, возвращаем нулевой указатель.

#### 5. В хеш-таблице, реализованной методом цепочек:

   Вычисляем хеш по переданному ключу:
   1. Если ячейка по переданному ключу не инициализирована, значит, элемента с данным ключом нет. Завершаем работу алгоритма, возвращая нулевой указатель.
   2. Если ячейка оказалась инициализированной, то производим поиск переданного ключа по списку. Если ключ был найден, то возвращаем указатель на найденный элемент и завершаем работу. Если ключ не был найден, то это говорит о том, что элемент отсутстсвует. Возвращаем нулевой указатель и завершаем работу.

### Алгоритмы работы с Полиномами:

#### 1. Приведение подобных членов 

Сначала выбираем первый элемент списка и сравниваем его степень с остальными  элементами до тех пор, пока не встретим элемент с такой же степенью или  не дойдем до конца. В случае если не встретилось ни одного элемента с  такой же степенью, переходим к следующему элементу списка. Если же такой элемент был найден, то алгебраически складываем  эти мономы и записываем получившийся моном на место первого. Второй  моном удаляем. Повторяем данный алгоритм до тех пор, пока не окажемся на последнем элементе списка. 

#### 2. Сложение полиномов

Для сложения полиномов создаем копию первого полинома, затем в эту копию  добавляем второй полином и приводим подобные слагаемые. 

#### 3. Вычитание полиномов

Для вычитания полиномов создаем копию первого полинома, затем инвертируем  все знаки мономов второго полинома, добавляем в копию первого полинома и приводим подобные. 

#### 4. Умножение полиномов 

Создаем  результирующий полином. Первый моном первого полинома умножаем  поочередно на каждый моном из второго. После каждого умножения результат добавляем в результирующий полином. Повторяем до тех пор, пока в первом полиноме не закончатся мономы. Затем приводим подобные внутри  результирующего полинома. 

### Алгоритмы работы с Постфиксной формой:

#### 1. Проверка правильности расстановки скобок

1) На вход поступает строка, которая содержит арифметическое выражение.
2) Все символы строки просматриваются слева направо. Символы, не являющиеся скобками, игнорируются.
3) Если текущий символ – открывающаяся скобка, то в стек помещается временное значение true.
4) Если текущий символ – закрывающаяся скобка, то из стека выталкивается временное значение true.
   1) Если стек оказывается пустым, то не нашлось пары для закрывающейся скобки – это ошибка в расстановке скобок. Алгоритм прекращает свою работу.
5) Если все символы строки были просмотрены и стек временных значений не пуст, то не нашлось хотя бы одной пары для открывающейся скобки – это ошибка в расстановке скобок. Алгоритм прекращает свою работу.
6) Если все символы строки были просмотрены и стек временных значений пуст, то нет ошибок в расстановке скобок. Алгоритм прекращает свою работу.

#### 2. Преобразование в постфиксную форму:

1. На вход поступает набор, состоящий из всех элементов арифметического выражения отдельно. 
   Он просматривается слева направо:
   1. Если текущий элемент – лексема, то помещаем её в постфиксное представление.
   2. Если текущий элемент – открывающаяся скобка, то помещаем её в стек.
   3. Если текущий элемент – закрывающаяся скобка, то помещаем все операции до открывающейся скобки с удалением из стека в постфиксную форму (скобку также удаляем).
   4. Если последняя операция в стеке имеет больший приоритет, чем у текущей операции, то помещаем в постфиксное представление (с удалением из стека) все операции, пока выполняется это условие.
   5. Если стек пустой, то заполняем его текущей операцией, иначе, если стек содержит что-либо и если приоритет текущей операции больше, чем приоритет последней операции в стеке, то добавляем в конец стека текущую операцию.
2. Оставшиеся в стеке операции помещаются в постфиксную форму. Алгоритм прекращает свою работу.

#### 3. Вычисление выражения по постфиксной форме:

На вход поступает набор строк, который содержит каждый элемент постфиксной записи арифметического выражения отдельно.

1. Если текущий элемент – лексема, то помещаем её в вершину стека.
2. Если текущий элемент – операция, то извлекаем из стека столько чисел, сколько арность у текущей операции, и используем их в качестве операндов для данной операции.
3. После прохода по всему постфиксному представлению, в стеке остаётся одно число, которое является результатом вычисления. Алгоритм прекращает свою работу.

## Используемые инструменты

  - Система контроля версий [Git][git].
  - Фреймворк для написания автоматических тестов [Google Test][gtest].
  - Среда разработки Microsoft Visual Studio 2019.

<!-- LINKS -->

[git]: https://git-scm.com/book/ru/v2
[ gtest ]: https://github.com/google/googletest
[list]: https://www.bestprog.net/ru/2022/02/11/c-linear-singly-linked-list-general-information-ru/
[stack]: https://www.bestprog.net/ru/2019/09/18/c-the-concept-of-stack-operations-on-the-stack-an-example-implementation-of-the-stack-as-a-dynamic-array-ru/
[binsearch]:https://ru.wikipedia.org/wiki/Двоичный_поиск

