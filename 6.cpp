#include <iostream>

using namespace std;

void erase_spaces(string &s)
{
    int i = 0;
    while (i < (int)s.size())
    {
        if (s[i] == ' ')
        {
            s.erase(i, 1);
        }
        else
        {
            i++;
        }
    }
    return;
}

void low_reg(string &s)
{
    for (int i = 0; i < (int)s.size(); i++)
    {
        if (s[i] >= 'A' && s[i] <= 'Z')
        {
            s[i] = s[i] - 'A' + 'a';
        }
    }
    return;
}

bool check(string &s)
{
    int n = s.size();
    for (int i = 0; i < n / 2; i++)
    {
        if (s[i] != s[n - i - 1])
        {
            return false;
        }
    }
    return true;
}

int main()
{

    string s; // input
    getline(cin, s);

    erase_spaces(s);

    low_reg(s);

    if (check(s))
    {
        cout << "YES";
    }
    else
    {
        cout << "NO";
    }

    return 0;
}
