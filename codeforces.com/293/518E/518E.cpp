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
const int MAX_COUNT = 1e5;
const int MOD = 1e9 + 7;


// #define ONLINE_JUDGE

#ifndef ONLINE_JUDGE 

///// trace helpers /////



#else
# define PR(...)
#endif


int n, k;
int data[MAX_COUNT];
bool x[MAX_COUNT];

int process(int i, int min_border = -INF, int x_streak = 0) {
    if (x[i]) {
        int max_border = process(i + k, min_border, x_streak + 1);

        if (max_border < 0) {
            data[i] = max_border - 1;
            return max_border - 1;;
        } else if (min_border > 0) {
            data[i] = min_border;
            return min_border + 1;
        }

        return max_border;
    } else {
        if (data[i] <= min_border) {
            cout << "Incorrect sequence" << endl;
            exit(0);
        }
        return process(i + k, data[i]);
    }
}

int main()
{
    ios::sync_with_stdio(false);

    cin >> n >> k;

    bool res = true;

    REP(i, n) {
        string s;
        cin >> s;

        if (s == "?") {
            x[i] = true;
        } else {
            data[i] = atoi(s.c_str());
        }
    }

    REP(i, k) {
        process(i);
    }

    REP(i, n) {
        cout << data[i] << " ";
    }

    return 0;
}
