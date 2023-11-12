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

/* Calls man if --help argument is passed;*/
void
my_print_help (char *flag)
{

    if (strcmp (flag, "--help") == 0)
    {
        system("man mySort");
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
