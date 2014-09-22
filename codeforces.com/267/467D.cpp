#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <fstream>
#include <string>
#include <numeric>

using namespace std;

#define REP(k,a) for(int k=0; k < (a); ++k)
#define ALL(a) begin(a), end(a)

typedef long long ll;
typedef vector<int> vi; 

const int MAX_COUNT = 1e5;

int article[MAX_COUNT];

map<string, int> w;
map<int, string> ind;

vi g[3*MAX_COUNT];    // graph
vi rg[3*MAX_COUNT];   // reverse graph
char v[3*MAX_COUNT];  // visited
int t[3*MAX_COUNT];   // topologically sorted
int nt = 0;           // temp t counter

int c[3*MAX_COUNT];   // vertex SCC
int nc = 0;           // SCCs count
vi vc[3*MAX_COUNT];   // SCC vertices

set<int> gc[3*MAX_COUNT]; // SCC graph

int min_r[3*MAX_COUNT];   // r, len for g
int min_len[3*MAX_COUNT];

int min_c_r[3*MAX_COUNT]; // r, len for gc
int min_c_len[3*MAX_COUNT];


template<typename T>
ostream& operator<< (ostream& o, const vector<T>& cont) {
    o << "[";
    for (const auto& v : cont) {
        o << v << ", ";
    }
    if (cont.size()) {
        o << "\b\b"; // remove last comma hack
    }
    o << "]";
    return o;
}

template<typename T>
ostream& operator<< (ostream& o, const set<T>& cont) {
    o << "[";
    for (const auto& v : cont) {
        o << v << ", ";
    }
    if (cont.size()) {
        o << "\b\b"; // remove last comma hack
    }
    o << "]";
    return o;
}

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

template<typename T> 
void print_array2(T array, int first, int last, const string& label = "") {
    if (label.size()) {
        cout << label << endl;
    }

    for (int i = first; i < last; i++) {
        cout << i << ": " << array[i] << endl;
    }
}


int add_word(const string& word) {
    if (w.find(word) == w.end()) {
        int i = w.size();
        w[word] = i;
        ind[i] = word;
        min_r[i] = count(word.begin(), word.end(), 'r');
        min_len[i] = word.size();
    }

    return w[word];
}

void to_lower(string& s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
}

void tsort_dfs(int i) {
    v[i] = true;

    for (auto& j : g[i]) {
        if (!v[j]) {
            tsort_dfs(j);
        }
    }

    t[nt++] = i;
}

void kosaraju_dfs(int i) {

    // cout << "kosaraju_dfs(" << i << ")" << endl;

    v[i] = true;

    c[i] = nc;
    vc[nc].push_back(i);

    if (min_c_len[nc] == 0) {
        min_c_len[nc] = min_len[i];
        min_c_r[nc] = min_r[i];
    } else if (min_r[i] < min_c_r[nc]) {
        min_c_r[nc] = min_r[i];
        min_c_len[nc] = min_len[i];
    } else if (min_r[i] == min_c_r[nc]) {
        min_c_len[nc] = min(min_len[i], min_c_len[nc]);
    }

    for (auto& j : rg[i]) {
        if (!v[j]) {
            kosaraju_dfs(j);
        }
    }
}

void propagate_dfs(int i) {
    v[i] = true;

    // cout << "dfs: " << i << endl;

    for (auto& j : gc[i]) {
        if (!v[j]) {
            propagate_dfs(j);
        }

        if (min_c_r[j] < min_c_r[i]) 
        {
            min_c_r[i]   = min_c_r[j];
            min_c_len[i] = min_c_len[j];
        }
        else if (min_c_r[j] == min_c_r[i]) {
            min_c_len[i] = min(min_c_len[i], min_c_len[j]);
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);

    int article_len;
    cin >> article_len;

    REP(i, article_len) {
        string s;
        cin >> s;
        to_lower(s);
        article[i] = add_word(s);
    }

    int n;
    cin >> n;

    // cout << "n: " << n << endl;

    REP(i, n) {
        string from, to;
        cin >> from >> to;
        to_lower(from);
        to_lower(to);

        int ifrom = add_word(from);
        int ito = add_word(to);
        g[ifrom].push_back(ito);
        rg[ito].push_back(ifrom);
    }

    fill(ALL(v), 0);
    REP(i, w.size()) {
        if (!v[i])
            tsort_dfs(i);
    }

    nc = 0;
    fill(ALL(v), 0);
    fill(ALL(c), -1);
    // print_array(v,  0, min(w.size(), (size_t)10), "v");
    REP(i, w.size()) {
        // cout << "t: " << t[w.size()-i-1] << endl;
        if (!v[t[w.size()-i-1]]) {
            kosaraju_dfs(t[w.size()-i-1]);
            nc++;
        }
        // print_array2(c,  0, min(w.size(), (size_t)10), "c");
        // cout << endl;
    }

    REP(c1, nc) {
        REP(j, vc[c1].size()) {
            int x = vc[c1][j];
            REP(k, g[x].size()) {
                int c2 = c[g[x][k]];
                gc[c1].insert(c2);
            }
        }
    }

    fill(ALL(v), 0);
    REP(i, nc) {
        propagate_dfs(i);
    }

    //

    ll ans_r   = 0;
    ll ans_len = 0;

    REP(i, article_len) {
        ans_r   += min_c_r[c[article[i]]];
        ans_len += min_c_len[c[article[i]]];
    }

    // print_array(article, 0, 10, "article");
    // print_array(min_len, 0, 10, "min_len");

    // print_array2(g,  0, min(w.size(), (size_t)10), "g");
    // print_array2(rg, 0, min(w.size(), (size_t)10), "rg");
    // print_array (t,  0, min(w.size(), (size_t)10), "t");
    // print_array2(c,  0, min(w.size(), (size_t)10), "c");

    // print_array2(vc, 0, min(nc, 10), "vc");
    // print_array2(gc, 0, min(nc, 10), "gc");

    cout << ans_r << " " << ans_len << endl;

    return 0;
}
