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

#else
# define PR(...)
#endif


int n;
int data[MAX_COUNT];
int temp[MAX_COUNT];

ll merge(int left_first, int left_last, int right_first, int right_last) {
    PR(left_first, left_last, right_first, right_last);
    int left = left_first;
    int right = right_first;
    int k = 0;
    ll inversions = 0;
    while (left <= left_last && right <= right_last) {
        PR(left, right);
        while (left <= left_last && data[left] <= data[right]) {
            temp[k++] = data[left++];
        }
        while (right <= right_last && data[right] < data[left]) {
            temp[k++] = data[right++];
            inversions += left_last - left + 1;
        }
    }
    while (left <= left_last) {
        temp[k++] = data[left++];
    }
    while (right <= right_last) {
        temp[k++] = data[right++];
        inversions += left_last - left + 1;
    }
    copy(temp, temp + k, data + left_first);
    PR(inversions);
    return inversions;
}

ll inversions(int first, int last) {
    PR(first, last);

    if (first == last) {
        return 0;
    }

    if (first == last - 1) {
        if (data[first] > data[last]) {
            swap(data[first], data[last]);
            return 1;
        }
        return 0;
    }

    int m = first + (last - first)/2;
    ll res = inversions(first, m) + inversions(m+1, last);
    res += merge(first, m, m+1, last);
    return res;
}

int main()
{
    ios::sync_with_stdio(false);

    cin >> n;
    REP(i, n) {
        cin >> data[i];
    }

    cout << inversions(0, n-1) << endl;

    PR(dump(data, data+n));

    return 0;
}