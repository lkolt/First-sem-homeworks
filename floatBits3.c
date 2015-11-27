#include <stdio.h>
#include <stdlib.h>

void printM(int M, int i) // print M
{
    if (i > 22)
        return;
    printM(M >> 1, i + 1);
    printf("%d", M & 1);
    return;
}

void solve(int my_int)
{
    int sign = !!(my_int >> 31);

    int M = my_int;
    M = M << 8;
    M = M & ~(1 << 31);
    M = M >> 8;

    int E = my_int & ~(1 << 31);
    E = E >> 23;

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

void floatBits3(float f)
{
    float *it = &f;
    int *in = (int*)it;
    solve(*in);
    return;
}

int main()
{
    float f;
    scanf("%f", &f);
    floatBits3(f);
    return 0;
}
