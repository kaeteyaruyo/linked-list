#!/bin/bash

rm -f test/bench-size.txt
touch test/bench-size.txt
testlist="sort-singly sort-circular-doubly sort-optimize sort-linux sort-iterative sort-xor"
for i in {1000..30000..1000};
do
    printf '%d ' "$i" >> test/bench-size.txt
    for exe in $testlist
    do
        sum=0
        for j in {1..10};
        do
            ./rand $i > test/random.txt
            res=$(./${exe} < test/random.txt)
            sum=`echo $sum + $res | bc`
        done
        avg=`echo $sum / 10 | bc -l`
        printf '%0.3f ' "$avg" >> test/bench-size.txt
    done
    printf '\n' >> test/bench-size.txt
done
gnuplot test/bench-size.gp