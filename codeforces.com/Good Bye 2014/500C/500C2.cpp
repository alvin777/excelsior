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


int n, m;
int w[MAX_COUNT];
int r[MAX_COUNT];
int order[MAX_COUNT];
bool visited[MAX_COUNT];


int main()
{
    ios::sync_with_stdio(false);

    cin >> n >> m;
    REP(i, n) {
        cin >> w[i];
    }

    REP(i, m) {
        cin >> r[i];
        r[i]--;
    }

    int j = 0;
    REP(i, m) {
        if (!visited[r[i]]) {
            order[j++] = r[i];
            visited[r[i]] = true;
        }
    }

    // calc weight
    ll weight = 0;
    REP(i, m) {
        REP(j, n) {
            if (r[i] == order[j]) {
                for (int k = j; k > 0; k--) {
                    order[k] = order[k-1];
                    weight += w[order[k]];
                }
                order[0] = r[i];
                break;
            }
        }
    }

    cout << weight << endl;

    return 0;
}