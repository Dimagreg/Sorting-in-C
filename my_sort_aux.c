#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include "lib/my_print.h"

/*AUXILIARY FILE TO STORE FUNCTIONS REQUIRED BY SORTING ALGORITHMS*/

void 
swap (long *xp, long *yp)
{
    long temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void 
merge (long arr[], long l, long m, long r)
{
    long i, j, k;
    long n1 = m - l + 1;
    long n2 = r - m;
 
    // Create temp arrays
    long L[n1], R[n2];
 
    // Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
 
    // Merge the temp arrays back into arr[l..r
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    // Copy the remaining elements of L[],
    // if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    // Copy the remaining elements of R[],
    // if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

long 
partition (long arr[],long low,long high)
{
  //choose the pivot
   
  long pivot=arr[high];
  //Index of smaller element and Indicate
  //the right position of pivot found so far
  long i=(low-1);
   
  for(long j=low;j<=high;j++)
  {
    //If current element is smaller than the pivot
    if(arr[j]<pivot)
    {
      //Increment index of smaller element
      i++;
      swap(&arr[i],&arr[j]);
    }
  }
  swap(&arr[i+1],&arr[high]);
  return (i+1);
}
 
void 
heapify (long arr[], long N, long i)
{
    // Find largest among root,
    // left child and right child
 
    // Initialize largest as root
    long largest = i;
 
    // left = 2*i + 1
    long left = 2 * i + 1;
 
    // right = 2*i + 2
    long right = 2 * i + 2;
 
    // If left child is larger than root
    if (left < N && arr[left] > arr[largest])
 
        largest = left;
 
    // If right child is larger than largest
    // so far
    if (right < N && arr[right] > arr[largest])
 
        largest = right;
 
    // Swap and continue heapifying
    // if root is not largest
    // If largest is not root
    if (largest != i) {
 
        swap(&arr[i], &arr[largest]);
 
        // Recursively heapify the affected
        // sub-tree
        heapify(arr, N, largest);
    }
}

long 
getMax (long a[], long n) 
{  
   long max = a[0];  
   
   for (long i = 1; i < n; i++)
   {  
    if (a[i] > max)  
        max = a[i];  
   }  
   return max; //maximum element from the array  
}  

void 
countingSort (long a[], long n, long place) // counting sort for radix  
{  
    long output[n + 1];  
    long count[10] = {0};    
    
    // Calculate count of elements  
    for (long i = 0; i < n; i++)  
        count[(a[i] / place) % 10]++;  
        
    // Calculate cumulative frequency  
    for (long i = 1; i < 10; i++)  
        count[i] += count[i - 1];  
    
    // Place the elements in sorted order  
    for (long i = n - 1; i >= 0; i--) 
    {  
        output[count[(a[i] / place) % 10] - 1] = a[i];  
        count[(a[i] / place) % 10]--;  
    }  
    
    for (long i = 0; i < n; i++)  
        a[i] = output[i];  
}  

void 
insertionsort (long arr[], long left, long right)
{
    for (long i = left + 1; i <= right; i++) {
        int temp = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}

int 
getNextGap (int gap)
{
    // Shrink gap by Shrink factor
    gap = (gap * 10) / 13;
 
    if (gap < 1)
        return 1;
    return gap;
}

/*The parameter dir indicates the sorting direction, ASCENDING
   or DESCENDING; if (a[i] > a[j]) agrees with the direction,
   then a[i] and a[j] are interchanged.*/
void 
compAndSwap (long a[], long i, long j, long dir)
{
    if (dir==(a[i]>a[j]))
        swap(&a[i],&a[j]);
}
 
/*It recursively sorts a bitonic sequence in ascending order,
  if dir = 1, and in descending order otherwise (means dir=0).
  The sequence to be sorted starts at index position low,
  the parameter cnt is the number of elements to be sorted.*/
void 
bitonicMerge (long a[], long low, long cnt, long dir)
{
    if (cnt>1)
    {
        long k = cnt/2;
        for (long i=low; i<low+k; i++)
            compAndSwap(a, i, i+k, dir);
        bitonicMerge(a, low, k, dir);
        bitonicMerge(a, low+k, k, dir);
    }
}

/* Reverses arr[0..i] */
void 
flip (long arr[], long i)
{
    long temp, start = 0;
    while (start < i) {
        temp = arr[start];
        arr[start] = arr[i];
        arr[i] = temp;
        start++;
        i--;
    }
}
 
// Returns index of the
// maximum element in
// arr[0..n-1]
long 
findMax (long arr[], long n)
{
    long mi, i;
    for (mi = 0, i = 0; i < n; ++i)
        if (arr[i] > arr[mi])
            mi = i;
    return mi;
}

// To check if array is sorted or not
int 
isSorted (long a[], long n)
{
    while (--n > 0)
        if (a[n] < a[n - 1])
            return 0;
    return 1;
}
 
// To generate permutation of the array
void 
shuffle (long a[], long n)
{
    for (long i = 0; i < n; i++)
        swap(&a[i], &a[rand() % n]);
}