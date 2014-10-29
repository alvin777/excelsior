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
#define COUNT2(a) (sizeof(a)/sizeof(a[0][0]))

const int INF = 1e9;
const int MAX_COUNT = 1e5;
const int MOD = 1e9 + 7;


// #define ONLINE_JUDGE

#ifndef ONLINE_JUDGE 

///// trace helpers /////



#else
# define PR(...)
#endif


int n;
int b[MAX_COUNT];

int memo[MAX_COUNT][2];

int solve(int i, bool prev) {

    if (i >= n) return 0;

    if (memo[i][prev] >= 0) return memo[i][prev];

    int sum_1 = solve(i+1, false);
    int sum_b = solve(i+1, true);

    if (i == 0) {
        return max(sum_1, sum_b);
    }

    int prev_value = prev ? b[i-1] : 1;
    return memo[i][prev] = max(sum_1 + abs(prev_value - 1), 
                               sum_b + abs(prev_value - b[i]));
}

int main()
{
    ios::sync_with_stdio(false);

    int tc;
    cin >> tc;
    
    REP(t, tc) {
        cin >> n;
        REP(i, n) {
            cin >> b[i];
        }
        
        fill_n(&memo[0][0], COUNT2(memo), -1);
        cout << solve(0, 0) << endl;
    }

    return 0;
}