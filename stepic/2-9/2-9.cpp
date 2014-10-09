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
const int MAX_COUNT = 1e5;


int n;
int data[MAX_COUNT];
map<int, int> m;

int main()
{
    ios::sync_with_stdio(false);

    cin >> n;
    REP(i, n) {
        int num;
        cin >> num;
        m[num] += 1;
    }

    map<int, int>::const_iterator it = m.begin();
    for (; it != m.end(); ++it) {
        // D(it->first); DE(it->second);
        if (it->second > n/2) {
            cout << "1" << endl;
            return 0;
        }
    }

    cout << "0" << endl;

    return 0;
}