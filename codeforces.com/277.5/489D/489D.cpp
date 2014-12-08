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
const int MAX_COUNT = 3001;
const int MAX_EDGES = 30001;
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


int n, m;
vector<int> g[MAX_COUNT];
vector<int> r[MAX_COUNT];

ll f(ll a) {
    return a * (a-1) / 2;
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

    FOR(i, 1, n+1) {
        sort(ALL(g[i]));
        sort(ALL(r[i]));
    }

    ll ans = 0;

    FOR(i, 1, n+1) {
        FOR(j, 1, n+1) {
            PR(i, j);

            if (i == j) continue;

            int k = 0;
            int l = 0;
            ll common = 0;
            while (k < g[i].size() && l < r[j].size()) {
                int a = g[i][k];
                int b = r[j][l];
                if (a == b) {
                    common++;
                    k++;
                    l++;
                } else if (a < b) {
                    k++;
                } else {
                    l++;
                }
            }

            PR(common);

            if (common >= 2) {
                ans += f(common);
            }

            PR(ans);
        }
    }

    cout << ans << endl;

    return 0;
}
