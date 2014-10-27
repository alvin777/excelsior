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
const int MAX_COUNT = 5001;
const int MOD = 1e9 + 7;


// #define ONLINE_JUDGE

#ifndef ONLINE_JUDGE 

///// trace helpers /////



#else
# define PR(...)
#endif

// typedef tuple<int, int> elem_t;
struct elem_t {
    int a;
    int b;
};

bool operator< (const elem_t& e1, const elem_t& e2) {
    if (e1.a == e2.a) {
        return e1.b < e2.b;
    } 

    return e1.a < e2.a;
}

int n;
elem_t data[MAX_COUNT];


int main()
{
    ios::sync_with_stdio(false);

    cin >> n;
    REP(i, n) {
        cin >> data[i].a >> data[i].b;
    }

    sort(data, data+n);

    int ans = data[0].b;

    REP(i, n) {
        if (data[i].b >= ans) {
            ans = data[i].b;
        } else {
            ans = data[i].a;
        }
    }

    cout << ans << endl;

    return 0;
}
