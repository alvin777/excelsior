#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

typedef long long ll;

const int ELEMENTS_COUNT = 10e5;

// trace
template<typename T>
void print_array(const T* array, int size, const string& label = "") {
    if (label.size())
        cout << label << ": ";

    for (int i = 0; i < size; ++i)
    {
        cout << array[i] << " ";
    }

    cout << endl;
}

template<typename T>
ostream& operator<<(ostream& o, const vector<T>& cont) {
    for (auto& el : cont)
        o << el << " ";
    return o;
}


int data[ELEMENTS_COUNT];
ll total_sum;
vector<int> ind_begin;
vector<int> ind_end;

int main()
{
    ios::sync_with_stdio(false);

    int count;
    cin >> count;

    if (count < 3) {
        cout << "0" << endl;
        return 0;
    }

    for (int i = 0; i < count; ++i)
    {
        cin >> data[i];
        total_sum += data[i];
    }

    ll running_sum = 0;
    for (int i = 0; i < count - 2; ++i)
    {
        running_sum += data[i];
        if (running_sum * 3 == total_sum) {
            ind_begin.push_back(i);
        }
    }

    running_sum = 0;
    for (int i = count - 1; i >= 2; i--)
    {
        running_sum += data[i];
        if (running_sum * 3 == total_sum) {
            ind_end.push_back(i);
        }
    }

    reverse(ind_end.begin(), ind_end.end());

    // print_array(data, count, "data");
    // cout << "total_sum: " << total_sum << endl;
    // cout << "ind_begin: " << ind_begin << endl;
    // cout << "ind_end: "   << ind_end << endl;

    ll ans = 0;
    int j = 0;
    for (int i = 0; i < ind_begin.size(); ++i)
    {
        while (j < ind_end.size() && ind_end[j] < ind_begin[i] + 2) {
            j++;
        }
        ans += ind_end.size() - j;
    }


    cout << ans << endl;

    return 0;
}