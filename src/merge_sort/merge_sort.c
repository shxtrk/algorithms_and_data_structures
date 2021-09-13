#include "merge_sort.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void ms_merge(ms_type *arr, int s1, int s2) {
    ms_type *tmp = (ms_type *)malloc(sizeof(ms_type) * (s1 + s2));

    int i = 0, j = 0, k = 0;
    while (i < s1 && j < s2) {
        if (arr[i] > arr[s1 + j])
            tmp[k++] = arr[s1 + j++];
        else
            tmp[k++] = arr[i++];
    }
    while (i < s1) tmp[k++] = arr[i++];
    while (j < s2) tmp[k++] = arr[s1 + j++];

    memcpy(arr, tmp, sizeof(ms_type) * (s1 + s2));
    free(tmp);
}

void ms_sort(ms_type *arr, int s) {
    if (s < 2) return;
    int s1 = s / 2;
    int s2 = s - s / 2;
    ms_sort(arr, s1);
    ms_sort(arr + s1, s2);
    ms_merge(arr, s1, s2);
}