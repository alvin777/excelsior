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
    if (name.find("\"") != string::npos) {
        cout << t << endl;
        return;
    }
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

#define PR(...)

#endif


class Heap
{
public:
    Heap() : size(0) {};

    void insert(int num) {
        data[size++] = num;
        sift_up(size-1);
    
        // check_valid();
        PR(dump(data, data+size));
    }

    void insert(int a[], int size) {
        copy(a, a + min<int>(size, COUNT(data)), data);
        this->size = size;
        heapify();
    }

    int extract() {
        PR("extract");
        // assert(last > 0);
        if (size == 0) return 0;

        int temp = data[0];
        swap(data[0], data[size-1]);

        --size;
        sift_down(0);

        // check_valid();

        return temp;
    }

    void check_valid() {
        int i = 0;
        while (left(i) < size) {
            if (right(i) < size) {
                assert(!less(data[i], data[right(i)]));
            }
            assert(!less(data[i], data[left(i)]));
            ++i;
        }
    }

private:

    bool less(int a, int b) {
        return a > b;
    }

    void sift_up(int i) {
        while (i > 0 && !less(data[i], data[parent(i)])) {
            PR(data[i], data[parent(i)]);
            swap(data[i], data[parent(i)]);
            i = parent(i);
        }
    }

    void sift_down(int i){
        int l_i;
        while ((l_i = left(i)) < size) {
            int r_i = right(i);

            PR(dump(data, data+size));

            if (r_i < size) {
                PR(i, l_i, r_i, data[i], data[l_i], data[r_i]);

                if (less(data[i], data[l_i]) || 
                    less(data[i], data[r_i])) 
                {
                    int new_i = !less(data[l_i], data[r_i]) ? l_i : r_i;
                    swap(data[i], data[new_i]);
                    i = new_i;
                } else {
                    break;
                }
            }
            else {
                PR(i, l_i, data[i], data[l_i]);
                if (less(data[i], data[l_i])) {
                    swap(data[i], data[l_i]);
                    i = l_i;
                } else {
                    break;
                }
            } 
        }
        PR(dump(data, data+size));
    }

    void heapify() {
        PR("heapify");
        int i = parent(size-1);
        while (i >= 0) {
            sift_down(i);
            i--;
        }

        PR(dump(data, data+size));
    }

    static inline int parent(int ind) { return (ind - 1) / 2; }
    static inline int left(int ind)   { return 2*ind + 1; }
    static inline int right(int ind)  { return 2*ind + 2; }

    int size;
    int data[MAX_COUNT];
};


Heap heap;
int data[MAX_COUNT];

int main()
{
    ios::sync_with_stdio(false);

    int n;
    cin >> n;

    REP(i, n) {
        cin >> data[i];
    }

    heap.insert(data, n);
    heap.check_valid();

    REP(i, n) {
        cout << heap.extract() << " ";
    }

    cout << endl;

    return 0;
}
