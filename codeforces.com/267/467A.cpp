#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

int main(int argc, char const *argv[])
{
    int count;
    cin >> count;

    int ans = 0;
    for (int i = 0; i < count; ++i)
    {
        int max, cur;
        cin >> cur >> max;
        if (max - cur >= 2) {
            ans++;
        }
    }

    cout << ans << endl;

    return 0;
}