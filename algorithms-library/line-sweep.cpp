#include <iostream>
#include <vector>
#include <queue>
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
const int MAX_COUNT = 1e5;
const int MOD = 1e9 + 7;
const double EPS = 1e-6;


// #define ONSegment_JUDGE

#ifndef ONSegment_JUDGE 

///// trace helpers /////
template<typename T>
struct print_t {
    T first;
    T last;
};

template<typename T>
ostream& operator<< (ostream& o, const print_t<T>& s) {
    o << "[";
    for (auto it = s.first; it != s.last; ++it) {
        if (it != prev(s.last)) {
            o << *it << ", ";
        } else {
            o << *it;
        }
    }
    o << "]";

    return o;
}

template<typename T>
print_t<T> dump(T first, T last, string label = "") {
    return {first, last};
}

#define PR(...) pr(#__VA_ARGS__, __VA_ARGS__);

template<typename T>
void print_value(const string& name, const T& value) {
    if (name.find("\"") != string::npos) {
        cout << value << " ";
        return;
    }
    cout << name << ": " << value << ", ";
}

// template<>
// void print_value<Indent>(const string& name, const Indent& value) {
//     cout << value;
// }

template<typename T>
void pr(const string& name, const T& t) {
    cout << name << ": " << t << endl;
}

template<typename T, typename ... Types>
void pr(const string& names, const T& t, Types ... rest) {
    auto comma_pos = names.find(',');
    print_value(names.substr(0, comma_pos), t);
    
    auto next_name_pos = names.find_first_not_of(" \t\n", comma_pos + 1);
    pr(string(names, next_name_pos), rest ...);
}


#else
# define PR(...)
#endif


int n;
// int data[MAX_COUNT];

struct Point {
    double x, y;
};

ostream& operator<< (ostream& o, const Point& p) {
    return o << "(" << p.x << ", " << p.y << ")";
}

struct Segment {
    Point l, r;
    double a, b, c;

    Segment(){}

    Segment(const Point& p1, const Point& p2) {
        if (p1.x < p2.x || ((p1.x == p2.x) && (p1.y > p2.y))) {
            l = p1; r = p2;
        } else {
            l = p2; r = p1;
        }

        if (l.x == r.x) {
            a = 1.0; b = 0; c = -l.x;
        } else {
            a = -(l.y - r.y) / (l.x - r.x);
            b = 1.0;
            c = -(a * l.x) - (b * l.y);
        }

        PR(a, b, c);
    }

    double valueAt(double x) const {
        if (x >= r.x || x <= l.x) return INF;

        return r.y + slope() * (x - r.x);
    }

    double slope() const {
        return (l.y - r.y)/(l.x - r.x);
    }
};

ostream& operator<< (ostream& o, const Segment& s) {
    return o << "a: " << s.a << ", b: " << s.b << ", c: " << s.c;
}

bool lessAtX(const Segment& s1, const Segment& s2, double x) {
    double res1 = s1.valueAt(x);
    double res2 = s2.valueAt(x);

    return res1 != res2 ? res1 < res2 : s1.slope() < s2.slope();
}

enum EventType {BEGIN, INTERSECTION, END};

struct Event {
    EventType type;
    double x;
    Segment s1;
    Segment s2;
};

struct EventLessX {
    bool operator() (const Event& e1, const Event& e2) {
        return e1.x > e2.x || (e1.x == e2.x && e1.type > e2.type);
    }
};

bool areParallel(const Segment& l1, const Segment& l2) { 
    // check coefficient a + b 
    return (fabs(l1.a-l2.a) < EPS) && 
           (fabs(l1.b-l2.b) < EPS); 
}
bool areSame(const Segment& l1, const Segment& l2) { 
    // also check coefficient c 
    return areParallel(l1 ,l2) && (fabs(l1.c - l2.c) < EPS); 
}

bool intersects(const Segment& l1, const Segment& l2, Point* p) {
    if (areSame(l1, l2)) return false; // all points intersect 
    if (areParallel(l1, l2)) return false; // no intersection

    cout << "intersects" << endl;
    cout << "s1: " << l1 << endl;
    cout << "s2: " << l2 << endl;

    // solve system of 2 Segmentar algebraic equations with 2 unknowns
    p->x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b);
    if (fabs(l1.b) > EPS) // special case: test for vertical Segment
        p->y = - (l1.a * p->x + l1.c) / l1.b; // avoid division by zero 
    else
        p->y = - (l2.a * p->x + l2.c) / l2.b; 
    cout << "p: " << *p << endl;
    return true;
}

typedef set<Segment, std::function<bool(const Segment&, const Segment&)>> StatusSetType;

priority_queue<Event, vector<Event>, EventLessX> q;

void addIntersectionEvent(StatusSetType::const_iterator it1, StatusSetType::const_iterator it2) {
    Point p;
    if (intersects(*it1, *it2, &p)) {
        q.push({INTERSECTION, p.x, *it1, *it2});
    }
}

vector<Point> calcIntersections(const vector<Segment>& v) {
    for (auto s : v) {
        q.push({BEGIN, s.l.x, s});
        q.push({END,   s.r.x, s});
    }

    double x = 0;

    StatusSetType ss([&x](const Segment& s1, const Segment& s2){
        return lessAtX(s1, s2, x);
    });

    vector<Point> res;

    while(q.size()) {
        Event e = q.top(); q.pop();

        PR(e.type, e.x);

        if (e.type == BEGIN) {
            x = e.x;

            auto it = ss.insert(e.s1).first;

            if (it != ss.begin()) addIntersectionEvent(it, prev(it));
            auto nextIt = next(it);
            if (nextIt != ss.end()) addIntersectionEvent(it, nextIt);

        } else if (e.type == END) {
            x = e.x;

            auto it = ss.find(e.s1);
            PR(it == ss.end())
            auto nextIt = next(it);

            if (it != ss.begin() && nextIt != ss.end()) {
                addIntersectionEvent(prev(it), nextIt);
            }

            ss.erase(e.s1);
        } else { 
            // intersection

            // reinsert segments
            ss.erase(e.s1);
            ss.erase(e.s2);

            x = e.x;

            auto it1 = ss.insert(e.s1).first;
            auto it2 = ss.insert(e.s2).first;

            auto higherIt = lessAtX(*it1, *it2, x) ? it2 : it1;
            auto lowerIt  = (it1 == higherIt)      ? it2 : it1;

            if (lowerIt != ss.begin()) { addIntersectionEvent(prev(lowerIt), lowerIt); }

            auto nextIt = next(higherIt);
            if (nextIt != ss.end())    { addIntersectionEvent(higherIt, nextIt); }

            res.push_back({e.x, it1->valueAt(e.x)});
        }
    }

    return res;
}

int main()
{
    ios::sync_with_stdio(false);

    vector<Segment> v {{{0, 0},  {5, 0}}, 
                       {{1, 1},  {3, -1}},
                       {{4, -1}, {4, 1}}};
    vector<Point> intersections = calcIntersections(v);

    cout << intersections.size() << endl;
    for (auto p : intersections) {
        cout << p.x << ", " << p.y << " ";
    }

    cout << endl;

    return 0;
}
