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
#define COUNT2(a) (sizeof(a)/sizeof(a[0][0]))

const int INF = 1e9;
const int MAX_COUNT = 2001;
const int MOD = 1e9 + 7;


// #define ONLINE_JUDGE

#ifndef ONLINE_JUDGE 

///// trace helpers /////

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


#define PR(...) pr(#__VA_ARGS__, __VA_ARGS__);

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

#else
# define PR(...)
# define Indent int
#endif

string str;
string prefix;

int memo[MAX_COUNT][MAX_COUNT];
int len[MAX_COUNT];

int calls = 0;
int hits = 0;

int solve(int str_pos, int left) {
    if (left < 0) return -INF;

    if (str_pos == str.length()) {
        return left == 0 ? 0 : -INF;
    }

    if (memo[str_pos][left] != -1) {
        return memo[str_pos][left];
    }

    int res = max(solve(str_pos + 1, left), 
                  solve(str_pos + 1, left - 1));

    if (len[str_pos] >= 0) {
        res = max(res, solve(str_pos + len[str_pos], left - len[str_pos] + prefix.length()) + 1);
    }

    memo[str_pos][left] = res;

    return res;
}

int main()
{
    ios::sync_with_stdio(false);

    cin >> str >> prefix;

    fill_n(&memo[0][0], COUNT2(memo), -1);
    fill_n(len, COUNT(len), -1);

    REP(i, str.length()) {

        if (str[i] == prefix[0]) {
            int j = i;
            int k = 0;

            while (j < str.length() && k < prefix.length()) {
                if (str[j] == prefix[k]) {
                    k++;
                }
                j++;
            }

            if (k == prefix.length()) {
                len[i] = j - i;
            }
        }
    }

    REP(i, str.length() + 1) {
        cout << solve(0, i) << " ";
    }

    cout << endl;

    return 0;
}