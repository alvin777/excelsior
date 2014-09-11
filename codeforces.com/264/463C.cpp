#include <stdio.h>
#include <memory.h>

#include <iostream>

int max(int x, int y) {
    return x > y ? x : y;
}

template<typename T>
void print_array(T array[], int size) {
    for (int i = 0; i < size; ++i)
    {
        // printf("%d ", array[i]);
        std::cout << array[i] << " ";
    }

    printf("\n");
}

unsigned int data[2000][2000];

int main(int argc, char const *argv[])
{
    /* code */

    int count;
    scanf("%d\n", &count);

    // printf("reading data\n");

    for (int i = 0; i < count; i++)  {
        for (int j = 0; j < count; j++) {
            scanf("%d\n", &data[i][j]);
        }
    }

    // print_array(&data[0], count);


    // printf("calculating diagonals\n");

    long long unsigned int tr_dial_sum[4001];
    long long unsigned int br_diag_sum[4001];

    memset(tr_dial_sum, 0, sizeof(tr_dial_sum));
    memset(br_diag_sum, 0, sizeof(br_diag_sum));

    // print_array(tr_dial_sum, 2*count + 1);
    // print_array(br_diag_sum, 2*count + 1);

    for (int i = 0; i < count; i++)  {
        for (int j = 0; j < count; j++) {
            tr_dial_sum[i + j] += data[i][j];
            br_diag_sum[count + 1 + i - j] += data[i][j];
        }
    }

    // print_array(tr_dial_sum, 2*count + 1);
    // print_array(br_diag_sum, 2*count + 1);


    // printf("calculating max sums\n");

    long long unsigned int max_sum_value_list[2] = {0, 0};
    int cells_list[2][2] = {{-1, -1}, {-1, -1}};

    for (int i = 0; i < count; i++)  {
        for (int j = 0; j < count; j++) {
            long long unsigned int sum = tr_dial_sum[i + j] + br_diag_sum[count + 1 + i - j] - data[i][j];
            // printf("i: %d, j: %d, %lld\n", i, j, sum);
            // printf("tr_dial_sum[i + j]: %d, br_diag_sum[count + 1 + i - j]: %d, data[i][j]: %d\n", 
            //         tr_dial_sum[i + j], br_diag_sum[count + 1 + i - j], data[i][j]);
            if (sum >= max_sum_value_list[(i + j) % 2]) {
                max_sum_value_list[(i + j) % 2] = sum;
                cells_list[(i + j) % 2][0] = i + 1;
                cells_list[(i + j) % 2][1] = j + 1;
            }
        }
    }

    // print_array(max_sum_value_list, 2);

    // printf("%I64d\n", max_sum_value_list[0] + max_sum_value_list[1]);
    printf("%lld\n", max_sum_value_list[0] + max_sum_value_list[1]);
    // std::cout << (max_sum_value_list[0] + max_sum_value_list[1]) << std::endl;
    printf("%d %d %d %d\n", cells_list[0][0], cells_list[0][1], cells_list[1][0], cells_list[1][1]);

    return 0;
}