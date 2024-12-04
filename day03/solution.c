#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

struct pair {
    int a;
    int b;
};

int mul(struct pair p) { return p.a * p.b; }

int verifyMul(const char *s, int l) {
    int q1 = 0; int q2 = 0; int q3 = 0;

    // Checks for three requirements
    // 1. the function has a number
    // 2. the function has a comma (2 numbers)
    // 3. the function is closed correctly
    for(int i=0;i<l;i++) {
        if(isdigit(s[i]) && !q1) q1 = 1;
        if(s[i] == ')' && !q2) q2 = 1;
        if(s[i] == ',' && (!q2 && !q3)) q3 = 1;
    }

    return q1 && q2 && q3;
}

struct pair extract(const char *s, int l) {
    // Mess of a function,
    // but I can't be asked to do better
    char *ts = strdup(s);
    char ts2[5];
    int x = strcspn(ts, ",");
    struct pair v = {0, 0};

    v.a = atoi(ts); // 1st num

    // poor mans string split
    (void)strcpy(ts2, s+(x+1));

    // remove anything that is not a number to not
    // trip up the conversion
    for(int i=0;i<5;i++) if(!isdigit(ts2[i])) ts2[i] = '\0';

    v.b = atoi(ts2); // 2nd num

    free(ts);

    return v;
}

int main(int argc, char **argv) {
    // the variables
    const char *inFile = NULL;
    FILE *fh = NULL;

    long fp[2048]; int fc = 0;
    int ma = 0;
    int en = 1;

    char buf[12];
    int ta = 0; int tb = 0;

    if(argc != 2) {
        printf("Usage: %s [file]\n", argv[0]);
        return 1;
    }

    if((inFile = argv[1]) == NULL)
        return -1;

    if((fh = fopen(inFile, "rb")) == NULL)
        return -1;

    char c = 0;

    // run through to find functions
    while((c = fgetc(fh)) != EOF) {
        if(c == 'm' || c == 'd') {
            fp[fc] = ftell(fh) - 1;
            fc++;
        }
    }
    printf("Func starts found count: %d\n", fc);

    // Back to the start
    if(feof(fh)) fseek(fh, 0, SEEK_SET);


    for(long i = 0;i < fc;i++) {
        fseek(fh, fp[i], SEEK_SET);
        fread(buf, 12, 1, fh);

        // Do we actually have a mul() function?
        if((strncmp("mul(", buf, 4) == 0)
            && verifyMul(buf, 12)) {
            struct pair v = {0,0};

            ma++;
            printf("%04ld (%d): %.12s\n", i, ma, buf);

            v = extract(buf+4, 12);

            if(en) {
                tb += mul(v);
            }

            ta += mul(v);
        }

        // See if we want to enable the next incoming mul functions
        if((strncmp("do()", buf, 4) == 0)) {
            puts("mul() enabled");

            printf("%04ld: %.4s\n", i, buf);

            en = 1;
        } else if(strncmp("don't()", buf, 7) == 0) {

            puts("mul() disabled");

            printf("%04ld: %.7s\n", i, buf);
            en = 0;
        }
    }

    printf("Func mul() found count: %d\n", ma);
    printf("Solution A: %d\n", ta);
    printf("Solution B: %d\n", tb);

    fclose(fh);

    return 0;
}