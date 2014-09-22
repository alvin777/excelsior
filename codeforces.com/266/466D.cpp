#include <iostream>
#include <cstdlib>

typedef long long ll;

using namespace std;

const int MAX_ELEMENTS = 2000;
const int DIVISOR = 1e9 + 7;

int data[MAX_ELEMENTS];

template<typename T>
void print_array(ostream& o, T array, size_t count, const string& label) {
    if (label.size())
        cout << label << ": ";

    for (int i = 0; i < count; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
}

int main(int argc, char const *argv[])
{
    int n, h;
    cin >> n >> h;

    for (int i = 0; i < n; ++i)
    {
        cin >> data[i];
    }

    // print_array(cout, data, n, "data");
    // cout << "divisor: " << DIVISOR << endl;

    if (h - data[n-1] > 1 ||
        h - data[0] > 1) {
        cout << "0" << endl;
        return 0;
    }


    ll ans = 1;
    for (int i = 1; i < n; ++i)
    {
        if (data[i] - data[i-1] == 0) {
            ans = (ans * (h - data[i] + 1)) % DIVISOR;
        } 
        else if (data[i] - data[i-1] == -1) {
            ans = (ans * (h - data[i])) % DIVISOR;
        }
        else if (data[i] - data[i-1] == -1) {
            // same ans
        } 
        else {
            // no solution
            ans = 0;
            break;
        }
    }

    cout << ans << endl;

    return 0;
}