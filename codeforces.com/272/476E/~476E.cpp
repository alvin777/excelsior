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
const int MAX_COUNT = 2001;
const int MOD = 1e9 + 7;


typedef tuple<int, bool> matches_t; // full, partial

ostream& operator<< (ostream& o, const matches_t& m) {
    return o << "(" << get<0>(m) << ", " << boolalpha << get<1>(m) << ")";
}


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

#else
# define PR(...)
# define Indent int
#endif

string str;
string prefix;

matches_t memo[MAX_COUNT][MAX_COUNT];

matches_t solve(int str_pos, int pref_pos, int left) {
    matches_t ret;

    Indent ind;
    PR(ind, str_pos, pref_pos, left);

    if (left < 0) {
        ret = matches_t{-INF, false};
        PR(ind, "<<", ret);
        return ret;
    }

    if (str_pos == str.length()) {

        if (left != 0) {
            ret = matches_t{-INF, false};
        } else {
            ret = (pref_pos == prefix.length()) ? matches_t{0, true} : matches_t{0, false};
        }

        PR(ind, "<<", ret);
        return ret;
    }

    if (pref_pos == prefix.length()) {
        pref_pos = 0;
    }

    if (get<0>(memo[str_pos][left]) != -INF) {
        ret = memo[str_pos][left];
        PR(ind, "cache hit");
    } else {
        auto matches_skip  = solve(str_pos + 1, pref_pos, left - 1);  // skip
        auto matches_match = solve(str_pos + 1, pref_pos + 1, left);  // match

        auto should_skip = matches_skip > matches_match;

        auto matches = max(matches_skip, matches_match);

        if (should_skip) {
            ret = matches_skip;
        } 
        else if (str[str_pos] == prefix[pref_pos]) {
            if (pref_pos == 0) {
                if (get<1>(matches)) {
                    ret = matches_t{get<0>(matches) + 1, false};    // was partial match, now full match
                } else {
                    ret = matches_t{get<0>(matches), false};        // were no partial match
                }
            }
            else if (pref_pos == prefix.length() - 1) {             // new partial match
                ret = matches_t{get<0>(matches), true};
            } 
            else {
                ret = matches;                                      // leave partial/full matches
            }
        } else {
            ret = matches_t{get<0>(matches), false};                // no partial match, retain full matches
        }

        memo[str_pos][left] = ret;
    }

    PR(ind, "<<", ret);

    return ret;
}

int main()
{
    ios::sync_with_stdio(false);

    cin >> str >> prefix;

    fill_n(&memo[0][0], sizeof(memo)/sizeof(memo[0][0]), matches_t{-INF, false});
    REP(i, str.length() + 1) {
        cout << get<0>(solve(0, 0, i)) << " ";
    }

    cout << endl;

    return 0;
}