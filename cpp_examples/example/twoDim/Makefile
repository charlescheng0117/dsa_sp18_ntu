
time: row col
	time -p ./row; time -p ./col

timeopt: rowopt colopt
	time -p ./rowopt; time -p ./colopt

row: row.c
	gcc -O0 row.c -o row

col: col.c
	gcc -O0 col.c -o col

rowopt: row.c
	gcc -O3 row.c -o rowopt

colopt: col.c
	gcc -O3 col.c -o colopt
