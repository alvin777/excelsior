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

#ifndef ONLINE_JUDGE

///// trace helpers /////

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

class Indent
{
public:
    friend ostream& operator<< (ostream& o, const Indent& indent);

    Indent()  { ++level; }
    ~Indent() { --level; }

private:
    static int level;
};

int Indent::level = -1;

ostream& operator<< (ostream& o, const Indent& indent) {
    return o << string(indent.level*4, ' ');
}


ostream& operator<< (ostream& o, const tuple<int, int>& t) {
    return o << "(" << get<0>(t) << ", " << get<1>(t) << ")";
}

#endif


int n;
int d;
ll data[MAX_COUNT];
ll c[MAX_COUNT];
int bt[MAX_COUNT];

typedef tuple<int, int> node_t;

node_t st[4*MAX_COUNT+1];

void st_update(int pos, node_t val, int tl, int tr, int i) {

    // D(pos); D(val); D(tl); D(tr); DE(i);

    if (tr == tl) {
        st[i] = val;
        // DE(st[i]);
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

    // D(st[ri]); D(st[li]); DE(st[i]);
}

node_t st_query_max(int ql, int qr, int tl, int tr, int i) {
    // Indent ind;
    // cout << ind; D(ql); D(qr); D(tl); D(tr); DE(i);

    if (ql > tr || qr < tl) return make_tuple(-1, 0);

    if (ql <= tl && qr >= tr) {
        // cout << ind << "<< " << st[i] << endl;
        return st[i];
    }

    int tm = tl + (tr - tl)/2;
    int li = 2*i + 1;
    int ri = 2*i + 2;
    node_t res_l = st_query_max(ql, qr, tl,   tm, li);
    node_t res_r = st_query_max(ql, qr, tm+1, tr, ri);

    node_t res = max(res_l, res_r);

    // cout << ind << "<< " << res << endl;

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

    // DE(c_size);
    // print_array(c, c + c_size);

    int max_value = c_size;

    fill(ALL(st), node_t{0, -1});
    // fill(ALL(bt), -1);

    int max_len = 0;
    int max_len_ind = -1;

    REP(i, n) {
        // D(i); DE(data[i]); 

        int l = distance(c, lower_bound(c, c + c_size, data[i] - d));
        if (c[l] > data[i] - d) { --l; }
        int r = distance(c, lower_bound(c, c + c_size, data[i] + d));

        // D(l); DE(r);

        node_t max_ind_l = st_query_max(0, l,         0, max_value, 0);
        node_t max_ind_r = st_query_max(r, max_value, 0, max_value, 0);

        node_t max_ind = max(max_ind_l, max_ind_r);

        // D(max_ind_l); D(max_ind_r); DE(max_ind); 

        // len[i] = (max_ind == -1) ? 1 : len[max_ind] + 1;
        int len = max(get<0>(max_ind) + 1, 1);
        // D(i); DE(len[i]);

        int ii = distance(c, lower_bound(c, c + c_size, data[i]));
        st_update(ii, make_tuple(len, i), 0, max_value, 0);
        // print_array(st, st+4*max_value, "st");

        if (len > max_len) {
            max_len = len;
            max_len_ind = i;
        }
        bt[i] = get<1>(max_ind);
        // DE(bt[i]);

        // cout << endl;
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