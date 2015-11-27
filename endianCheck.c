#include <stdio.h>
#include <stdlib.h>

union check{
    int x;
    char bytes[sizeof(int)];
};

int endianCheck()
{
    union check ch;
    ch.x = 1;
    return ch.bytes[0];
}


int main()
{
    printf("%d", endianCheck());
    return 0;
}
