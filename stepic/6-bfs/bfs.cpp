#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>
#include <queue>

using namespace std;
typedef long long ll;
typedef vector<int> vi; 

#define REP(k,a) for(int k=0; k < (a); ++k)
#define FOR(i,a,b) for(int i=a; i < (b); ++i)
#define ALL(a) begin(a), end(a)
#define COUNT(a) (sizeof(a)/sizeof(a[0]))

const int INF = 1e9;
const int MAX_COUNT = 1e5 + 1;
const int MOD = 1e9 + 7;


// #define ONLINE_JUDGE

#ifndef ONLINE_JUDGE 

///// trace helpers /////



#else
# define PR(...)
#endif


int n, m;
vi g[MAX_COUNT];
bool visited[MAX_COUNT];

queue<int> q;
int dist[MAX_COUNT];

void bfs(int s) {
    q.push(s);
    dist[s] = 0;

    while (q.size()) {
        int u = q.front();
        q.pop();

        REP(i, g[u].size()) {
            int v = g[u][i];
            if (!visited[v]) {
                q.push(v);
                visited[v] = true;
            }
            dist[v] = min(dist[v], dist[u]+1);
        }
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

    fill_n(dist, n+1, INF);
    bfs(u);

    cout << (dist[v] != INF ? dist[v] : -1) << endl;

    return 0;
}
