#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>

using namespace std;
typedef long long ll;
typedef vector<int> vi; 

#define REP(k,a) for(int k=0; k < (a); ++k)
#define FOR(i,a,b) for(int i=a; i < (b); ++i)
#define ALL(a) begin(a), end(a)
#define D(a) cout << #a ": " << a << " ";
#define DE(a) cout << #a ": " << a << endl;
#define COUNT(a) (sizeof(a)/sizeof(a[0]))

const int INF = 1e9;
const int MAX_COUNT = 1e5;
const int MOD = 1e9 + 7;

// int dp[MAX_COUNT + 1];
// int run[MAX_COUNT + 1];
// int last = 0;

// int solve(int n, int k) {
//     dp[0] = 1;

//     FOR(i, last + 1, n+1) {
//         // DE(i);
//         dp[i] = (dp[i-1] + (i >= k ? dp[i-k] : 0)) % MOD;
//         run[i] = (run[i-1] + dp[i]) % MOD;
//     }

//     last = max(last, n);

//     return dp[n];
// }

int mem[MAX_COUNT+1];
int run[MAX_COUNT + 1];

int solve(int m, int k) {
    if (m < 0) return 0;
    if (m == 0) return 1;

    if (mem[m] > 0) return mem[m];

    mem[m] = (solve(m - 1, k) + solve(m - k, k)) % MOD;
    run[m] = (run[m-1] + mem[m]) % MOD;

    return mem[m];
}

int main()
{
    ios::sync_with_stdio(false);

    fill_n(mem, COUNT(mem), -1);

    int t, k;
    cin >> t >> k;

    REP(i, t) {
        int a, b;
        cin >> a >> b;

        solve(b, k);

        cout << (run[b] + (MOD - run[a-1])) % MOD << endl;
    }

    return 0;
}