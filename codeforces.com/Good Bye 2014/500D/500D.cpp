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
const int MAX_COUNT = 1e5 + 1;
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

struct edge_t {
    ll u, v, w, t;
};


int n;
edge_t e[MAX_COUNT];
vi g[MAX_COUNT];
bool visited[MAX_COUNT];

ll dfs(int u) {
    PR(u);
    visited[u] = true;

    ll sum = 1;
    for (const auto& ei : g[u]) {
        edge_t& e = ::e[ei];
        
        int v = e.u == u ? e.v : e.u;
        PR(v, visited[v]);
        if (!visited[v]) {            
            ll subset = dfs(v);
            // PR(v, ei, subset);
            e.t = subset*(n - subset);

            sum += subset;
        }
    }

    return sum;
}

int main()
{
    ios::sync_with_stdio(false);

    cin >> n;
    REP(i, n - 1) {
        int u, v, w;
        cin >> u >> v >> w;
        e[i] = {u, v, w};
        g[u].push_back(i);
        g[v].push_back(i);
    }

    ll total = 0;
    // FOR(i, 1, n+1) {
        fill_n(visited, n + 1, false);
        // dfs(i);
        dfs(1);

        total = 0;
        REP(i, n - 1) {
            PR(e[i].w, e[i].t);
            total += (ll)e[i].w * e[i].t;
        }

        PR(total);
    // }

    int q;
    cin >> q;

    PR(q, n, n*(n-1));

    const double factor = 6.0/n/(n-1);

    REP(i, q) {
        int ei, new_w;
        cin >> ei >> new_w;

        ei--;

        total += (new_w - e[ei].w) * e[ei].t;
        PR(ei, e[ei].w, e[ei].t, new_w, total);
        
        e[ei].w = new_w;

        cout << setprecision(10) << fixed << factor*total << endl;
    }

    return 0;
}
