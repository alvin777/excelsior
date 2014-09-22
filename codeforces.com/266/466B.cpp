#include <iostream>
#include <math.h>

#define d(x) cout << #x ": " << x << endl;

typedef long long ll;

using namespace std;


void solve(int a0, int b0, ll s, ll& a, ll& b) {
    ll max_a = ceil(sqrt(s));

    // d(max_a);

    ll ai = a0;
    ll bi = max<ll>(b0, ceil(double(s)/ai));
    a = ai;
    b = bi;
    ll min_s = a*b;
    while (ai <= max_a && bi >= b0) {
        bi = ceil(double(s)/ai);
        // d(ai);
        // d(bi);
        if (ai * bi < min_s && bi >= b0) {
            a = ai;
            b = bi;
            min_s = a * b;
            // cout << "current sol, a: " << a << ", b: " << b << ", s: " << min_s << endl;
        }
        ai++;
    }
}

int main()
{
    int n, a0, b0;
    cin >> n >> a0 >> b0;

    ll s = n*6LL;

    bool swapped = false;
    if (a0 > b0) {
        swap(a0, b0);
        swapped = true;
    }

    ll a = a0;
    ll b = b0;
    solve(a0, b0, s, a, b);

    cout << ll(a) * b << endl;
    if (swapped) {
        swap(a, b);
    }
    cout << a << " " << b << endl;

    return 0;
}