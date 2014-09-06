#include <iostream>
#include <vector>
#include <initializer_list>

#ifndef ONLINE_JUDGE
# define d(fmt)      printf(fmt);
# define da(fmt, ...) printf(fmt, __VA_ARGS__);
#else
# define da(fmt, ...)
#endif

using namespace std;

const int MAX_COUNT =  100000; // [1 .. 100000]
const int MIN_VALUE = -100000; // [-100000 .. 100000]
const int MAX_VALUE =  100000;

int data[MAX_COUNT];
int queries[MAX_COUNT][2]; 
int freq[MAX_VALUE - MIN_VALUE + 1];
int b[MAX_VALUE - MIN_VALUE + 1];

int tree[3*128000 + 1];

template<typename T>
void print_array(T array[], int count, const string& label = "") {
    if (label.size()) {
        cout << label << ": ";
    }

    for (int i = 0; i < count; ++i)
    {
        cout << array[i] << " ";
    }

    cout << endl;
}

void build_segment_tree(int data[], int node, int b, int e) {
    // cout << "build_segment_tree, tree node index: " << node << ", b: " << b << ", e: " << e << endl;

    if (b == e) {
        tree[node] = freq[data[b] - MIN_VALUE];
    } else {
        // int m = b + (e-b)/2;
        int m = (b + e)/2;
        int l = 2 * node;
        int r = 2 * node + 1;

        build_segment_tree(data, l, b,     m);
        build_segment_tree(data, r, m + 1, e);

        tree[node] = max(tree[l], tree[r]);
    }

    // cout << "tree[" << node << "] = " << tree[node] << endl;
}

int query(int tree[], int node, int node_b, int node_e, int b, int e) {
    if (b <= node_b && e >= node_e) return tree[node];

    if (b > node_e || e < node_b) return -1;

    int node_m = node_b + (node_e-node_b)/2;
    int l = 2 * node;
    int r = 2 * node + 1;

    int res_l = query(tree, l, node_b,     node_m, b, e);
    int res_r = query(tree, r, node_m + 1, node_e, b, e);

    if (res_l == -1) return res_r;
    if (res_r == -1) return res_l;

    return max(res_l, res_r);
}

int main(int argc, char const *argv[]) {
    std::ios::sync_with_stdio(false);
    int count;
    int queries_count;
    cin >> count >> queries_count;

    fill_n(freq, sizeof(freq)/sizeof(freq[0]), 0);

    for (int i = 0; i < count; ++i)
    {
        cin >> data[i];
        freq[data[i] - MIN_VALUE]++;

        if (i == 0 || data[i] != data[i-1]) {
            b[data[i] - MIN_VALUE] = i;

        }
    }

    // print_array(data, count, "data");
    // print_array(b - MIN_VALUE,    10, "b");
    // print_array(freq - MIN_VALUE, 10, "freq");


    for (int i = 0; i < queries_count; ++i)
    {
        cin >> queries[i][0] >> queries[i][1];
    }

    // build segment tree
    build_segment_tree(data, 1, 0, count - 1);

    // print_array(tree, count*2 + 1, "tree");

    // d("processing queries\n");
    // process queries
    for (int i = 0; i < queries_count; ++i)
    {
        int from = queries[i][0] - 1;
        int to   = queries[i][1] - 1;

        if (data[from] == data[to]) {
            cout << to - from + 1 << endl;
            continue;
        }

        int partial_begin = min(b[data[from] - MIN_VALUE] + freq[data[from] - MIN_VALUE], to) - from;
        int partial_end   = to - max(b[data[to] - MIN_VALUE], from) + 1;
        // da("freq[data[from] - MIN_VALUE]: %d, from: %d, b[data[from] - MIN_VALUE]: %d\n", freq[data[from] - MIN_VALUE], from, b[data[from] - MIN_VALUE]);

        int n = query(tree, 1, 0, count - 1, from + partial_begin + 1, to - partial_end - 1);
        // da("from %d to %d, partial_begin: %d, partial_end: %d, res: %d\n", from, to, partial_begin, partial_end, n);

        int res = max(n, max(partial_begin, partial_end));
        cout << res << endl;
    }

    return 0;
}