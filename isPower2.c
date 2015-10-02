#include <stdio.h>
#include <stdlib.h>

int isPower2(int x)
{
    int _x = (x & (x + ~0));
    return (1 & !_x) & !(!x);
}

int main()
{
    int x;
    scanf("%d", &x);
    printf("%d", isPower2(x));

    return 0;
}
