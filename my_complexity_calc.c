#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include "lib/my_sort.h"
#include "lib/my_print.h"

/* Calculate estimated time of sorting algorithm.
 * Takes a sorting function as parameter.
 * Returns time in seconds. On error returns -1. */
double
my_get_estimated_time_sort (char *sorting_function_name,
                            long *file_numbers_array, long lines_count)
{
    long *array;
    int i;

    int lines = 30000;

    if (lines_count > lines){
        array = malloc (lines * sizeof (long));

        if (array == NULL)
        {
            return -1;
        }

        for (i = 0; i < lines; i++)
        {
            array[i] = file_numbers_array[i];
        }

        double time_estimated, time_exec;

        clock_t time_start = clock ();
        
        if (strcmp (sorting_function_name, "bubbleSort")) // O(n^2)
        {

            if (bubbleSort (array, lines) == 0)
            {
                my_print_error ("Error on bubbleSort.", "");

                return 0;
            }
        }
        else if (strcmp (sorting_function_name, "insertionSort") == 0) // O(n^2)
        {
            if (insertionSort (array, lines) == 0)
            {
                my_print_error ("Error on insertionSort.", "");

                return 0;
            }
        }
        else if (strcmp (sorting_function_name, "selectionSort") == 0) //O(n^2)
        {
            if (selectionSort (array, lines) == 0)
            {
                my_print_error ("Error on selectionSort.", "");

                return 0;
            }
        }
        else if (strcmp (sorting_function_name, "mergeSort") == 0) //O(nlogn)
        {
            if (mergeSort (array, 0, lines - 1) == 0)
            {
                my_print_error ("Error on mergeSort.", "");

                return 0;
            }
        }
        else if (strcmp (sorting_function_name, "quickSort") == 0) //O(nlogn)
        {
            if (quickSort (array, 0, lines - 1) == 0)
            {
                my_print_error ("Error on quickSort.", "");

                return 0;
            }
        }
        else if (strcmp (sorting_function_name, "heapSort") == 0) //O(nlogn)
        {
            if (heapSort (array, lines) == 0)
            {
                my_print_error ("Error on heapSort.", "");

                return 0;
            }
        }
        else if (strcmp (sorting_function_name, "countSort") == 0) //O(nlogn)
        {
            if (countSort (array, lines) == 0)
            {
                my_print_error ("Error on countSort.", "");

                return 0;
            }
        }
        else if (strcmp (sorting_function_name, "radixSort") == 0)
        {
            if (radixSort (array, lines) == 0)
            {
                my_print_error ("Error on radixSort.", "");

                return 0;
            }
        }
        else if (strcmp (sorting_function_name, "bucketSort") == 0)
        {
            if (bucketSort (array, lines) == 0)
            {
                my_print_error ("Error on bucketSort.", "");

                return 0;
            }
        }
        else if (strcmp (sorting_function_name, "bingoSort") == 0)
        {
            if (bingoSort (array, lines) == 0)
            {
                my_print_error ("Error on bingoSort.", "");

                return 0;
            }
        }
        else if (strcmp (sorting_function_name, "shellSort") == 0)
        {
            if (shellSort (array, lines) == 0)
            {
                my_print_error ("Error on shellSort.", "");

                return 0;
            }
        }
        else if (strcmp (sorting_function_name, "timSort") == 0)
        {
            if (timSort (array, lines) == 0)
            {
                my_print_error ("Error on timSort.", "");

                return 0;
            }
        }
        else if (strcmp (sorting_function_name, "combSort") == 0)
        {
            if (combSort (array, lines) == 0)
            {
                my_print_error ("Error on combSort.", "");

                return 0;
            }
        }
        else if (strcmp (sorting_function_name, "pingeonholeSort") == 0)
        {
            if (pigeonholeSort (array, lines) == 0)
            {
                my_print_error ("Error on pingeonholeSort.", "");

                return 0;
            }
        }
        else if (strcmp (sorting_function_name, "cycleSort") == 0)
        {
            if (cycleSort (array, lines) == 0)
            {
                my_print_error ("Error on cycleSort.", "");

                return 0;
            }
        }
        else if (strcmp (sorting_function_name, "cocktailSort") == 0)
        {
            if (cocktailSort (array, lines) == 0)
            {
                my_print_error ("Error on cocktailSort.", "");

                return 0;
            }
        }
        else if (strcmp (sorting_function_name, "bitonicSort") == 0)
        {
            if (bitonicSort (array, 0, lines, 1) == 0)
            {
                my_print_error ("Error on bitonicSort.", "");

                return 0;
            }
        }
        else if (strcmp (sorting_function_name, "pancakeSort") == 0)
        {
            if (pancakeSort (array, lines) == 0)
            {
                my_print_error ("Error on pancakeSort.", "");

                return 0;
            }
        }
        else if (strcmp (sorting_function_name, "bogoSort") == 0)
        {
            if (bogoSort (array, lines) == 0)
            {
                my_print_error ("Error on bogoSort.", "");

                return 0;
            }
        }
        else if (strcmp (sorting_function_name, "gnomeSort") == 0)
        {
            if (gnomeSort (array, lines) == 0)
            {
                my_print_error ("Error on gnomeSort.", "");

                return 0;
            }
        }
        else
        {
            my_print_error ("Unknown command.\n", "");

            return 0;
        }
        
        clock_t time_end = clock ();

        time_exec = (double) (time_end - time_start) / CLOCKS_PER_SEC;

        time_estimated = (lines_count / lines) * time_exec;

        free (array);

        return time_estimated;
    }
    else
    {
        return 0; /* If lines_count < lines, sorting time is negligible. */
    }
}
