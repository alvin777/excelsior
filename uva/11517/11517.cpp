#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>
#include <bitset>

using namespace std;
typedef long long ll;
typedef vector<int> vi; 

#define REP(k,a) for(int k=0; k < (a); ++k)
#define FOR(i,a,b) for(int i=a; i < (b); ++i)
#define ALL(a) begin(a), end(a)
#define D(a) cout << #a ": " << a << " ";
#define DE(a) cout << #a ": " << a << endl;

const int INF = 1e9;
const int MAX_AMOUNT = 1e4;
const int MAX_ITEMS = 100;


int n;
int data[MAX_ITEMS];
int dp[2*MAX_AMOUNT];
bitset<MAX_ITEMS> b[2*MAX_AMOUNT];

int main()
{
    ios::sync_with_stdio(false);

    int tc;
    cin >> tc;

    REP(c, tc) {
        int a, n;
        cin >> a >> n;

        REP(i, n) {
            cin >> data[i];
        }

        fill_n(dp, sizeof(dp)/sizeof(dp[0]), INF);

        int ans = INF;
        int ans_amount = 0;
        REP(i, 2 * MAX_AMOUNT) {
            b[i].reset();
            REP(j, n) {
                if (data[j] == i) {
                    dp[i] = 1;
                    b[i].reset();
                    b[i][j] = 1;
                    break;
                } else if (data[j] < i && (b[i-data[j]][j] == 0)) {
                    if (dp[i - data[j]] + 1 < dp[i]) {
                        dp[i] = dp[i - data[j]] + 1;
                        b[i] = b[i - data[j]];
                        b[i][j] = 1;
                    }
                }
            }
            if (i >= a && dp[i] < INF) {
                ans = dp[i];
                ans_amount = i;
                break;
            }
        }

        if (n == 0) {
            cout << 0 << " " << 0 << endl;
        } else {
            cout << ans_amount << " " << ans << endl;
        }
    }

    return 0;
}