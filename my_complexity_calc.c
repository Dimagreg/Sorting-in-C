#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/* Calculate estimated time of sorting algorithm.
 * Takes a sorting function as parameter.
 * Returns time in seconds. On error returns -1. */

double
my_get_estimated_time_sort (int (*sort_function) (long*, long),
                            long *file_numbers_array, long lines_count)
{
    long *array;
    int i;

    if (lines_count > 40000){
        array = malloc (40000 * sizeof (long));

        if (array == NULL)
        {
            return -1;
        }

        for (i = 0; i < 40000; i++)
        {
            array[i] = file_numbers_array[i];
        }

        clock_t time_start = clock ();

        if (sort_function (array, 40000) == 0)
        {
            return -1;
        }

        clock_t time_end = clock ();

        double time_exec = (double) (time_end - time_start) / CLOCKS_PER_SEC;

        /* Estimated time for complexity n^2
         * TODO: different time complexity estimation based on function */

        double time_estimated, power;

        /* add 1 if power is bigger equal 2 so the pow will align correctly. */

        power = (double) lines_count / 40000;

        if (power < 2)
            time_estimated = pow (time_exec, power);
        else
            time_estimated = pow (time_exec, 1 + power);

        free (array);

        return time_estimated;
    }
    else
    {
        return 0; /* If lines_count < 40000, sorting time is negligible. */
    }
}
