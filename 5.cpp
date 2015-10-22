#include <iostream>

using namespace std;

const int maxn = 1000; // maximal number of elements

int ar[maxn];          // array with elements
int n;                 // number of elements

bool check()           // check function
{
    for (int i = 0; i < n / 2; i++)
    {
        if (ar[i] != ar[n - i - 1])
        {
            return false;
        }
    }
    return true;
}

int main()
{

    cin >> n;
    for (int i = 0; i < n; i++) 
    {
        cin >> ar[i];
    }

    if (check())
    {
        cout << "YES";
    }
    else
    {
        cout << "NO";
    }


    return 0;
}
