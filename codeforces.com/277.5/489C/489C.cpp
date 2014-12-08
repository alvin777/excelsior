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

int data[MAX_COUNT];

int main()
{
    ios::sync_with_stdio(false);

    int m, s;
    cin >> m >> s;

    if (s == 0) {
        if (m == 1) {
            cout << 0 << " " << 0 << endl;
        } else {
            cout << -1 << " " << -1 << endl;
        }
        return 0;
    }

    if (s > m*9) {
        cout << -1 << " " << -1 << endl;
        return 0;
    }

    REP(i, m) {
        PR(i, m, s);

        data[i] = min(9, s-1);
        s -= data[i];

        PR(data[i]);
    }

    data[m-1]++;
    s--;

    PR(dump(data, data + m));

    for (int i = m - 1; i >= 0; --i) {
        cout << data[i];
    }

    if (data[m-1] == 1) {
        data[m-1]--;
        REP(i, m) {
            if (data[i] < 9) {
                data[i]++;
                break;
            }
        }
    }

    cout << " ";

    REP(i, m) {
        cout << data[i];
    }

    cout << endl;

    return 0;
}
