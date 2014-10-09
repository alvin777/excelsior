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

char kb[] = "qwertyuiopasdfghjkl;zxcvbnm,./";


int main()
{
    ios::sync_with_stdio(false);

    char side;
    cin >> side;

    int off = side == 'R' ? -1 : 1;

    char c;
    while (cin >> c) {
        REP(i, sizeof(kb)) {
            if (kb[i] == c) {
                cout << kb[i+off];
                break;
            }
        }
    }

    cout << endl;

    return 0;
}