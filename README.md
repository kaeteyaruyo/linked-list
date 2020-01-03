A little benchmark for sorting algorithm on different implementation of linked list like:

* Singly-linked list with insertion sort in recursive fashion
* Singly-linked list with insertion sort in iterative fashion
* Singly-linked list with locality-optimized merge sort
* Circular doubly-linked list with insertion sort in recursive fashion
* Linux `<list.h>` style linked list with insertion sort in recursive fashion
* Xor doubly-linked list with insertion sort in recursive fashion

For more detailed analysis, please read [this note](https://hackmd.io/@kaeteyaruyo/2019q3_homework4).

# Compile

`make all`

# Run benchmark

`make bench-size`
! Warning ! This may cost a few dozen of minutes.

# Other

* To find best configuration for locality optimization on merge sort, run `make test-optimize`

# TODO

* Reduce the impact of context swtich on performance when benchmarking
* 參照 [kdb](https://github.com/hoang-khoi/kdb) 的實作手法，允許對不同的資料結構 (或變種) 進行大範圍的資料測試，從而理解整體的效能分佈，例如裡頭 `Linked-list as a "lookup table"` (by [jserv](https://github.com/jserv))