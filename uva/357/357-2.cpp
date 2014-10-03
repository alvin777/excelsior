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


int data[] = {1, 5, 10, 25, 50};
const int n = sizeof(data)/sizeof(*data);
int a;

ll dp[MAX_COUNT][n];


ll solve(int i, int sum) {
    // Indent ind;
    // cout << ind; DE(sum);
    if (sum < 0) {
        // cout << ind << "<< " << 0 << endl;
        return 0;
    }

    if (sum == 0) {
        // cout << ind << "<< " << 0 << endl;
        return 1;
    }

    // if (dp[sum][i] == 0) {
    ll a = 0;
        FOR(j, i, n) {
            // dp[sum][i] += solve(j, sum - data[j]);
            a += solve(j, sum - data[j]);
        }
    // }

    // cout << ind << "<< " << dp[sum] << endl;

    // return dp[sum][i];
        return a;
}

int main()
{
    ios::sync_with_stdio(false);


    while (cin >> a) {
        fill_n(&dp[0][0], sizeof(dp)/sizeof(dp[0][0]), 0);

        ll ans = solve(0, a);

        if (ans > 1) {
            cout << "There are " << ans << " ways to produce " << a << " cents change." << endl;
        } else {
            cout << "There is only 1 way to produce " << a << " cents change." << endl;
        }
    }

    return 0;
}