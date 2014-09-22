#include <iostream>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <cstring>

using namespace std;

typedef long long ll;

// const int MAX_NUMBER = 1e9;
const int MAX_COUNT = 5000;

ll data[MAX_COUNT];
ll sums[MAX_COUNT];
ll dp[MAX_COUNT];
ll prev_dp[MAX_COUNT];

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

int main(int argc, char const *argv[])
{
    ios::sync_with_stdio(false);

    int n, m, k;
    cin >> n >> m >> k;

    for (int i = 0; i < n; ++i)
    {
        cin >> data[i];
    }

    sums[0] = accumulate(data, data + m, 0LL);
    // cout << "sums[" << 0 << "]: " << sums[0] << endl;
    for (int i = 1; i < n - m + 1; ++i)
    {
        sums[i] = sums[i-1] - data[i-1] + data[i+m-1];
        // cout << "sums[" << i << "]: " << sums[i] << endl;
    }

    // init dp
    dp[0] = sums[0];
    for (int i = 1; i < n - m + 1; ++i)
    {
        dp[i] = max(dp[i-1], sums[i]);
    }
    // print_array(dp, 0, n - m + 1, "dp");

    copy(dp, dp + n, prev_dp);
    for (int i = 1; i < k; ++i)
    {
        dp[m*i] = prev_dp[m*(i-1)] + sums[m*i];
        for (int j = m*i + 1; j < n - m + 1; ++j)
        {
            dp[j] = max(prev_dp[j-m] + sums[j], dp[j-1]);
        }
        // print_array(dp, 0, n - m + 1, "dp");
        copy(dp, dp + n, prev_dp);
    }

    cout << dp[n-m] << endl;

    return 0;
}