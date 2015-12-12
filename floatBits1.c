#include <stdio.h>
#include <stdlib.h>

union float_to_int {
    int my_int;
    float my_float;
};

void printM(int M, int i) // print M
{
    if (i > 22)
        return;
    printM(M >> 1, i + 1);
    printf("%d", M & 1);
    return;
}

void floatBits1(float myf) // (-1)^(sign) * 1.M * 2^(E - 127);
{
    union float_to_int conversion;
    conversion.my_float = myf;

    int sign = !!(conversion.my_int >> 31);

    int M = conversion.my_int;
    M = M << 8;
    M = M & ~(1 << 31);
    M = M >> 8;

    int E = conversion.my_int & ~(1 << 31);
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

int main()
{
    float myf;
    scanf("%f", &myf);
    floatBits1(myf);
    return 0;
}
