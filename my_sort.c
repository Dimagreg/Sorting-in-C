#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include "lib/my_print.h"

const long RUN = 32;

void 
swap (long *xp, long *yp)
{
    long temp = *xp;
    *xp = *yp;
    *yp = temp;
}

/* Randomly shuffle elements of array. */
void
my_shuffle_array (long *file_numbers_array, long lines_count)
{
    long random_i, temp;
    long i;

    srand (time (NULL));

    for (i = 0; i < lines_count; i++)
    {
        do {
            random_i = rand () % lines_count;

        } while (random_i == i); /* Indices should be different in order to shuffle. */

        temp = file_numbers_array[i];

        file_numbers_array[i] = file_numbers_array[random_i];

        file_numbers_array[random_i] = temp;
    }
}


/*Insertion sort is a simple sorting algorithm that works similar to the way you sort playing cards in your hands. The array is virtually split into a sorted and an unsorted part. Values from the unsorted part are picked and placed at the correct position in the sorted part.

Time Complexity: O(N^2)
Average time to sort 100,000 numbers: 14.50s 
*/
int
insertionSort (long *arr, long size)
{
    long key;
    long j, i;

    for (i = 1; i < size; i++){
        key = arr[i];

        j = i - 1;

        while ((j >= 0) && (arr[j] >= key)){
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }

    return 1;
}

/* In this algorithm, traverse from left and compare adjacent elements and the higher one is placed at right side. In this way, the largest element is moved to the rightmost end at first. This process is then continued to find the second largest and place it and so on until the data is sorted.

Time Complexity: O(N^2)
Average time to sort 100,000 numbers: 62.55s 
*/
int
bubbleSort (long *arr, long size)
{
    long i, j, temp;
    int swapped;

    for (i = 0; i < size - 1; i++) {

        swapped = 0;

        for (j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {

                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;

                swapped = 1;
            }
        }

        if (!swapped)
            break;
    }

    return 1;
}

/*Selection sort is a simple and efficient sorting algorithm that works by repeatedly selecting the smallest (or largest) element from the unsorted portion of the list and moving it to the sorted portion of the list. 

Time Complexity: O(N^2)
Average time to sort 100,000 numbers: 55.88s 
*/
int 
selectionSort (long *arr, long n)
{
    long i, j, min_idx;
 
    // One by one move boundary of unsorted subarray
    for (i = 0; i < n-1; i++)
    {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i+1; j < n; j++)
          if (arr[j] < arr[min_idx])
            min_idx = j;
 
        // Swap the found minimum element with the first element
           if(min_idx != i)
            swap(&arr[min_idx], &arr[i]);
    }

    return 1;
}

/*Merge sort is defined as a sorting algorithm that works by dividing an array into smaller subarrays, sorting each subarray, and then merging the sorted subarrays back together to form the final sorted array.

Time Complexity: O(N log(N))
Average time to sort 100,000 numbers: ?
*/
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
 
// l is for left index and r is right index of the
// sub-array of arr to be sorted
int 
mergeSort (long arr[], long l, long r)
{
    if (l < r) {
        long m = l + (r - l) / 2;
 
        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
 
        merge(arr, l, m, r);
    }

    return 1;
}

/*QuickSort is a sorting algorithm based on the Divide and Conquer algorithm that picks an element as a pivot and partitions the given array around the picked pivot by placing the pivot in its correct position in the sorted array.

Time Complexity: O(N log(N))
Average time to sort 100,000 numbers: ?
*/
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
 
// The Quicksort function Implement
            
int 
quickSort (long arr[],long low,long high) //TODO: test
{
  // when low is less than high
  if(low<high)
  {
    // pi is the partition return index of pivot
     
    int pi=partition(arr,low,high);
     
    //Recursion Call
    //smaller element than pivot goes left and
    //higher element goes right
    quickSort(arr,low,pi-1);
    quickSort(arr,pi+1,high);
  }

  return 1;
}


void 
heapify (long arr[], long N, long i) //TODO: on make gives warnings due to swap function
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
 
/*Heap sort is a comparison-based sorting technique based on Binary Heap data structure. It is similar to the selection sort where we first find the minimum element and place the minimum element at the beginning. Repeat the same process for the remaining elements.
Time Complexity: O(N log(N))
Average time to sort 100,000 numbers: ?
*/
int 
heapSort(long arr[], long N)
{
 
    // Build max heap
    for (long i = N / 2 - 1; i >= 0; i--)
 
        heapify(arr, N, i);
 
    // Heap sort
    for (long i = N - 1; i >= 0; i--) {
 
        swap(&arr[0], &arr[i]);
 
        // Heapify root element
        // to get highest element at
        // root again
        heapify(arr, i, 0);
    }

    return 1;
}

long 
getMax (long a[], long n) {  
   long max = a[0];  
   
   for (long i = 1; i < n; i++)
   {  
    if (a[i] > max)  
        max = a[i];  
   }  
   return max; //maximum element from the array  
}  
  
/*Counting Sort is a non-comparison-based sorting algorithm that works well when there is limited range of input values. It is particularly efficient when the range of input values is small compared to the number of elements to be sorted. The basic idea behind Counting Sort is to count the frequency of each distinct element in the input array and use that information to place the elements in their correct sorted positions.
Time Complexity: O(N+M), where N and M are the size of inputArray[] and countArray[] respectively.
Average time to sort 100,000 numbers: ?
*/
int 
countSort (long a[], long n)  
{  
    long output[n + 1];  
    long max = getMax (a, n);  
    long count[max + 1]; //create count array with size [max+1]  
  
  
    for (long i = 0; i <= max; ++i)   
    {  
        count[i] = 0; // Initialize count array with all zeros  
    }  
    
    for (long i = 0; i < n; i++) // Store the count of each element  
    {  
        count[a[i]]++;  
    }  
  
    for (long i = 1; i <= max; i++)   
        count[i] += count[i - 1]; //find cumulative frequency  

    /* This loop will find the index of each element of the original array in count array, and 
    place the elements in output array*/  
    for (long i = n - 1; i >= 0; i--) 
    {  
        output[count[a[i]] - 1] = a[i];  
        count[a[i]]--; // decrease count for same numbers  
    }  
  
    for (long i = 0; i < n; i++) 
    {  
      a[i] = output[i]; //store the sorted elements into main array  
    }  

    return 1;
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
  
/*Radix Sort is a linear sorting algorithm that sorts elements by processing them digit by digit. It is an efficient sorting algorithm for integers or strings with fixed-size keys. 
Time Complexity: O(d * (n + b)), where d is the number of digits, n is the number of elements, and b is the base of the number system being used.
Average time to sort 100,000 numbers: ?
*/ 
int 
radixSort (long a[], long n) {  
   
    // get maximum element from array  
    long max = getMax (a, n);  
    
    // Apply counting sort to sort elements based on place value  
    for (long place = 1; max / place > 0; place *= 10)  
        countingSort (a, n, place);  

    return 1;
}  

/*Bucket sort is a sorting technique that involves dividing elements into various groups, or buckets. These buckets are formed by uniformly distributing the elements. Once the elements are divided into buckets, they can be sorted using any other sorting algorithm. Finally, the sorted elements are gathered together in an ordered fashion.
Time Complexity: O(n^2)
Average time to sort 100,000 numbers: ?
*/
int 
bucketSort (long a[], long n)
{  
    long max = getMax(a, n); //max is the maximum element of array  
    long bucket[max];  

    for (long i = 0; i <= max; i++)  
    {  
        bucket[i] = 0;  
    }  
    for (long i = 0; i < n; i++)  
    {  
        bucket[a[i]]++;  
    }  
    for (long i = 0, j = 0; i <= max; i++)  
    {  
        while (bucket[i] > 0)  
        {  
        a[j++] = i;  
        bucket[i]--;  
        }  
    }  

    return 1;
}  

/*This Sorting Technique is similar to the Selection Sort in which we first find the smallest element called Bingo Element, and then we repeatedly iterate the elements of the array to get the correct positions of all the elements. Similarly, find the next bingo element for the next pass, and so on. Every distinct element is considered a Bingo Element and called out in increasing order.
Time Complexity: O(M * N) where M = number of distinct elements and N = size of the array
Average time to sort 100,000 numbers: ?
*/
int 
bingoSort(long arr[], long n)
{
    long min = arr[0], max = arr[0];
    long i;

    for (i = 1; i < n; i++)
    {
        if (arr[i] < min)
            min = arr[i];
        else if (arr[i] > max)
            max = arr[i];
    }
    
    long *flags = (long *)calloc(max - min + 1, sizeof(long));
    
    for (i = 0; i < n; i++)
        flags[arr[i] - min] = 1;
    
    long index = 0;
    
    for (i = 0; i < max - min + 1; i++)
    {
        if (flags[i])
        {
            arr[index] = i + min;
            index++;
        }
    }
 
    free(flags);

    return 1;
}

/*Shell sort is mainly a variation of Insertion Sort. In insertion sort, we move elements only one position ahead. When an element has to be moved far ahead, many movements are involved. The idea of ShellSort is to allow the exchange of far items. In Shell sort, we make the array h-sorted for a large value of h. We keep reducing the value of h until it becomes 1. An array is said to be h-sorted if all sublists of every h’th element are sorted. 
Time Complexity: O(n^2)
Average time to sort 100,000 numbers: ?
*/
int 
shellSort (long arr[], long n) 
{ 
    // Start with a big gap, then reduce the gap 
    for (long gap = n/2; gap > 0; gap /= 2) 
    { 
        // Do a gapped insertion sort for this gap size. 
        // The first gap elements a[0..gap-1] are already in gapped order 
        // keep adding one more element until the entire array is 
        // gap sorted  
        for (long i = gap; i < n; i += 1) 
        { 
            // add a[i] to the elements that have been gap sorted 
            // save a[i] in temp and make a hole at position i 
            long temp = arr[i]; 
  
            // shift earlier gap-sorted elements up until the correct  
            // location for a[i] is found 
            long j;             
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) 
                arr[j] = arr[j - gap]; 
              
            //  put temp (the original a[i]) in its correct location 
            arr[j] = temp; 
        } 
    } 

    return 1; 
}

// This function sorts array from left
// index to to right index which is
// of size atmost RUN
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

/*Tim Sort is a hybrid sorting algorithm derived from merge sort and insertion sort. It was designed to perform well on many kinds of real-world data. Tim Sort is the default sorting algorithm used by Python’s sorted() and list.sort() functions.
Time Complexity: O(n*log(n))
Average time to sort 100,000 numbers: ?
*/
int 
timSort (long arr[], long n)
{

    // Sort individual subarrays of size RUN
    for (long i = 0; i < n; i += RUN)
        insertionsort(arr, i, fmin((i + RUN - 1), (n - 1)));

    // Start merging from size RUN (or 32).
    // It will merge
    // to form size 64, then 128, 256
    // and so on ....
    for (long size = RUN; size < n; size = 2 * size) {

        // pick starting point of
        // left sub array. We
        // are going to merge
        // arr[left..left+size-1]
        // and arr[left+size, left+2*size-1]
        // After every merge, we
        // increase left by 2*size
        for (long left = 0; left < n; left += 2 * size) {

            // Find ending point of
            // left sub array
            // mid+1 is starting point
            // of right sub array
            long mid = left + size - 1;
            long right = fmin((left + 2 * size - 1), (n - 1));

            // merge sub array arr[left.....mid] &
            // arr[mid+1....right]
            if (mid < right)
                merge(arr, left, mid, right);
        }
    }

    return 1;
}

// To find gap between elements
int 
getNextGap (int gap)
{
    // Shrink gap by Shrink factor
    gap = (gap * 10) / 13;
 
    if (gap < 1)
        return 1;
    return gap;
}
 
/*Comb Sort is mainly an improvement over Bubble Sort. Bubble sort always compares adjacent values. So all inversions are removed one by one. Comb Sort improves on Bubble Sort by using a gap of the size of more than 1. The gap starts with a large value and shrinks by a factor of 1.3 in every iteration until it reaches the value 1. Thus Comb Sort removes more than one inversion count with one swap and performs better than Bubble Sort.
Time Complexity: O(n^2)
Average time to sort 100,000 numbers: ?
*/
int 
combSort (long a[], long n)
{
    // Initialize gap
    long gap = n;
 
    // Initialize swapped as true to make sure that
    // loop runs
    int swapped = 1;
 
    // Keep running while gap is more than 1 and last
    // iteration caused a swap
    while (gap != 1 || swapped)
    {
        // Find next gap
        gap = getNextGap (gap);
 
        // Initialize swapped as false so that we can
        // check if swap happened or not
        swapped = 0;
 
        // Compare all elements with current gap
        for (int i = 0; i < n - gap; i++)
        {
            if (a[i] > a[i + gap])
            {
                swap (&a[i], &a[i + gap]);
                swapped = 1;
            }
        }
    }

    return 1;
}

/*Pigeonhole sorting is a sorting algorithm that is suitable for sorting lists of elements where the number of elements and the number of possible key values are approximately the same. 
Time Complexity: O(n + range), where n is the number of elements in the array and range is the range of the input data
Average time to sort 100,000 numbers: ?
*/
int 
pigeonholeSort (long arr[], long n) 
{
    long min = arr[0], max = arr[0];
    for (long i = 1; i < n; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    long range = max - min + 1;
    long* pigeonholes = (long*)malloc(range * sizeof(long));
    memset(pigeonholes, 0, range * sizeof(long));

    if (!pigeonholes){
        my_print_error("error malloc pigeonhole", "");
        return 0;
    }

    for (long i = 0; i < n; i++) {
        pigeonholes[arr[i] - min]++;
    }

    long index = 0;
    for (long i = 0; i < range; i++) {
        while (pigeonholes[i] > 0) {
            arr[index++] = i + min;
            pigeonholes[i]--;
        }
    }

    free(pigeonholes);

    return 1;
}

/*Cycle sort is an in-place, unstable sorting algorithm that is particularly useful when sorting arrays containing elements with a small range of values. The basic idea behind cycle sort is to divide the input array into cycles, where each cycle consists of elements that belong to the same position in the sorted output array. The algorithm then performs a series of swaps to place each element in its correct position within its cycle, until all cycles are complete and the array is sorted.
Time Complexity: O(n^2)
Average time to sort 100,000 numbers: ?
*/
int 
cycleSort(long arr[], long n)
{
    // count number of memory writes
    long writes = 0;
 
    // traverse array elements and put it to on
    // the right place
    for (long cycle_start = 0; cycle_start <= n - 2; cycle_start++) {
        // initialize item as starting point
        long item = arr[cycle_start];
 
        // Find position where we put the item. We basically
        // count all smaller elements on right side of item.
        long pos = cycle_start;
        for (long i = cycle_start + 1; i < n; i++)
            if (arr[i] < item)
                pos++;
 
        // If item is already in correct position
        if (pos == cycle_start)
            continue;
 
        // ignore all duplicate  elements
        while (item == arr[pos])
            pos += 1;
 
        // put the item to it's right position
        if (pos != cycle_start) {
            swap(&item, &arr[pos]);
            writes++;
        }
 
        // Rotate rest of the cycle
        while (pos != cycle_start) {
            pos = cycle_start;
 
            // Find position where we put the element
            for (int i = cycle_start + 1; i < n; i++)
                if (arr[i] < item)
                    pos += 1;
 
            // ignore all duplicate  elements
            while (item == arr[pos])
                pos += 1;
 
            // put the item to it's right position
            if (item != arr[pos]) {
                swap(&item, &arr[pos]);
                writes++;
            }
        }
    }

    return 1;
}

/*Cocktail Sort is a variation of Bubble sort. The Bubble sort algorithm always traverses elements from left and moves the largest element to its correct position in the first iteration and second-largest in the second iteration and so on. Cocktail Sort traverses through a given array in both directions alternatively. Cocktail sort does not go through the unnecessary iteration making it efficient for large arrays.
Time Complexity: O(n^2)
Average time to sort 100,000 numbers: ?
*/
int 
cocktailSort (long a[], long n)
{
    int swapped = 1;
    long start = 0;
    long end = n - 1;
 
    while (swapped) {
        // reset the swapped flag on entering
        // the loop, because it might be true from
        // a previous iteration.
        swapped = 0;
 
        // loop from left to right same as
        // the bubble sort
        for (long i = start; i < end; ++i) {
            if (a[i] > a[i + 1]) {
                swap(&a[i], &a[i + 1]);
                swapped = 1;
            }
        }
 
        // if nothing moved, then array is sorted.
        if (!swapped)
            break;
 
        // otherwise, reset the swapped flag so that it
        // can be used in the next stage
        swapped = 0;
 
        // move the end point back by one, because
        // item at the end is in its rightful spot
        --end;
 
        // from right to left, doing the
        // same comparison as in the previous stage
        for (int i = end - 1; i >= start; --i) {
            if (a[i] > a[i + 1]) {
                swap(&a[i], &a[i + 1]);
                swapped = 1;
            }
        }
 
        // increase the starting point, because
        // the last stage would have moved the next
        // smallest number to its rightful spot.
        ++start;
    }

    return 1;
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
 
/*Bitonic Sort is a classic parallel algorithm for sorting. 

The number of comparisons done by Bitonic sort is more than popular sorting algorithms like Merge Sort [ does O(log N) comparisons], but Bitonic sort is better for parallel implementation because we always compare elements in a predefined sequence and the sequence of comparison doesn’t depend on data. Therefore it is suitable for implementation in hardware and parallel processor array.
Bitonic Sort can only be done if the number of elements to sort is 2^n. The procedure of bitonic sequence fails if the number of elements is not in the aforementioned quantity precisely.
Time complexity: O(log n)
Average time to sort 100,000 numbers: ?
*/
int 
bitonicSort (long a[],long low, long cnt, long dir)
{
    if (cnt>1)
    {
        long k = cnt/2;
 
        // sort in ascending order since dir here is 1
        bitonicSort(a, low, k, 1);
 
        // sort in descending order since dir here is 0
        bitonicSort(a, low+k, k, 0);
 
        // Will merge whole sequence in ascending order
        // since dir=1.
        bitonicMerge(a,low, cnt, dir);

        return 1;
    }

    return 0;
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
 
/*Pancake sorting is the mathematical problem of sorting a disordered stack of pancakes in order of size when a spatula can be inserted at any point in the stack and used to flip all pancakes above it. A pancake number is the minimum number of flips required for a given number of pancakes.
Time Complexity: O(n2)
Average time to sort 100,000 numbers: ?
*/
int 
pancakeSort (long arr[], long n)
{
    // Start from the complete
    // array and one by one
    // reduce current size
    // by one
    for (long curr_size = n; curr_size > 1; 
                                 --curr_size) 
    {
        // Find index of the
        // maximum element in
        // arr[0..curr_size-1]
        long mi = findMax(arr, curr_size);
 
        // Move the maximum
        // element to end of
        // current array if
        // it's not already
        // at the end
        if (mi != curr_size - 1) {
            // To move at the end,
            // first move maximum
            // number to beginning
            flip(arr, mi);
 
            // Now move the maximum
            // number to end by
            // reversing current array
            flip(arr, curr_size - 1);
        }
    }

    return 1;
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
 
/*BogoSort also known as permutation sort, stupid sort, slow sort, shotgun sort or monkey sort is a particularly ineffective algorithm one person can ever imagine. It is based on generate and test paradigm. The algorithm successively generates permutations of its input until it finds one that is sorted.(Wiki) For example, if bogosort is used to sort a deck of cards, it would consist of checking if the deck were in order, and if it were not, one would throw the deck into the air, pick the cards up at random, and repeat the process until the deck is sorted.
Time Complexity: O(?) (since this algorithm has no upper bound)
Average time to sort 100,000 numbers: ?
*/
int 
bogoSort (long a[], long n)
{
    // if array is not sorted then shuffle
    // the array again
    while (!isSorted(a, n))
        shuffle(a, n);

    return 1;
}

/*Gnome Sort also called Stupid sort is based on the concept of a Garden Gnome sorting his flower pots. A garden gnome sorts the flower pots by the following method:  
He looks at the flower pot next to him and the previous one; if they are in the right order he steps one pot forward, otherwise he swaps them and steps one pot backwards.
If there is no previous pot (he is at the starting of the pot line), he steps forwards; if there is no pot next to him (he is at the end of the pot line), he is done.
Time Complexity: O(n^2)
Average time to sort 100,000 numbers: ?
*/
int 
gnomeSort (long arr[], long n) 
{ 
    long index = 0; 
  
    while (index < n) { 
        if (index == 0) 
            index++; 
        if (arr[index] >= arr[index - 1]) 
            index++; 
        else { 
            swap(&arr[index], &arr[index - 1]); 
            index--; 
        } 
    } 
    return 1; 
} 