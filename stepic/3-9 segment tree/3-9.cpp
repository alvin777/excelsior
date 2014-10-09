#include <iostream>
#include <vector>
#include <map>
#include <set>
// #include <array>
#include <algorithm>
#include <iomanip>

using namespace std;
typedef long long ll;
typedef vector<int> vi; 

#define REP(k,a) for(int k=0; k < (a); ++k)
#define FOR(i,a,b) for(int i=a; i < (b); ++i)
#define ALL(a) begin(a), end(a)
#define D(a) cout << #a ": " << a << " ";
#define DE(a) cout << #a ": " << a << endl;
#define COUNT(a) (sizeof(a)/sizeof(a[0]))

const int INF = 1e9;
const int MAX_COUNT = 1e5;
const int MOD = 1e9 + 7;


// #ifndef ONLINE_JUDGE 
// ///// trace helpers /////

// template<typename T>
// struct print_t {
//     T first;
//     T last;
// };

// template<typename T>
// ostream& operator<< (ostream& o, const print_t<T>& s) {
//     o << "[";
//     for (auto it = s.first; it != s.last; ++it) {
//         if (it != prev(s.last)) {
//             o << *it << ", ";
//         } else {
//             o << *it;
//         }
//     }
//     o << "]";

//     return o;
// }

// template<typename T>
// print_t<T> dump(T first, T last, string label = "") {
//     return {first, last};
// }

// #define PR(...) pr(#__VA_ARGS__, __VA_ARGS__);

// template<typename T>
// void pr(const string& name, T t) {
//     cout << name << ": " << t << endl;
// }

// template<typename T, typename ... Types>
// void pr(const string& names, T t, Types ... rest) {
//     auto comma_pos = names.find(',');
//     cout << names.substr(0, comma_pos) << ": " << t << ", ";
    
//     auto next_name_pos = names.find_first_not_of(" \t\n", comma_pos + 1);
//     pr(string(names, next_name_pos), rest ...);
// }

// #endif


template<typename T, int ElementsCount>
class SegmentTree {
public:
    void build(T data[], int tl, int tr, int i = 0) {

        if (tl == tr) {
            st[i] = data[tl];
            return;
        }

        int tm = tl + (tr-tl)/2;   // partition original array
        int li = 2*i + 1;          // calc heap indices for st
        int ri = 2*i + 2;

        build(data, tl, tm,   li); 
        build(data, tm+1, tr, ri);
        st[i] = min(st[li], st[ri]);
    }

    void update(int pos, T val, int tl, int tr, int i = 0) {
        if (tl == tr) {
            st[i] = val;
            return;
        }

        int tm = tl + (tr-tl)/2;
        int li = 2*i + 1;
        int ri = 2*i + 2;

        if (pos <= tm) {
            update(pos, val, tl,   tm, li);
        } else {
            update(pos, val, tm+1, tr, ri);
        }
        st[i] = min(st[li], st[ri]);
    }

    T query(int ql, int qr, int tl, int tr, int i = 0) {
        if (ql > tr || qr < tl) return INF;

        if (ql <= tl && qr >= tr) {
            return st[i];
        }

        int tm = tl + (tr-tl)/2;
        int li = 2*i + 1;
        int ri = 2*i + 2;
        return min(query(ql, qr, tl,   tm, li), 
                   query(ql, qr, tm+1, tr, ri));
    }
private:
    T st[4*ElementsCount];
};


int n, m;
int data[MAX_COUNT];
SegmentTree<int, 100000> st;


int main()
{
    ios::sync_with_stdio(false);

    cin >> n >> m;
    REP(i, n) {
        cin >> data[i];
    }

    // PR(dump(data, data+n));

    st.build(data, 0, n-1);

    REP(i, m) {
        string command;
        int arg1, arg2;
        cin >> command >> arg1 >> arg2;
        // PR(command, arg1, arg2);
        
        if (command == "Min") {
            cout << st.query(arg1 - 1, arg2 - 1, 0, n-1) << endl;
        } else if (command == "Set") {
            st.update(arg1 - 1, arg2, 0, n-1);
        }
    }

    return 0;
}