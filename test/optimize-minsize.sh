#!/bin/bash

rm -f test/optimize-minsize.txt
touch test/optimize-minsize.txt
for i in {1..2048};
do
    gcc -D MIN_SIZE=$i -o sort-optimize sort-list.c sort-optimize.c
    sum=0
    for j in {1..10};
    do
        ./rand 1024 > test/random.txt
        res=$(./sort-optimize < test/random.txt)
        sum=`echo $sum + $res | bc`
    done
    avg=`echo $sum / 10 | bc -l`
    printf '%d %0.3f\n' "$i" "$avg" >> test/optimize-minsize.txt
done
gnuplot test/optimize-minsize.gp