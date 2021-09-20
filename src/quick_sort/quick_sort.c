#include "quick_sort.h"
#include <stdlib.h>
#include <stdio.h>

void qs_sort(qs_type *arr, int s) {
    if (s < 2) return;

    int p = arr[rand() % s];
    int l = 0;
    int r = s - 1;
    int tmp = 0;

    while (l <= r) {
        if (arr[l] > p) {
            tmp = arr[l];
            arr[l] = arr[r];
            arr[r--] = tmp;
        } else l++;
    }

    qs_sort(arr, l);
    qs_sort(arr + l, s - l);
}