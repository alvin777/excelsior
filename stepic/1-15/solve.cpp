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

const int MAX_COUNT = 1e5;


int data[MAX_COUNT];


int main()
{
    ios::sync_with_stdio(false);

    int n;
    cin >> n;

    REP(i, n) {
        cin >> data[i];
    }

    REP(i, n) {
        int j = 0;
        int k = n - 1;
        while (j <= k) {
            if (data[i] + data[j] + data[k] == 0) {
                cout << i + 1 << " " << j + 1 << " " << k + 1 << endl;
                return 0;
            } else if (data[i] + data[j] + data[k] > 0) {
                k--;
            } else {
                j++;
            }
        }
    }

    cout << "NO" << endl;

    return 0;
}