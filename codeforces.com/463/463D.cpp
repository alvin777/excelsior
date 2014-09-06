#include <stdio.h>

#include <iostream>
#include <algorithm>
#include <vector>
#include <string.h>

#ifdef ONLINE_JUDGE
#   define LOG(fmt, ...)
#else
#   define LOG(fmt, ...) printf(fmt, __VA_ARGS__);
#endif

const int MAX_ARRAYS = 5;
const int MAX_COUNT  = 1000;
const int MAX_NUMBER = 1001;

int data[MAX_ARRAYS][MAX_COUNT];
int pos[MAX_ARRAYS][MAX_NUMBER];
std::vector<int> g[MAX_NUMBER];

void print_graph() {
    printf("printing graph\n");
    for (int i = 1; i <= MAX_NUMBER; i++) {
        for (int j : g[i]) {
            printf("%4d -> %4d\n", i, j);
        }
    }
}

template<typename T>
void print_array(const T array[], int count) {
    for (int i = 0; i < count; i++) {
        std::cout << array[i] << " ";
    }

    std::cout << std::endl;
}

void dfs_rec(int n, int depth[]) {
    for (int c : g[n]) {
        if (depth[c] == 0) {
            dfs_rec(c, depth);
        }
        depth[n]  = std::max(depth[n],  depth[c] + 1);
    }

    depth[n]  = std::max(depth[n], 1);
}

int dfs(int nums_count) {
    int max_depth = 0;
    int depth[MAX_NUMBER];
    std::fill_n(depth, sizeof(depth)/sizeof(depth[0]), 0);

    for (int i = 1; i <= nums_count; ++i) {
        LOG("dfs for: %d\n", i);

        if ((g[i].size() == 0) || (depth[i] > 0)) {
            continue;
        }

        dfs_rec(i, depth);
        max_depth  = std::max(max_depth, depth[i]);
    }

    return max_depth;
}

int main(int argc, char const *argv[])
{
    int nums_count;
    scanf("%d", &nums_count);

    int arrays_count;
    scanf("%d\n", &arrays_count);

    for (int i = 0; i < arrays_count; ++i) {
        for (int j = 0; j < nums_count; ++j) {
            scanf("%d", &data[i][j]);
            pos[i][data[i][j]] = j;
        }
    }

    if (nums_count == 1) {
        printf("1\n");
        return 0;
    }

    for (int j = 1; j <= nums_count; ++j) {
        for (int p = 1; p <= nums_count; p++) {
            if (j == p) continue;

            bool before_in_all_arrays = true;
            for (int i = 0; i < arrays_count; ++i) {
                if (pos[i][p] >= pos[i][j]) {
                    before_in_all_arrays = false;
                    break;
                }
            }

            if (before_in_all_arrays) {
                g[p].push_back(j);
            }
        }
    }

    // print_graph();

    printf("%d\n", dfs(nums_count));

    return 0;
}