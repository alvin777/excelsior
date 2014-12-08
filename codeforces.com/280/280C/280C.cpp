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
const int MAX_COUNT = 1e5 + 1;
const int MOD = 1e9 + 7;


// #define ONLINE_JUDGE

#ifndef ONLINE_JUDGE 

///// trace helpers /////

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


struct exam_t {
    int mark;
    int cost;
};

ll n, r, avg;
exam_t exams[MAX_COUNT];


int main()
{
    ios::sync_with_stdio(false);

    cin >> n >> r >> avg;
    ll marks_sum = 0;
    ll req_sum = n * avg;

    REP(i, n) {
        cin >> exams[i].mark >> exams[i].cost;
        marks_sum += exams[i].mark;
    }

    PR(n, r, avg, marks_sum, req_sum);

    sort(exams, exams + n, [](const exam_t& e1, const exam_t& e2){
        return e1.cost < e2.cost;
    });

    ll count = 0;
    for (int i = 0; i < n && marks_sum < req_sum; ++i) {
        PR(exams[i].mark, exams[i].cost, marks_sum, req_sum - marks_sum, r - exams[i].mark);

        ll taking = min(req_sum - marks_sum, r - exams[i].mark);

        marks_sum += taking;
        count += taking * exams[i].cost;
    }

    cout << count << endl;

    return 0;
}
