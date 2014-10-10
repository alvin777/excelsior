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

typedef tuple<int, int, int> node_t;
const int GCD = 0;
const int MIN = 1;
const int COUNT = 2;

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
node_t st[4*MAX_COUNT];


inline int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

node_t combine(const node_t& a, const node_t& b) {
    node_t res;
    if (get<MIN>(a) == get<MIN>(b)) {
        get<MIN>(res) = get<MIN>(a);
        get<COUNT>(res) = get<COUNT>(a) + get<COUNT>(b);
    } else {
        res = get<MIN>(a) < get<MIN>(b) ? a : b;
    }
    get<GCD>(res) = gcd(get<GCD>(a), get<GCD>(b));
    return res;
}

void st_build(int data[], int tl, int tr, int i = 0) {
    // Indent ind;s
    // PR(ind, tl, tr, i);

    if (tl == tr) {
        st[i] = node_t{data[tl], data[tl], 1};
        // PR(ind, st[i]);
        return;
    }

    int tm = tl + (tr - tl)/2;
    int li = 2*i + 1;
    int ri = 2*i + 2;
    st_build(data, tl,   tm, li);
    st_build(data, tm+1, tr, ri);

    st[i] = combine(st[li], st[ri]);
}

node_t st_query(int ql, int qr, int tl, int tr, int i = 0) {
    // Indent ind;
    // PR(ind, ql, qr, tl, tr, i);

    if (ql > tr || qr < tl) {
        // PR(ind, "<<", 0);
        return node_t{0, INF, 0};
    }

    if (ql <= tl && qr >= tr) {
        // PR(ind, "<<", st[i]);
        return st[i];
    }

    int tm = tl + (tr - tl)/2;
    int li = 2*i + 1;
    int ri = 2*i + 2;
    return combine(st_query(ql, qr, tl,   tm, li), 
                   st_query(ql, qr, tm+1, tr, ri));
}

int main()
{
    ios::sync_with_stdio(false);

    cin >> n;
    REP(i, n) {
        cin >> data[i];
    }

    // PR(dump(data, data+n));

    st_build(data, 0, n-1);

    int qn;
    cin >> qn;
    REP(i, qn) {
        int l, r;
        cin >> l >> r;

        node_t min_node = st_query(l-1, r-1, 0, n-1);

        // PR(l, r, gcd, min_node);

        int queens = (get<GCD>(min_node) == get<MIN>(min_node)) ? get<COUNT>(min_node) : 0;
        cout << r - l - queens + 1 << endl;
    }

    return 0;
}