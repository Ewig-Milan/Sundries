#define FILE(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout);
#include <iostream>
#include <cstring>
using namespace std;
int N, X, M;
int DP[2][105][105 * 105];
int Fact[200005], InvFact[200005];
void Read()
{
    cin >> N >> X >> M;

}
int powerLog(int n, int p)
{
    int sol = 1;
    while(p)
    {
        if(p % 2 == 1)
            sol = (1LL * sol * n) % M;
        p /= 2;
        n = (1LL * n * n) % M;
    }
    return sol;
}


void precalcFact()
{
    Fact[0] = 1;
    InvFact[0] = 1;
    for(int i = 1; i <= N + X; i++)
    {
        Fact[i] = (1LL * Fact[i - 1] * i) % M;
        InvFact[i] = powerLog(Fact[i], M - 2);
    }

}
int comb(int n, int k)
{
    return (1LL * ((1LL * Fact[n] * InvFact[n - k]) % M) * InvFact[k]) % M;
}
inline void Add(int& x, int y)
{
    x += y;
    if(x >= M)
        x -= M;
}
void precalcDP()
{
    int ind = 0;
    DP[ind][0][0] = 1;
    for(int i = 1; i < N; i++, ind = 1 - ind)
    {
        for(int j = 0; j < i; j++)
            for(int k = 0; k <= i * i; k++)
            {
                if(DP[ind][j][k] == 0)
                continue;
                Add(DP[1 - ind][j + 2][k + 2 * i + 2], (1LL * (i - 1 - j) * DP[ind][j][k]) % M);
                Add(DP[1 - ind][j + 1][k + i + 1], (2LL * (i - j) * DP[ind][j][k]) % M);
                Add(DP[1 - ind][j][k], ((1LL * (i + 1 - j) * DP[ind][j][k]) % M));
                DP[ind][j][k] = 0;
            }
    }
    int ans = 0;
    --X;
    for(int i = 0; i <= min(X, N * N); i++)
    {
        int ways = DP[ind][N - 1][i];
        int c = X - i;
        c = comb(c + N, N);
        Add(ans, (1LL * c * ways) % M);
    }
    cout << ans << "\n";
}
int main()
{
    FILE("build");
    Read();
    precalcFact();
    precalcDP();

    return 0;
}