# CW2. Parallel Breadth-First-Search

## Problem

Нужно реализовать параллельный bfs. От Вас требуется написать последовательную версию алгоритма  (seq) и параллельную версию (par). Протестировать надо на кубическом графе со стороной 500 и источником в (0, 0, 0). (Усреднить по 5 запускам) Сравнить время работы par на 4 процессах и seq на одном процессе - у Вас должно быть раза в 3 быстрее.  (Если будет медленнее, то выставление баллов оставляется на моё усмотрение.) Учтите, что Ваш bfs должен работать на любом графе, если Вам дан его список смежности.

## Solution

Было реализовано два алгоритма bfs:

- Параллельный с помощью OpenCilk -- `src/par_bfs.cpp`;
- Последовательный -- `src/seq_bfs.cpp`.

Скрипты запусков находятся в `Makefile`.

Результаты запусков можно посмотреть в файлах `results/bench_par.txt` и `results/bench_seq.txt`. Использую кф 24 - коэффициент, на который умножается количество воркеров силка, чтобы определить гранулярность. При кф 8 скорость работы параллельного алгоритма не особо быстрее последовательно :(
Таблица для кф 24 (ms)

| algorithm | 1st run | 2nd run | 3rd run | 4th run | 5th run | mean | diff |
| --------- | ------- | ------- | ------- | ------- | ------- | ---- | ---- |
| sequential | 79057 | 79421 | 79756 | 79570 | 78163 | 79213.4 | x3.36 |
| parallel | 23925 | 23742 | 23389 | 23453 | 23449 | 23591.6 | x1.0 |

Среднее время параллельного алгоритма ~23591.6 ms, а последовательного -- ~79213.4 ms. Параллельный алгоритм быстрее последовательного в ~3.36 раза.
