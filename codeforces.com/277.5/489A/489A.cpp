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
const int MAX_COUNT = 3e3+1;
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
int data[MAX_COUNT];
int sorted_data[MAX_COUNT];

vector<pair<int, int>> ans;

int main()
{
    ios::sync_with_stdio(false);

    cin >> n;
    REP(i, n) {
        cin >> data[i];
        sorted_data[i] = data[i];
    }

    sort(sorted_data, sorted_data + n);

    REP(i, n) {
        PR(i, data[i]);
        if (data[i] != sorted_data[i]) {
            FOR(j, i + 1, n) {
                PR(j, data[j]);
                if (data[j] == sorted_data[i]) {
                    ans.push_back(make_pair(i, j));
                    swap(data[i], data[j]);
                    break;
                }
            }
        }
    }

    cout << ans.size() << endl;
    REP(i, ans.size()) {
        cout << ans[i].first << " " << ans[i].second << " " << endl;
    }

    return 0;
}
