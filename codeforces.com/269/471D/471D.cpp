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
#define FOR(i,a,b) for(int i=a; i < (b); ++i)
#define D(a) cout << #a ": " << a << endl;

const int MAX_COUNT = 2*1e5;


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

int bear[MAX_COUNT];
int elephant[MAX_COUNT];

int delta_bear[MAX_COUNT];
int delta_elephant[MAX_COUNT];


int ans = 0;

void kmp_preprocess(const int *p, int m, int kmp_next[]) {
    int i, j; 
 
    i = 0; 
    j = kmp_next[0] = -1; 

    while ( i < m ) {
        while ( j > -1 && p[i] != p[j] ) j = kmp_next[j]; 

        i++; 
        j++; 
        
        // if ( p[i] == p[j] ) 
        //     kmp_next[i] = kmp_next[j]; 
        // else 
        kmp_next[i] = j; 
    }
}

void kmp_search(const int *p, int m, const int *s, int n ) {
    int i, j, kmp_next[2*MAX_COUNT+1]; 
   
    /* Preprocessing */
    kmp_preprocess(p, m, kmp_next ); 
   
    /* Searching */
   
    i = j = 0; 
    while ( i < n ) {
        while ( j > -1 && p[j] != s[i] ) j = kmp_next[j];
        
        i++; 
        j++; 
        
        if ( j >= m ) {
            ans++;
            j = kmp_next[j]; 
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);

    int bear_n, elephant_n;
    cin >> bear_n >> elephant_n;

    if (elephant_n == 1) {
        cout << bear_n << endl;
        return 0;
    }

    REP(i, bear_n) {
        cin >> bear[i];
    }

    REP(i, elephant_n) {
        cin >> elephant[i];
    }

    FOR(i, 1, bear_n) {
        delta_bear[i - 1] = bear[i] - bear[i-1];
    }

    FOR(i, 1, elephant_n) {
        delta_elephant[i - 1] = elephant[i] - elephant[i-1];
    }

    // print_array(delta_bear, 0, bear_n - 1, "delta_bear");
    // print_array(delta_elephant, 0, elephant_n - 1, "delta_elephant");

    kmp_search(delta_elephant, elephant_n - 1, delta_bear, bear_n - 1);
    
    cout << ans << endl;

    return 0;
}