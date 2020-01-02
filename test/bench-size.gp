reset
set title "Benchmark with different dataset size"
set xlabel "number of record"
set ylabel "average execution time (ms)"
set output "test/bench-size.png"
set xtics 0, 5000, 30000
set xtics rotate by 45 right
set key left
set terminal png font " Times_New_Roman,12 "

plot\
"test/bench-size.txt" using 1:2 with linespoints linewidth 2 title "sort-singly", \
"test/bench-size.txt" using 1:3 with linespoints linewidth 2 title "sort-circular-doubly", \
"test/bench-size.txt" using 1:4 with linespoints linewidth 2 title "sort-optimize", \
"test/bench-size.txt" using 1:5 with linespoints linewidth 2 title "sort-linux", \
"test/bench-size.txt" using 1:6 with linespoints linewidth 2 title "sort-iterative", \
"test/bench-size.txt" using 1:7 with linespoints linewidth 2 title "sort-xor"