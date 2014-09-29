#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <fstream>
#include <math.h>

using namespace std;
typedef long long ll;
typedef vector<int> vi; 

#define REP(k,a) for(int k=0; k < (a); ++k)
#define ALL(a) begin(a), end(a)
#define FOR(i,a,b) for(int i=a; i < (b); ++i)
#define D(a) cout << #a ": " << a << endl;

const int MAX_COUNT = 1e5;


int data[MAX_COUNT];


int main()
{
    ios::sync_with_stdio(false);

    ll n;
    cin >> n;

    ll ans = 0;
    FOR(i, 1, 1000000) {
        // D(i);
        ll min_cards = 1.5*i*i + 0.5*i;
        if (min_cards > n) {
            break;
        }
        // D((n - min_cards) % 3);
        if ((n - min_cards) % 3 == 0) {
            ans++;
        }
    }

    cout << ans << endl;

    return 0;
}