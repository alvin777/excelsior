#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;
typedef long long ll;
typedef vector<int> vi; 

#define REP(k,a) for(int k=0; k < (a); ++k)
#define FOR(i,a,b) for(int i=a; i < (b); ++i)
#define ALL(a) begin(a), end(a)
// #define D(a) cout << #a ": " << a << endl;

const int INF = 1e9;
const int MAX_MONEY = 10201;
const int MAX_COUNT = 101;


template<typename T> 
void print_array(T array, int first, int last, const string& label = "") {
    if (label.size()) {
        // cout << label << ": ";
    }

    for (int i = first; i < last; i++) {
        // cout << array[i] << " ";
    }

    // cout << endl;
}

template<typename T>
void print_matrix(const T m, int first_row, int first_col, int last_row, int last_col, const string label = "") {
    if (label.size()) {
        // cout << label << ": " << endl;
    }

    for (int i = first_row; i < last_row; i++) {
        // cout << setw(3) << i << ": ";
        print_array(m[i], first_col, last_col);
    }

    cout << endl;
}


int m, n;
int c[MAX_COUNT];
int v[MAX_COUNT];
int dp[MAX_MONEY][MAX_COUNT];


class IndentationHolder {
public:
    IndentationHolder() {
        ++level;
    }
    ~IndentationHolder() {
        --level;
    }

    string getIndentationString() {
        return string(level*2, ' ');
    }
private:
    static int level;
};

int IndentationHolder::level = -1;


int solve(int spent, int i) {

    if (spent > m && m < 1800) {
        return -INF;
    }

    if (spent > m + 200) {
        return -INF;
    }

    if (i == n) {
        if (spent > m && spent <= 2000) {
            return -INF;
        }

        return 0;
    } 

    if (dp[spent][i] == -1) {    
        dp[spent][i] = max(solve(spent, i+1), 
                           solve(spent+c[i], i+1) + v[i]);
    } 

    return dp[spent][i];
}

int main()
{
    ios::sync_with_stdio(false);

    while (cin >> m >> n) 
    {
        REP(i, n) {
            cin >> c[i] >> v[i];
        }

        fill_n(&dp[0][0], sizeof(dp)/sizeof(dp[0][0]), -1);

        int ans = solve(0, 0);

        // print_matrix(dp, 0, 0, m, n, "dp");

        cout << ans << endl;
    }

    return 0;
}