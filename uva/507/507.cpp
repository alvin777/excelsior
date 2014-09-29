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
#define FOR(i,a,b) for(int i=a; i < (b); ++i)
#define ALL(a) begin(a), end(a)
#define D(a) cout << #a ": " << a << ", ";
#define DE(a) cout << #a ": " << a << endl;

const int MAX_COUNT = 20000;
const int INF = 1e9;

template<typename T> 
void print_array(T array, int first, int last, const string& label = "") {
    if (label.size()) {
        cout << label << ": ";
    }

    for (int i = first; i < last; i++) {
        cout << array[i] << " ";
    }

    cout << endl;
}

int data[MAX_COUNT];

int main()
{
    ios::sync_with_stdio(false);

    int tc;
    cin >> tc;

    REP(t, tc) {

        int n;
        cin >> n;
        n--;

        REP(i, n) {
            cin >> data[i];
        }

        ll max_sum = -INF;
        int max_begin = -1;
        int max_end = -1;

        ll cumulative_sum = 0;
        int cur_begin = 0;
        REP(i, n) {
            cumulative_sum += data[i];

            if (cumulative_sum > max_sum) {
                max_sum = cumulative_sum;
                max_begin = cur_begin;
                max_end = i;
            } else if (cumulative_sum == max_sum) {
                if ((i - cur_begin  > max_end - max_begin) || 
                    ((i - cur_begin == max_end - max_begin) && (i < max_begin)))
                {
                    max_begin = cur_begin;
                    max_end = i;                    
                }
            } 

            if (cumulative_sum < 0) {
                cumulative_sum = 0;
                cur_begin = i + 1;
            }
        }

        if (max_sum > 0) {
            cout << "The nicest part of route " << t + 1 << " is between stops " << max_begin + 1 << " and " << max_end + 2 << endl;
        } else {
            cout << "Route " << t + 1 << " has no nice parts" << endl;
        }
    }
 
    return 0;
}