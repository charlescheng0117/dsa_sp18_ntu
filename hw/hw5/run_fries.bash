#!/bin/bash/

for i in `seq 5 20`;
do
    cat ./1-20005/my$i.in
    ./fries < ./1-20005/my$i.in
    echo $i DONE
done

echo DONE

