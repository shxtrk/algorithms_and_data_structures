#include "insert_sort.h"
#include <stdlib.h>
#include <stdio.h>

void is_sort(is_type *arr, int s) {
    for (int i = 1; i < s; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}