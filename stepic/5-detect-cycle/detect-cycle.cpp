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
const int MAX_COUNT = 1e5;
const int MOD = 1e9 + 7;


// #define ONLINE_JUDGE

#ifndef ONLINE_JUDGE 

///// trace helpers /////



#else
# define PR(...)
#endif


int n, m;
vi g[MAX_COUNT];
enum color_t {WHITE, GREY, BLACK};
color_t vis[MAX_COUNT];
bool cycle = false;

void dfs(int v) {
    vis[v] = GREY;

    REP(i, g[v].size()) {
        int u = g[v][i];
        if (vis[u] == GREY) {
            cycle = true;
        }
        if (vis[u] != WHITE) continue;

        dfs(u);
    }
    vis[v] = BLACK;
}

int main()
{
    ios::sync_with_stdio(false);

    cin >> n >> m;
    REP(i, m) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
    }

    fill_n(vis, n, WHITE);

    int scc = 0;
    FOR(i, 1, n+1) {
        if (vis[i] == WHITE) {
            dfs(i);
        }
    }

    cout << cycle << endl;

    return 0;
}
