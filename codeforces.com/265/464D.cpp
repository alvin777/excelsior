#include <iostream>
#include <algorithm>

using namespace std;

int vertices[8][3];
// int coords_order[8][3] = {{0, 1, 2}, {0, 1, 2}, {0, 1, 2}, {0, 1, 2}, {0, 1, 2}, {0, 1, 2}, {0, 1, 2}, {0, 1, 2}};
int vertices_order[8] = {0, 1, 2, 3, 4, 5, 6, 7};


// trace
template<typename T>
void print_array(const T array[], int size) {
    for (int i = 0; i < size; ++i)
    {
        cout << array[i] << " ";
    }

    cout << endl;
}


void print_vertices() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 3; j++) {
            // cout << vertices[i][coords_order[i][j]] << " ";
            cout << vertices[i][j] << " ";
        }
        cout << endl;
    }
}

void print_permutation() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 3; j++) {
            // cout << coords_order[i][j] << " ";
            cout << vertices[i][j] << " ";
        }
        cout << "  ";
    }

    cout << endl;
}


// 

struct vertex_t
{
    long long int x, y, z;
    // vertex_t (int x, int y, int z):x(x), y(y), z(z){};
};

bool operator== (const vertex_t& v1, const vertex_t& v2) {
    return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
}

ostream& operator<< (ostream& o, const vertex_t& v) {
    return o << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}

int get_value(int index, int coord) {
    // return vertices[vertices_order[index]][coords_order[vertices_order[index]][coord]];
    return vertices[vertices_order[index]][coord];
}

// bool is_coplanar(int i1, int i2, int i3, int i4) {
//     vertex_t v1{get_value(i1, 0), get_value(i1, 1), get_value(i1, 2)};
//     vertex_t v2{get_value(i2, 0), get_value(i2, 1), get_value(i2, 2)};
//     vertex_t v3{get_value(i3, 0), get_value(i3, 1), get_value(i3, 2)};
//     vertex_t v4{get_value(i4, 0), get_value(i4, 1), get_value(i4, 2)};
    
//     return value(normal(v1, v2, v3) * v4);
//     return true;
// }

long long int distance2(const vertex_t& v1, const vertex_t& v2) {
    return (v2.x - v1.x)*(v2.x - v1.x) + 
           (v2.y - v1.y)*(v2.y - v1.y) +
           (v2.z - v1.z)*(v2.z - v1.z);
}

long long int distance2(int i1, int i2) {
    vertex_t v1 = {get_value(i1, 0), get_value(i1, 1), get_value(i1, 2)};
    vertex_t v2 = {get_value(i2, 0), get_value(i2, 1), get_value(i2, 2)};
    return distance2(v1, v2);
}

bool is_square(int i1, int i2, int i3, int i4) {
    vertex_t v1 = {get_value(i1, 0), get_value(i1, 1), get_value(i1, 2)};
    vertex_t v2 = {get_value(i2, 0), get_value(i2, 1), get_value(i2, 2)};
    vertex_t v3 = {get_value(i3, 0), get_value(i3, 1), get_value(i3, 2)};
    vertex_t v4 = {get_value(i4, 0), get_value(i4, 1), get_value(i4, 2)};

    bool res = distance2(v1, v2) == distance2(v2, v3) &&
               distance2(v2, v3) == distance2(v3, v4) &&
               distance2(v3, v4) == distance2(v4, v1) &&
               distance2(v1, v3) == distance2(v2, v4);

    // cout << "vertices: " << v1 << " " << v2 << " " << v3 << " " << v4 << ": " << res << endl;
    // if (res) {
    //     cout << "vertices: " << v1 << " " << v2 << " " << v3 << " " << v4 << ": " << res << endl;
    // }

    return res;
}

bool check_next(int i) {

    bool trace = false;
    // bool trace = true;

    do {
        if (trace)
            cout << std::string(4*(7-i), ' ') << "i: "<< i << ", (" << get_value(i, 0) << ", " << get_value(i, 1) << ", " << get_value(i, 2) << "): ";

        bool should_continue = false;
        for (int j = i + 1; j < 8; j++){
            if (get_value(i, 0) == get_value(j, 0) &&
                get_value(i, 1) == get_value(j, 1) &&
                get_value(i, 2) == get_value(j, 2)) {

                if (trace)
                    cout << "same value" << endl;

                should_continue = true;
                break;
            }
        }

        if (should_continue) {
            continue;
        }

        if (i == 5) {
            if (distance2(5, 6) != distance2(6, 7)) { if (trace) cout << "invalid distance (5)" << endl; continue; }
        } else if (i == 4) {
            if (!is_square(4, 5, 6, 7))             { if (trace) cout << "not square (4)" << endl;       continue; }
        } else if (i == 3) {
            if (distance2(3, 7) != distance2(4, 7)) { if (trace) cout << "invalid distance (3)" << endl; continue; }
        } else if (i == 2) {
            if (!is_square(2, 3, 7, 6))             { if (trace) cout << "not square (2)" << endl;       continue; }
        } else if (i == 1) {
            if (!is_square(1, 2, 6, 5))             { if (trace) cout << "not square (1)" << endl;       continue; }
        } else if (i == 0) {
            if (!is_square(0, 1, 2, 3))             { if (trace) cout << "not square (0)" << endl;       continue; }

            return true;
        }

        if (trace)
            cout << endl;

        if (check_next(i - 1)) {
            return true;
        }
    // } while (next_permutation(coords_order[vertices_order[i]], coords_order[vertices_order[i]] + 3));
    } while (next_permutation(vertices[vertices_order[i]], vertices[vertices_order[i]] + 3));

    return false;
}

int main(int argc, char const *argv[])
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            cin >> vertices[i][j];
        }

        sort(vertices[i], vertices[i] + 3);
    }

    do {
        // print_array(vertices_order, sizeof(vertices_order)/sizeof(vertices_order[0]));
        if (check_next(7)) {
            cout << "YES" << endl;
            print_vertices();
            return 0;
        }
    } while (next_permutation(vertices_order, vertices_order + 8));

    cout << "NO" << endl;

    return 0;
}