#include <stdio.h>
#include <stdlib.h>

#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int similarity(int v, int *a, int l) {
    int t = 0;
    for(int i=0;i<l;i++) {
        if(a[i] == v) t++;
    }

    return t;
}

int main() {
    FILE *fh = NULL;

    int l1[1024];
    int l2[1024];
    //int s = sizeof(l1) / sizeof(*l1);
    int c = 0;
    int s = 0;
    int s2 = 0;

    if((fh = fopen("input","rb")) == NULL)
        return -1;

    char b[15]; // 13 + newline + null terminator
    while(fgets(b, sizeof(b), fh)) {
        char *n;
        //printf("%s", b);
        l1[c] = (int)strtol(b, &n, 10);
        l2[c] = (int)strtol(n, NULL, 10);
        c++;
    }

    printf("Size of elems retrieved: %d\n", c);

    qsort(l1, c, sizeof(int), compare);
    qsort(l2, c, sizeof(int), compare);

    for(int i=0;i<c;i++) {
        s += MAX(l2[i], l1[i]) - MIN(l1[i], l2[i]);
        int temp = similarity(l1[i], l2, c);
        printf("%d * %d = %d\n", l1[i], temp, l1[i] * temp);

        s2 += l1[i] * temp;
        //printf("%d %d\n", l1[i], l2[i]);
    }

    printf("Solution 1: %d\n", s);
    printf("Solution 2: %d\n", s2);

    fclose(fh);

    return 0;
}