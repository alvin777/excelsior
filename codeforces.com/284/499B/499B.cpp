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


map<string, string> dict;

int main()
{
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    REP(i, m) {
        string k, v;
        cin >> k >> v;
        dict[k] = v;
    }

    REP(i, n) {
        string w;
        cin >> w;
        if (w.length() <= dict[w].length()) {
            cout << w << " ";
        } else {
            cout << dict[w] << " ";
        }
    }

    cout << endl;

    return 0;
}
