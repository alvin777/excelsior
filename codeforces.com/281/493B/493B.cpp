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
const int MAX_COUNT = 2e5+1;
const int MOD = 1e9 + 7;


// #define ONLINE_JUDGE

#ifndef ONLINE_JUDGE 

///// trace helpers /////



#else
# define PR(...)
#endif


int n;

vi first;
vi second;

int main()
{
    ios::sync_with_stdio(false);

    cin >> n;
    int last = 0;
    ll first_sum = 0;
    ll second_sum = 0;
    REP(i, n) {
        int x;
        cin >> x;

        if (x > 0) {
            first.push_back(x);
            first_sum += x;
        } else {
            second.push_back(-x);
            second_sum += -x;
        }
        last = x;
    }

    if (first_sum != second_sum) {
        cout << (first_sum > second_sum ? "first" : "second") << endl;
    } else if (first.size() == second.size() && equal(ALL(first), second.begin())) {
        cout << (last > 0 ? "first" : "second") << endl;
    } else {
        cout << (lexicographical_compare(ALL(first), ALL(second)) ? "second" : "first") << endl;
    }

    return 0;
}
