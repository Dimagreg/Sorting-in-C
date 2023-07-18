#include <stdio.h>

#include "lib/my_print.h"

/* Gets system available memory in kB located in /proc/meminfo. Returns 0 on fail. */

unsigned long long
my_get_system_available_memory_kB (void)
{
    FILE *meminfo = fopen ("/proc/meminfo", "r");
    if (meminfo == NULL)
    {
        my_print_error("Fail to access /proc/meminfo", "");

        return 0;
    }

    char line[256];
    while (fgets (line, sizeof (line), meminfo))
    {
        unsigned long long ram;

        if (sscanf (line, "MemAvailable: %llu kB", &ram) == 1)
        {
            fclose (meminfo);
            return ram;
        }
    }

    fclose (meminfo);

    my_print_error("No MemAvailable found in /proc/meminfo", "");

    return 0;
}
