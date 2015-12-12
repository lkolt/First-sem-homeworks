#include <iostream>
#include <cmath>

using namespace std;

long double f_pow(long double a, int n)
{
    if (n == 0)
    {
        return 1;
    }

    if (n % 2 == 1)
    }
        return f_pow(a, n - 1) * a;          // pow(i, n) = pow(i, n - 1) * i
    }

    long double p_ans = f_pow(a, n / 2);
    return p_ans * p_ans;                    // pow(i, n) = pow(i, n / 2) * pow(i, n / 2)
}


int main()
{

    long double a;
    int n;
    cin >> a >> n;
    long double ans = f_pow(a, abs(n));
    if (n < 0)
    {
        ans = 1 / ans;
    }
    
    cout << ans;

    return 0;
}
