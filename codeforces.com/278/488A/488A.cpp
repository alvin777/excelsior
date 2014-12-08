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


bool contains(ll num) {
    if (num < 0) {
        num = -num;
    }

    while (num > 0) {
        if (num % 10 == 8) return true;
        num /= 10;
    }

    return false;
}

int main()
{
    ios::sync_with_stdio(false);

    ll a;
    cin >> a;

    for (ll c = a + 1; c < a + 17; ++c) {
        if (contains(c)) {
            cout << c - a << endl;
            break;
        }
    }

    return 0;
}
