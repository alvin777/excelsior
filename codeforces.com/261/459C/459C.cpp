#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;
typedef long long ll;
typedef vector<int> vi; 

#define REP(k,a) for(int k=0; k < (a); ++k)
#define FOR(i,a,b) for(int i=a; i < (b); ++i)
#define ALL(a) begin(a), end(a)
#define COUNT(a) (sizeof(a)/sizeof(a[0]))

const int INF = 1e9;
const int MAX_COUNT = 1e5;
const int MOD = 1e9 + 7;


// #define ONLINE_JUDGE

#ifndef ONLINE_JUDGE 

///// trace helpers /////



#else
# define PR(...)
#endif


int main()
{
    ios::sync_with_stdio(false);

    int n, k, d;
    cin >> n >> k >> d;

    if (d < ceil(log(n)/log(k))) {
        cout << -1 << endl;
        return 0;
    }

    // int period = (n % k) ? n/k + 1 : n/k;
    ll period = 1;
    REP(i, d) {
        REP(j, n) {
            cout << (j/period) % k + 1 << " ";
        }
        cout << endl;

        period *= k;
        period %= 1007;
        // period = max(period, 1);
    }

    return 0;
}
