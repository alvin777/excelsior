#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <array>
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
const int MAX_COUNT = 1e3+1;
const int MOD = 1e9 + 7;


// #define ONLINE_JUDGE

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


int n, m;
int w[MAX_COUNT];
int r[MAX_COUNT];
int order[MAX_COUNT];
bool visited[MAX_COUNT];


int calc_weight(const array<int, 4>& r, array<int, 4> order) {
    ll weight = 0;
    REP(i, m) {
        bool found = false;
        REP(j, n) {
            if (r[i] == order[j]) {
                found = true;
                for (int k = j; k > 0; k--) {
                    order[k] = order[k-1];
                    weight += w[order[k]];
                    // PR(k, dump(ALL(order)), order[k], w[order[k]]);
                }
                order[0] = r[i];
                break;
            }
        }

        if (!found) {
            return INF;
        }
    }

    return weight;
}

int calc_best_weight(const array<int, 4>& r, array<int, 4>* best_order) {
    array<int, 4> check_order;

    int min_weight = INF;

    REP(i, n) {
        check_order[0] = i;
        REP(j, n) {
            check_order[1] = j;
            REP(k, n) {
                check_order[2] = k;
                REP(l, n) {
                    check_order[3] = l;
                    int check_order_weight = calc_weight(r, check_order);
                    if (check_order_weight < min_weight) {
                        min_weight = check_order_weight;
                        *best_order = check_order;
                    }
                }
            }
        }
    }

    return min_weight;
}

array<int, 4> make_order(const array<int, 4>& r) {
    bool visited[MAX_COUNT];
    fill_n(visited, 4, false);

    int j = 0;
    array<int, 4> order;
    REP(i, n) {
        if (!visited[r[i]]) {
            order[j++] = r[i];
            visited[r[i]] = true;
        }
    }

    return order;
}

void check_all_read_orders() {
    array<int, 4> r;

    REP(i, n) {
        r[0] = i;
        REP(j, n) {
            r[1] = j;
            REP(k, n) {
                r[2] = k;
                REP(l, n) {
                    r[3] = l;
                    array<int, 4> my_order = make_order(r);
                    int weight = calc_weight(r, my_order);

                    array<int, 4> best_order;
                    int best_weight = calc_best_weight(r, &best_order);

                    if (best_weight != weight) {
                        PR(dump(ALL(r)), weight, best_weight, dump(ALL(my_order)), dump(ALL(best_order)));
                    }
                }
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);

    cin >> n >> m;
    REP(i, n) {
        cin >> w[i];
    }

    REP(i, m) {
        cin >> r[i];
        r[i]--;
    }

    int j = 0;
    REP(i, n) {
        if (!visited[r[i]]) {
            order[j++] = r[i];
            visited[r[i]] = true;
        }
    }

    // PR(calc_weight({0,0,0,0}, {0,0,0,0}));

    // weight = calc_weight(order);
    check_all_read_orders();

    // calc weight

    // cout << weight << endl;

    return 0;
}
