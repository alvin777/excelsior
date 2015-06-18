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
const int MAX_COUNT = 101;
const int MAX_COLOR = 101;
const int MOD = 1e9 + 7;


// #define ONLINE_JUDGE

#ifndef ONLINE_JUDGE 

///// trace helpers /////

class Indent
{
public:
    friend ostream& operator<< (ostream& o, const Indent& indent);

    Indent()  { ++level; }
    ~Indent() { --level; }

private:
    static int level;
};

int Indent::level = -1;

ostream& operator<< (ostream& o, const Indent& indent) {
    return o << string(indent.level*4, ' ');
}

#define PR(...) pr(#__VA_ARGS__, __VA_ARGS__);

template<typename T>
void print_value(const string& name, const T& value) {
    if (name.find("\"") != string::npos) {
        cout << value << " ";
        return;
    }
    cout << name << ": " << value << ", ";
}

template<>
void print_value<Indent>(const string& name, const Indent& value) {
    cout << value;
}

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
vi g[MAX_COLOR][MAX_COUNT];

bool visited[MAX_COUNT];

bool dfs(int u, int t, int c) {
    // Indent ind;
    // PR(ind, u, t, c);

    visited[u] = true;

    if (u == t) {
        // PR(ind, "<<", true);
        return true;
    }

    for (auto v : g[c][u]) {
        // PR(ind, v, visited[v]);
        if (!visited[v]) {
            if(dfs(v, t, c)) { 
                // PR(ind, "<<", true);

                return true;
            }
        }
    }

    // PR(ind, "<<", false);
    return false;
}

int main()
{
    ios::sync_with_stdio(false);

    cin >> n >> m;
    REP(i, m) {
        int u, v, c;
        cin >> u >> v >> c;
        g[c][u].push_back(v);
        g[c][v].push_back(u);

        PR(u, "->", v, c);
        PR(v, "->", u, c);
    }

    int q;
    cin >> q;
    REP(x, q) {
        int u, v;
        cin >> u >> v;

        int ans = 0;
        FOR(c, 1, m + 1) {
            fill_n(visited, n + 1, false);
            if (dfs(u, v, c)) {
                ans++;
            }
        }
        cout << ans << endl;
    }


    return 0;
}
