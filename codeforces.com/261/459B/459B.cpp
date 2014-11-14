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
const int MAX_COUNT = 2e5;
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

    cin >> n;
    REP(i, n) {
        cin >> data[i];
    }

    auto pair = minmax_element(data, data+n);
    ll min_count = count(data, data+n, *pair.first);
    ll max_count = count(data, data+n, *pair.second);

    ll ans_count = (*pair.second != *pair.first) ? 
                    min_count * max_count : 
                    max_count * (max_count - 1) / 2;

    cout << (*pair.second - *pair.first) << " " <<  ans_count << endl;

    return 0;
}
