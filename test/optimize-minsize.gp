set title "MIN SIZE vs. Average execution time (MIN SIZE < 2048)"
set xlabel "MIN SIZE"
set ylabel "average execution time (ms)"
set terminal png font " Times_New_Roman,12 "
set output "test/optimize-minsize.png"
set key left
set logscale x 2

plot\
"test/optimize-minsize.txt" using 1:2 with linespoints linewidth 2 title ''