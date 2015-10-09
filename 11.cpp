#include <iostream>

using namespace std;

struct mat                                      //  matrix for Fibonacci numbers: a = F(1)
{
    int a, b, c, d;
    const mat operator* (const mat& mn) const {
        int a1 = a * mn.a + b * mn.c;
        int b1 = a * mn.b + b * mn.d;
        int c1 = c * mn.a + d * mn.c;
        int d1 = c * mn.b + d * mn.d;
        return mat{a1, b1, c1, d1};
    }
};

const mat start = mat{1, 1, 1, 0};

mat pow(int n)
{
    if (n == 1)
    {
        return start;
    }

    if (n % 2 == 1)
    {
        return pow(n - 1) * start;
    }

    if (n % 2 == 0)
    {
        mat _pw = pow(n / 2);
        return _pw * _pw;
    }
}

int main()
{

    int n;
    cin >> n;
    mat F = pow(n);
    cout << F.a;

    return 0;
}
