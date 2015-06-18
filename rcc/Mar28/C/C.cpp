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
struct print_t {
    T first;
    T last;
};

template<typename T>
ostream& operator<< (ostream& o, const print_t<T>& s) {
    o << "[";
    for (auto it = s.first; it != s.last; ++it) {
        if (it != prev(s.last)) {
            o << *it << ", ";
        } else {
            o << *it;
        }
    }
    o << "]";

    return o;
}

template<typename T>
print_t<T> dump(T first, T last, string label = "") {
    return {first, last};
}

class Indent
{
public:
    friend ostream& operator<< (ostream& o, const Indent& indent);

    Indent()  { ++level; }
    ~Indent() { --level; }

private:
    static int level;
};

int Indent::level = -1;

ostream& operator<< (ostream& o, const Indent& indent) {
    return o << string(indent.level*4, ' ');
}

template<typename T>
void print_value(const string& name, const T& value) {
    if (name.find("\"") != string::npos) {
        cout << value << " ";
        return;
    }
    cout << name << ": " << value << ", ";
}

template<>
void print_value<Indent>(const string& name, const Indent& value) {
    cout << value;
}

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
ll memo[101][101][3][3];

ll solve2(const vi& stack) {
    int m_c_left = n/2;
    int ph_c_left = n/2;

    ll res = 1;
    int last = 0;

    REP(i, stack.size() - 1) {
        int v = stack[i];

        PR(i, v, last, res, m_c_left, ph_c_left);
        if (v == 1) {
            if (last == 0 || last == 1) {
                res = (res * m_c_left) % MOD;
            } else {
                res = (res * (m_c_left - 1)) % MOD;
            }
            m_c_left--;
        } else { // v == 2
            if (last == 0 || last == 2) {
                res = (res * ph_c_left) % MOD;
            } else {
                res = (res * (ph_c_left - 1)) % MOD;
            }
            ph_c_left--;
        }
        last = v;
    }

    return res;
}

ll solve(int m_left, int ph_left, int last2, int last, vi stack) {
    Indent ind;


    int i = n - m_left - ph_left;

    // PR(ind, i, m_left, ph_left, last2, last);

    if (m_left + ph_left <= 0) {
        // PR(dump(ALL(stack)));
        // return solve2(stack);
        return 1;
    }

    // if (memo[m_left][ph_left][last2][last] >= 0) 
    //     return memo[m_left][ph_left][last2][last];
    
    ll res = 0;
    if (m_left > 0  && (data[i] == 1 || data[i] == 3) && (i <= 1 || last == 1 || last == last2)) 
    {
        vi stack2 = stack;
        stack2.push_back(1);
        res += solve(m_left - 1, ph_left, last, 1, stack2);
    }

    if (ph_left > 0 && (data[i] == 2 || data[i] == 3) && (i <= 1 || last == 2 || last == last2)) {
        vi stack2 = stack;
        stack2.push_back(2);
        res += solve(m_left, ph_left - 1, last, 2, stack2);
    }

    res = res % MOD;
    // PR(ind, res);

    return memo[m_left][ph_left][last2][last] = res;
}

int main()
{
    ios::sync_with_stdio(false);

    int t;
    cin >> t;
    REP(ti, t) {
        cin >> n;
        n *= 2;
        REP(i, n) {
            cin >> data[i];
        }

        PR(dump(data, data + n));

        // fill(&memo[0][0][0][0], &memo[0][0][0][0] + sizeof(memo), -1);
        fill_n(&memo[0][0][0][0], sizeof(memo)/sizeof(memo[0][0][0][0]), -1);
        cout << solve(n/2, n/2, 0, 0, vi()) << endl;
    }

    return 0;
}
