#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <array>
#include <string.h>

using namespace std;


template<typename T>
void print_array(T array, int count, const string& label = "") {
    const int MAX_COUNT = 80;

    if (label.size()) {
        cout << label << ": ";
    }

    for (int i = 0; i < min(count, MAX_COUNT); ++i)
    {
        cout << array[i] << " ";
    }

    if (count > MAX_COUNT) {
        cout << "...";
    }

    cout << endl;
}

int count = 0;

const int ARRAY_LENGTH = 100001 + 3*50000 + 1000;
char data[ARRAY_LENGTH];
int next[ARRAY_LENGTH];
long long chunk_rem[ARRAY_LENGTH]; // chunk remainder, i.e. in 11(103)(103): 103 mod N
long long one_rem[ARRAY_LENGTH];   // 1xxx remainder,   i.e in 11(103)(103): 1000 mod N

array<vector<int>, 10> ind;
vector<int> chunks;

// bool trace = true;
bool trace = false;

void replace(const char c, const string& str) {
    int i = c - '0';

    if (str.length() == 0) {
        for (auto j : ind[i]) {
            data[j] = '-';
        }

        ind.at(i).clear();
    } else if (str.length() == 1) {
        if (c == str[0]) return;
        
        for (auto j : ind[i]) {
            data[j] = str[0];
        }

        ind.at(str[0] - '0').insert(ind.at(str[0] - '0').end(), 
                                    ind.at(i).begin(), ind.at(i).end());
        ind.at(i).clear();
    } else {
        chunks.push_back(::count);

        for (auto j : ind[i]) {
            data[j] = 'j';
            ::next[j] = ::count;
        }

        ind[i].clear();

        for (auto c : str) {
            data[::count] = c;
            ind[c - '0'].push_back(::count);
            
            ::next[::count] = ::count+1;

            ::count++;
        }
        data[::count] = 0;
        ::next[::count] = -1;
        ::count++;
    }
}

int get_number(int divisor) {
    // preprocess chunks
    // for each chunk from last:
    //   chunk_rem = 0
    //   one_rem = 1
    //   if digit - add chunk_rem, one_rem
    //   if jump - add chunk chunk_rem, one_rem
    // process original string
    //   if digit rem += rem*10 + digit
    //   if jump - rem = rem*one_rem + chunk_rem

    for (auto it = chunks.rbegin(); it != chunks.rend(); ++it) {
        int i = *it;
        chunk_rem[i] = 0;
        one_rem[i] = 1;

        int j = *it;
        while (data[j]) {
            if (isdigit(data[j])) {
                chunk_rem[i] = (chunk_rem[i] * 10 + data[j] - '0') % divisor;
                one_rem[i]   = (one_rem[i] * 10) % divisor;
            } else if (data[j] == 'j') {
                chunk_rem[i] = (chunk_rem[i] * one_rem[::next[j]] + chunk_rem[::next[j]]) % divisor;
                one_rem[i]   = (one_rem[i] * one_rem[::next[j]]) % divisor;
            }
            
            // skip deleted ('-')

            j++;
        }

        if (trace)
            cout << "chunk: " << i << ", chunk_rem: " << chunk_rem[i] << ", one_rem: " << one_rem[i] << endl;
    }

    int i = 0;
    long long rem = 0;
    while (data[i]) {
        if (isdigit(data[i])) {
            rem = (rem * 10 + data[i] - '0') % divisor;
        } else if (data[i] == 'j') {
            rem = (rem * one_rem[::next[i]] + chunk_rem[::next[i]]) % divisor;
        }

        if (trace)
            cout << "i: " << i << ", rem: " << rem << endl;

        i++;
    }

    return rem;
}

int main(int argc, char const *argv[])
{
    ios::sync_with_stdio(false);

    // ifstream in("464E-test1.in");
    // streambuf *cinbuf = cin.rdbuf(); //save old buf
    // cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!

    fill_n(chunk_rem, -1, sizeof(chunk_rem)/sizeof(chunk_rem[0]));
    fill_n(one_rem, -1,   sizeof(one_rem)/sizeof(one_rem[0]));

    cin.getline(data, sizeof(data));
    ::count = strlen(data);

    for (int i = 0; i < ::count; i++) {
        ::next[i] = i + 1;
        ind[data[i] - '0'].push_back(i);
    }
    ::next[::count] = -1;
    
    ::count++; // leave terminating zero

    if (trace) {
        cout << "count: " << ::count << endl;
        print_array(data,   ::count, "data");
        print_array(::next, ::count, "next");
    }

    int queries_count;
    cin >> queries_count;

    if (trace) {
        cout << "queries_count: " << queries_count << endl;
    }

    for (int i = 0; i < queries_count; i++) {
        char c;
        cin >> c;
        
        cin.ignore(2); // ->

        string s;
        getline(cin, s);

        if (trace) {
            cout << "replace " << c << " with " << s << endl;
        }

        replace(c, s);

        if (trace) {
            cout << "count: " << ::count << endl;
            print_array(data,   ::count, "data");
            print_array(::next, ::count, "next");
        }
    }

    int number = get_number(1000000007);

    cout << number << endl;

    return 0;
}