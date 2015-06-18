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
const int MAX_COUNT = 1001;
const int MOD = 1e9 + 7;


// #define ONLINE_JUDGE

#ifndef ONLINE_JUDGE 

///// trace helpers /////



#else
# define PR(...)
#endif


int n, m, k;
int data[MAX_COUNT][MAX_COUNT];

bool check(int x, int y) {
    return x > 0 && x < n &&
           y > 0 && y < m &&
           data[x][y] && 
           data[x+1][y] && 
           data[x][y+1] && 
           data[x+1][y+1];
}

int main()
{
    ios::sync_with_stdio(false);

    cin >> n >> m >> k;
    REP(i, k) {
        int x, y;
        cin >> x >> y;
        data[x][y] = 1;

        if (check(x - 1, y - 1) ||
            check(x,     y - 1) ||
            check(x - 1, y) ||
            check(x, y)) {

            cout << i + 1 << endl;
            return 0;
        }
    }

    cout << "0" << endl;

    return 0;
}
