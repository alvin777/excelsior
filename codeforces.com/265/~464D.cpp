#include <iostream>
#include <algorithm>

using namespace std;

int vertices[8][3];
int coords_order[8][3] = {{0, 1, 2}, {0, 1, 2}, {0, 1, 2}, {0, 1, 2}, {0, 1, 2}, {0, 1, 2}, {0, 1, 2}, {0, 1, 2}};
int vertices_order[8] = {0, 1, 2, 3, 4, 5, 6, 7};


int counter = 0;

template<typename T>
void print_array(const T array[], int size) {
    for (int i = 0; i < size; ++i)
    {
        cout << array[i] << " ";
    }

    cout << endl;
}


int get_value(int index, int coord) {
    return vertices[vertices_order[index]][coords_order[vertices_order[index]][coord]];
}

// bool check(int coord, int i1, int i2, int i3, int i4) {
//     return get_value(i1, coord) == get_value(i2, coord) &&
//            get_value(i2, coord) == get_value(i3, coord) &&
//            get_value(i3, coord) == get_value(i4, coord);
// }

// bool check() {
//     // x1, x2
//     if (!check(0, 0, 1, 2, 3)) return false;
//     if (!check(0, 4, 5, 6, 7)) return false;

//     // // y1, y2
//     if (!check(1, 0, 1, 4, 5)) return false;
//     if (!check(1, 2, 3, 6, 7)) return false;

//     // // z1, z2
//     if (!check(2, 0, 2, 4, 6)) return false;
//     if (!check(2, 1, 3, 5, 7)) return false;

//     return true;
// }

void print_vertices() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 3; j++) {
            cout << vertices[i][coords_order[i][j]] << " ";
        }
        cout << endl;
    }
}

void print_permutation() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 3; j++) {
            cout << coords_order[i][j] << " ";
        }
        cout << "  ";
    }

    cout << endl;
}

// 0 x1 y1 z1
// 1 x1 y1 z2 
// 2 x1 y2 z1
// 3 x1 y2 z2
// 4 x2 y1 z1
// 5 x2 y1 z2
// 6 x2 y2 z1
// 7 x2 y2 z2

bool check_next(int i) {
    if (i == 5) {
        if (get_value(6, 0) != get_value(7, 0)) return false;
        if (get_value(6, 1) != get_value(7, 1)) return false;
        if (get_value(6, 2) == get_value(7, 2)) return false;
    } else if (i == 4) {
        if (get_value(5, 0) != get_value(7, 0)) return false;
        if (get_value(5, 1) == get_value(7, 1)) return false;
        if (get_value(5, 2) != get_value(7, 2)) return false;
    } else if (i == 3) {
        if (get_value(4, 0) != get_value(7, 0)) return false;
        if (get_value(4, 1) != get_value(5, 1)) return false;
        if (get_value(4, 2) != get_value(6, 2)) return false;
    } else if (i == 2) {
        if (get_value(3, 0) == get_value(7, 0)) return false;
        if (get_value(3, 1) != get_value(7, 1)) return false;
        if (get_value(3, 2) != get_value(7, 2)) return false;
    } else if (i == 1) {
        if (get_value(2, 0) != get_value(3, 0)) return false;
        if (get_value(2, 1) != get_value(7, 1)) return false;
        if (get_value(2, 2) != get_value(6, 2)) return false;
    } else if (i == 0) {
        if (get_value(1, 0) != get_value(3, 0)) return false;
        if (get_value(1, 1) != get_value(5, 1)) return false;
        if (get_value(1, 2) != get_value(7, 2)) return false;
    } else if (i < 0) {
        if (get_value(0, 0) != get_value(3, 0)) return false;
        if (get_value(0, 1) != get_value(5, 1)) return false;
        if (get_value(0, 2) != get_value(6, 2)) return false;

        // counter++;
        // if (counter % 1000 == 0) {
        //     cout << counter << endl;
        // }

        // print_permutation();
        // if (check()) {
        //     print_permutation();
        //     return true;
        // } else {
        //     return false;
        // }

        // return check();

        return true;
    }

    do {
        // cout << "i: " << i << endl;
        if (check_next(i - 1)) {
            return true;
        }
    } while (next_permutation(coords_order[vertices_order[i]], coords_order[vertices_order[i]] + 3));

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
    }

    do {
        print_array(vertices_order, sizeof(vertices_order)/sizeof(vertices_order[0]));
        if (check_next(7)) {
            cout << "YES" << endl;
            print_vertices();
            return 0;
        }
    } while (next_permutation(vertices_order, vertices_order + 8));

    cout << "NO" << endl;

    return 0;
}