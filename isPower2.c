#include <stdio.h>
#include <stdlib.h>

int isPower2(int x)
{
	int xmone = x + ~0;
    int _x = (x & xmone);      // 0 for 2^n
    return  (1 & !_x) & !(!x) & ~(x >> 31);
}

int main()
{
    int x;
    scanf("%d", &x);
    printf("%d", isPower2(x));

    return 0;
}
