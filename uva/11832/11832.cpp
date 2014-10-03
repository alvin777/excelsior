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
const int MAX_COUNT = 41;
const int MAX_VALUE = 1000;


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
void print_array(T first, T last, const string& label = "") {
    if (label.size()) {
        cout << label << ": ";
    }

    while (first != last) {
        cout << *first++ << " ";
    }

    cout << endl;
}

int n;
int r;
int data[MAX_COUNT];

// m values
// -1 – undefined
//  0 - no solution
//  1 - add
//  2 - sub
//  3 - both

char m[MAX_COUNT][2*MAX_VALUE*MAX_COUNT + 1]; // -40*1000 .. 40*1000
char ans[MAX_COUNT];


bool solve(int i, int sum) {

    Indent ind;

    // cout << ind; D(i); DE(sum);

    if (i == n) {
        if (sum == r) {
            // cout << ind << "<< " << boolalpha << true << endl;
            return true;
        }
        // cout << ind << "<< " << boolalpha << false << endl;
        return false;
    }

    if (m[i][MAX_VALUE * MAX_COUNT + sum] != -1) {
        // cout << ind << "<< " << boolalpha << (bool)m[i][MAX_VALUE * MAX_COUNT + sum] << endl;
        return m[i][MAX_VALUE * MAX_COUNT + sum];
    }

    bool check_add = solve(i + 1, sum + data[i]);
    bool check_sub = solve(i + 1, sum - data[i]);

    // cout << ind; D(check_add); DE(check_sub);

    if (check_add && check_sub) {
        m[i][MAX_VALUE * MAX_COUNT + sum] = 3;
        ans[i] |= 3;
    } 
    else if (check_add) {
        m[i][MAX_VALUE * MAX_COUNT + sum] = 1;
        ans[i] |= 1;
    }
    else if (check_sub) {
        m[i][MAX_VALUE * MAX_COUNT + sum] = 2;
        ans[i] |= 2;
    } 
    else {
        m[i][MAX_VALUE * MAX_COUNT + sum] = 0;
        // ans[i] = 0;
    }

    // cout << ind << "<< " << boolalpha << (check_add || check_sub) << endl;

    return check_add || check_sub;
}

string get_result() {
    string res;
    REP(i, n) {
        switch(ans[i]) {
        case 0:
            res += '*';
            return res;
        case 1:
            res += '+';
            break;
        case 2:
            res += '-';
            break;
        case 3:
            res += '?';
            break;
        }
    }

    return res;
}

int main()
{
    ios::sync_with_stdio(false);

    while(true) {
        cin >> n >> r;
        if (!n && !r) return 0;

        REP(i, n) {
            cin >> data[i];
        }

        // print_array(data, data + n, "data");

        fill_n(&m[0][0], sizeof(m)/sizeof(m[0][0]), -1);
        fill_n(&ans[0], sizeof(ans)/sizeof(ans[0]), 0);

        solve(0, 0);
        cout << get_result() << endl;
    }

    return 0;
}