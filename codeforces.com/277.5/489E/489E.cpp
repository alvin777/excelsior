#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;
typedef long long ll;
typedef vector<int> vi; 
typedef pair<double, ll> dll;

#define REP(k,a) for(int k=0; k < (a); ++k)
#define FOR(i,a,b) for(int i=a; i < (b); ++i)
#define ALL(a) begin(a), end(a)
#define COUNT(a) (sizeof(a)/sizeof(a[0]))

const int INF = 1e9;
const int MAX_COUNT = 1001;
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


int n, d;
int x[MAX_COUNT];
int b[MAX_COUNT];

dll dp[MAX_COUNT];
int p[MAX_COUNT];

double calc(const dll& pair) {
    return pair.first / pair.second;
}

double discomfort(int actual, int planned) {
    return sqrt(abs(actual - planned));
}

int main()
{
    ios::sync_with_stdio(false);

    cin >> n >> d;
    REP(i, n) {
        cin >> x[i] >> b[i];
    }

    REP(i, n) {
        PR(i);

        dp[i].first = discomfort(x[i], d);
        dp[i].second = b[i];
        double best_ratio = calc(dp[i]);

        p[i] = -1;

        PR("    ", dp[i].first, dp[i].second, discomfort(x[i], d), b[i], best_ratio);

        REP(j, i) {
            auto check_stop = make_pair(dp[j].first + discomfort(x[i] - x[j], d),
                                      dp[j].second + b[i]);
            double ratio = calc(check_stop);

            PR("    ", j, dp[j].first, dp[j].second, discomfort(x[i] - x[j], d), b[i], ratio);

            if (ratio < best_ratio) 
            {
                best_ratio = ratio;
                dp[i] = check_stop;

                p[i] = j;
            }
        }
    }

    vi ans;
    int i = n-1;
    while(i >= 0) {
        ans.push_back(i);
        i = p[i];
    }

    reverse(ALL(ans));

    for (int v : ans) {
        cout << v + 1 << " ";
    }

    cout << endl;

    return 0;
}
