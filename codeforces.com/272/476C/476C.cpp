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


int main()
{
    ios::sync_with_stdio(false);

    ll a, b;
    cin >> a >> b;

    ll p1  = (b * (b - 1) / 2) % MOD;
    ll p21 = (a * (a + 1) / 2) % MOD;
       p21 = (p21 * b) % MOD;
    ll p2  = (p21 + a) % MOD;
    ll ans = (p1 * p2) % MOD;


    cout << ans << endl;

    return 0;
}