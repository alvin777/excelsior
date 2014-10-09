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
#define COUNT(a) (sizeof(a)/sizeof(a[0]))

const int INF = 1e9;
const int MAX_COUNT = 1e5 + 1;
const int MOD = 1e9 + 7;

const int LEN = 0;
const int IND = 1;


int n;
int d;
ll data[MAX_COUNT];
ll c[MAX_COUNT];
int bt[MAX_COUNT];

typedef tuple<int, int> node_t;

node_t st[4*MAX_COUNT+1];

void st_update(int pos, node_t val, int tl, int tr, int i) {
    if (tr == tl) {
        st[i] = val;
        return;
    }

    int tm = tl + (tr - tl)/2;
    int li = 2*i + 1;
    int ri = 2*i + 2;
    if (pos <= tm) {
        st_update(pos, val, tl,   tm, li);
    } else {
        st_update(pos, val, tm+1, tr, ri);
    }

    st[i] = max(st[li], st[ri]);
}

node_t st_query_max(int ql, int qr, int tl, int tr, int i) {
    if (ql > tr || qr < tl) return make_tuple(-1, 0);

    if (ql <= tl && qr >= tr) {
        return st[i];
    }

    int tm = tl + (tr - tl)/2;
    int li = 2*i + 1;
    int ri = 2*i + 2;
    node_t res = max(st_query_max(ql, qr, tl,   tm, li), 
                     st_query_max(ql, qr, tm+1, tr, ri));

    return res;
}

int main()
{
    ios::sync_with_stdio(false);

    cin >> n >> d;

    REP(i, n) {
        cin >> data[i];
        c[i] = data[i];
    }

    sort(c, c + n);
    int c_size = distance(c, unique(c, c + n));

    int max_value = c_size;

    fill(ALL(st), node_t{0, -1});

    int max_len = 0;
    int max_len_ind = -1;

    REP(i, n) {
        int l = distance(c, upper_bound(c, c + c_size, data[i] - d)) - 1;
        int r = distance(c, lower_bound(c, c + c_size, data[i] + d));

        node_t max_ind = max(st_query_max(0, l,         0, max_value, 0), 
                             st_query_max(r, max_value, 0, max_value, 0));

        int len = max(get<LEN>(max_ind) + 1, 1);

        int ii = distance(c, lower_bound(c, c + c_size, data[i]));
        st_update(ii, make_tuple(len, i), 0, max_value, 0);

        if (len > max_len) {
            max_len = len;
            max_len_ind = i;
        }

        bt[i] = get<IND>(max_ind);
    }

    vi path;
    while (max_len_ind != -1) {
        path.push_back(max_len_ind);
        max_len_ind = bt[max_len_ind];
    }

    cout << max_len << endl;
    for (auto it = path.rbegin(); it != path.rend(); ++it) {
        cout << *it + 1 << " ";
    }
    cout << endl;

    return 0;
}