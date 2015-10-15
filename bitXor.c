#include <stdio.h>
#include <stdlib.h>

int BitXor(int x, int y) // (((~x) & y)|(x & (~y)))
{
    int ax = ~x;
    int ay = ~y;
    int res1 = ax & y;
    int res2 = x & ay;
    int ares1 = ~res1;
    int ares2 = ~res2;
    int ares = ares1 & ares2;
    int res = ~ares;
    return res;
}

int main()
{

    int x, y;
    scanf("%d %d", &x, &y);
    printf("%d", BitXor(x, y));
    return 0;
}
