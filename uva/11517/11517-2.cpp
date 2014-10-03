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


int n;
int data[MAX_ITEMS];
int dp[2*MAX_AMOUNT];

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
        dp[0] = 0;

        int ans = INF;
        int ans_amount = 0;
        REP(j, n) {
            for (int i = 2 * MAX_AMOUNT- 1; i >= 0; --i) {
                if (data[j] <= i && dp[i-data[j]] < INF) {
                    dp[i] = min(dp[i], dp[i - data[j]] + 1);
                }
            }
            // print_array(dp, dp + a * 2, "dp");
        }

        FOR(i, a, 2*MAX_AMOUNT) {
            if (dp[i] < ans) {
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