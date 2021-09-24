#include "select_sort.h"
#include <stdlib.h>
#include <stdio.h>

void ss_sort(ss_type *arr, int s) {
    for (int i = 0; i < s; i++) {
        int m = i;
        for (int j = i; j < s; j++) {
            if (arr[j] < arr[m]) m = j;
        }
        if (m != i) {
            int tmp = arr[i];
            arr[i] = arr[m];
            arr[m] = tmp;
        }
    }
}