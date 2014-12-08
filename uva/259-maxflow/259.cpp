#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>
#include <cassert>
#include <numeric>

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


int cap[MAX_COUNT][MAX_COUNT];
int p[MAX_COUNT];

void print_cap() {
    REP(i, MAX_COUNT) {
        cout << setw(2) << i << " ";
    }

    cout << endl;

    REP(i, MAX_COUNT) {
        REP(j, MAX_COUNT) {
            cout << setw(2) << (cap[i][j] < INF - 100 ? cap[i][j] : -1) << " ";
        }
        cout << endl;
    }
}

bool visited[MAX_COUNT];

int dfs(int u, int t, int flow) {
    PR(u, t, flow);

    visited[u] = true;

    if (u == t) return flow;

    for (int v = 0; v < MAX_COUNT; ++v) {
        if (visited[v] || cap[u][v] == 0) continue;

        int flowDelta = dfs(v, t, min(cap[u][v], flow));
        if (flowDelta > 0) {
            PR(flowDelta, v, u);
            p[v] = u;
            return flowDelta;
        }
    }

    return 0;
}

string solve(int count) {
    // print_cap();

    int maxFlow = 0;

    while (true) {
        fill_n(p, MAX_COUNT, -1);
        fill_n(visited, MAX_COUNT, false);
        int flow = dfs(SOURCE, TARGET, INF);

        if (flow == 0) break;

        maxFlow += flow;

        PR(maxFlow);
        assert(maxFlow <= count);

        int n = TARGET;
        while(n > 0) {
            PR(n);
            cap[p[n]][n] -= flow;
            cap[n][p[n]] += flow;
            n = p[n];
        }
        // print_cap();
    }

    // print_cap();

    if (maxFlow < count) {
        return "!";
    }

    char ans[TOTAL_HOSTS + 1];
    REP(i, TOTAL_HOSTS) {
        auto begin = cap[FIRST_HOST + i] + FIRST_TASK;
        auto end   = cap[FIRST_HOST + i] + FIRST_TASK + TOTAL_TASKS;
        int sum = accumulate(begin, end, 0);
        assert(sum == 0 || sum == 1);

        PR(i, sum);

        if (sum == 0) {
            ans[i] = '_';
            continue;
        }

        ans[i] = 'A' + distance(begin, find(begin, end, 1));
    }
    ans[TOTAL_HOSTS] = 0;

    return ans;
}

int main()
{
    ios::sync_with_stdio(false);

    string line;
    int total_count = 0;

    while (getline(cin, line)) {

        if (line.empty()) {
            cout << solve(total_count) << endl;

            fill_n(&cap[0][0], MAX_COUNT*MAX_COUNT, 0);
            total_count = 0;
            continue;
        }

        int taskId = line[0] - 'A';
        int count  = line[1] - '0';

        PR(taskId, count);

        cap[SOURCE][FIRST_TASK + taskId] = count;
        total_count += count;

        for (char c : line.substr(3, line.length() - 4)) {
            int hostId = c - '0';
            PR(hostId);
            cap[FIRST_TASK + taskId][FIRST_HOST + hostId] = INF;
            cap[FIRST_HOST + hostId][TARGET] = 1;
        } 
    }

    cout << solve(total_count) << endl;

    return 0;
}
