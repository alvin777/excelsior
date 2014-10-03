#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <fstream>

using namespace std;
typedef long long ll;
typedef vector<int> vi; 

#define REP(k,a) for(int k=0; k < (a); ++k)
#define FOR(i,a,b) for(int i=a; i < (b); ++i)
#define ALL(a) begin(a), end(a)
#define D(a) cout << #a ": " << a << endl;

const int INF = 1e9;
const int MAX_COUNT = 201;
const int MAX_DIVISOR = 21;
const int MAX_ALLOWED = 11;

template<typename T> 
void print_array(T array, int first, int last, const string& label = "") {
    if (label.size()) {
        cout << label << ": ";
    }

    for (int i = first; i < last; i++) {
        cout << array[i] << " ";
    }

    cout << endl;
}

int n;
ll data[MAX_COUNT];
ll dp[MAX_COUNT][MAX_ALLOWED][MAX_DIVISOR];


ll llmod(ll a, ll b)
{
    ll c;

    if(a < b)
    {
        a = -a;
        c = a % b;
        c = b-c;
    }
    else
        c = a;
    return c % b;
}

ll rec(int item, int left, int mod, int d) {

    int offset = item*4;

    // cout << string(offset, ' ') << "rec, item: " << item << ", data[i]: " << data[item] << ", left: " << left << ", mod: " << mod << ", d: " << d << endl;

    if (item == n && left > 0) {
        return 0;
    }

    if (left == 0) {
        return mod == 0;
    }

    // if (item >= n) {
    //     return 0;
    // }

    // if (left > n - item) {
    //     return 0;
    // }

    if (dp[item][left][mod] >= 0) {
        // cout << string(offset, ' ') << "cache hit: " << dp[item][left][mod] << endl;
        return dp[item][left][mod];
    }

    dp[item][left][mod] = rec(item+1, left, mod, d) + 
                          rec(item+1, left-1, llmod(mod + data[item], d), d);

    // cout << string(offset, ' ') << "result: " << dp[item][left][mod] << endl;

    return dp[item][left][mod];
}

int main()
{
    ios::sync_with_stdio(false);

    int q, ii = 1;
    cin >> n >> q;

    while (n > 0 && q > 0) {
        REP(i, n) {
            cin >> data[i];
        }

        cout << "SET " << ii++ << ":" << endl;

        // print_array(data, 0, n, "data");

        REP(qq, q) {
            int d, m;
            cin >> d >> m;

            fill_n(&dp[0][0][0], sizeof(dp)/sizeof(dp[0][0][0]), -1);

            ll ans = rec(0, m, 0, d);
            cout << "QUERY " << qq + 1 << ": " << ans << endl;
        }

        cin >> n >> q;
    }

    return 0;
}