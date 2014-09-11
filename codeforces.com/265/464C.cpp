#include <iostream>

using namespace std;

bool process_rest_of_string(string& str, int p, int pos) {
    for (int i = pos + 1; i < str.size(); ++i)
    {
        str[i] = 'a';
        while (          (str[i] == str[i-1]) ||
               (i > 1 && (str[i] == str[i-2]))) 
        {
            str[i]++;
            if (str[i] > 'a' + p - 1) {
                return false;
            }
        }
    }

    return true;
}

int main(int argc, char const *argv[]) {
    int n; 
    int p;
    cin >> n >> p;

    string str;
    cin >> str;

    // cout << "str: '" << str << "'" << endl;

    int pos = str.size() - 1;
    while (pos >= 0) {
        // cout << "str[" << pos << "]: " << str[pos] << " -> " << char(str[pos] + 1) << endl;
        str[pos]++;
        if (str[pos] > 'a' + p - 1) {
            // cout << "overflow" << endl;
            pos--;
            continue;
        }

        if ((pos > 0 && str[pos] == str[pos - 1]) ||
            (pos > 1 && str[pos] == str[pos - 2])) { 
            continue; 
        }

        if (process_rest_of_string(str, p, pos)) {
            break;
        }
    }

    if (pos >= 0) {
        cout << str << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}