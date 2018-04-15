int getMinPos(int *arr, int len){
	int minPos=0;
	for (int i=1; i<len; i++){
		if (arr[i]<arr[misPos])
			minPos=i;
	}
	return minPos;
}


getMinPos(integer array arr, integer len)
minPos <- 0
for i <- 1 to len-1 do
	if arr[i] smaller than arr[minPos] then
		minPos <- i
return minPos

