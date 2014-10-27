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


int n;
vi g[MAX_COUNT];
bool visited[MAX_COUNT];
int t = 0;
int disc[MAX_COUNT];
int low[MAX_COUNT];
int found_ap[MAX_COUNT];
int parent[MAX_COUNT];

void ap(int u) {
    visited[u] = true;
    low[u] = disc[u] = ++t;

    for (int v : g[u]) {
        if (!visited[v]) {
            parent[v] = u;

            ap(v);

            low[u] = min(low[u], low[v]);

            if (parent[u] == -1 && g[u].size() >= 2) {      // root and has two children
                found_ap[u] = true;
            } else if (parent[u] != -1 && low[v] >= disc[u]) { // 
                found_ap[u] = true;
            }
        } else if (v != parent[u]) {
            low[u] = min(low[u], disc[v]);
        }
    }
}


int main()
{
    ios::sync_with_stdio(false);

    cin >> n;
    REP(i, n) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    fill_n(parent, parent + n, -1);
    REP(i, n) {
        if (!visited[i])
            ap(i);
    }

    REP(i, n) {
        if (found_ap[i]) {
            cout << i << " ";
        }
    }

    cout << endl;

    return 0;
}
