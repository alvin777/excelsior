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
#define COUNT(a) (sizeof(a)/sizeof(a[0]))

const int INF = 1e9;
const int MAX_COUNT = 30001;
const int MOD = 1e9 + 7;

int n, d;
int data[MAX_COUNT];

int dp[MAX_COUNT][500];
bool used[MAX_COUNT][500];

int solve(int i, int j) {

    if (i < 0 || i >= MAX_COUNT) return 0;

    // int jj = j - d + 250;
    int jj = j + 250;
    if (used[i][jj]) return dp[i][jj];
    // if (dp[i][jj] > 0) return dp[i][jj];
    used[i][jj] = true;

    if (j == 1) {
        return dp[i][jj] = data[i] + max(solve(i + j, j), solve(i + j + 1, j + 1));
    }
    return dp[i][jj] = data[i] + max({solve(i + j - 1, j - 1), solve(i + j, j), solve(i + j + 1, j + 1)});
}

int main()
{
    ios::sync_with_stdio(false);

    cin >> n >> d;
    REP(i, n) {
        int ind;
        cin >> ind;
        data[ind]++;
    }

    // fill(&dp[0][0], &dp[MAX_COUNT][500], -1);
    cout << solve(d, d) << endl;

    return 0;
}
