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
const int MAX_COUNT = 1e4+1;
const int MOD = 1e9 + 7;


// #define ONLINE_JUDGE

#ifndef ONLINE_JUDGE 

///// trace helpers /////



#else
# define PR(...)
#endif


struct edge_t {
    int u, v, w;
};

int n, m;
edge_t g[MAX_COUNT];

bool visited[MAX_COUNT];

int dist[MAX_COUNT];

int bellman_ford() {

    int found = false;
    REP(i, n) {
        found = false;
        REP(j, m) {
            int u = g[j].u;
            int v = g[j].v;
            if (dist[v] > dist[u] + g[j].w) {
                dist[v] = dist[u] + g[j].w;
                found = true;
            }
        }
    }

    return found ? 1 : 0;
}

int main()
{
    ios::sync_with_stdio(false);

    cin >> n >> m;
    REP(i, m) {
        cin >> g[i].u >> g[i].v >> g[i].w;
    }

    // fill_n(dist, n+1, INF);
    // dist[1] = 0;

    cout << bellman_ford() << endl;

    return 0;
}
