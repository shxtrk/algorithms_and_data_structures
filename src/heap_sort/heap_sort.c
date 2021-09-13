#include "heap_sort.h"
#include <stdlib.h>
#include <stdio.h>

static void hs_heapify(hs_type *array, int s, int i) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int largest = i;
    if (left < s && array[left] > array[largest]) {
        largest = left;
    }
    if (right < s && array[right] > array[largest]) {
        largest = right;
    }
    if (largest != i) {
        int temp = array[i];
        array[i] = array[largest];
        array[largest] = temp;
        hs_heapify(array, s, largest);
    }
}

void hs_sort(hs_type *array, int s) {
    for (int i = s / 2 - 1; i >= 0; i--) {
        hs_heapify(array, s, i);
    }

    for (int i = s - 1; i > 0; i--) {
        int temp = array[i];
        array[i] = array[0];
        array[0] = temp;
        hs_heapify(array, i, 0);
    }
}