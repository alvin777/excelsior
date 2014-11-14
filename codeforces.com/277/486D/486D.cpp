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
const int MAX_COUNT = 2e3+1;
const int MOD = 1e9 + 7;


// #define ONLINE_JUDGE

#ifndef ONLINE_JUDGE 

///// trace helpers /////

#define PR(...) pr(#__VA_ARGS__, __VA_ARGS__);

template<typename T>
void print_value(const string& name, const T& value) {
    if (name.find("\"") != string::npos) {
        cout << value << " ";
        return;
    }
    cout << name << ": " << value << ", ";
}

// template<>
// void print_value<Indent>(const string& name, const Indent& value) {
//     cout << value;
// }

template<typename T>
void pr(const string& name, const T& t) {
    cout << name << ": " << t << endl;
}

template<typename T, typename ... Types>
void pr(const string& names, const T& t, Types ... rest) {
    auto comma_pos = names.find(',');
    print_value(names.substr(0, comma_pos), t);
    
    auto next_name_pos = names.find_first_not_of(" \t\n", comma_pos + 1);
    pr(string(names, next_name_pos), rest ...);
}

#else
# define PR(...)
#endif


int n;
int d;
vi g[MAX_COUNT];
int val[MAX_COUNT];
ll ans;

ll dfs(int u, int p, int root) {

    if (val[u] < val[root]) return 0;
    if (val[u] > val[root] + d) return 0;
    if (val[u] == val[root] && u < root) return 0;

    ll res = 1;
    for (int v : g[u]) {
        if (v == p) continue;

        res = (res * (dfs(v, u, root) + 1)) % MOD;
    }

    return res;
}


int main()
{
    ios::sync_with_stdio(false);

    cin >> d >> n;
    FOR(i, 1, n+1) {
        cin >> val[i];
    }

    REP(i, n-1) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    FOR(i, 1, n+1) {
        ans = (ans + dfs(i, -1, i)) % MOD;
        PR(ans);
    }

    cout << ans << endl;

    return 0;
}
