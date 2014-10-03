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
const int MAX_COUNT = 30001;


int data[] = {1, 5, 10, 25, 50};
const int n = sizeof(data)/sizeof(*data);
int a;

ll dp[MAX_COUNT];


int main()
{
    ios::sync_with_stdio(false);


    while (cin >> a) {
        fill_n(&dp[0], sizeof(dp)/sizeof(dp[0]), 0);

        REP(i, n) {
            REP(j, a+1) {
                if (j == data[i]) {
                    dp[j] += 1;
                }
                else if (j > data[i]) {
                    dp[j] += dp[j-data[i]];
                }
            }
        }

        if (dp[a] > 1) {
            cout << "There are " << dp[a] << " ways to produce " << a << " cents change." << endl;
        } else {
            cout << "There is only 1 way to produce " << a << " cents change." << endl;
        }
    }

    return 0;
}