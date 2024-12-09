#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LIMIT 3
#define BOOLSTR(s) s ? "True" : "False"

int cCount(const char *s, char n) {
    int c = 0;

    // Assumes null terminated
    for(const char *p1 = s;*p1 != '\0';p1++)
        if(*p1 == n) c++;

    return c;
}

int checkDiff(int a, int b) {
    return (b-a) <= LIMIT && (b-a) >= -LIMIT && (b-a) != 0;
}

int sgn(int v) {
    return (0 < v) - (v < 0);
}

int main() {
    // the variables
    FILE *fh = NULL;

    int f = 0;
    int sc = 0;
    int sc2 = 0;
    char buf[1024];
    int nums[8];
    long int n1 = 0;
    long int n2 = 0;

    if((fh = fopen("test", "rb")) == NULL)
        return -1;

    while(fgets(buf, sizeof(buf), fh)) {
        const char *p = buf;
        int c = cCount(buf, ' ');
        long int pv = 0;

        puts(buf);

        f = 0;
        for(;;) {
            char *next;

            if(c > 0) {
                // Let's get our two numbers shall we?
                n1 = strtol(p, &next, 10);
                n2 = strtol(next, NULL, 10);
            }

            // Cludgy as hell, but makes sure we do
            // not calculate one too many
            if(c == 0) {
                printf("Was it safe? %s\n", BOOLSTR(!f));
                if(!f)  {
                    puts("SAFE");
                    sc++;
                }
                break;
            }

            // Are we increasing/decreasing consistently?
            if(pv && (sgn(pv) != sgn(n2-n1)))
                f = 1;

            if(next != p)
            {
                c--;
                p = next;
            }
            else
                break;

            pv = n2 - n1;

            printf("%ld - %ld = %ld (%s)\n", n2, n1, (n2-n1),
                BOOLSTR(checkDiff(n2,n1)));

            if(!checkDiff(n2, n1) && f != 1)
                f = 1;
        }

        putchar('\n');
    }

    printf("Amount of safe: %d\n", sc);

    fclose(fh);

    return 0;
}