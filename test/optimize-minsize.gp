set title "MIN SIZE vs. Average execution time (MIN SIZE < 1024)"
set xlabel "MIN SIZE"
set ylabel "average execution time (ms)"
set terminal png font " Times_New_Roman,12 "
set output "minsize-1024.png"
set key left

plot\
"data.txt" using 1:2 with linespoints linewidth 2 title ''