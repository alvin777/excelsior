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

const ll INF = 1e18;
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

int n, m, s;
edge_t g[MAX_COUNT];

ll dist[MAX_COUNT];
int p[MAX_COUNT];
bool cycled[MAX_COUNT];

vi g2[MAX_COUNT];
bool accessible[MAX_COUNT];
bool visited[MAX_COUNT];

void mark_accessible(int u) {
    accessible[u] = true;

    REP(i, g2[u].size()) {
        int v = g2[u][i];
        if (accessible[v]) continue;

        mark_accessible(v);
    }
}

void mark_cycled(int u) {
    visited[u] = true;

    REP(i, g2[u].size()) {
        int v = g2[u][i];
        if (visited[v] || cycled[v] || !accessible[v]) continue;

        cycled[v] |= cycled[u];
        mark_cycled(v);
    }
}

void bellman_ford() {
    fill_n(p, n+1, -1);

    REP(i, n) {
        REP(j, m) {
            int u = g[j].u;
            int v = g[j].v;
            if (dist[v] > dist[u] + g[j].w) {
                dist[v] = max(dist[u] + g[j].w, -INF);
                p[v] = u;
            }
        }
    }

    REP(j, m) {
        int u = g[j].u;
        int v = g[j].v;
        if (dist[v] > dist[u] + g[j].w) {

            REP(i, n) {
                v = p[v];
            }

            if (accessible[v])
                cycled[v] = true;
            fill_n(visited, n+1, false);
            mark_cycled(v);
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);

    cin >> n >> m >> s;
    REP(i, m) {
        cin >> g[i].u >> g[i].v >> g[i].w;
        g2[g[i].u].push_back(g[i].v);
    }

    mark_accessible(s);

    fill_n(dist, n+1, INF);
    dist[s] = 0;

    bellman_ford();

    FOR(i, 1, n+1) {
        if (!accessible[i]) {
            cout << "*";
        } else if (cycled[i]) {
            cout << "-";
        } else {
            cout << dist[i];
        }

        cout << endl;
    }

    return 0;
}
