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
#define D(a) cout << #a ": " << a << endl;

const int MAX_COUNT = 1000;
const int INF = 1e9;


int data[MAX_COUNT][MAX_COUNT];
int sum[MAX_COUNT][MAX_COUNT];

int calc_sum(int t, int l, int b, int r, int n) {

    int trace = false;
    // if (t == 0 && l == 3 && b == 1 && r == 5) {
    //     trace = true;
    // }

    if (trace)
        cout << "t: " << t << ", l: " << l << ", b: " << b << ", r: " << r << ", n: " << n << endl;

    if (t == b && l == r) return data[t][l];

    if ((b - t == n - 1) && 
        (r - l == n - 1))
    {
        // D(data[n-1][n-1]);
        return sum[n-1][n-1];
    }

    int tor_sum = 0;
    if (b >= n && r >= n) {
        tor_sum += sum[b % n][r % n];

        if (trace)
            D(tor_sum);
    }

    if (r >= n) {
        tor_sum += sum[b][r % n] - (t > 0 ? sum[t - 1][r % n] : 0);

        if (trace) {
            D((t > 0 ? sum[t - 1][r % n] : 0));
            D(sum[b][r % n]);
            D(tor_sum);
        }
    }

    if (b >= n) {
        tor_sum += sum[b % n][r] - (l > 0 ? sum[b % n][l - 1] : 0);

        if (trace)
            D(tor_sum);
    }

    tor_sum += sum[min(b, n - 1)][min(r, n - 1)] 
                   - (t > 0 ? sum[t-1][min(r, n-1)] : 0)
                   - (l > 0 ? sum[min(b, n-1)][l-1] : 0) 
                   + ((t > 0 && l > 0) ? sum[t-1][l-1] : 0);

    if (trace)
        D(tor_sum);

    return tor_sum;
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

                if (i == 0) {
                    sum[i][j] = data[i][j] + sum[i][j-1];
                }
                else if (j == 0) {
                    sum[i][j] = data[i][j] + sum[i-1][j];
                }
                else {
                    sum[i][j] = data[i][j] + sum[i][j-1] + sum[i-1][j] - sum[i-1][j-1];
                }
            }
        }

        int max_sum = -INF;
        REP(i, n) {
            REP(j, n) {
                REP(h, n) {
                    REP(w, n) {
                        int cur_sum = calc_sum(i, j, i+h, j+w, n);
                        // D(cur_sum);
                        // D(max_sum);
                        max_sum = max(max_sum, cur_sum);
                    }
                }
            }
        }

        cout << max_sum << endl;
    }

    return 0;
}