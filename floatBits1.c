#include <stdio.h>
#include <stdlib.h>

union float_to_int {
    int my_int;
    float my_float;
};

int floatBits1(float myf)
{
    union float_to_int conversion;
    conversion.my_float = myf;
    return conversion.my_int;
}

int main()
{
    float myf;
    scanf("%f", &myf);
    printf("%d", floatBits1(myf));
    return 0;
}
