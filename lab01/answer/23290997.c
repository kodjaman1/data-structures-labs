#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 500
#define MAX_FLIGHTNO 16

typedef struct {
    char flightNo[MAX_FLIGHTNO]; /* Örn: "TK217" */
    int chainNo;
    int  schedDepMin;            /* 00:00'dan itibaren dakika (kalkış) */
} Flight;


static int parseTime(const char *hhmm) {
    int h, m;
    if (sscanf(hhmm, "%d:%d", &h, &m) != 2) return -1;
    if (h < 0 || h > 23 || m < 0 || m > 59) return -1;
    return h * 60 + m;
}

static void formatTime(int minutes, char out[6]) {
    if (minutes < 0) minutes = 0;
    int h = (minutes / 60) % 24, m = minutes % 60;
    sprintf(out, "%02d:%02d", h, m);
}

static int cmpByDepThenFlightNo(const void *A, const void *B) {
    const Flight *a = (const Flight*)A, *b = (const Flight*)B;
    if (a->schedDepMin != b->schedDepMin) return a->schedDepMin - b->schedDepMin;
    return strcmp(a->flightNo, b->flightNo); /* eşit saatlerde deterministik sıra */
}


int main(void) {
    int N;
    if (scanf("%d", &N) != 1 || N <= 0 || N > MAXN) {
        printf("ERROR: N must be 1..%d\n", MAXN);
        return 1;
    }

    Flight f[MAXN];

    for (int i = 0; i < N; i++) {
        char t[6];
        int chain;
        if (scanf("%5s %d %5s", f[i].flightNo, &chain, t) != 3) {
            printf("ERROR: bad input at line %d\n", i+1);
            return 1;
        }
        f[i].schedDepMin = parseTime(t);
        f[i].chainNo = chain;

        if (f[i].chainNo < 1 || f[i].chainNo > 3){
            printf("ERROR: bad chain no at line %d\n", i+1);
        }

        if (f[i].schedDepMin < 0) {
            printf("ERROR: bad time at line %d\n", i+1);
            return 1;
        }
    }

    qsort(f, N, sizeof(Flight), cmpByDepThenFlightNo);

    int count1 = 0;
    int count2 = 0;
    int count3 = 0;

    Flight chain1[N];
    Flight chain2[N];
    Flight chain3[N];

    for (int i = 0; i < N; i++) {
        switch (f[i].chainNo) {
            case 1:
            chain1[count1] = f[i];
            count1++;
            break;

            case 2:
            chain2[count2] = f[i];
            count2++;

            break;

            case 3:
            chain3[count3] = f[i];
            count3++;
            break;
        }
    }

    char badNo[6];
    int badChain;
    int badMinute;
    scanf("%d %5s %2d", &badChain, badNo, &badMinute);

    int shit = 0;
    switch (badChain) {
        case 1:
            for (int i = 0; i<count1; i++){
                if (strcmp(chain1[i].flightNo, badNo)==0){
                   chain1[i].schedDepMin += badMinute;
                   shit=1;
                   continue;
                }
                if (shit==1){
                    chain1[i].schedDepMin += badMinute;
                }
            }
        break;

        case 2:
        for (int i = 0; i<count2; i++){
                if (strcmp(chain2[i].flightNo, badNo)==0){
                   chain2[i].schedDepMin += badMinute;
                   shit = 1;
                   continue;
                }
                if (shit==1){
                    chain2[i].schedDepMin += badMinute;
                }
            }
        break;

        case 3:
            for (int i = 0; i<count3; i++){
                if (strcmp(chain3[i].flightNo, badNo)==0){
                   chain3[i].schedDepMin += badMinute;
                   shit = 1;
                   continue;
                }
                if (shit==1){
                    chain3[i].schedDepMin += badMinute;
                }
            }
        break;
    }


    for (int i = 0; i<count1; i++) {
        char hhmm[6];
        if (chain1[i].schedDepMin >= 1440){
            chain1[i].schedDepMin %= 1440;
        }
        formatTime(chain1[i].schedDepMin, hhmm);
        printf("%s %d %s\n", chain1[i].flightNo, chain1[i].chainNo, hhmm);
    }

        for (int i = 0; i<count2; i++) {
        char hhmm[6];
        if (chain2[i].schedDepMin >= 1440){
            chain2[i].schedDepMin %= 1440;
        }
        formatTime(chain2[i].schedDepMin, hhmm);
        printf("%s %d %s\n", chain2[i].flightNo, chain2[i].chainNo, hhmm);
    }

        for (int i = 0; i<count3; i++) {
        char hhmm[6];
        if (chain3[i].schedDepMin >= 1440){
            chain3[i].schedDepMin %= 1440;
        }
        formatTime(chain3[i].schedDepMin, hhmm);
        printf("%s %d %s\n", chain3[i].flightNo, chain3[i].chainNo, hhmm);
    }



    return 0;
}
