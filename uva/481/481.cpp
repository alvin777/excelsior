#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <fstream>
#include <queue>
#include <tuple>

using namespace std;
typedef long long ll;
typedef vector<int> vi;

const int MAX_COUNT = 1e7;

#define D(a) cout << #a ": " << a << endl;

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


int data[MAX_COUNT];
int P[MAX_COUNT];
int M[MAX_COUNT];


int main()
{
    ios::sync_with_stdio(false);

    int n = 0;
    int d = 0;
    while (cin >> d) {
        data[n++] = d;
    }

    M[0] = -1;
    M[1] = 0;
    P[0] = -1;
    int max_len = 1;

    for (int i = 1; i < n; ++i)
    {
        int j = distance(M, lower_bound(M, M + max_len + 1, i, [](int it, int val){ return data[it] < data[val]; }));

        if (j > max_len) {
            max_len++;
        }

        M[j] = i;
        P[i] = M[j-1];
    }

    int i = M[max_len];
    vi ans;
    while (i >= 0) {
        ans.push_back(data[i]);
        i = P[i];
    }

    cout << max_len << endl << "-" << endl;

    for (auto it = ans.rbegin(); it != ans.rend(); ++it)
    {
        cout << *it << endl;
    }

    return 0;
}
