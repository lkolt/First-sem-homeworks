//  Print primes in [1..n]

#include <iostream>

using namespace std;

const int maxn = (int)(1e6); // maximal n

bool aprime[maxn];           // false == prime; true == not prime

int main()
{

    int n;
    cin >> n;

    aprime[0] = aprime[1] = true; // initial

    for (int i = 2; i <= n; i++)
    {
        if (aprime[i] == false)   // i is prime
        {
            for (int j = i * i; j <= n; j += i)
            {
                aprime[j] = true;
            }
            cout << i << " ";     // print i
        }
    }

    return 0;
}
