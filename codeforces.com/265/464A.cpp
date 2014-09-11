#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    int n;
    cin >> n;

    string s;
    cin >> s;

    int i = 0;
    while (i < s.size() && s[i] == '1') {
        i++;
    }

    cout << min(i + 1, (int)s.size()) << endl;

    return 0;
}