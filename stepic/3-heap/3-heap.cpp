#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>
#include <cassert>

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

#define ONLINE_JUDGE

#ifndef ONLINE_JUDGE 

///// trace helpers /////

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

#define PR(...) pr(#__VA_ARGS__, __VA_ARGS__);

template<typename T>
void pr(const string& name, T t) {
    cout << name << ": " << t << endl;
}

template<typename T, typename ... Types>
void pr(const string& names, T t, Types ... rest) {
    auto comma_pos = names.find(',');
    cout << names.substr(0, comma_pos) << ": " << t << ", ";
    
    auto next_name_pos = names.find_first_not_of(" \t\n", comma_pos + 1);
    pr(string(names, next_name_pos), rest ...);
}
#else

#define PR(...)

#endif


class Heap
{
public:
    Heap() : last(0) {};

    void insert(int num) {
        data[last++] = num;
        sift_up(last-1);
    
        // check_valid();
        PR(dump(data, data+last));
    }

    int extract() {
        // assert(last > 0);
        if (last == 0) return 0;

        int temp = data[0];
        swap(data[0], data[last-1]);

        --last;
        sift_down(0);

        // check_valid();

        return temp;
    }

    void check_valid() {
        int i = 0;
        while (left(i) < last) {
            if (right(i) < last) {
                assert(data[i] > data[right(i)]);
            }
            assert(data[i] > data[left(i)]);
            ++i;
        }
    }

private:
    void sift_up(int i) {
        while (i > 0 && data[i] > data[parent(i)]) {
            PR(data[i], data[parent(i)]);
            swap(data[i], data[parent(i)]);
            i = parent(i);
        }
    }

    void sift_down(int i){
        int l_i;
        while ((l_i = left(i)) < last) {
            int r_i = right(i);

            PR(dump(data, data+last));

            if (r_i < last) {
                PR(i, l_i, r_i, data[i], data[l_i], data[r_i]);

                if (data[i] < data[l_i] || 
                    data[i] < data[r_i]) 
                {
                    int new_i = data[l_i] > data[r_i] ? l_i : r_i;
                    swap(data[i], data[new_i]);
                    i = new_i;
                } else {
                    break;
                }
            }
            else {
                PR(i, l_i, data[i], data[l_i]);
                if (data[i] < data[l_i]) {
                    swap(data[i], data[l_i]);
                    i = l_i;
                } else {
                    break;
                }
            } 
        }
        PR(dump(data, data+last));
    }

    static inline int parent(int ind) { return (ind - 1) / 2; }
    static inline int left(int ind)   { return 2*ind + 1; }
    static inline int right(int ind)  { return 2*ind + 2; }

    int last;
    int data[4*MAX_COUNT];
};


Heap heap;

int main()
{
    ios::sync_with_stdio(false);

    int n;
    cin >> n;

    REP(i, n) {
        string command;
        cin >> command;

        if (command == "Insert") {
            int num;
            cin >> num;

            PR(command, num);

            heap.insert(num);
        } else if (command == "Extract") {
            PR(command);
            cout << heap.extract() << endl;
        }
    }

    heap.check_valid();

    return 0;
}