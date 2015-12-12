#include <stdio.h>
#include <stdlib.h>


struct bit
{
    int m:23;
    int e:8;
    int s:1;
};

union float_to_int
{
    float f;
    struct bit b;
};

void printM(int M, int i) // print M
{
    if (i > 22)
        return;
    printM(M >> 1, i + 1);
    printf("%d", M & 1);
    return;
}

void floatBits2(float f)
{
    union float_to_int ftn;
    ftn.f = f;

    int sign = ftn.b.s;
    int M = ftn.b.m;
    int E = ftn.b.e;

    if (E == 255 && M > 0)                  // Not a Number
    {
        printf("NaN");
        return;
    }

    if (E == 255 && M == 0)                 // inf or -inf
    {
        if (sign == 1)
            printf("-inf");
        else
            printf("inf");
        return;
    }

    printf("(-1)^(%d) * ", sign);                  //print solution
    printf("1.");
    printM(M, 0);
    printf(" * 2^(%d - 127)", E);

    return;
}

int main()
{
    float f;
    scanf("%f", &f);
    floatBits2(f);
    return 0;
}
