#ifndef __MY_SORT_AUX_H
#define __MY_SORT_AUX_H

void 
swap (long *xp, long *yp);

void 
merge (long arr[], long l, long m, long r);

long 
partition (long arr[],long low,long high);

void 
heapify (long arr[], long N, long i);

long 
getMax (long a[], long n);

void 
countingSort (long a[], long n, long place);

void 
insertionsort (long arr[], long left, long right);

int 
getNextGap (int gap);

void 
compAndSwap (long a[], long i, long j, long dir);

void 
bitonicMerge (long a[], long low, long cnt, long dir);

void 
flip (long arr[], long i);

long 
findMax (long arr[], long n);

int 
isSorted (long a[], long n);

void 
shuffle (long a[], long n);

#endif //__MY_SORT_AUX_H