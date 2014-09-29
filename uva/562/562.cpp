#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <fstream>
#include <numeric>

#define REP(k,a) for(int k=0; k < (a); ++k)
#define FOR(k,a,b) for(int k=(a); k <= (b); ++k)
#define ALL(a) begin(a), end(a)
#define D(a) cout << #a ": " << a << endl;

using namespace std;


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


typedef long long ll;

const int MAX_COUNT    =   100;
const int MAX_WEIGHT = 25100; // (500/2 + 1) * 100

int data[MAX_COUNT];

int dp[MAX_WEIGHT][MAX_COUNT];

int solve(int n) {
    // fill(&dp[0][0], &dp[0][0] + sizeof(dp), 0);
    int sum = accumulate(data, data+n, 0);
    int halfsum = sum >> 1;

    // print_array(data, 0, n, "data");
    // D(n);
    // D(sum);
    // D(halfsum);

    fill(dp[0], dp[1], 0);

    REP(i, n) {
        dp[1][i] = data[i] <= 1 ? data[i] : 0;
    }

    // print_array(dp[0], 0, n, "dp");

    FOR(w, 2, halfsum) {
        REP(i, n) {
            if (i == 0) {
                dp[w][i] = data[i] <= w ? data[i] : 0;
            } else if (data[i] <= w && dp[w-data[i]][i-1] + data[i] <= w) {
                dp[w][i] = max(dp[w][i-1], dp[w-data[i]][i-1] + data[i]);
            } else {
                dp[w][i] = dp[w][i-1];
            }
        }
        // print_array(dp[w], 0, n, "dp");
    }

    return dp[halfsum][n-1];
}

int main()
{
    ios::sync_with_stdio(false);

    int tc;
    cin >> tc;

    for (int i = 0; i < tc; ++i)
    {
        int n;
        cin >> n;

        // D(n);

        for (int j = 0; j < n; ++j)
        {
            cin >> data[j];
        }

        int sum = accumulate(data, data+n, 0);
        cout << sum - 2*solve(n) << endl;
    }

    return 0;
}
