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


#else
# define PR(...)
#endif


template<typename T>
void check_equals(const T& actual, const T& expected, const string& message = "Check failed.") {
    if (actual != expected) {
        cout << message << " Expected: " << expected << ", actual: " << actual << endl;
    } else {
        cout << ".";
    }
}

int bm_find(const string& text, const string& pattern) {
    int right[2 << 8 * sizeof(char)];

    fill_n(right, sizeof(right)/sizeof(right[0]), -1);

    for (int i = 0; i < pattern.length(); ++i) {
        right[pattern[i]] = i;
    }

    int skip = 1;
    for (int i = 0; i <= text.length() - pattern.length(); i += skip) {
        int j = pattern.length() - 1;

        while (j >= 0 && text[i + j] == pattern[j]) { j--; }

        if (j == -1) {
            return i;
        }

        skip = j - right[text[i + j]];
        if (skip < 0) {
            skip = 1;
        }
    }

    return -1;
}

void test() {
    check_equals(bm_find("AAAAA", "A"), 0);
    check_equals(bm_find("AAAAA", "B"), -1);
    check_equals(bm_find("TONWASSOSENSIBLEOFARISINGDESIR", "SINGDES"), 21);
}

int main()
{
    test();

    return 0;
}
