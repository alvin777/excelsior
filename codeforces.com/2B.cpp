#include <stdio.h>
#include <string>
#include <iostream>
#include <iomanip>

#include <time.h>
#include <stdlib.h>
#include <cstdio>


const int MAX_SIZE = 1000;
const int WEIGHT2 = 0;
const int WEIGHT5 = 1;

int matrix[MAX_SIZE][MAX_SIZE];
int  matrixWeight[MAX_SIZE][MAX_SIZE][2];
int  matrixCumulativeWeight[MAX_SIZE][MAX_SIZE][2];
char matrixDir[MAX_SIZE][MAX_SIZE][2];
bool matrixZero[MAX_SIZE][MAX_SIZE][2];

short getDividersCount(int number, int divider, int& leftover) {
    int count = 0;

    if (number == 0) {
        leftover = number;
        return 0;
    }

    if (divider == 2) {
        while (!(number & 1)){
            number >>= 1;
            count++;
        }
        leftover = number;
        return count;
    }

    // printf("dividers count for %d by %d", number, divider);

    while (number % divider == 0) {
        number /= divider;
        count++;
    }

    // printf(" is %d\n", count);
    leftover = number;

    return count;
}

template<typename T>
void printMatrix(T matrix[][MAX_SIZE], int width, int height) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            printf("%3d ", matrix[x][y]);
        }
        printf("\n");
    }
    printf("\n");
}

template<typename T>
void printMatrixWeight(T matrix[][MAX_SIZE][2], int width, int height) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            printf("%d/%d ", matrix[x][y][0], matrix[x][y][1]);
        }
        printf("\n");
    }
    printf("\n");
}

template<typename T>
void printCumulativeMatrixWeight(T matrix[][MAX_SIZE][2], int width, int height, int type) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // printf("%3d ", matrix[x][y][type]);
            std::cout << std::setw(3) << matrix[x][y][type] << " ";
        }
        printf("\n");
    }
    printf("\n");
}

void calculateCumulativeMatrix(int width, int height) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {

            bool isZero = matrix[x][y] == 0;

            if (isZero) {
                matrixWeight[x][y][WEIGHT2] = 1;
                matrixWeight[x][y][WEIGHT5] = 1;
            } else {
                int leftover;
                matrixWeight[x][y][WEIGHT2] = getDividersCount(matrix[x][y], 2, leftover);
                matrixWeight[x][y][WEIGHT5] = getDividersCount(leftover, 5, leftover);
            }

            if (x == 0 && y == 0) {
                matrixCumulativeWeight[x][y][WEIGHT2] = matrixWeight[x][y][WEIGHT2];
                matrixCumulativeWeight[x][y][WEIGHT5] = matrixWeight[x][y][WEIGHT5];
                matrixZero[x][y][WEIGHT2] = isZero;
                matrixZero[x][y][WEIGHT5] = isZero;
                matrixDir[x][y][WEIGHT2] = ' ';
                matrixDir[x][y][WEIGHT5] = ' ';
                continue;
            }

            // printf("cell: %d, %d\n", x, y);

            for (int i = 0; i <= 1; i++) {

                int weight = matrixWeight[x][y][i];
                char direction = ' ';
                if (x == 0) {
                    if (isZero || matrixZero[x][y-1][i]) {
                        weight = 1;
                        matrixZero[x][y][i] = 1;
                    } else {
                        weight += matrixCumulativeWeight[x][y-1][i];
                    }
                    direction = 'D';
                } else if (y == 0) {
                    if (isZero || matrixZero[x-1][y][i]){
                        weight = 1;
                        matrixZero[x][y][i] = 1;
                    } else {
                        weight += matrixCumulativeWeight[x-1][y][i];
                    }
                    direction = 'R';
                } else {
                    int weightFromTop = 0;
                    if (isZero || matrixZero[x][y-1][i]){
                        weightFromTop = 1;
                    } else {
                        weightFromTop = weight + matrixCumulativeWeight[x][y-1][i];
                    }

                    int weightFromLeft = 0;
                    if (isZero || matrixZero[x-1][y][i]) {
                        weightFromLeft = 1;
                    } else {
                        weightFromLeft = weight + matrixCumulativeWeight[x-1][y][i];
                    }
                    // printf("weight: %d, weightFromLeft: %d, weightFromTop: %d\n", weight, weightFromLeft, weightFromTop);
                    if (weightFromTop < weightFromLeft) {
                        weight = weightFromTop;
                        matrixZero[x][y][i] = isZero || matrixZero[x][y-1][i];
                        direction = 'D';
                    } else {
                        weight = weightFromLeft;
                        matrixZero[x][y][i] = isZero || matrixZero[x-1][y][i];
                        direction = 'R';
                    }
                }

                matrixCumulativeWeight[x][y][i] = weight;
                matrixDir[x][y][i] = direction;
            }
        }
    }
}

std::string getPath(int width, int height, int type, int& minWeight) {
    int x = width - 1;
    int y = height - 1;

    std::string path;
    minWeight = 0;
    bool zero = false;
    while (x != 0 || y != 0) {
        // printf("%d, %d, %c\n", x,y,matrixDir[x][y][type]);
        path = matrixDir[x][y][type] + path;
        zero |= matrix[x][y] == 0;
        if (zero) {
            minWeight = 1;
        } else {
            minWeight += matrixWeight[x][y][type == WEIGHT2 ? WEIGHT5 : WEIGHT2];
        }
        if (matrixDir[x][y][type] == 'D') {
            y -= 1;
        } else {
            x -= 1;
        }
    }
    // printf("%s\n", path.c_str());
    minWeight = std::min(minWeight, matrixCumulativeWeight[width-1][height-1][type]);
    return path;
}

// inline void fastRead_int(int &x) {
//     int c = getchar_unlocked();
//     x = 0;
//     int neg = 0;

//     for(; ((c<48 || c>57) && c != '-'); c = getchar_unlocked());

//     // if(c=='-') {
//     //     neg = 1;
//     //     c = getchar_unlocked();
//     // }

//     for(; c>47 && c<58 ; c = getchar_unlocked()) {
//         x = (x<<1) + (x<<3) + c - 48;
//     }

//     // if(neg)
//     //     x = -x;
// }

// std::string buildPathVia(int viaX, int viaY, int width, int height) {
//     int x = 0;
//     int y = 0;
//     std::string path;
//     while (y++ < viaY) {
//         path += 'D';
//     }
//     while (x++ < viaX) {
//         path += 'R';
//     }
//     while (y++ < height) {
//         path += 'D';
//     }
//     while (x++ < width) {
//         path += 'R';
//     }
//     return path;
// }

int main(int, char**){

    int matrixSize = 1000;
    std::cin >> matrixSize;

    for (int y = 0; y < matrixSize; y++) {
        for (int x = 0; x < matrixSize; x++) {
            //std::cin >> matrix[x][y];
            scanf("%i", &matrix[x][y]);
            // fastRead_int(matrix[x][y]);
        }
    }

    // srand(time(NULL));
    // for (int y = 0; y < matrixSize; y++) {
    //     for (int x = 0; x < matrixSize; x++) {
    //         matrix[x][y] = abs(rand() % 1000000000);
    //     }
    // }

    // printMatrix(matrix, matrixSize, matrixSize);

    calculateCumulativeMatrix(matrixSize, matrixSize);

    int minWeight2, minWeight5;
    std::string path2 = getPath(matrixSize, matrixSize, WEIGHT2, minWeight2);
    std::string path5 = getPath(matrixSize, matrixSize, WEIGHT5, minWeight5);

    // printMatrixWeight(matrixWeight, matrixSize, matrixSize);
    // printCumulativeMatrixWeight(matrixCumulativeWeight, matrixSize, matrixSize, WEIGHT2);
    // printCumulativeMatrixWeight(matrixCumulativeWeight, matrixSize, matrixSize, WEIGHT5);
    // printCumulativeMatrixWeight(matrixDir, matrixSize, matrixSize, WEIGHT2);
    // printCumulativeMatrixWeight(matrixDir, matrixSize, matrixSize, WEIGHT5);

    std::string path;
    int minWeight;
    if (minWeight2 < minWeight5) {
        minWeight = minWeight2;
        path = path2;
    } else {
        minWeight = minWeight5;
        path = path5;
    }

    printf("%d\n", minWeight);
    printf("%s\n", path.c_str());

}