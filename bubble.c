#include <stdio.h>
int swap(int *a, int* b) {
  int t = *a;
  *a = *b;
  *b = t;
}
    int a[] = {2, 1, 5, 3, 4, };
    int i, j, t;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4-i; j++) {
            if (a[j] > a[j+1]) {
              swap(a[j]> a[j+i])
                t = a[j];
                a[j] = a[j+1];
                a[j+1] = t;
            }
        }
    }
    for (int i = 0; i < 5; i++)
        printf("%d ", a[i]);
    return 0;
}
