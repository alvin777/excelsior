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
const int MAX_COUNT = 3e4 + 1;
const int MOD = 1e9 + 7;


// #define ONLINE_JUDGE

#ifndef ONLINE_JUDGE 

///// trace helpers /////



#else
# define PR(...)
#endif


int n, t;
int data[MAX_COUNT];

int main()
{
    ios::sync_with_stdio(false);

    cin >> n >> t;
    REP(i, n) {
        cin >> data[i + 1];
    }

    int v = 1;
    while (v <= n) {
        // cout << v << endl;
        if (v == t) {
            cout << "YES" << endl;
            return 0;
        }

        if (v == n) break;

        v += data[v];
    }

    cout << "NO" << endl;

    return 0;
}
