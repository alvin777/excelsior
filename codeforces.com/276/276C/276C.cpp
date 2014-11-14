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

void set_bits(ll& number, int from, int to) {
    for (int pos = from; pos <= to; ++pos) {
        number |= (1LL << pos);
    }
}

bool all_bits_set(const ll& number, int from, int to) {
    for (int pos = from; pos <= to; ++pos) {
        if ((number & (1LL << pos)) == 0) {
            return false;
        }
    }

    return true;
}

ll solve(ll from, ll to) {
    ll ans = 0;
    for (int i = 63; i >= 0; --i) {
        ll bit = 1LL << i;

        if (i > 0 && (to & bit) != (from & bit)) {
            set_bits(ans, 0, all_bits_set(to, 0, i) ? i : i-1);
            break;
        }
        ans |= (to & bit);
    }

    return ans;
}

int main()
{
    ios::sync_with_stdio(false);

    int n;
    cin >> n;
    REP(i, n) {
        ll l, r;
        cin >> l >> r;

        cout << solve(l, r) << endl;
    }

    return 0;
}
