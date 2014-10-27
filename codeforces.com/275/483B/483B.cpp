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


bool check(ll v, ll c1, ll c2, ll x, ll y) {
    ll res_x = max(c1 - (v/y - v/(x*y)), 0LL);
    ll res_y = max(c2 - (v/x - v/(x*y)), 0LL);

    ll res = v - v/x - v/y + v/(x*y);

    PR(res, res_x, res_y);

    return res >= res_x + res_y;
}

int main()
{
    ios::sync_with_stdio(false);

    ll c1, c2, x, y;
    cin >> c1 >> c2 >> x >> y;

    PR(c1, c2, x, y);

    ll min_v = 1;
    ll max_v = max(c1 * x, c2 * y);

    while (max_v >= min_v) {
        ll mid_v = min_v + (max_v - min_v)/2;

        PR(min_v, max_v, mid_v, check(mid_v, c1, c2, x, y));

        if (check(mid_v, c1, c2, x, y)) {
            max_v = mid_v - 1;
        } else {
            min_v = mid_v + 1;
        }
    }

    cout << min_v << endl;

    return 0;
}
