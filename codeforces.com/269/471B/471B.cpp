#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <fstream>

using namespace std;
typedef long long ll;
typedef vector<int> vi; 

#define REP(k,a) for(int k=0; k < (a); ++k)
#define ALL(a) begin(a), end(a)
#define D(a) cout << #a ": " << a << endl;

const int MAX_COUNT = 2001;

typedef struct {
    int complexity;
    int index;
} rec_t;

rec_t data[MAX_COUNT];


int main()
{
    ios::sync_with_stdio(false);

    int n;
    cin >> n;

    REP(i, n) {
        cin >> data[i].complexity;
        data[i].index = i;
    }

    stable_sort(data, data+n, [](const rec_t& r1, const rec_t& r2){ return r1.complexity < r2.complexity; });

    int i1 = -1;
    REP(i, n-1) {
        if (data[i].complexity == data[i+1].complexity) {
            i1 = i;
            break;
        }
    }

    int i2 = -1;
    for(int i = i1 + 1; i < n-1; i++) {
        if (data[i].complexity == data[i+1].complexity) {
            i2 = i;
            break;
        }
    }

    if (i1 < 0 || i2 < 0) {
        cout << "NO" << endl;
        return 0;
    }

    cout << "YES" << endl;

    REP(k, 3) {
        if (k == 1) {
            swap(data[i1], data[i1+1]);
        } else if (k == 2) {
            swap(data[i1], data[i1+1]);
            swap(data[i2], data[i2+1]);
        }
        
        REP(i, n) {
            cout << data[i].index + 1 << " ";
        }
        cout << endl;

        if (k == 1) {
            swap(data[i1], data[i1+1]);
        }
    }

    return 0;
}