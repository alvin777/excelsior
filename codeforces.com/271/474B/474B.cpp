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
int cum_data[MAX_COUNT];


template<typename T> 
void print_array(T first, T last, const string& label = "") {
    if (label.size()) {
        cout << label << ": ";
    }

    while (first != last) {
        cout << *first++ << " ";
    }

    cout << endl;
}

int main()
{
    ios::sync_with_stdio(false);

    cin >> n;

    REP(i, n) {
        cin >> data[i];
    }

    cum_data[0] = data[0];
    FOR(i, 1, n) {
        cum_data[i] = cum_data[i-1] + data[i];
    }

    // print_array(data, data+n, "data");
    // print_array(cum_data, cum_data+n, "cum_data");

    int m;
    cin >> m;

    REP(i, m) {
        int t;
        cin >> t;

        auto it = lower_bound(cum_data, cum_data + n, t);
        cout << distance(cum_data, it) + 1 << endl;
    }

    return 0;
}