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

ll s(ll x) {
    int sum = 0;
    while (x > 0) {
        sum += x % 10;
        x /= 10;
    }
    return sum;
}

ll pow(int x, int y) {
    ll res = 1;
    while (y-- > 0) {
        res *= x;
    }
    return res;
}

int main()
{
    ios::sync_with_stdio(false);

    int a, b, c;
    cin >> a >> b >> c;

    vi ans;

    FOR(i, 1, 82) {
        ll x = b * pow(i, a) + c;
        PR(i, x, s(x));
        if (x < 1000000000 && s(x) == i) {
            ans.push_back(x);
        }
    }

    cout << ans.size() << endl;
    for (auto v : ans) {
        cout << v << " ";
    }

    cout << endl;

    return 0;
}
