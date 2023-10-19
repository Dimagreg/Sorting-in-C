#include <stdlib.h>
#include <time.h>

void swap(long *xp, long *yp)
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
insertion_sort (long *arr, long size)
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
bubble_sort (long *arr, long size)
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
merge (long arr[], long l, long m, long r) //TODO: test and write in main
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
      swap(arr[i],arr[j]);
    }
  }
  swap(arr[i+1],arr[high]);
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

/*Heap sort is a comparison-based sorting technique based on Binary Heap data structure. It is similar to the selection sort where we first find the minimum element and place the minimum element at the beginning. Repeat the same process for the remaining elements.

Time Complexity: O(N log(N))
Average time to sort 100,000 numbers: ?
*/
// To heapify a subtree rooted with node i
// which is an index in arr[].
// n is size of heap
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
 
// Main function to do heap sort
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