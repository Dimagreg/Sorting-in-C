/*
 * TODO: calculate ram/disk memory required for a maximum write capacity. throw error if request is more than it.
 *       calculate estimate time of computing
 *       progress bar?
 */

/*
 *  Utility program for generating/sorting a file of unsorted unsigned integers
 *   --help
 *   -v
 *   -g, --generate <filename_original> <filename_shuffled> <line_count>
 *              filename_original and filename_shuffled - non_space string 1....128
 *              line_count - unsigned int 1....2^21
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

/* Debugging option. 1 for TRUE, 0 for FALSE. */

enum
{
    DEBUG = 0,
    STATS = 1
};

/* Program version. */

char *VERSION = "17-Jul-23";

/* Original file of elements which are then shuffled. */

static FILE *file_original;

/* Shuffled file_original. */

static FILE *file_shuffled;

/* Output sorted file. */

static FILE *file_sorted;

/* Array of unsorted input file numbers. */

static unsigned int *file_numbers_array = NULL;

/* The total number of elements in array. */

static int file_numbers_array_count = 0;

/* Execution time for reading from file, sorting, writing to file. */

//static int exec_time_read, exec_time_sort, exec_time_write;

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
        printf("EXIT CODE %d\n", code);

    exit (code);
}

/* Counts the number of consecutive array elements. */

static int
my_count_consecutive_array (const int *arr, int n)
{
    int count = 0;

    int i;
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
my_generate_input_files (char *file_original_path, char *file_shuffled_path, int lines_number)
{
    int numbers_arr[lines_number];
    int i;

    srand (time (NULL));

    if (DEBUG)
    {
        printf("DEBUG: my_generate_input_files arguments - %s, %s, %d\n",
               file_original_path, file_shuffled_path, lines_number);
    }

    /* Access to file_original. */

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

    /* Writing the standard values to file_original */

    for (i = 0; i < lines_number; i++)
    {
        numbers_arr[i] = i;
    }

    for (i = 0; i < lines_number; i++)
    {
        if (DEBUG)
            printf("DEBUG: Print to file_original: %d\n", numbers_arr[i]);

        fprintf (file_original, "%d\n", numbers_arr[i]);
    }

    /* Randomly shuffle elements of array. */

    int random_i, temp;

    for (i = 0; i < lines_number; i++)
    {
        do {
            random_i = rand() % lines_number;

        } while (random_i == i); /* Indices should be different in order to shuffle. */

        temp = numbers_arr[i];

        numbers_arr[i] = numbers_arr[random_i];

        numbers_arr[random_i] = temp;
    }

    for (i = 0; i < lines_number; i++)
    {
        if (DEBUG)
            printf("DEBUG: Print to file_shuffled: %d\n", numbers_arr[i]);

        fprintf (file_shuffled, "%d\n", numbers_arr[i]);
    }

    if (STATS)
    {
        int count = my_count_consecutive_array (numbers_arr, lines_number);

        printf("STATS: Consecutive elements: %.2f%%, %d / %d\n",
               (double) 100 * count / lines_number, count, lines_number);
    }

    return 1;
}

/* Get the number of digits of an int. */

static int
my_get_digits (int number)
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
my_sort_file (char *file_shuffled_path, char *file_sorted_path)
{
    int i;

    /* Access to file_shuffled. */

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

    file_numbers_array = malloc (sizeof (unsigned int));

    if (file_numbers_array == NULL)
    {
        my_print_error ("Can't allocate memory to file_numbers_array", "");

        my_exit (-1);
    }

    while (fscanf (file_shuffled, "%d", &file_numbers_array[file_numbers_array_count]) == 1)
    {
        file_numbers_array_count += 1;

        file_numbers_array = realloc (file_numbers_array, (file_numbers_array_count + 1) * sizeof (unsigned int));

        if (file_numbers_array == NULL)
        {
            my_print_error ("Can't reallocate memory to file_numbers_array", "");

            my_exit (-1);
        }
    }

    /* Insertion Sort */

    if (my_insertion_sort (file_numbers_array, file_numbers_array_count) == 0)
    {
        my_print_error("Error on insertion sort.", "");

        my_exit(-1);
    }

    /* Access to file_sorted. */

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

    for (i = 0; i < file_numbers_array_count; i++)
    {
        if (fprintf (file_sorted, "%d\n", file_numbers_array[i]) < 0)
        {
            char str[my_get_digits(i) + 1];

            // itoa(i, str, 10); //throws error on some compilers

            sprintf(str, "%d", i);

            my_print_error ("Error while writing in file_sorted. Last element", str);
        }
    }

    return 1;
}

int
main (int argc, char* argv[])
{
    /* Get system available memory */

    mem_available_kB = my_get_system_available_memory_kB ();

    if (mem_available_kB == 0)
        my_exit(-1);

    if (DEBUG)
        printf("DEBUG: MemAvailable: %llu kB\n", mem_available_kB);

    /* Check argument options */

    if (argc == 2 && (strcmp (argv[1], "--help") == 0
        || strcmp (argv[1], "-v") == 0))
    {
        /* --help or -v option */

        my_print_help(argv[1]);

        my_exit(0);
    }
    else if (argc == 5 && (strcmp (argv[1], "--generate") == 0
             || strcmp (argv[1], "-g") == 0)
            && strlen (argv[2]) < 128 && strlen (argv[3]) < 128
            && strtol (argv[4], NULL, 10) > 1 && strtol (argv[4], NULL, 10) < 2097152 )
    {
        /* -generate option */

        int line_count = strtol (argv[4], NULL, 10);

        unsigned long long mem_required_kB = (2000 + line_count * 4) / 1024;

        if (mem_required_kB >= mem_available_kB)
        {
            char str[256];

            sprintf (str, "Fail to generate. Using too much "
                         "memory, %llu kB out of %llu kB available.",
                          mem_required_kB, mem_available_kB);

            my_print_error (str, "");

            my_exit (-1);
        }

        if (my_generate_input_files (argv[2], argv[3], line_count) == 0)
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

        if (my_sort_file (argv[2], argv[3]) == 0)
        {
            my_exit(-1);
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
