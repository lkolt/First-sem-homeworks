#include <stdio.h>
#include <stdlib.h>

int getByte(int x, int n)
{
    int res = ((x >> (n << 3)) & 255);
    return res;
}

int main()
{
    int x, n;
    scanf("%d %d", &x, &n);
    printf("%d", getByte(x, n));
    return 0;
}
