#include <iostream>
#include <algorithm>

using namespace std;

int n;

int main()
{
    freopen("gcdxor.in", "r", stdin);
    freopen("gcdxor.out", "w", stdout);
    ios::sync_with_stdio(false);

    cin >> n;

    int ans = 0;
    for (int c = 1; c <= n; ++c)
    {
        for (int a = 2 * c; a <= n; a += c)
        {
            if ( (a ^ c) == a - c )
                ++ans;
        }
    }
    cout << ans << endl;
    return 0;
}