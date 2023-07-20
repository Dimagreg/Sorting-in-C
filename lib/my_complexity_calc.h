#ifndef __COMPLEXITY_CALC_H
#define __MY_COMPLEXITY_CALC_H

double
my_get_estimated_time_sort (int (*sort_function) (long*, long),
                            long *file_numbers_array, long lines_count);

#endif //__MY_COMPLEXITY_CALC_H
