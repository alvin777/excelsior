#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>
#include <array>

using namespace std;
typedef long long ll;
typedef vector<int> vi; 

#define REP(k,a) for(int k=0; k < (a); ++k)
#define FOR(i,a,b) for(int i=a; i < (b); ++i)
#define ALL(a) begin(a), end(a)
#define COUNT(a) (sizeof(a)/sizeof(a[0]))

const int INF = 1e9;
const int MAX_COUNT = 5;
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

typedef array<int, 4> array_t;

int n;
vi d;


void check(vi d, const vi& newNumbers) {
    for (auto num : newNumbers) {
        d.push_back(num);
    }
    sort(ALL(d));

    PR(dump(ALL(d)));

    bool isOk = d[0] + d[1] + d[2] + d[3] == 2*(d[1] + d[2]) && 
                d[0] + d[1] + d[2] + d[3] == 4*(d[3] - d[0]);

    PR(isOk, d[0] + d[1] + d[2] + d[3], 2*(d[1] + d[2]), d[3] - d[0]);

    if (isOk) {
        cout << "YES" << endl;
        for (auto num : newNumbers) {
            cout << num << endl;
        }
        exit(0);
    }
}

int main()
{
    ios::sync_with_stdio(false);

    cin >> n;
    REP(i, n) {
        int v;
        cin >> v;
        d.push_back(v);
    }

    if (n == 0) {
        cout << "YES" << endl;
        for (auto num : {1,1,3,3}) {
            cout << num << endl;
        }
        return 0;
    } 

    if (n == 4) {
        check(d, vi{});
        cout << "NO" << endl;
        return 0;
    }

    sort(ALL(d));

    if (n == 3) {
        // x1
        if (d.back() % 3 == 0) {
            check(d, vi{d.back() / 3});
        }

        // x2, x3
        check(d, vi{4*d.front() - d[1]});

        // x4
        check(d, vi{3*d.front()});

        cout << "NO" << endl;
        return 0;
    }

    if (n == 2) {
        // x1, x4
        if ((d.front() + d.back()) % 4 == 0) {
            check(d, vi{(d.front() + d.back()) / 4, 3*(d.front() + d.back()) / 4});
        }

        // x2, x3
        if ((d.back() - d.front()) % 2 == 0) {
            check(d, vi{(d.back() - d.front()) / 2, (d.back() - d.front()) / 2});
        } else {
            check(d, vi{(d.back() - d.front()) / 2, (d.back() - d.front()) / 2 + 1});
        }

        // x1, x2/x3
        if (d.back() % 3 == 0) {
            check(d, vi{d.back() / 3, d.back() * 4 / 3 - d.front()});
        }

        // x2/x3, x4
        PR(4*d.front() - d.back(), d.front() * 3);
        check(d, vi{4*d.front() - d.back(), d.front() * 3});

        cout << "NO" << endl;
        return 0;
    }

    if (n == 1) {
        // given x1
        check(d, vi {d.front() * 2, d.front() * 2, d.front()*3});

        cout << "NO" << endl;
        return 0;
    }

    return 0;
}
