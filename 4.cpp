#include <iostream>

using namespace std;

int main()
{

    int n;
    cin >> n;    // number of element
    int ans = 0; // answer
    for (int i = 0; i < n; i++){
        int cur; // cur element
        cin >> cur;
        if (cur == 0)
            ans++;
    }

    cout << ans; // print answer

    return 0;
}
