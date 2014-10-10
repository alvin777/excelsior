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

typedef tuple<int, int> node_t;
const int MIN = 0;
const int COUNT = 1;

ostream& operator<< (ostream& o, const node_t& node) {
    return o << "(" << get<0>(node) << ", " << get<1>(node) << ")";
}

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


template<typename T>
struct print_t {
    T first;
    T last;
};

template<typename T>
ostream& operator<< (ostream& o, const print_t<T>& s) {
    o << "[";
    for (auto it = s.first; it != s.last; ++it) {
        if (it != prev(s.last)) {
            o << *it << ", ";
        } else {
            o << *it;
        }
    }
    o << "]";

    return o;
}

template<typename T>
print_t<T> dump(T first, T last, string label = "") {
    return {first, last};
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


int n;
int data[MAX_COUNT];
int st_gcd[4*MAX_COUNT];
node_t st_min[4*MAX_COUNT];


int gcd(int a, int b) {
    if (a < b) {
        swap(a, b);
    }

    if (b == 0) return a;

    return gcd(b, a % b);
}

void st_build_gcd(int st[], int data[], int tl, int tr, int i = 0) {
    // Indent ind;s
    // PR(ind, tl, tr, i);

    if (tl == tr) {
        st[i] = data[tl];
        // PR(ind, st[i]);
        return;
    }

    int tm = tl + (tr - tl)/2;
    int li = 2*i + 1;
    int ri = 2*i + 2;
    st_build_gcd(st, data, tl,   tm, li);
    st_build_gcd(st, data, tm+1, tr, ri);

    st[i] = gcd(st[li], st[ri]);
}

int st_query_gcd(int st[], int ql, int qr, int tl, int tr, int i = 0) {
    // Indent ind;
    // PR(ind, ql, qr, tl, tr, i);

    if (ql > tr || qr < tl) {
        // PR(ind, "<<", 0);
        return 0;
    }

    if (ql <= tl && qr >= tr) {
        // PR(ind, "<<", st[i]);
        return st[i];
    }

    int tm = tl + (tr - tl)/2;
    int li = 2*i + 1;
    int ri = 2*i + 2;
    return gcd(st_query_gcd(st, ql, qr, tl,   tm, li), 
               st_query_gcd(st, ql, qr, tm+1, tr, ri));
}

void st_build_min(node_t st[], int data[], int tl, int tr, int i = 0) {
    // Indent ind;
    // PR(ind, tl, tr, i);

    if (tl == tr) {
        st[i] = node_t{data[tl], 1};
        // PR(ind, st[i]);
        return;
    }

    int tm = tl + (tr - tl)/2;
    int li = 2*i + 1;
    int ri = 2*i + 2;
    st_build_min(st, data, tl,   tm, li);
    st_build_min(st, data, tm+1, tr, ri);

    if (get<MIN>(st[li]) == get<MIN>(st[ri])) {
        st[i] = node_t{get<MIN>(st[li]), get<COUNT>(st[li]) + get<COUNT>(st[ri])};
    } else {
        st[i] = min(st[li], st[ri]);
    }
    // PR(ind, st[i]);
}

node_t st_query_min(node_t st[], int ql, int qr, int tl, int tr, int i = 0) {
    // Indent ind;
    // PR(ind, ql, qr, tl, tr, i);

    if (ql > tr || qr < tl) {
        // PR(ind, "<<", "INF");
        return node_t{INF, 0};
    }

    if (ql <= tl && qr >= tr) {
        // PR(ind, "<<", st[i]);
        return st[i];
    }

    int tm = tl + (tr - tl)/2;
    int li = 2*i + 1;
    int ri = 2*i + 2;
    node_t res_l = st_query_min(st, ql, qr, tl,   tm, li);
    node_t res_r = st_query_min(st, ql, qr, tm+1, tr, ri);

    // PR(ind, res_l, res_r);

    node_t res;
    if (get<MIN>(res_l) == get<MIN>(res_r)) {
        res = node_t{get<MIN>(res_l), get<COUNT>(res_l) + get<COUNT>(res_r)};
    } else {
        res = min(res_l, res_r);
    }
    // PR(ind, "<<", res);
    return res;
}

int main()
{
    ios::sync_with_stdio(false);

    cin >> n;
    REP(i, n) {
        cin >> data[i];
    }

    // PR(dump(data, data+n));

    st_build_gcd(st_gcd, data, 0, n-1);
    st_build_min(st_min, data, 0, n-1);

    int qn;
    cin >> qn;
    REP(i, qn) {
        int l, r;
        cin >> l >> r;

        int gcd = st_query_gcd(st_gcd, l-1, r-1, 0, n-1);
        node_t min_node = st_query_min(st_min, l-1, r-1, 0, n-1);

        // PR(l, r, gcd, min_node);

        int queens = (gcd == get<MIN>(min_node)) ? get<COUNT>(min_node) : 0;
        cout << r - l - queens + 1 << endl;
    }

    return 0;
}