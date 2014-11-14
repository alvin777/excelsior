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
const int MAX_COUNT = 1e2+1;
const int MOD = 1e9 + 7;


#define ONLINE_JUDGE

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
bool data[MAX_COUNT][MAX_COUNT];

bool data_and_row[MAX_COUNT];
bool data_and_col[MAX_COUNT];
bool data_and[MAX_COUNT][MAX_COUNT];

bool data_or_row[MAX_COUNT];
bool data_or_col[MAX_COUNT];

int main()
{
    ios::sync_with_stdio(false);

    cin >> n >> m;

    REP(i, n) {
        REP(j, m) {
            cin >> data[i][j];
        }
    }

    fill_n(data_and_row, n, 1);
    REP(i, n) {
        REP(j, m) {
            data_and_row[i] &= data[i][j];
        }        
    }

    fill_n(data_and_col, m, 1);
    REP(j, m) {
        REP(i, n) {
            data_and_col[j] &= data[i][j];
        }
    }

    PR(dump(data_and_row, data_and_row + n));
    PR(dump(data_and_col, data_and_col + m));

    REP(i, n) {
        REP(j, m) {
            data_and[i][j] = data_and_row[i] & data_and_col[j];
        }
    }

    REP(i, n) {
        PR(dump(data_and[i], data_and[i] + m));
    } 


    fill_n(data_or_row, n, 0);
    REP(i, n) {
        REP(j, m) {
            data_or_row[i] |= data_and[i][j];
        }        
    }

    fill_n(data_or_col, m, 0);
    REP(j, m) {
        REP(i, n) {
            data_or_col[j] |= data_and[i][j];
        }
    }

    PR(dump(data_or_row, data_or_row + n));
    PR(dump(data_or_col, data_or_col + m));

    REP(i, n) {
        REP(j, m) {
            PR(data_or_row[i] | data_or_col[j], data[i][j]);
            if ((data_or_row[i] | data_or_col[j]) != data[i][j]) {
                cout << "NO" << endl;
                return 0;
            }
        }
    }

    cout << "YES" << endl;
    REP(i, n) {
        REP(j, m) {
            cout << data_and[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
