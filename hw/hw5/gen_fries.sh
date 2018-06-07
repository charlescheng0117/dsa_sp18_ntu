#!/bin/bash/

for i in `seq 5 20`;
do 
    python3 gen_fries.py $i > 1-20005/my$i.in
done

echo DONE

