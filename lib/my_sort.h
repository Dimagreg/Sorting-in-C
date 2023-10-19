#ifndef __MY_SORT_H
#define __MY_SORT_H

void
my_shuffle_array (long *file_numbers_array, long lines_count);

int
insertion_sort (long *arr, long size);

int
bubble_sort (long *arr, long size);

int 
selectionSort (long *arr, long n);

int 
mergeSort (long arr[], long l, long r);

int 
quickSort (long arr[],long low,long high);

int 
heapSort(long arr[], long N);

#endif //__MY_SORT_H
