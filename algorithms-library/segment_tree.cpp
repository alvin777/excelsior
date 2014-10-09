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
#define D(a) cout << #a ": " << a << ", ";
#define DE(a) cout << #a ": " << a << endl;
#define COUNT(a) (sizeof(a)/sizeof(a[0]))

const int INF = 1e9;
const int MAX_COUNT = 1e5;
const int MOD = 1e9 + 7;


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


template<typename T>
void check_equals(const T& actual, const T& expected, const string& message = "Check failed.") {
    if (actual != expected) {
        cout << message << " Expected: " << expected << ", actual: " << actual << endl;
    } else {
        cout << ".";
    }
}

int data[] = {1, 20, 10, 15, 4};
// int data[] = {1,2,3,4,5};
// int data[] = {5,4,3,2,1};
// int data[] = {1,2,1,3,1,4};
int n = COUNT(data);
int st[MAX_COUNT];

void st_build(int data[], int tl, int tr, int i) {

    if (tl == tr) {
        st[i] = data[tl];
        return;
    }

    int tm = tl + (tr-tl)/2;   // partition original array
    int li = 2*i + 1;          // calc heap indices for st
    int ri = 2*i + 2;

    st_build(data, tl, tm,   li); 
    st_build(data, tm+1, tr, ri);
    st[i] = max(st[li], st[ri]);
}

void st_update(int pos, int val, int tl, int tr, int i) {
    if (tl == tr) {
        st[i] = val;
        return;
    }

    int tm = tl + (tr-tl)/2;
    int li = 2*i + 1;
    int ri = 2*i + 2;

    if (pos <= tm) {
        st_update(pos, val, tl,   tm, li);
    } else {
        st_update(pos, val, tm+1, tr, ri);
    }
    st[i] = max(st[li], st[ri]);
}

int st_query(int ql, int qr, int tl, int tr, int i) {
    if (ql > tr || qr < tl) return -INF;

    if (ql <= tl && qr >= tr) {
        return st[i];
    }

    int tm = tl + (tr-tl)/2;
    int li = 2*i + 1;
    int ri = 2*i + 2;
    return max(st_query(ql, qr, tl,   tm, li), 
               st_query(ql, qr, tm+1, tr, ri));
}

int main()
{
    ios::sync_with_stdio(false);

    // cin >> n;
    st_build(data, 0, n-1, 0);
    // print_array(ALL(st), "st");

    REP(k, 100) {    
        REP(i, n) {
            FOR(j, i, n) {
                string message = "i: " + to_string(i) + ", j: " + to_string(j);
                check_equals(st_query(i, j, 0, n-1, 0), *max_element(data + i, data + j + 1), message);
            }
        }
        data[k % n] += 100;
        st_update(k % n, data[k % n], 0, n-1, 0);
    }

    return 0;
}