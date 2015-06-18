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
// const int MOD = 53;
const int MOD = 1e7+7;


//  0 1 2 3 4 5 6
//  A B A B A B C
//    ^
//  (r - bm*text[i-len])*10 + text[i]

//    r
// 0 65
// 1 66
// ...

// 

int rk_find(const string& text, const string& pattern) {
    int bm = 1;
    REP(i, pattern.size() - 1) {
        bm = bm*10 % MOD;
    }

    int f = 0;
    REP(i, pattern.size()) {
        f = (f*10 + pattern[i]) % MOD;
    }

    int r = 0;
    FOR(i, 0, text.size()) {
        int sub = 0;
        if (i >= pattern.size()) {
            sub = text[i - pattern.size()] * bm % MOD;
        }

        r = (((r + MOD - sub) * 10) + text[i]) % MOD;

        if (r == f) {
            return i - (pattern.size() - 1);
        }
    }

    return -1;
}

template<typename T>
void check_equals(const T& actual, const T& expected, const string& message = "Check failed.") {
    if (actual != expected) {
        cout << message << " Expected: " << expected << ", actual: " << actual << endl;
    } else {
        cout << ".";
    }
}

int main()
{
    check_equals(rk_find("AAAAA", "A"), 0);
    check_equals(rk_find("AAAAA", "B"), -1);
    check_equals(rk_find("AAAAA", "AA"), 0);
    check_equals(rk_find("BAAAA", "AA"), 1);
    check_equals(rk_find("BABAB", "AA"), -1);
    check_equals(rk_find("BBBAA", "AA"), 3);
    check_equals(rk_find("TONWASSOSENSIBLEOFARISINGDESIR", "SINGDES"), 21);


    return 0;
}
