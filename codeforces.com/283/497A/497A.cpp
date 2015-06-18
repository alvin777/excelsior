#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>

using namespace std;
typedef long long ll;
typedef vector<int> vi; 
typedef set<int> si;

#define REP(k,a) for(int k=0; k < (a); ++k)
#define FOR(i,a,b) for(int i=a; i < (b); ++i)
#define ALL(a) begin(a), end(a)
#define COUNT(a) (sizeof(a)/sizeof(a[0]))

const int INF = 1e9;
const int MAX_COUNT = 1e3+1;
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


int n, m;
string data[MAX_COUNT];

struct range {
    int from;
    int to;
};

ostream& operator <<(ostream& o, const range& r) {
    return o << "(" << r.from << ", " << r.to << ")";
}

vector<range> vr;

int main()
{
    ios::sync_with_stdio(false);

    cin >> n >> m;
    REP(i, n) {
        cin >> data[i];
    }

    if (n <= 1) {
        cout << 0 << endl;
        return 0;
    }

    if (m == 0) {
        cout << 0 << endl;
        return 0;
    }

    vr.push_back(range {0, n});

    PR(dump(ALL(vr)));

    int index = 0;
    int ans = 0;
    while (index < m) {
        PR(index);
        bool skip = false;
        for (auto r : vr) {
            PR(r.from, r.to);
            for (int i = r.from + 1; i < r.to; ++i) {
                if (data[i][index] < data[i-1][index]) {
                    ans++;
                    skip = true;
                    
                    PR(index, data[i][index], data[i-1][index], skip);

                    break;
                }
            }

            if (skip) {
                break;
            }
        }

        vector<range> vr_next;
        if (!skip) {
            for (auto r : vr) {
                int last_from = r.from;
                for (int i = r.from + 1; i < r.to; ++i) {
                    if (data[i][index] != data[i-1][index]) {
                        vr_next.push_back(range {last_from, i});
                        last_from = i;
                    }
                }
                vr_next.push_back(range {last_from, r.to});
            }

            vr = vr_next;
        }

        index++;
    }

    cout << ans << endl;

    return 0;
}
