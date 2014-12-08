#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>
#include <cassert>

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


struct stats_t {
    int hp, a, d;
} pl, mon, cost;

int ceil_div(int x, int y) {
    assert(x >= 0 && y >= 0);
    if (y == 0) return INF;

    return (x + y - 1) / y;
}

int calc_cost(int hp, int a, int d) {
    return hp*cost.hp + a*cost.a + d*cost.d;
}

int main()
{
    ios::sync_with_stdio(false);

    cin >> pl.hp >> pl.a >> pl.d;
    cin >> mon.hp >> mon.a >> mon.d;
    cin >> cost.hp >> cost.a >> cost.d;

    int min_cost = INF;
    FOR(a, max(mon.d + 1, pl.a), 201) {
        FOR(d, pl.d, 101) {
            int turns = ceil_div(mon.hp, max(a - mon.d, 0));
            int req_hp = turns * max(mon.a - d, 0);
            int cost = calc_cost(max(req_hp + 1, pl.hp) - pl.hp, a - pl.a, d - pl.d);
            if (cost < min_cost)
                PR(a, d, turns, req_hp, cost);
            min_cost = min(min_cost, max(cost, 0));
        }
    }

    cout << min_cost << endl;

    return 0;
}
