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


unsigned long long
choose(unsigned long long k, unsigned long long n) {
    PR("choose", k, n);
    if (k > n) {
        return 0;
    }
    unsigned long long r = 1;
    for (unsigned long long d = 1; d <= k; ++d) {
        r *= n--;
        r /= d;
    }
    return r;
}

int main()
{
    ios::sync_with_stdio(false);

    string sent, received;
    cin >> sent >> received;

    int delta = 0;
    int free_steps = 0;

    REP(i, sent.length()) {
        if (sent[i] == '+') {
            delta++;
        } else if (sent[i] == '-') {
            delta--;
        }
    }

    REP(i, received.length()) {
        if (received[i] == '+') {
            delta--;
        } else if (received[i] == '-') {
            delta++;
        } else {
            free_steps++;
        }
    }

    delta = abs(delta);

    PR(delta, delta + (free_steps - delta)/2, free_steps, choose(delta + (free_steps - delta)/2, free_steps), 1 << free_steps);
    // check edge cases

    if ((delta & 1) != (free_steps & 1)) {
        cout << 0 << endl;
        return 0;
    }

    if (delta > free_steps) {
        cout << 0 << endl;
        return 0;
    }

    double prob = (double)choose(delta + (free_steps - delta)/2, free_steps) / (1 << free_steps);

    cout << setprecision(12) << prob << endl;

    return 0;
}