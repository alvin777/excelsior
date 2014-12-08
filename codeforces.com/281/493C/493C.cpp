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
const int MAX_COUNT = 2e5+1;
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


int first_size = 0;
int second_size = 0;
int first[MAX_COUNT];
int second[MAX_COUNT];


int main()
{
    ios::sync_with_stdio(false);

    cin >> first_size;
    REP(i, first_size) {
        cin >> first[i];
    }

    cin >> second_size;
    REP(i, second_size) {
        cin >> second[i];
    }

    sort(first, first + first_size);
    sort(second, second + second_size);

    int i = 0;
    int j = 0;

    ll max_delta = first_size*3 - second_size*3;
    ll ans_a = 3*first_size;
    ll ans_b = 3*second_size;

    PR(first_size, second_size);

    while (i < first_size && j < second_size) {
        ll a = 2*i + 3*(first_size - i);
        ll b = 2*j + 3*(second_size - j);
        ll delta = a - b;

        PR(i, j, first[i], second[j], a, b, delta, max_delta);

        if (delta > max_delta || (delta == max_delta && a > ans_a)) {
            max_delta = delta;
            ans_a = a;
            ans_b = b;
        }

        if (first[i] < second[j]) {
            i++;
        } else if (first[i] > second[j]) {
            j++;
        } else {
            i++;
            j++;
        }
    }

    while (i < first_size) {
        ll a = 2*i + 3*(first_size - i);
        ll b = 2*second_size;
        ll delta = a - b;

        PR("i", i, j, a, b, delta, max_delta);

        if (delta > max_delta || (delta == max_delta && a > ans_a)) {
            max_delta = delta;
            ans_a = a;
            ans_b = b;
        }

        i++;
    }

    while (j < second_size) {
        ll a = 2*first_size;
        ll b = 2*j + 3*(second_size - j);
        ll delta = a - b;

        PR("j", i, j, a, b, delta, max_delta);

        if (delta > max_delta || (delta == max_delta && a > ans_a)) {
            max_delta = delta;
            ans_a = a;
            ans_b = b;
        }

        j++;
    }

    {
        ll a = 2*first_size;
        ll b = 2*second_size;
        ll delta = a - b;

        PR("j", i, j, a, b, delta, max_delta);

        if (delta > max_delta || (delta == max_delta && a > ans_a)) {
            max_delta = delta;
            ans_a = a;
            ans_b = b;
        }
    }

    cout << ans_a << ":" << ans_b << endl;

    return 0;
}
