#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <iomanip>

using namespace std;
typedef long long ll;
typedef vector<int> vi; 

#define REP(k,a) for(int k=0; k < (a); ++k)
#define FOR(i,a,b) for(int i=a; i < (b); ++i)
#define ALL(a) begin(a), end(a)
#define COUNT(a) (sizeof(a)/sizeof(a[0]))

const int INF = 1e9;
const int MAX_COUNT = 1e3;
const int MOD = 1e9 + 7;


// #define ONLINE_JUDGE

#ifndef ONLINE_JUDGE 

///// trace helpers /////



#else
# define PR(...)
#endif


int g[MAX_COUNT];
int d[MAX_COUNT];


int main()
{
    ios::sync_with_stdio(false);

    auto s = 5;

    int tc;
    cin >> tc;
    REP(t, tc) {
        int n, l;
        cin >> n >> l;
        
        REP(i, n) {
            cin >> g[i];
        }

        REP(i, n) {
            cin >> d[i];
        }

        sort(g, g + n);
        sort(d, d + n);
        reverse(d, d+n);

        int g_sum = accumulate(g, g+l, 0);
        int d_sum = accumulate(d, d+l, 0);

        cout << ( g_sum > d_sum ? "YES" : "NO") << endl;
    }


    return 0;
}
