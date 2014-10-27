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
const int MAX_COUNT = 1e5;
const int MOD = 1e9 + 7;


// #define ONLINE_JUDGE

#ifndef ONLINE_JUDGE 

///// trace helpers /////



#else
# define PR(...)
#endif


int n, m;

ll pairs(ll men) {
    return men * (men - 1) / 2;
}

int main()
{
    ios::sync_with_stdio(false);

    cin >> n >> m;

    // max
    ll max_count = pairs(n-m+1);

    int left = n % m;
    ll min_count = pairs(n/m + 1) * left + pairs(n/m) * (m - left);

    cout << min_count << " " << max_count << endl;

    return 0;
}