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
const int MAX_COUNT = 1e6 + 1;
const int MOD = 1e9 + 7;


// #define ONLINE_JUDGE

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

char data[MAX_COUNT];

int main()
{
    ios::sync_with_stdio(false);

    int p, x;
    cin >> p >> x;

    bool found = false;
    FOR(f, 1, 10) {
        PR(f);

        data[0] = f / x;
        int q = f % x;

        if (data[0] == 0) continue;

        FOR(i, 1, p) {
            int number = (q * 10 + data[i - 1]);
            PR((int)data[i-1], q, number);
            data[i] = number / x;
            q = number % x;
        }

        if (q == 0 && data[p-1] == f) {
            found = true;
            break;
        }
    }

    if (found) {
        REP(i, p) {
            cout << (int)data[i];
        }
        cout << endl;
    } else {
        cout << "Impossible" << endl;
    }

    return 0;
}
