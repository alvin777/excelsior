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
#define COUNT(a) (sizeof(a)/sizeof(a[0]))

const int INF = 1e9;
const int MAX_COUNT = 2e5;
const int MOD = 1e9 + 7;


// #define ONLINE_JUDGE

#ifndef ONLINE_JUDGE 

///// trace helpers /////



#else
# define PR(...)
#endif


ll n, l, x, y;
ll data[MAX_COUNT];

bool check(int mark) {
    ll found_mark = *lower_bound(data, data+n, mark);
    return found_mark == mark;
}

int main()
{
    ios::sync_with_stdio(false);

    cin >> n >> l >> x >> y;
    REP(i, n) {
        cin >> data[i];
    }

    int x_ind = -1;
    int y_ind = -1;
    int d_ind = -1;
    int d2_ind = -1;
    REP(i, n) {
        if ((x_ind < 0 && check(data[i] + x)) || check(data[i] - x)) {
            x_ind = i;
        }
        if ((y_ind < 0 && check(data[i] + y)) || check(data[i] - y)) {
            y_ind = i;
        }
        if (d_ind < 0 && check(data[i] + (y-x)) && (data[i] + y <= l)) {
            d_ind = i;
        } else if (d_ind < 0 && check(data[i] - (y-x)) && (data[i] - y >= 0)) {
            d_ind = i;
        }
        if (d2_ind < 0 && check(data[i] + (y+x)) && (data[i] + y+x <= l)) {
            d2_ind = i;
        } 
    }

    if (x_ind >= 0 && y_ind >= 0) {
        cout << 0 << endl;
    } 
    else if (x_ind < 0 && y_ind < 0) {
        if (d_ind >= 0) {
            cout << 1 << endl;
            if (check(data[d_ind] + (y-x)) && (data[d_ind] + y <= l)) {
                cout << data[d_ind] + y << endl;
            } else {
                cout << data[d_ind] - y << endl;
            }
        } else if (d2_ind >= 0) {
            cout << 1 << endl;
            cout << data[d2_ind] + x << endl;
        }
        else {
            cout << 2 << endl;
            cout << x << " " << y << endl;
        }
    } 
    else if (x_ind < 0) {
        cout << 1 << endl;
        cout << x << endl;
    }
    else if (y_ind < 0) {
        cout << 1 << endl;
        cout << y << endl;
    }

    return 0;   
}
