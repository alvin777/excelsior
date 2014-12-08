#include <iostream>
#include <vector>
#include <array>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>
#include <cassert>
#include <numeric>
#include <queue>

using namespace std;
typedef long long ll;
typedef vector<int> vi; 

#define REP(k,a) for(int k=0; k < (a); ++k)
#define FOR(i,a,b) for(int i=a; i < (b); ++i)
#define ALL(a) begin(a), end(a)
#define COUNT(a) (sizeof(a)/sizeof(a[0]))

const int INF = 1e9;
const int TOTAL_TASKS = 26;
const int TOTAL_HOSTS = 10;
const int MAX_COUNT = TOTAL_TASKS + TOTAL_HOSTS + 2;
const int SOURCE = 0;
const int FIRST_TASK = 1;
const int FIRST_HOST = FIRST_TASK + TOTAL_TASKS; // 27
const int TARGET = FIRST_HOST + TOTAL_HOSTS;     // 37
const int MOD = 1e9 + 7;


#define ONLINE_JUDGE

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



struct edge_t {
    int v;
    int r;
};

struct flow_t
{
    int u;
    int f;
};

typedef array<vector<edge_t>, MAX_COUNT> graph_t;
graph_t g;

bool visited[MAX_COUNT];

int p[MAX_COUNT];

void print_graph(const graph_t& g) {
    for (int i = 0; i < g.size(); ++i) {
        for (const auto& e : g[i]) {
            cout << i << " -> " << e.v << " (" << (e.r > INF - 100 ? -1 : e.r) << ")" << endl;
        }
    }
}

int bfs(int s, int t, int flow) {
    queue<flow_t> q;
    q.push({s, INF});

    while (q.size()) {
        flow_t f = q.front(); q.pop();
        visited[f.u] = true;
        PR(f.u, f.f);

        if (f.u == t) return f.f;

        for (const auto& e : g[f.u]) {
            if (visited[e.v] || e.r == 0) continue;

            PR("  ", e.v, e.r);

            p[e.v] = f.u;

            q.push({e.v, min(f.f, e.r)});
        }
    }

    return 0;
}

int edmonds_karp() {
    int maxFlow = 0;

    while (true) {
        fill_n(p, MAX_COUNT, -1);
        fill_n(visited, MAX_COUNT, false);
        int flow = bfs(SOURCE, TARGET, INF);

        if (flow == 0) break;

        maxFlow += flow;

        PR(maxFlow);

        int n = TARGET;
        while(p[n] >= 0) {
            PR(n);

            for (auto& e : g[p[n]]) {
                if (e.v == n) {
                    e.r -= flow;
                    break;
                }
            }

            for (auto& e : g[n]) {
                if (e.v == p[n]) {
                    e.r += flow;
                    break;
                }
            }

            n = p[n];
        }
        // print_graph(g);
    }

    return maxFlow;
}

string solve(int count) {

    int maxFlow = edmonds_karp();
    assert(maxFlow <= count);

    if (maxFlow < count) {
        return "!";
    }

    char ans[TOTAL_HOSTS + 1];
    REP(i, TOTAL_HOSTS) {
        ans[i] = '_';
        int totalSum = 0;
        REP(j, g[FIRST_HOST + i].size()) {
            const auto& e = g[FIRST_HOST + i][j];

            if (e.v < FIRST_HOST && e.r > 0) {
                ans[i] = 'A' + e.v - FIRST_TASK;
            }

            totalSum += e.r;
        }

        assert(totalSum == 0 || totalSum == 1);
    }
    ans[TOTAL_HOSTS] = 0;

    return ans;
}

void add_edge(int from, int to, int capacity) {
    g[from].push_back(edge_t {to, capacity});
    g[to].push_back(edge_t {from, 0});
}

int main() {
    ios::sync_with_stdio(false);

    while (!cin.eof()) { // test cases
        g.fill(vector<edge_t>{});
        int total_count = 0;

        string line;
        while (getline(cin, line) && !line.empty()) { // lines

            // if (line.empty())) break;

            int taskId = line[0] - 'A';
            int count  = line[1] - '0';

            PR(taskId, count);

            add_edge(SOURCE, FIRST_TASK + taskId, count);
            total_count += count;

            for (char c : line.substr(3, line.length() - 4)) {
                int hostId = c - '0';
                PR(hostId);

                add_edge(FIRST_TASK + taskId, FIRST_HOST + hostId, INF);
            }
        }

        REP(i, TOTAL_HOSTS) {
            add_edge(FIRST_HOST + i, TARGET, 1);
        }

        cout << solve(total_count) << endl;
    }

    return 0;
}
