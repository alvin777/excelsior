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
const int MAX_COUNT = 2e5+1;
const int MOD = 1e9 + 7;

typedef map<int, vi> mivi;
typedef pair<int, int> ii;


#define ONLINE_JUDGE

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

template<>
void print_value<mivi>(const string& name, const mivi& m) {
    cout << name << ": {";
    for (auto mit = m.begin(); mit != m.end(); ++mit) {
        cout << mit->first << ": [";

        auto& v = mit->second;
        for (auto it = v.begin(); it != v.end(); ++it) {
            cout << *it;
            if (it != prev(v.end())) {
                 cout << ", ";
            }
        }
        cout << "]";

        if (mit != prev(m.end())) {
             cout << ", ";
        }
    }
    cout << "}, ";
}

template<typename T>
void pr(const string& name, const T& t) {
    // cout << name << ": " << t << endl;
    print_value(name, t);
    cout << endl;
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


int n, m, q;

ii p[MAX_COUNT];
mivi st[4*MAX_COUNT];

mivi join(const mivi& m1, const mivi& m2) {
    mivi res = m1;

    for (auto& pair : m2) {
        res[pair.first].insert(res[pair.first].end(), ALL(pair.second));
    }

    // PR(join, m1, m2, res);
    return res;
}

void st_build(int tl, int tr, int i = 0) {
    if (tr == tl) {
        st[i][p[tr].first].push_back(p[tr].second);
        st[i][p[tr].second].push_back(p[tr].first);
        return;
    }

    int tm = tl + (tr - tl)/2;
    int li = 2*i+1;
    int ri = 2*i+2;

    st_build(tl, tm, li);
    st_build(tm+1, tr, ri);
    st[i] = join(st[li], st[ri]);
}

mivi st_query(int l, int r, int tl, int tr, int i = 0) {

    // PR("st_query", l, r, tl, tr, i);

    if (l <= tl && r >= tr) {
        return st[i];
    }

    if (l > tr || r < tl) {
        return mivi{};
    }

    int tm = tl + (tr - tl)/2;
    int li = 2*i+1;
    int ri = 2*i+2;
    auto res_l = st_query(l, r, tl,   tm, li);
    auto res_r = st_query(l, r, tm+1, tr, ri);
    // auto res = join(res_l, res_r);
    // PR(res);
    // return res;
    return join(st_query(l, r, tl,   tm, li), st_query(l, r, tm+1, tr, ri));
}

enum color_t {WHITE, RED, BLACK};
color_t vis[MAX_COUNT];

bool bipart(mivi& g, int u, color_t c) {

    PR("bipart", u, c);

    vis[u] = c;

    for (int v : g[u]) {
        PR(v, vis[v]);
        if (vis[v] == c) {
            PR("vis[v] == c");
            return false;
        }

        if (vis[v] != WHITE) continue;

        int res = bipart(g, v, c == RED ? BLACK : RED);
        if (!res) {
            PR("!res");
            return false;
        }
    }

    return true;
}

int main()
{
    ios::sync_with_stdio(false);

    cin >> n >> m >> q;
    REP(i, m) {
        int x, y;
        cin >> x >> y;
        p[i+1] = make_pair(x, y);
    }

    st_build(1, m);

    cout << 1 << endl;

    REP(i, q) {
        int l, r;
        cin >> l >> r;
        PR(l, r);

        auto g = st_query(l, r, 1, m);
        PR(g);

        fill(ALL(vis), WHITE);

        bool res = true;
        FOR(j, 1, n) {
            if (vis[j] == WHITE) {
                if (!bipart(g, j, RED)) {
                    res = false;
                    break;
                }
            }
        }
        cout << (res ? "Possible" : "Impossible") << endl;
        // cout << endl;
    }

    return 0;
}
