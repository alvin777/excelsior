#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <array>
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
const int MAX_COUNT = 1e3+1;
const int MOD = 1e9 + 7;


#define ONLINE_JUDGE

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
array<char, MAX_COUNT> data;

bool less(int i1, int i2, int shift1, int shift2) {
    REP(i, n) {
        int val1 = (data[(i1 + i) % n] + shift1) % 10;
        int val2 = (data[(i2 + i) % n] + shift2) % 10;
        if (val1 < val2) {
            return true;
        } else if (val1 > val2) {
            return false;
        }
    }
    return false;
}

void print(int i1, int shift) {
    REP(i, n) {
        cout << ((data[(i1 + i) % n] + shift) % 10);
    }

    cout << endl;
}

int main()
{
    ios::sync_with_stdio(false);

    cin >> n;
    REP(i, n) {
        char c;
        cin >> c;
        data[i] = c - '0';
        PR(data[i]);
    }

    int min_shift = 0;
    int min_ind = 0;
    REP(i, n) {
        REP(j, 10) {
            if (::less(i, min_ind, j, min_shift)) {
                min_ind = i;
                min_shift = j;
            }
        }
    }

    print(min_ind, min_shift);

    return 0;
}
