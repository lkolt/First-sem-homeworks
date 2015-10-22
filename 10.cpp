// find the number of occurrences of string S1 in a string S as substring

//--------------------- includes

#include <iostream>

using namespace std;

//--------------------- const

const int maxn = (int)(1e5);         // maximal length of S
const long long int MOD = (1e9) + 7; // mod for hash function
const long long P = 271;             // base for hash function

//--------------------- init

long long int hs[maxn];
long long int _pow[maxn];
long long int h_ss;
string s, s1;

//--------------------- functions

long long int get_hash(int l, int r) // return polinomial hash of S in [l..r]
{
    if (l == 0)
    {
        return hs[r];
    }
    return ((hs[r] - hs[l - 1] * _pow[r - (l - 1)]) % MOD + MOD) % MOD;
}

void init(int n, int m)
{
    _pow[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        _pow[i] = (_pow[i - 1] * P) % MOD;             // find power(p, 1..n) mod MOD
    }

    hs[0] = s[0];
    for (int i = 1; i < n; i++)
    {
        hs[i] = (hs[i - 1] * P + s[i]) % MOD;          // find polinomial hash of S
    }

    h_ss = 0;
    for (int i = 0; i < m; i++)
    {
        h_ss = (h_ss * P + s1[i]) % MOD;               // find hash of S1
    }

    return;
}

//--------------------- main

int main()
{
    cin >> s >> s1;
    int n = s.size();
    int m = s1.size();

    init(n, m);

    int ans = 0;
    for (int i = 0; i < n - m + 1; i++)
    {
        if (get_hash(i, i + m - 1) == h_ss)     // if hash s [i..i + m - 1] == hash s1 [0..m - 1] then inc ans
        {
            ans++;
        }
    }

    cout << ans;

    return 0;
}
