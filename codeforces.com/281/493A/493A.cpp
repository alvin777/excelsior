#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>

using namespace std;
typedef long long ll;
typedef vector<int> vi; 

#define REP(k,a) for(int k=0; k < (a); ++k)
#define FOR(i,a,b) for(int i=a; i < (b); ++i)
#define ALL(a) begin(a), end(a)
#define COUNT(a) (sizeof(a)/sizeof(a[0]))

const int INF = 1e9;
const int MAX_COUNT = 1e5;
const int MOD = 1e9 + 7;


// #define ONLINE_JUDGE

#ifndef ONLINE_JUDGE 

///// trace helpers /////



#else
# define PR(...)
#endif

map<char, map<int, int>> cards;

int main()
{
    ios::sync_with_stdio(false);

    string team1;
    string team2;
    int n;
    cin >> team1 >> team2 >> n;
    REP(i, n) {
        int min;
        char team;
        int player;
        char card;
        cin >> min >> team >> player >> card;
        
        cards[team][player] += (card == 'y' ? 1 : 2);

        if (cards[team][player] >= 2 && cards[team][player] < INF) {
            cout << (team == 'h' ? team1 : team2) << " " << player << " " << min << endl;
            cards[team][player] = INF;
        }
    }

    return 0;
}
