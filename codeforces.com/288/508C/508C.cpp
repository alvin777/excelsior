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
const int MAX_COUNT = 1000;
const int MOD = 1e9 + 7;


// #define ONLINE_JUDGE

#ifndef ONLINE_JUDGE 

///// trace helpers /////



#else
# define PR(...)
#endif


int m, t, r;
int data[MAX_COUNT];
int arr[MAX_COUNT];

void add_candle(int pos) {

    for (int i = 0; i < t; i++) {
        if (pos + i < 0 || pos + i >= MAX_COUNT) continue;
        data[pos + i] += 1;
    }
}

int main()
{
    ios::sync_with_stdio(false);

    cin >> m >> t >> r;

    if (t <= r) {
        cout << -1 << endl;
        return 0;
    }

    int ans = 0;
    REP(i, m) {
        int k;
        cin >> k;

        int j = k;
        while (data[k] < r) {
            add_candle(j--);
            ans++;
        }
    }

    cout << ans << endl;

    return 0;
}
