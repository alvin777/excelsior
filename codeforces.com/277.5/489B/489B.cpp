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
const int MAX_COUNT = 101;
const int MOD = 1e9 + 7;


// #define ONLINE_JUDGE

#ifndef ONLINE_JUDGE 

///// trace helpers /////



#else
# define PR(...)
#endif


int n, m;
int men[MAX_COUNT];
int women[MAX_COUNT];


int main()
{
    ios::sync_with_stdio(false);

    cin >> n;
    REP(i, n) {
        cin >> men[i];
    }

    cin >> m;
    REP(i, m) {
        cin >> women[i];
    }

    sort(men, men+n);
    sort(women, women+m);

    int i = 0, j = 0;
    int ans = 0;
    while (i < n && j < m) {
        if (abs(men[i] - women[j]) <= 1) {
            ans++;
            i++;
            j++;
        } else if (men[i] < women[j]) {
            i++;
        } else {
            j++;
        }
    }

    cout << ans << endl;

    return 0;
}
