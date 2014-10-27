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
const int MAX_COUNT = 6;
const int MOD = 1e9 + 7;


// #define ONLINE_JUDGE

#ifndef ONLINE_JUDGE 

///// trace helpers /////



#else
# define PR(...)
#endif


int n;
int data[MAX_COUNT];


int main()
{
    ios::sync_with_stdio(false);

    int sum = 0;
    REP(i, 5) {
        int v;
        cin >> v;
        sum += v;
    }

    if (sum > 0 && (sum % 5 == 0)) {
        cout << sum/5 << endl;
    } else {
        cout << -1 << endl;
    }

    return 0;
}