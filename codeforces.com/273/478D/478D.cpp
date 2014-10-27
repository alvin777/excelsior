#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <numeric>

using namespace std;
typedef long long ll;
typedef vector<int> vi; 

#define REP(k,a) for(int k=0; k < (a); ++k)
#define FOR(i,a,b) for(int i=a; i < (b); ++i)
#define ALL(a) begin(a), end(a)
#define COUNT(a) (sizeof(a)/sizeof(a[0]))

const int INF = 1e9;
const int MAX_COUNT = 2e5 + 1;
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


ll r, g;

ll prev_dp[MAX_COUNT];
ll dp[MAX_COUNT];

int main()
{
    ios::sync_with_stdio(false);

    cin >> r >> g;

    ll h = (sqrt(1+8*(r+g)) - 1)/2;

    ll balls = h*(h+1)/2;

    ll min_r = balls - g;
    ll max_r = r;

    // PR(h, balls, min_r, max_r);

    fill_n(prev_dp, COUNT(prev_dp), 1);
    // prev_dp[0] = 1;
    // fill_n(dp,      COUNT(dp),      0);

    FOR(i, 1, h+1) {
        // PR(dump(prev_dp, prev_dp+10));
        REP(j, max_r + 1) {
            // PR(j, h, dp[j], prev_dp[j-h])

            dp[j] = prev_dp[j];
            if (j >= i) {
                dp[j] = (dp[j] + prev_dp[j-i]) % MOD;
            }
        }
        // PR(dump(dp, dp+10));
        swap(dp, prev_dp);
    }

    ll ans = prev_dp[max_r];
    if (min_r > 0) {
        ans = (ans + MOD - prev_dp[min_r - 1]) % MOD;
    }

    cout << ans << endl;

    return 0;
}