#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;
int p[1000];

long count_bits(long n) {     
    unsigned int c; // c accumulates the total bits set in v
    for (c = 0; n; c++) 
        n &= n - 1; // clear the least significant bit set
    return c;
}

int diff_bits(int a, int b) {
    return count_bits(a ^ b);
}

int main(int argc, char const *argv[])
{
    int n, m, k;
    cin >> n >> m >> k;

    for (int i = 0; i < m; ++i)
    {
        cin >> p[i];
    }

    int f;
    cin >> f;

    int ans = 0;
    for (int i = 0; i < m; ++i)
    {
        if (diff_bits(p[i], f) <= k) {
            ans++;
        }
    }

    cout << ans << endl;

    return 0;
}