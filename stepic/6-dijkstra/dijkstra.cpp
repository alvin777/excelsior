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
    edge_t(int a, int b) : v(a), w(b){}
    int v, w;
};

int n, m;
vector<edge_t> g[MAX_COUNT];
bool vis[MAX_COUNT];
int dist[MAX_COUNT];


void dijkstra() {

    REP(i, n) {
        int u = -1;
        FOR(j, 1, n+1) {
            if (vis[j]) continue;

            if (u == -1 || dist[j] < dist[u]) {
                u = j;
            }
        }

        if (u == -1) return;

        REP(j, g[u].size()) {
            const edge_t& e = g[u][j];
            if (vis[e.v]) continue;

            dist[e.v] = min(dist[e.v], dist[u] + e.w);
        }

        vis[u] = true;
    }
}

int main()
{
    ios::sync_with_stdio(false);

    cin >> n >> m;
    REP(i, m) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back(edge_t(v, w));
    }

    int u, v;
    cin >> u >> v;

    fill_n(dist, n+1, INF);
    dist[u] = 0;

    dijkstra();

    cout << (dist[v] < INF ? dist[v] : -1) << endl;

    return 0;
}
