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
vi g[MAX_COUNT];
bool vis[MAX_COUNT];

void dfs(int v) {
    vis[v] = true;

    REP(i, g[v].size()) {
        int u = g[v][i];
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
        g[v].push_back(u);
    }

    int u, v;
    cin >> u >> v;
    dfs(u);

    cout << vis[v] << endl;

    return 0;
}
