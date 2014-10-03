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
#define D(a) cout << #a ": " << a << endl;

const int INF = 1e9;
const int MAX_MONEY = 10201;
const int MAX_COUNT = 101;


template<typename T> 
void print_array(T array, int first, int last, const string& label = "") {
    if (label.size()) {
        cout << label << ": ";
    }

    for (int i = first; i < last; i++) {
        cout << array[i] << " ";
    }

    cout << endl;
}

template<typename T>
void print_matrix(const T m, int first_row, int first_col, int last_row, int last_col, const string label = "") {
    if (label.size()) {
        cout << label << ": " << endl;
    }

    for (int i = first_row; i < last_row; i++) {
        cout << setw(3) << i << ": ";
        print_array(m[i], first_col, last_col);
    }

    // cout << endl;
}

int c[MAX_COUNT];
int v[MAX_COUNT];
int dp[MAX_MONEY][MAX_COUNT];

int main()
{
    ios::sync_with_stdio(false);

    int m, n;
    while (cin >> m >> n) 
    {
        REP(i, n) {
            cin >> c[i] >> v[i];
        }

        if (m > 1800) {
            m += 200;
        }

        // print_array(c, 0, n, "c");
        // print_array(v, 0, n, "v");

        fill_n(&dp[0][0], sizeof(dp)/sizeof(dp[0][0]), 0);

        REP(i, m + 1) {
            REP(j, n) {
                if (j == 0) {
                    dp[i][j] = c[j] > i ? 0 : v[j];
                } 
                else if (c[j] > i) {
                    dp[i][j] = dp[i][j-1];
                } 
                else {
                    dp[i][j] = max(dp[i][j-1], dp[i - c[j]][j-1] + v[j]);
                }
            }
        }

        // print_matrix(dp, 0, 0, m + 1, n, "dp");

        cout << dp[m][n-1] << endl;
    }

    return 0;
}