/*
 * TODO: separate sorting process in 3 different function - read, sort, write
 *       when reading sort check for number
 *       calculate estimate time of computing
 *       progress bar?
 *       parallel sorting:
 *       basically for 500 random values in a file separate it to 1..10 parallel processes
 *       where for example if chooses 5 it will create 5 different arrays of equal interval of
 *       values - each array is a struct that contains: array of elements, count, int_min, int_max,
 *       order. int_min and int_max will be subjected for each array. Ideally we will have 100
 *       elements per array. If not we will neglect if the number is between 60..120. If it is more
 *       then we will create 2 more arrays of equal intervals of int_min and int_max. If it is less,
 *       then compress 2 into one. If the number of elements is 0 - delete array. After that
 *       compress all the arrays into one respecting the order of intervals.
 */

/*
 *  Utility program for generating/sorting a file of unsorted unsigned integers
 *   --help
 *   -v
 *   -g, --generate <filename_original> <filename_shuffled> <line_count>
 *              filename_original and filename_shuffled - non_space string 1....128
 *              line_count - 2....2,147,483,647 (max long value)
 *
 *   -s, --sort <file_shuffled> <filename_result>
 *          file_shuffled and filename_result - non_space string 1....128
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include "lib/my_print.h"
#include "lib/my_sort.h"
#include "lib/my_memory.h"
#include "lib/my_complexity_calc.h"

/* Debugging option. 1 for TRUE, 0 for FALSE. */

enum
{
    DEBUG = 1,
    STATS = 1
};

/* Program version. */

char *VERSION = "20-Jul-23";

/* Array of unsorted input file numbers. */

long *file_numbers_array = NULL;

/* The total number of elements in array. */

long file_numbers_array_count = 0;

/* Original file of elements which are then shuffled. */

static FILE *file_original;

/* Shuffled file_original. */

static FILE *file_shuffled;

/* Output sorted file. */

static FILE *file_sorted;

/* System available memory in kB */

static unsigned long long mem_available_kB;

/* Free's allocated memory and exits with code. */

static void
my_exit (int code)
{
    if (file_numbers_array)
        free (file_numbers_array);

    if (file_original)
        fclose (file_original);

    if (file_shuffled)
        fclose (file_shuffled);

    if (file_sorted)
        fclose (file_sorted);

    if (DEBUG)
        printf ("EXIT CODE %d\n", code);

    exit (code);
}

/* Counts the number of consecutive array elements. */

static long
my_count_consecutive_array (const long *arr, long n)
{
    long count = 0;

    long i;
    for (i = 0; i < (n - 1); i ++)
    {
        if ((arr[i + 1] - arr[i]) == 1)
            count += 2;
    }

    return count;
}

/* Generates two files; file_original contains original values that are then
 * shuffled and written to file_shuffled. The number of values depend
 * on lines_number. Returns 1 on success. */

static int
my_generate_input_files (char *file_original_path, char *file_shuffled_path,
                         long lines_count, long *file_numbers_array)
{
    if (DEBUG)
    {
        printf ("DEBUG: Called my_generate_input_files with arguments: \n");
        printf ("DEBUG: file_original_path = %s\n", file_original_path);
        printf ("DEBUG: file_shuffled_path = %s\n", file_shuffled_path);
        printf ("DEBUG: lines_count = %ld\n", lines_count);
    }

    long i;

    file_numbers_array = malloc ((lines_count + 1) * sizeof (long));
    if (file_numbers_array == NULL)
    {
        my_print_error ("Can't allocate memory to file_numbers_array", "");

        return 0;
    }

    /* Access to file_original. */

    if (DEBUG)
    {
        printf ("DEBUG: Accessing file_original...\n");
    }

    if (access (file_original_path, F_OK) == 0)
    {
        my_print_error ("This file exists", file_original_path);

        return 0;
    }
    else
    {
        file_original = fopen (file_original_path, "w");

        if (file_original == NULL)
        {
            my_print_error ("Cannot create this file", file_original_path);

            return 0;
        }
    }

    /* Access to file_shuffled. */

    if (DEBUG)
    {
        printf ("DEBUG: Accessing file_shuffled...\n");
    }

    if (access (file_shuffled_path, F_OK) == 0)
    {
        my_print_error ("This file exists", file_shuffled_path);

        return 0;
    }
    else
    {
        file_shuffled = fopen (file_shuffled_path, "w");

        if (file_shuffled == NULL)
        {
            my_print_error ("Cannot create this file", file_shuffled_path);

            return 0;
        }
    }

    /* Writing the standard numbers to file_original */

    if (DEBUG)
    {
        printf ("DEBUG: Writing the standard numbers to file_original...\n");
    }

    for (i = 0; i < lines_count; i++)
    {
        file_numbers_array[i] = i;
    }

    for (i = 0; i < lines_count; i++)
    {
        fprintf (file_original, "%ld\n", file_numbers_array[i]);
    }

    /* Randomly shuffle numbers of array. */

    if (DEBUG)
        printf ("DEBUG: Randomly shuffling numbers of array...\n");

    my_shuffle_array (file_numbers_array, lines_count);

    if (DEBUG)
        printf ("DEBUG: Writing the shuffled numbers to file_shuffled...\n");

    for (i = 0; i < lines_count; i++)
    {
        fprintf (file_shuffled, "%ld\n", file_numbers_array[i]);
    }

    if (DEBUG)
        printf ("DEBUG: Computing stats...\n");

    if (STATS)
    {
        long count = my_count_consecutive_array (file_numbers_array, lines_count);

        printf ("STATS: Consecutive numbers: %.2f%%, %ld / %ld\n",
               (double) 100 * count / lines_count, count, lines_count);
    }

    if (DEBUG)
        printf ("DEBUG: my_generate_input_files finished.\n");

    return 1;
}

/* Get the number of digits of a number. */

static int
my_get_digits (long number)
{
    int digits = 0;

    while (number)
    {
        digits++;

        number /= 10;
    }

    return digits;
}

/* Reads file_shuffled_path, sorts the array based on insertion sort and
 * writes to file_sorted_path. Returns 1 on success. */

static int
my_sort_file (char *file_shuffled_path, char *file_sorted_path,
              long *file_numbers_array, long file_numbers_array_count)
{
    long i;

    if (DEBUG)
    {
        printf ("DEBUG: Called my_sort_file with arguments: \n");
        printf ("DEBUG: file_shuffled_path = %s\n", file_shuffled_path);
        printf ("DEBUG: file_sorted_path = %s\n", file_sorted_path);
    }

    /* Access to file_shuffled. */

    if (DEBUG)
        printf ("DEBUG: Accessing file_shuffled...\n");

    if (access (file_shuffled_path, F_OK) != 0)
    {
        my_print_error ("This file does not exist", file_shuffled_path);

        return 0;
    }
    else
    {
        file_shuffled = fopen (file_shuffled_path, "r");

        if (file_shuffled == NULL)
        {
            my_print_error ("Cannot read this file", file_shuffled_path);

            return 0;
        }
    }

    /* Reading file_shuffled. */

    if (DEBUG)
        printf ("DEBUG: Reading file_shuffled...\n");

    file_numbers_array = malloc (sizeof (long));

    if (file_numbers_array == NULL)
    {
        my_print_error ("Can't allocate memory to file_numbers_array", "");

        my_exit (-1);
    }

    while (fscanf (file_shuffled, "%ld", &file_numbers_array[file_numbers_array_count]) == 1)
    {
        file_numbers_array_count += 1;

        file_numbers_array = realloc (file_numbers_array,
                                      (file_numbers_array_count + 1) * sizeof (long));

        if (file_numbers_array == NULL)
        {
            my_print_error ("Can't reallocate memory to file_numbers_array", "");

            my_exit (-1);
        }
    }

    /* Estimate time for sorting */

    if (DEBUG)
    {
        printf ("DEBUG: Estimating time for sorting %ld numbers...\n", file_numbers_array_count);

        double time_estimated = my_get_estimated_time_sort(my_insertion_sort,
                                                           file_numbers_array,
                                                           file_numbers_array_count);

        if (time_estimated == -1)
        {
            my_print_error("Error while estimating time for sorting.", "");

            return 0;
        }

        printf ("DEBUG: Time estimated for sorting: %.2f s\n", time_estimated);
    }

    /* Sort */

    clock_t timeStart = clock ();

    if (my_insertion_sort (file_numbers_array, file_numbers_array_count) == 0)
    {
        my_print_error ("Error on insertion sort.", "");

        my_exit(-1);
    }

    clock_t timeEnd = clock ();

    if (DEBUG)
    {
        printf ("DEBUG: Time needed for sorting: %.2f s\n", (float) (timeEnd - timeStart) / CLOCKS_PER_SEC);
    }

    /* Access to file_sorted. */

    if (DEBUG)
    {
        printf ("DEBUG: Accessing file_sorted...\n");
    }

    if (access (file_sorted_path, F_OK) == 0)
    {
        my_print_error ("This file exists", file_sorted_path);

        return 0;
    }
    else
    {
        file_sorted = fopen (file_sorted_path, "w");

        if (file_sorted == NULL)
        {
            my_print_error ("Cannot create this file", file_sorted_path);

            return 0;
        }
    }

    if (DEBUG)
    {
        printf ("DEBUG: Writing to file_sorted...\n");
    }

    for (i = 0; i < file_numbers_array_count; i++)
    {
        if (fprintf (file_sorted, "%ld\n", file_numbers_array[i]) < 0)
        {
            char str[my_get_digits(i) + 1];

            sprintf (str, "%ld", i);

            my_print_error ("Error while writing in file_sorted. Last element", str);
        }
    }

    if (DEBUG)
    {
        printf ("DEBUG: my_sort_file finished.\n");
    }

    return 1;
}

int
main (int argc, char* argv[])
{
    /* Get system available memory */

    if (DEBUG)
        printf ("DEBUG: Getting system available memory...\n");

    mem_available_kB = my_get_system_available_memory_kB ();

    if (mem_available_kB == 0)
        my_exit (-1);

    if (DEBUG)
        printf ("DEBUG: MemAvailable: %llu kB\n", mem_available_kB);

    /* Calculate the maximum amount of lines that can be generated.
     * 2000 bytes is base memory required to run the program. */

    unsigned long long possible_lines_to_generate = (mem_available_kB * 1024 - 2000) / 4;

    if (DEBUG)
        printf ("DEBUG: Total number of possible lines to generate: %llu \n",
               possible_lines_to_generate);

    /* Check argument options */

    if (DEBUG)
        printf ("DEBUG: Getting argument options...\n");

    if (argc == 2 && (strcmp (argv[1], "--help") == 0
        || strcmp (argv[1], "-v") == 0))
    {
        /* --help or -v option */

        if (DEBUG)
            printf ("DEBUG: --help or -v option selected.\n");

        my_print_help (argv[1]);

        my_exit (0);
    }
    else if (argc == 5 && (strcmp (argv[1], "--generate") == 0
             || strcmp (argv[1], "-g") == 0)
            && strlen (argv[2]) < 128 && strlen (argv[3]) < 128
            && strtol (argv[4], NULL, 10) >= 2 && strtol (argv[4], NULL, 10) < 2147483647)
    {
        /* -generate option */

        long line_count = strtol (argv[4], NULL, 10);

        if (DEBUG)
        {
            printf ("DEBUG: -generate option selected\n");
            printf ("DEBUG: line_count = %ld\n", line_count);
        }

        unsigned long mem_required_kB = (2000 + line_count * 4) / 1024;

        if (mem_required_kB >= mem_available_kB)
        {
            char str[256];

            sprintf (str, "Fail to generate. Using too much "
                         "memory, %lu kB out of %llu kB available.",
                          mem_required_kB, mem_available_kB);

            my_print_error (str, "");

            my_exit (-1);
        }

        if (my_generate_input_files (argv[2], argv[3], line_count, file_numbers_array) == 0)
        {
            my_exit (-1);
        }

        my_exit (0);
    }
    else if (argc == 4 && (strcmp (argv[1], "--sort") == 0
             || strcmp (argv[1], "-s") == 0)
            && strlen (argv[2]) < 128 && strlen (argv[3]) < 128 )
    {
        /* -sort option */

        if (my_sort_file (argv[2], argv[3], file_numbers_array, file_numbers_array_count) == 0)
        {
            my_exit (-1);
        }

        my_exit (0);
    }
    else
    {
        my_print_error ("Unknown command.\n", "");

        my_print_help ("");

        my_exit (0);
    }

    return 0;
}
