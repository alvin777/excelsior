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
int data_a[4];
int data_b[4];
int data_x[4];
int data_y[4];


ll distance2(int x1, int y1, int x2, int y2) {
    return ((ll)(x2-x1))*(x2-x1) + ((ll)(y2-y1))*(y2-y1);
}

ll distance2_ind(int i1, int i2) {
    return distance2(data_a[i1] + data_x[i1], data_b[i1] + data_y[i1],
                     data_a[i2] + data_x[i2], data_b[i2] + data_y[i2]);
}

void rotate(int i) {
    int temp_x = data_x[i];
    data_x[i] = -data_y[i];
    data_y[i] = temp_x;
}

bool is_square() {
    map<ll, int> distance_counts;
    REP(i, 3) {
        FOR(j, i + 1, 4) {
            distance_counts[distance2_ind(i, j)]++;
            if (distance_counts.size() > 2) return false;
        }
    }

    auto first = *distance_counts.begin();
    auto last  = *distance_counts.rbegin();

    if (first.first > 0 &&
        last.first > 0 &&
        first.second == 4 && 
        last.second == 2) 
    {
        return true;
    }

    return false;
}

int solve() {
    int min_rotations = INF;
    REP(i, 4) {
        REP(j, 4) {
            REP(k, 4) {
                REP(l, 4) {
                    if (is_square()) {
                        min_rotations = min(min_rotations, i + j + k + l);
                    }
                    rotate(3);
                }
                rotate(2);
            }
            rotate(1);
        }
        rotate(0);
    }

    if (min_rotations == INF) {
        return -1;
    }

    return min_rotations;
}

int main()
{
    ios::sync_with_stdio(false);

    cin >> n;

    REP(i, n) {
        REP(j, 4) {
            cin >> data_x[j] >> data_y[j] >> data_a[j] >> data_b[j];
            data_x[j] -= data_a[j];
            data_y[j] -= data_b[j];
        }

        cout << solve() << endl;
    }

    return 0;
}