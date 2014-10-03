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
#define D(a) cout << #a ": " << a << " ";
#define DE(a) cout << #a ": " << a << endl;

const int INF = 1e9;
const int MAX_COUNT = 40;
const int MAX_S = 300;


template<typename T> 
void print_array(T first, T last, const string& label = "") {
    if (label.size()) {
        cout << label << ": ";
    }

    while (first != last) {
        cout << *first++ << " ";
    }

    cout << endl;
}

template<typename T>
void print_matrix(const T m, int first_row, int first_col, int last_row, int last_col, const string label = "") {
    if (label.size()) {
        // cout << label << ": " << endl;
    }

    for (int i = first_row; i < last_row; i++) {
        // cout << setw(3) << i << ": ";
        print_array(m[i] + first_col, m[i] + last_col);
    }

    cout << endl;
}

int n, s;
ll val_c[MAX_COUNT];
ll val_i[MAX_COUNT];

int dp[MAX_S + 1][MAX_S + 1];

// int m[MAX_S+1][MAX_S+1];

// int solve(int cur_c, int cur_i, int cur_step, int s) {
//     ll sum = cur_c*cur_c + cur_i*cur_i;
//     if (sum == s*s) {
//         return 0;
//     } else if (sum > s*s) {
//         return INF;
//     }

//     REP(j, n) {
//         m[cur_c][m_cur_i] = min(m[cur_c][m_cur_i], solve(cur_c + val_c[j], cur_i + val_i[j], s));
//     }

//     return m[cur_c][m_cur_i] + 1;
// }

int main()
{
    ios::sync_with_stdio(false);

    int tc;
    cin >> tc;

    REP(c, tc) {
        cin >> n >> s;

        REP(i, n) {
            cin >> val_c[i] >> val_i[i];
        }

        // fill_n(&m[0][0], sizeof(m)/sizeof(m[0][0]), INF);
        fill_n(&dp[0][0], sizeof(dp)/sizeof(dp[0][0]), INF);

        // int ans = solve(0, 0, 0, s);

        int ans = INF;
        REP(x, s+1) {
            REP(y, s+1) {
                if (x*x + y*y > s*s) continue;

                REP(i, n) {
                    if (val_c[i] > s || val_i[i] > s) continue;

                    if (x == val_c[i] && y == val_i[i]) {
                        dp[x][y] = 1;
                    } else if (x >= val_c[i] && y >= val_i[i]) {
                        dp[x][y] = min(dp[x][y], dp[x-val_c[i]][y-val_i[i]] + 1);
                    }                    
                }

                if (x*x + y*y == s*s) {
                    ans = min(ans, dp[x][y]);
                }
            }
        }

        // print_matrix(dp, 0, 0, s+1, s+1, "dp");

        if (ans >= INF) {
            cout << "not possible" << endl;
        } else {
            cout << ans << endl;
        }
    }

    return 0;
}