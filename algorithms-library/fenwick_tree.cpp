#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>
#include <numeric>

using namespace std;
typedef long long ll;
typedef vector<int> vi; 

#define REP(k,a) for(int k=0; k < (a); ++k)
#define FOR(i,a,b) for(int i=a; i < (b); ++i)
#define ALL(a) begin(a), end(a)
#define COUNT(a) (sizeof(a)/sizeof(a[0]))

const int INF = 1e9;
const int MAX_COUNT = 1e5;
const int MOD = 1e9 + 7;


// #define ONLINE_JUDGE

#ifndef ONLINE_JUDGE 

#else
# define PR(...)
#endif

#define LSOne(n) (n & -n);

int data[] = {0, 5, 42, 2, 5, 67, 4};
int n = COUNT(data);
int ft[MAX_COUNT];

void ft_adjust(int pos, int val, int n) {
    if (pos == 0) return;

    while (pos < n) {
        ft[pos] += val;
        pos += LSOne(pos);
    }
}

int ft_query(int r) {
    int sum = 0;
    while (r > 0) {
        sum += ft[r];
        r -= LSOne(r);
    }
    return sum;
}

int ft_query(int l, int r) {
    return ft_query(r) - ft_query(l - 1);
}

template<typename T>
void check_equals(const T& actual, const T& expected, const string& message = "Check failed.") {
    if (actual != expected) {
        cout << message << " Expected: " << expected << ", actual: " << actual << endl;
    } else {
        cout << ".";
    }
}

int main()
{
    ios::sync_with_stdio(false);

    FOR(i, 1, n+1) {
        ft_adjust(i, data[i], n);
    }

    REP(k, 100) {    
        FOR(i, 1, n) {
            FOR(j, i, n) {
                string message = "i: " + to_string(i) + ", j: " + to_string(j);
                check_equals(ft_query(i, j), accumulate(data + i, data + j + 1, 0), message);
            }
        }
        int ind = k % n;
        data[ind] += 100;
        ft_adjust(ind, 100, n);
    }


    return 0;
}