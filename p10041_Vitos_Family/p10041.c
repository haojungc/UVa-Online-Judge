/* Vito's Family */
/* UVa ID: 10041 */
#include <stdio.h>

static void swap(int*, int*);
static void quicksort(int[], int, int);             // quicksort(array of street numbers, start index, end index);
static int partition(int[], int, int);              // partition(array of street numbers, start index, end index);
static int get_sum_of_distances(int[], int, int);   // get_sum_of_distances(sorted array of street numbers, 
                                                    // length of the array, street number of Vito's house);

int main() {
    int total_cases, 
        total_relatives, 
        street_number[510];
    
    scanf("%d", &total_cases);
    while (total_cases--) {
        scanf("%d", &total_relatives);
        for (int i = 0; i < total_relatives; ++i)
            scanf("%d", &street_number[i]);
        
        quicksort(street_number, 0, total_relatives - 1);

        int median_index = (total_relatives - 1) / 2;
        int sum_of_distances = get_sum_of_distances(street_number, total_relatives, street_number[median_index]);

        printf("%d\n", sum_of_distances);
    }

    return 0;
}

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void quicksort(int array[], int start, int end) {
    if (start >= end) return;

    int split_point = partition(array, start, end);

    quicksort(array, start, split_point - 1);
    quicksort(array, split_point + 1, end);
}

int partition(int array[], int start, int end) {
    int pivot = array[end],
        latest_index = start - 1;   // array[latest_index] is the latest scanned value which is lesser than the pivot
    
    for (int current = start; current < end; ++current) {
        if (array[current] < pivot)
            swap(&array[current], &array[++latest_index]);
    }
    swap(&array[end], &array[++latest_index]);

    return latest_index;
}

int get_sum_of_distances(int street_number[], int length, int reference_value) {
    int sum = 0;

    for (int i = 0; i < length; ++i) {
        int distance = street_number[i] - reference_value;
        distance = (distance >= 0) ? distance : -distance;
        sum += distance;
    }
    return sum;
}
