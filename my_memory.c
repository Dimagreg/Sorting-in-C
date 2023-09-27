#include <stdio.h>

#ifdef WIN32
    #include <windows.h>
#endif

#include "lib/my_print.h"

/* Gets 80% of system available memory in kB located in /proc/meminfo.
 * Returns 0 on fail. */
unsigned long long
my_get_system_available_memory_kB (void)
{
    #ifdef WIN32 /* Windows */
        MEMORYSTATUSEX status;

        status.dwLength = sizeof (status);

        GlobalMemoryStatusEx (&status);

        return status.ullAvailPhys / 1024 * 0.8;

    #else /* Linux */
        FILE *meminfo = fopen ("/proc/meminfo", "r");
        if (meminfo == NULL)
        {
            my_print_error ("Fail to access /proc/meminfo", "");

            return 0;
        }

        char line[256];
        while (fgets (line, sizeof (line), meminfo))
        {
            unsigned long long ram;

            if (sscanf (line, "MemAvailable: %llu kB", &ram) == 1)
            {
                fclose (meminfo);
                return ram * 0.8;
            }
        }

        /* No MemAvailable found. Probably old Linux. */

        meminfo = fopen ("/proc/meminfo", "r");
        if (meminfo == NULL)
        {
            my_print_error ("Fail to access /proc/meminfo", "");

            return 0;
        }

        while (fgets (line, sizeof (line), meminfo))
        {
            unsigned long long ram;

            if (sscanf (line, "MemFree: %llu kB", &ram) == 1)
            {
                fclose (meminfo);
                return ram * 0.8;
            }
        }

        /* Nothing found in the file. Return error. */

        fclose (meminfo);

        my_print_error ("No information about memory found in /proc/meminfo", "");

        return 0;
    #endif
}
