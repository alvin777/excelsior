#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;
typedef long long ll;
typedef vector<int> vi; 

#define REP(k,a) for(int k=0; k < (a); ++k)
#define FOR(i,a,b) for(int i=a; i < (b); ++i)
#define ALL(a) begin(a), end(a)
#define COUNT(a) (sizeof(a)/sizeof(a[0]))

const int INF = 1e9;
const int MAX_COUNT = 301;
const int MOD = 1e9 + 7;
const double EPS = 1e-6;


// #define ONLINE_JUDGE

#ifndef ONLINE_JUDGE 

///// trace helpers /////



#else
# define PR(...)
#endif


struct Point {
    double x, y;
};

Point p1;
Point p2;

struct Line {
    double a, b, c;
};

// Line l[MAX_COUNT];

Line lineFromPoints(const Point& p1, const Point& p2) {
    Line line;
    if (p1.x == p2.x) { 
        // vertical line is handled nicely here 
        line = {1.0, 0.0, -p1.x};
    } else {
        line.a = -(double)(p1.y - p2.y) / (p1.x - p2.x); 
        line.b = 1.0;
        line.c = -(double)(line.a * p1.x) - (line.b * p1.y);
    }

    return line;
}

bool areParallel(const Line& l1, const Line& l2) { 
    // check coefficient a + b 
    return (fabs(l1.a-l2.a) < EPS) && 
           (fabs(l1.b-l2.b) < EPS); 
}
bool areSame(const Line& l1, const Line& l2) { 
    // also check coefficient c 
    return areParallel(l1 ,l2) && (fabs(l1.c - l2.c) < EPS); 
}

bool intersects(const Line& l1, const Line& l2, Point* p) {
    if (areSame(l1, l2)) return false; // all points intersect 
    if (areParallel(l1, l2)) return false; // no intersection

    // solve system of 2 linear algebraic equations with 2 unknowns
    p->x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b);
    if (fabs(l1.b) > EPS) // special case: test for vertical line
        p->y = - (l1.a * p->x + l1.c) / l1.b; // avoid division by zero 
    else
        p->y = - (l2.a * p->x + l2.c) / l2.b; 
    return true;
}

bool isPointInBox(const Point& p, const Point& p1, const Point& p2) {
    return p.x >= min(p1.x, p2.x) && 
           p.x <= max(p1.x, p2.x) && 
           p.y >= min(p1.y, p2.y) &&
           p.y <= max(p1.y, p2.y);
}

int main()
{
    ios::sync_with_stdio(false);

    cin >> p1.x >> p1.y;
    cin >> p2.x >> p2.y;

    Line way = lineFromPoints(p1, p2);

    int ans = 0;

    int n;
    cin >> n;
    REP(i, n) {
        // cin >> l[i].a >> l[i].b >> l[i].c;
        Line line;
        cin >> line.a >> line.b >> line.c;

        Point p;
        if (intersects(line, way, &p)) {
            if (isPointInBox(p, p1, p2)) {
                ans++;
            }
        }
    }

    cout << ans << endl;

    return 0;
}
