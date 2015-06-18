#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>

#include <stdio.h>

using namespace std;
typedef long long ll;
typedef vector<int> vi; 

#define REP(k,a) for(int k=0; k < (a); ++k)
#define FOR(i,a,b) for(int i=a; i < (b); ++i)
#define ALL(a) begin(a), end(a)
#define COUNT(a) (sizeof(a)/sizeof(a[0]))

const int INF = 1e9;
const int MAX_COUNT = 2001;
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


int n, t;
double p;
double dp[MAX_COUNT][MAX_COUNT];


int main()
{
    ios::sync_with_stdio(false);

    cin >> n >> p >> t;

    // PR(n, p, t);

    dp[0][0] = 1;
    FOR(i, 0, t) {
        REP(j, i + 1) {
            // PR(i, j, n);
            if (j < n) {
                dp[i + 1][j + 1] += p * dp[i][j];
                dp[i + 1][j]     += (1 - p) * dp[i][j];
            } else {
                dp[i + 1][j] += dp[i][j];
            }
            // PR(dp[i + 1][j + 1], dp[i + 1][j]);
        }
    }

    double ans = 0;
    // PR(t + 1, n);
    FOR(j, 1, min(t, n) + 1) {
        // PR(j, t, ans);
        ans += dp[t][j] * j; 
    }
    // PR(ans);

    // cout << setprecision(6) << ans << endl;
    printf("%.6f\n", ans);

    return 0;
}
