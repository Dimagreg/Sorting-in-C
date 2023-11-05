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
#include <string.h>
#include <stdlib.h>

#include "lib/my_print.h"

extern char *VERSION;

/* Prints error to stderr, adds \n and exits the program with code -1.
 * var is used as a variable value. */
void
my_print_error (char *message, char *var)
{
    if (strcmp (var, "") == 0)
        fprintf (stderr, "%s\n", message);
    else
        fprintf (stderr, "%s - '%s'\n", message, var);
}

/* Prints help or version information; flag = "" is same as "--help". */
void
my_print_help (char *flag)
{

    if (strcmp (flag, "--help") == 0 || strcmp (flag, "") == 0)
    {
        printf ("Usage:\n"
               ".\\my_sort [OPTION...] [file_path] [number]\n\n"
               "Utility program for generating/sorting a file of unsorted unsigned integers.\n\n"
               "Application Options:\n");

        printf (" %-68s Prints Program version\n\n", "-v");

        printf (" %-68s Generates 2 files. First consists of 2..line_count "
                "consecutive positive numbers.\n",
                "-g, --generate <filename_original> <filename_shuffled> <line_count>");
        printf (" %-68s Second is shuffled version of the first. <line_count> "
                "is 2..2,147,483,647 .\n\n", "");

        printf (" %-68s Sorts the init file using Insertion Sort and outputs "
                    "in a new file\n\n", "-s, --sort <file_shuffled> <filename_result>");
    }
    else if (strcmp (flag, "-v") == 0)
    {
        printf ("Program version: %s\n", VERSION);
    }

    else
    {
        my_print_error ("my_print_help unknown flag", flag);

        exit(-1); /* force exit */
    }
}
