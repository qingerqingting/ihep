#!/bin/bash
sum=0
I=101
i=1
while [[ $i -le 49 ]]
do
i=`echo $I |cut -c 2-3`
var=`tail -4 ana_$i.txt.bosslog |head -1|awk '{print $3}'`
x=${var:4}
let I=$I+1
i=10#$i
let sum+=$x
echo $i $sum
#echo $x
done
echo $i $sum
#echo $sum
                 
