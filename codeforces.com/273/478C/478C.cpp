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

int main()
{
    ios::sync_with_stdio(false);

    int r, g, b;
    cin >> r >> g >> b;

    ll c[3] = {r, g, b};
    sort(ALL(c));

    ll sum = c[0] + c[1] + c[2];

    cout << (min(sum/3, c[0] + c[1])) << endl;

    return 0;
}