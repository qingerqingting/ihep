#!/bin/bash
#check if all jobs ended successfully

I=1
#The number of jobs
C=50

sum=0
#am="ApplicationMgr       INFO Application Manager Stopped successfully"
bm="ApplicationMgr       INFO Application Manager Finalized successfully"
cm="ApplicationMgr       INFO Application Manager Terminated successfully"
for ((i=$I;i<$I+$C;++i))
do
    NUM=`echo $i`
    #Name of jobOptions!
    name=sim_$NUM.txt.bosslog
 #   a=`tail -8 $name |head -1`
    b=`tail -3 $name |head -1`
    c=`tail -2 $name |head -1`
 
    if [ "$b" != "$bm" ];then
        echo "$name is wrong!!!"
        #rm -f sim_$NUM.rtraw
        #rm -f sim_$NUM.txt.bosslog
        #rm -f sim_$NUM.txt.bosserr
        #boss.condor sim_$NUM.txt
        sum=$((sum+1))
    fi
 
done
echo "sum= $sum"

