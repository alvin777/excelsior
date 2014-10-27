#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>

using namespace std;
typedef unsigned long long ll;
typedef vector<int> vi; 

#define REP(k,a) for(int k=0; k < (a); ++k)
#define FOR(i,a,b) for(int i=a; i < (b); ++i)
#define ALL(a) begin(a), end(a)
#define COUNT(a) (sizeof(a)/sizeof(a[0]))

const int INF = 1e9;
const int MAX_COUNT = 1e5+1;
const int MOD = 1e9 + 7;

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

struct query_t {
    int l, r, q;
} qa[MAX_COUNT];

ll st[4*MAX_COUNT];
ll a[MAX_COUNT];

void st_update(int l, int r, ll value, int tl, int tr, int i = 0) {

    PR(st_update, l, r, value, tl, tr);

    if (tl >= l && tr <= r) {
        st[i] |= value;
        return;
    }

    if (tl > r || tr < l) {
        PR("<<");
        return;
    }

    int tm = tl + (tr-tl)/2;
    int li = 2*i+1;
    int ri = 2*i+2;
    st_update(l, r, value, tl,   tm, li);
    st_update(l, r, value, tm+1, tr, ri);
    // st[i] = st[ri] | st[li];
}

void st_build_array(int val, int tl, int tr, int i = 0) {

    if (tl == tr) {
        a[tl] = val | st[i];
        return;
    }

    int tm = tl + (tr-tl)/2;
    int li = 2*i+1;
    int ri = 2*i+2;
    st_build_array(val | st[i], tl,   tm, li);
    st_build_array(val | st[i], tm+1, tr, ri);
}

void st_rebuild(int tl, int tr, int i = 0) {

    if (tl == tr) {
        st[i] = a[tl];
        return;
    }

    int tm = tl + (tr-tl)/2;
    int li = 2*i+1;
    int ri = 2*i+2;
    st_rebuild(tl,   tm, li);
    st_rebuild(tm+1, tr, ri);
    st[i] = st[li] & st[ri];
}

ll st_query(int l, int r, int tl, int tr, int i = 0) {

    PR(st_query, l, r, tl, tr);

    if (tl >= l && tr <= r) {
        return st[i];
    }

    if (tl > r || tr < l) {
        return -1;
    }

    int tm = tl + (tr-tl)/2;
    int li = 2*i+1;
    int ri = 2*i+2;

    ll l_res = st_query(l, r, tl,   tm, li);
    ll r_res = st_query(l, r, tm+1, tr, ri);

    PR(l_res, r_res, l_res & r_res);

    return l_res & r_res;
};

int main()
{
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    PR(n, m);

    REP(i, m) {
        cin >> qa[i].l >> qa[i].r >> qa[i].q;
    }

    REP(i, m) {
        st_update(qa[i].l, qa[i].r, qa[i].q, 1, n);
    }

    st_build_array(0, 1, n);

    st_rebuild(1, n);

    REP(i, m) {
        // PR(qa[i].l, qa[i].r, qa[i].q, st_query(qa[i].l, qa[i].r, 1, n));
        if (st_query(qa[i].l, qa[i].r, 1, n) != qa[i].q) {
            cout << "NO" << endl;
            return 0;
        }
    }

    cout << "YES" << endl;
    FOR(i, 1, n+1) {
        cout << a[i] << " ";
    }

    cout << endl;

    return 0;
}
