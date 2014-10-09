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
const int MAX_COUNT = 1e5;
const int MOD = 1e9 + 7;


#ifndef ONLINE_JUDGE 
///// trace helpers /////

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

#define PR(...) pr(#__VA_ARGS__, __VA_ARGS__);

template<typename T>
struct print_t {
    T first;
    T last;
};

template<typename T>
ostream& operator<< (ostream& o, const print_t<T>& s) {
    o << "[";
    for (auto it = s.first; it != s.last; ++it) {
        if (it != prev(s.last)) {
            o << *it << ", ";
        } else {
            o << *it;
        }
    }
    o << "]";

    return o;
}

template<typename T>
print_t<T> dump(T first, T last, string label = "") {
    return {first, last};
}

template<typename T>
ostream& operator<< (ostream& o, const vector<T>& v) {
    o << "[";
    for (auto it = v.begin(); it != v.end(); ++it) {
        if (it != prev(v.end())) {
            o << *it << ", ";
        } else {
            o << *it;
        }
    }
    o << "]";

    return o;
}

template<typename T>
void pr(const string& name, T t) {
    cout << name << ": " << t << endl;
}

template<typename ... Types>
void pr(const string& names, const Indent& i, Types ... rest) {
    auto comma_pos = names.find(',');
    cout << i;
    
    auto next_name_pos = names.find_first_not_of(" \t\n", comma_pos + 1);
    pr(string(names, next_name_pos), rest ...);
}

template<typename T, typename ... Types>
void pr(const string& names, T t, Types ... rest) {
    auto comma_pos = names.find(',');
    cout << names.substr(0, comma_pos) << ": " << t << ", ";
    
    auto next_name_pos = names.find_first_not_of(" \t\n", comma_pos + 1);
    pr(string(names, next_name_pos), rest ...);
}

#endif


int main()
{
    ios::sync_with_stdio(false);

    int a = 3;
    float b = 5.1;
    string c = "asd";

    vi v = {1, 2, 3};
    int arr[] = {10, 20, 30};

    Indent ind;
    Indent ind2;
    PR(ind2, a, b, c, v, dump(arr, arr + 4));

    dump(begin(v), begin(v)+2, "v");

    // cout << dump(begin(v), begin(v)+2, "v");
    PR(a, b, dump(begin(v), begin(v)+2));

    return 0;
}