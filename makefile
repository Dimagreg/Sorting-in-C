all:
	gcc -Wall -c my_print.c
	gcc -Wall -c my_sort.c
	gcc -Wall -c my_memory.c
	gcc -Wall -c main.c
	gcc -Wall -o ./my_sort my_print.o my_sort.o my_memory.o main.o