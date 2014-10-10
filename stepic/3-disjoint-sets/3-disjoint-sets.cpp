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
const int MAX_COUNT = 1e5 + 1;
const int MOD = 1e9 + 7;


// #define ONLINE_JUDGE

// #ifndef ONLINE_JUDGE 

// ///// trace helpers /////
// #define PR(...) pr(#__VA_ARGS__, __VA_ARGS__);

// template<typename T>
// void pr(const string& name, T t) {
//     cout << name << ": " << t << endl;
// }

// template<typename T, typename ... Types>
// void pr(const string& names, T t, Types ... rest) {
//     auto comma_pos = names.find(',');
//     cout << names.substr(0, comma_pos) << ": " << t << ", ";
    
//     auto next_name_pos = names.find_first_not_of(" \t\n", comma_pos + 1);
//     pr(string(names, next_name_pos), rest ...);
// }

// #else
// # define PR(...)
// #endif


int data[MAX_COUNT];


int find(int a) {
    // PR(a, data[a]);
    if (a == data[a]) return a;

    int p = find(data[a]);
    data[a] = p;
    return p;
}

void union_sets(int a, int b) {
    data[find(a)] = find(b);
}

int main()
{
    ios::sync_with_stdio(false);

    int n, qn;
    cin >> n >> qn;
    REP(i, n+1) {
        data[i] = i;
    }

    REP(i, qn) {
        string command;
        cin >> command;

        if (command == "Check") {
            int a, b;
            cin >> a >> b;
            cout << (find(a) == find(b)) << endl;
        } else if (command == "Union") {
            int a, b;
            cin >> a >> b;
            union_sets(a, b);
        }
    }

    return 0;
}