#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>
#include <array>

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

template<typename T, int ElementsCount, T defaultValue = T()>
class SegmentTree {
public:
    typedef function<const T& (const T&, const T&)> Function;
    SegmentTree(Function func) : func(func) {};
    void build(T data[], int tl, int tr, int i = 0) {

        if (tl == tr) {
            st[i] = data[tl];
            return;
        }

        int tm = tl + (tr-tl)/2;   // partition original array
        int li = 2*i + 1;          // calc heap indices for st
        int ri = 2*i + 2;

        build(data, tl, tm,   li); 
        build(data, tm+1, tr, ri);
        st[i] = func(st[li], st[ri]);
    }

    void update(int pos, T val, int tl, int tr, int i = 0) {
        if (tl == tr) {
            st[i] = val;
            return;
        }

        int tm = tl + (tr-tl)/2;
        int li = 2*i + 1;
        int ri = 2*i + 2;

        if (pos <= tm) {
            update(pos, val, tl,   tm, li);
        } else {
            update(pos, val, tm+1, tr, ri);
        }
        st[i] = func(st[li], st[ri]);
    }

    T query(int ql, int qr, int tl, int tr, int i = 0) {
        if (ql > tr || qr < tl) return defaultValue;

        if (ql <= tl && qr >= tr) {
            return st[i];
        }

        int tm = tl + (tr-tl)/2;
        int li = 2*i + 1;
        int ri = 2*i + 2;
        return func(query(ql, qr, tl,   tm, li), 
                    query(ql, qr, tm+1, tr, ri));
    }
private:
    array<T, 4*ElementsCount> st;
    Function func;
};


int data[] = {1, 20, 10, 15, 4};
// int data[] = {1,2,3,4,5};
// int data[] = {5,4,3,2,1};
// int data[] = {1,2,1,3,1,4};
int n = COUNT(data);

SegmentTree<int, MAX_COUNT, -INF> segmentTree([](const int& a, const int& b){ return max(a, b); });
// SegmentTree<int, MAX_COUNT, -INF> segmentTree(max);

int main()
{
    ios::sync_with_stdio(false);

    segmentTree.build(data, 0, n-1);

    REP(k, 100) {    
        REP(i, n) {
            FOR(j, i, n) {
                string message = "i: " + to_string(i) + ", j: " + to_string(j);
                check_equals(segmentTree.query(i, j, 0, n-1), *max_element(data + i, data + j + 1), message);
            }
        }
        data[k % n] += 100;
        segmentTree.update(k % n, data[k % n], 0, n-1);
    }

    return 0;
}