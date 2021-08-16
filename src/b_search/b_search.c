#include "b_search.h"

static int _r_b_search(bs_type *arr, int l, int r, bs_type v) {
    if (l > r) return - 1;
    int m = l + (r - l) / 2;
    if (arr[m] > v)
        return _r_b_search(arr, l, m - 1, v);
    else if (arr[m] < v)
        return _r_b_search(arr, m + 1, r, v);
    else if (m > 0 && arr[m - 1] == v)
        return _r_b_search(arr, l, m, v);
    else
        return m;
}

int i_b_search(bs_type *arr, int size, bs_type v) {
    int l = 0, r = size - 1;
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (arr[m] > v)
            r = m - 1;
        else if (arr[m] < v)
            l = m + 1;
        else if (m > 0 && arr[m - 1] == v)
            r = m;
        else
            return m;
    }
    return -1;
}

int r_b_search(bs_type *arr, int size, bs_type v) {
    if (size < 1) return -1;
    return _r_b_search(arr, 0, size - 1, v);
}