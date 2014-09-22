#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

int data[300000];

int main(int argc, char const *argv[])
{
    int count;
    cin >> count;

    for (int i = 0; i < count; ++i)
    {
        cin >> data[i];
    }

    sort(data, data+count);

    ll ans = 0;
    for (int i = 0; i < count; ++i)
    {
        ans += ll(data[i]) * (i + 2);
    }

    ans -= data[count - 1];

    cout << ans << endl;

    return 0;
}