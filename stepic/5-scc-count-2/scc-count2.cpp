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
const int MAX_COUNT = 1e5+1;
const int MOD = 1e9 + 7;


// #define ONLINE_JUDGE

#ifndef ONLINE_JUDGE 

///// trace helpers /////



#else
# define PR(...)
#endif


int n, m;
vi g[MAX_COUNT];
vi r[MAX_COUNT];
bool vis[MAX_COUNT];
vi t;

void toposort(int v) {
    vis[v] = true;

    REP(i, g[v].size()) {
        int u = g[v][i];
        if (vis[u]) continue;

        toposort(u);
    }
    t.push_back(v);
}

void dfs(int v) {
    vis[v] = true;

    REP(i, r[v].size()) {
        int u = r[v][i];
        if (vis[u]) continue;

        dfs(u);
    }
}

int main()
{
    ios::sync_with_stdio(false);

    cin >> n >> m;
    REP(i, m) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        r[v].push_back(u);
    }

    // fill(vis, vis + n+1, false);

    FOR(i, 1, n+1) {
        if (!vis[i]) {
            toposort(i);
        }
    }

    int scc = 0;
    fill(vis, vis + n+1, false);
    reverse(t.begin(), t.end());

    REP(i, t.size()) {
        if (!vis[t[i]]) {
            scc++;
            dfs(t[i]);
        }
    }

    cout << scc << endl;

    return 0;
}
