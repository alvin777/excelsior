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
const int MAX_COUNT = 1e3+1;
const int MOD = 1e9 + 7;


// #define ONLINE_JUDGE

#ifndef ONLINE_JUDGE 

///// trace helpers /////



#else
# define PR(...)
#endif

struct point_t {
    ll x, y;
};

int n;
point_t data[MAX_COUNT];

int main()
{
    ios::sync_with_stdio(false);

    cin >> n;

    cin >> data[0].x >> data[0].y;

    point_t min_point{data[0].x, data[0].y};
    point_t max_point{data[0].x, data[0].y};

    FOR(i, 1, n) {
        cin >> data[i].x >> data[i].y;
        min_point.x = min(min_point.x, data[i].x);
        min_point.y = min(min_point.y, data[i].y);
        
        max_point.x = max(max_point.x, data[i].x);
        max_point.y = max(max_point.y, data[i].y);
    }

    ll side = max(abs(max_point.x - min_point.x),
                  abs(max_point.y - min_point.y));
    side = max(side, 1LL);

    cout << side*side << endl;

    return 0;
}
