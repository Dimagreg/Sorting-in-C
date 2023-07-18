/* Sorts the array based on Insertion Sort. Returns 1 on success. */

int
my_insertion_sort (unsigned int *arr, int size)
{
    unsigned int key;
    int j;

    for (int i = 1; i < size; i++){
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
