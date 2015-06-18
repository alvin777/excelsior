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


int n;
string s, t;

int s_map[256];
int t_map[256];

int main()
{
    ios::sync_with_stdio(false);

    cin >> s >> t;

    for (char c : s) {
        s_map[c]++;
    }

    for (char c : t) {
        t_map[c]++;
    }

    int hooray = 0;
    for (char i = 'A'; i <= 'Z'; i++) {
        int local_hooray = min(s_map[i], t_map[i]);
        hooray += local_hooray;
        s_map[i] -= local_hooray;
        t_map[i] -= local_hooray;
        // PR(i, s_map[i], t_map[i]);
    }

    for (char i = 'a'; i <= 'z'; i++) {
        int local_hooray = min(s_map[i], t_map[i]);
        hooray += local_hooray;
        s_map[i] -= local_hooray;
        t_map[i] -= local_hooray;
        // PR(i, s_map[i], t_map[i]);
    }

    int opa = 0;
    const char DELTA = 'a' - 'A';
    for (char i = 'A'; i <= 'Z'; i++) {
        int local_opa = min(s_map[i], t_map[i + DELTA]);
        opa += local_opa;
        s_map[i] -= local_opa;
        t_map[i + DELTA] -= local_opa;
        // PR(i, char(i + DELTA), s_map[i], t_map[i + DELTA]);
    }

    PR(opa);

    for (char i = 'a'; i <= 'z'; i++) {
        int local_opa = min(s_map[i], t_map[i - DELTA]);
        opa += local_opa;
        s_map[i] -= local_opa;
        t_map[i - DELTA] -= local_opa;
        // PR(i, char(i - DELTA), s_map[i], t_map[i - DELTA], opa);
    }

    cout << hooray << " " << opa << endl;

    return 0;
}
