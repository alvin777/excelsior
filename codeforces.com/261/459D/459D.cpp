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
const int MAX_COUNT = 1e6;
const int MOD = 1e9 + 7;


// #define ONLINE_JUDGE

#ifndef ONLINE_JUDGE 

///// trace helpers /////

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


int n;
struct val_t{
    int val, count, rev_count;
} data[MAX_COUNT];

struct node_t {
    int value;
    int count;
    // int total;

    bool operator< (const node_t& o) const {
        return value < o.value;
    }
};

ostream& operator<< (ostream& o, const node_t& n) {
    // return o << "(" << n.value << ", " << n.count << ", " << n.total << ")";
    return o << "(" << n.value << ", " << n.count << ")";
}

// typedef vector<node_t> vn;
int st[MAX_COUNT*4];

// ostream& operator<< (ostream& o, const vn& vn) {
//     o << "[";

//     for (const auto& n : vn) {
//         o << n << " ";
//     }

//     o << "]";
//     return o;
// }

// vn join(const vn& v1, const vn& v2) {
//     vn res;
//     res.reserve(v1.size() + v2.size());

//     merge(ALL(v1), ALL(v2), back_inserter(res));

//     FOR(i, 1, res.size()) {
//         res[i].total = res[i-1].total + res[i].count;
//     }
//     return res;
// }

// void st_build(int tl, int tr, int i = 0) {
//     Indent ind;
    
//     // PR(ind, tl, tr);

//     if (tl == tr) {
//         // PR(ind, i, data[tl].rev_count, node_t{data[tl].rev_count, 1, 1});
//         st[i].push_back(node_t{data[tl].rev_count, 1, 1});
//         return;
//     }

//     int tm = tl + (tr - tl)/2;
//     int li = 2*i + 1;
//     int ri = 2*i + 2;
//     st_build(tl,   tm, li);
//     st_build(tm+1, tr, ri);

//     // PR(ind, st[li], st[ri]);

//     st[i] = join(st[li], st[ri]);
//     // PR(ind, "<<",  st[i]);
// }

void st_update(int val, int delta, int tl, int tr, int i = 0) {

    if (tl == tr) {
        st[i] += delta;
        return;
    }

    int tm = tl + (tr - tl)/2;
    int li = 2*i + 1;
    int ri = 2*i + 2;

    if (val <= tm) {
        st_update(val, delta, tl,   tm, li);
    } else {
        st_update(val, delta, tm+1, tr, ri);
    }
    st[i] = st[li] + st[ri];
}

int st_query(int l, int r, int tl, int tr, int i = 0) {

    if (tl >= l && tr <= r) {
        return st[i];
    }

    if (tr < l || tl > r) {
        return 0;
    }

    int tm = tl + (tr - tl)/2;
    int li = 2*i + 1;
    int ri = 2*i + 2;

    return st_query(l, r, tl,     tm, li) + 
           st_query(l, r, tm + 1, tr, ri);
}

// #include<mach/mach.h>

// mach_vm_size_t get_res_mem() {
//     struct task_basic_info t_info;
//     mach_msg_type_number_t t_info_count = TASK_BASIC_INFO_COUNT;

//     if (KERN_SUCCESS != task_info(mach_task_self(),
//                                   TASK_BASIC_INFO, (task_info_t)&t_info, 
//                                   &t_info_count))
//     {
//         return -1;
//     }
//     // resident size is in t_info.resident_size;
//     // virtual size is in t_info.virtual_size;

//     return t_info.resident_size;
// }

int main()
{
    ios::sync_with_stdio(false);

    cin >> n;
    REP(i, n) {
        cin >> data[i].val;
    }

    {
        map<int, int> m;
        for (int i = 0; i < n; ++i) {
            data[i].count = ++m[data[i].val];
        }

        m.clear();
        for (int i = n - 1; i >= 0; --i) {
            data[i].rev_count = ++m[data[i].val];
            st_update(data[i].rev_count, 1, 0, n-1);
        }
    }

    ll ans = 0;
    REP(i, n-1) {
        st_update(data[i].rev_count, -1, 0, n-1);
        auto res = st_query(0, data[i].count-1, 0, n-1);
        ans += res;
        // PR(data[i].count, res);
    }

    cout << ans << endl;

    // PR(get_res_mem());

    return 0;
}
