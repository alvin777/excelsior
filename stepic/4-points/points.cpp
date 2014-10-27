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
#define COUNT(a) (sizeof(a)/sizeof(a[0]))

const int INF = 1e9;
const int MAX_COUNT = 1e5;
const int MOD = 1e9 + 7;


#define ONLINE_JUDGE

#ifndef ONLINE_JUDGE 

///// trace helpers /////

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

ostream& operator<< (ostream& o, const vi& s) {
    o << "[";
    for (auto it = s.begin(); it != s.end(); ++it) {
        if (it != prev(s.end())) {
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
void print_value(const string& name, const T& value) {
    if (name.find("\"") != string::npos) {
        cout << value << " ";
        return;
    }
    cout << name << ": " << value << ", ";
}

// template<>
// void print_value<Indent>(const string& name, const Indent& value) {
//     cout << value;
// }

template<typename T>
void pr(const string& name, const T& t) {
    cout << name << ": " << t << endl;
}

template<typename T, typename ... Types>
void pr(const string& names, const T& t, Types ... rest) {
    auto comma_pos = names.find(',');
    print_value(names.substr(0, comma_pos), t);
    
    auto next_name_pos = names.find_first_not_of(" \t\n", comma_pos + 1);
    pr(string(names, next_name_pos), rest ...);
}

template<typename T>
void check_equals(const T& actual, const T& expected, const string& message = "Check failed.") {
    if (actual != expected) {
        cout << message << " Expected: " << expected << ", actual: " << actual << endl;
    } else {
        cout << ".";
    }
}

#else
# define PR(...)
#endif


int n, m;
int a[MAX_COUNT];
int b[MAX_COUNT];
int p[MAX_COUNT];

bool less_than(int a, int b) {
    return a < b;
}

void sort3(int* a, int* b, int* c) {
    if (!less_than(*a, *b)) {
        swap(*a, *b);
    }

    if (!less_than(*b, *c)) {
        swap(*b, *c);
    }

    if (!less_than(*a, *b)) {
        swap(*a, *b);
    }
}

void quicksort(int* first, int* last) {

    // PR(">>", dump(first, last+1));

    if (first >= last) {
        return;
    }

    if (first == last - 1) {
        if (less_than(*last, *first)) {
            swap(*last, *first);
        }
        return;
    }

    int* m = first + (last - first)/2;

    sort3(first, m, last);

    if (last - first == 2) return;

    int p = *m;
    swap(*m, *first);

    int* lt  = first;      // first pivot element
    int* ptr = first + 1;  // current 
    int* gt  = last;       // first known greater element

    while (ptr <= gt) {
        if (less_than(*ptr, p))       { swap(*ptr++, *lt++);}
        else if (less_than(p, *ptr))  { swap(*ptr, *gt--);}
        else { ptr++; }
    }

    quicksort(first, lt-1);
    quicksort(gt+1, last);

    // PR("<<", dump(first, last+1));
}

// void test() {
//     vi data;
//     // vi data{56237, 23449, 97087, 81867, 24653, 69905, 86689, 37483, 53590, 59193};
//     srand (time(NULL));

//     REP(i, 100) {
//         data.push_back(rand() % 100000 + 1);
//     }

//     vi sorted(data);
//     sort(ALL(sorted));

//     quicksort(data.data(), data.data() + data.size() - 1);

//     check_equals(data, sorted);
// }

int main()
{
    ios::sync_with_stdio(false);

    // test();
    // return 0;

    cin >> n >> m;
    REP(i, n) {
        cin >> a[i] >> b[i];
    }

    PR(dump(a, a+n));
    PR(dump(b, b+n));

    REP(i, m) {
        cin >> p[i];
    }

    quicksort(a, a+n-1);
    quicksort(b, b+n-1);

    // PR(dump(a, a+n));
    // PR(dump(b, b+n));

    REP(i, m) {
        int begins_le = distance(a, upper_bound(a, a+n, p[i]));
        int end_ge    = distance(b, lower_bound(b, b+n, p[i]));
        // PR(p[i], begins_le, end_ge);
        cout << begins_le - end_ge << " ";
    }

    cout << endl;

    return 0;
}