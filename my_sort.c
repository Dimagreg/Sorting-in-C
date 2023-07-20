#include <stdlib.h>
#include <time.h>

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


/* Sorts the array based on Insertion Sort, O(n^2). Returns 1 on success. */

int
my_insertion_sort (long *arr, long size)
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

/* Sorts the array based on Bubble Sort, O(n^2). Returns 1 on success. */

int
my_bubble_sort (long *arr, long size)
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
