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
const int MAX_COUNT = 1e3+1;
const int MOD = 1e9 + 7;


int n, m;
string data[MAX_COUNT];
bool skip_row[MAX_COUNT];


int main()
{
    ios::sync_with_stdio(false);

    cin >> n >> m;
    REP(i, n) {
        cin >> data[i];
    }

    int ans = 0;
    REP(i, m) {
        bool skip_col = false;
        FOR(j, 1, n) {
            if (!skip_row[j] && data[j][i] < data[j - 1][i]) {
                ans++;
                skip_col = true;
                break;
            }
        }

        if (!skip_col) {
            FOR(j, 1, n) {
                if (data[j][i] > data[j - 1][i]) {
                    skip_row[j] = true;
                }
            }
        }
    }
    
    cout << ans << endl;

    return 0;
}
