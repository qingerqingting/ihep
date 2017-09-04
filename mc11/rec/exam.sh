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
    name=rec_$NUM.txt.bosslog
    #a=`tail -8 $name |head -1`
    b=`tail -3 $name |head -1`
    c=`tail -2 $name |head -1`
 
    if [ "$b" != "$bm" ];then
        echo "$name is wrong!!!"
        #rm -f /scratchfs/higgs/lvxd/g3pi2k2/data/rec_$NUM.root
        #rm -f rec_$NUM.txt.bosslog
        #rm -f rec_$NUM.txt.bosserr
        #boss -q rec_$NUM.txt
        sum=$((sum+1))
    fi
 
done
echo "sum= $sum"

