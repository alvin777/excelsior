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
#define COUNT(a) (sizeof(a)/sizeof(a[0]))

const int INF = 1e9;
const int MAX_COUNT = 1e5;
const int MOD = 1e9 + 7;


typedef vector<vector<double>> mat_t;

ostream& operator<< (ostream& o, const mat_t& m) {
    o << endl;
    for (const auto& row : m) {
        o << "  ";
        for (const auto& value : row) {
            o.setf(ios::fixed, ios::floatfield);
            o.precision(1);
            o << setw(6)  << value << " ";
        }
        o << endl;
    }

    return o;
}

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

mat_t build_matrix(const mat_t& a, const vector<double>& b, const vector<double>& c) {
    int m = a.size();
    int n = a.front().size();

    mat_t mat(m + 1);

    for (int i = 0; i < m; i++) {
        mat[i].resize(n + m + 1);
        for (int j = 0; j < n; j++) {
            mat[i][j] = a[i][j];
        }
    }

    for (int i = 0; i < m; i++) {
        mat[i][m + n] = b[i];
        mat[i][n + i] = 1;
    }

    mat.back().resize(n + m + 1);
    for (int i = 0; i < n; i++) {
        mat.back()[i] = c[i];
    }

    return mat;
}

int blunt(const vector<double>& c, int n) {
    int p = -1;

    for (int i = 0; i < n; i++) {
        if (c[i] <= 0) continue;
        else if (p == -1) p = i;
        else if (c[i] > c[p]) {
            p = i;
        }
    }

    return p;
}

int minRow(const mat_t& mat, int col) {
    int q = -1;

    for (int i = 0; i < mat.size() - 1; i++) {
        if (mat[i][col] <= 0) continue;
        else if (q == -1) q = i;
        else if (mat[i].back()/mat[i][col] < mat[q].back()/mat[q][col]) {
            q = i;
        }
    }

    return q;
}

void pivot(mat_t& mat, int row, int col) {
    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat[i].size(); j++) {
            if (i != row && j != col) {
                // PR(i, j, mat[i][j], mat[i][col], mat[row][j], mat[row][col], mat[i][col]*mat[row][j]/mat[row][col]);
                mat[i][j] -= mat[i][col]*mat[row][j]/mat[row][col];
            }
        }
    }

    for (int i = 0; i < mat[row].size(); i++) {
        if (i == col) continue;
        mat[row][i] /= mat[row][col];
    }

    for (int i = 0; i < mat.size(); i++) {
        mat[i][col] = 0;
    }

    mat[row][col] = 1.0;
}

mat_t solve(const mat_t& a, const vector<double>& b, const vector<double>& c) {
    int m = a.size();
    int n = a.front().size();
    assert(b.size() == m);
    assert(c.size() == n);

    // build matrix
    mat_t mat = build_matrix(a, b, c);

    // PR(mat);

    while (true) {
        int col = blunt(mat.back(), n);
        // PR(col);
        if (col == -1) break;

        int row = minRow(mat, col);
        // PR(row);
        if (row == -1) break;

        pivot(mat, row, col);
        // PR(mat);
    }
    return mat;
}

int main()
{
    mat_t mat = solve({{5, 15}, {4, 4}, {35, 20}}, {480, 160, 1190}, {13, 23});
    PR(mat);
    assert(mat.back().back() == -800);

    return 0;
}
