#ifndef __MY_SORT_H
#define __MY_SORT_H

void
my_shuffle_array (long *file_numbers_array, long lines_count);

int
insertionSort (long *arr, long size);

int
bubbleSort (long *arr, long size);

int 
selectionSort (long *arr, long n);

int 
mergeSort (long arr[], long l, long r);

int 
quickSort (long arr[],long low,long high);

int 
heapSort (long arr[], long N);

int 
countSort (long a[], long n);

int 
radixSort (long a[], long n);

int 
bucketSort (long a[], long n);

int 
bingoSort (long arr[], long n);

int 
shellSort (long arr[], long n);

int 
timSort (long arr[], long n);

#endif //__MY_SORT_H
