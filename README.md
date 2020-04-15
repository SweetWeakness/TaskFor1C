Пасьянс.
Есть две колоды карт. В каждой 36 карт, т.е. 4 масти, от шестёрок до тузов. Колоды соединяются и перемешиваются. Затем, карты раскладываются в 8 кучек по 9 карт. Карты раскладываются рубашкой вниз.
Мы будем использовать только верхние карты в каждой из кучек. Разрешено перекладывать карту меньшего номинала на карту большего номинала. Масти при этом не учитываются. Например, можно переложить 7-пики на 8-бубны.
Если в одной из кучек оказалось 9 карт в правильном порядке, то этот набор убирается. Правильный порядок это от туза до шестерки. Если из одной кучки убрали все карты, то на её место можно положить любую карту.
Напишите программу, которая посчитает можно ли убрать все карты, т.е. разрешить пасьянс. На вход данная программа получает информацию о всех 8 кучках. Формат входа/выхода на ваше усмотрение.

Решение: будем исполбзовать жадные алгоритм.

Всего будет 8 итераций, каждая пытается собрать полный набор из 9 карт.
Итерация:
1) Ищем туз со следующими свойствами:
    - суффикс от туза до вверха колоды есть префикс готового набора (если это не будет выполняться, то собрать набор с данным тузом просто невозможно, так как в задаче можно перемещать только одну карту в отличие от реального пасьянса).
    - среди всех тузов, обладающих свойством выше, данный туз находится выше остальных (в куче) (опять таки, нам нужен доступ к как можно большим картам после удаления данного набора, в этом и заключается жадность алгоритма).
2) Если найденный туз лежит сверху и есть пустая куча, то перекладываем этот туз в нее, чтобы освободить еще 1 карту.
3) Дособираем набор вместе с этим тузом; для этого ищем в соседних кучах необходимые карты (занимает несколько итераций).


Я не успел реализовать еще одну функцию - если в процессе сборки набора мы не можем найти следующий элемент в кучах и есть пустые кучи, то надо поосвобождать кучи от верхних элементов и поискать там (с использованием свобоных куч)

Я в 23-47 узнал, что можно класть 7 на 9. Мой код не использует это. Надо было в 3 пункте итерации это использовать.
