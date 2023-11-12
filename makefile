all:
	gcc -Wall -c my_print.c
	gcc -Wall -c my_sort_aux.c
	gcc -Wall -c my_sort.c
	gcc -Wall -c my_memory.c
	gcc -Wall -c my_complexity_calc.c
	gcc -Wall -c main.c
	gcc -Wall -o ./mySort my_print.o my_sort_aux.o my_sort.o my_memory.o my_complexity_calc.o main.o -lm