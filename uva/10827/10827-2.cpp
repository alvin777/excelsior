#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <fstream>
#include <numeric>
#include <iomanip>

using namespace std;
typedef long long ll;
typedef vector<int> vi; 

#define REP(k,a) for(int k=0; k < (a); ++k)
#define FOR(i,a,b) for(int i=a; i < (b); ++i)
#define ALL(a) begin(a), end(a)
#define D(a) cout << #a ": " << a << endl;

const int MAX_COUNT = 1000;
const int INF = 1e9;


int data[2*MAX_COUNT][MAX_COUNT];
int sum[2*MAX_COUNT][MAX_COUNT];
int sum2[MAX_COUNT];

template<typename T> 
void print_array(T array, int first, int last, const string& label = "") {
    if (label.size()) {
        cout << label << ": ";
    }

    for (int i = first; i < last; i++) {
        cout << setw(2) << array[i] << " ";
    }

    cout << endl;
}

template<typename T>
void print_matrix(const T m, int first_row, int first_col, int last_row, int last_col, const string label = "") {
    if (label.size()) {
        cout << label << ": " << endl;
    }

    for (int i = first_row; i < last_row; i++) {
        print_array(m[i], first_col, last_col);
    }

    // cout << endl;
}

int kadane(const int array[], int n) {
    int cum_sum = 0;
    int max_sum = 0;
    REP(i, n) {
        cum_sum += array[i];

        if (cum_sum <= 0) {
            cum_sum = 0;
        } else {
            max_sum = max(cum_sum, max_sum);
        }
    }
    return max_sum;
}

int circ_kadane(int array[], int n) {
    int max_kadane = kadane(array, n);

    int max_wrap = 0;
    REP(i, n) {
        max_wrap += array[i];
        array[i] = -array[i];
    }
    max_wrap += kadane(array, n);

    return max(max_wrap, max_kadane);
}

int main()
{
    ios::sync_with_stdio(false);

    int tc;
    cin >> tc;

    REP(t, tc) {
        int n;
        cin >> n;

        REP(i, n) {
            REP(j, n) {
                cin >> data[i][j];
                data[n + i][j] = data[i][j];
            }
        }

        REP(i, 2*n) {
            REP(j, n) {
                sum[i][j] = (i == 0 ? 0 : sum[i-1][j]) + data[i][j];
            }
        }

        // print_matrix(data, 0, 0, 2*n, 2*n, "data");
        // print_matrix(sum, 0, 0, 2*n, 2*n, "sum");

        int max_sum = -INF;
        REP(i1, n) {
            fill_n(sum2, n, 0);
            FOR(i2, i1, i1+n) {
                REP(j, n) {
                    sum2[j] = sum[i2][j] - (i1 > 0 ? sum[i1-1][j] : 0) ;
                }

                // cout << "i1: " << i1 << ", i2: " << i2 << " ";
                // print_array(sum2, 0, 2*n, "sum2");

                max_sum = max(max_sum, circ_kadane(sum2, n));
            }
        }

        cout << max_sum << endl;
    }

    return 0;
}