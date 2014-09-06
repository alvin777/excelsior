#include <stdio.h>
#include <string.h>
#include <ctype.h>

const int MOD = 1000000007;

int main(int argc, char const *argv[])
{
    int test_cases;
    scanf("%d\n", &test_cases);
    
    for (int i = 0; i < test_cases; ++i)
    {
        char buffer[100001];
        memset(buffer, 0, sizeof(buffer));
        // scanf("%s", buffer);
        fgets(buffer, sizeof(buffer), stdin);

        char* buffer_ptr = buffer;
        unsigned int result = 1;
        int even = 0;
        while (*buffer_ptr) {
            // printf("result: %d, even: %d, char: %c\n", result, even, *buffer_ptr);
            if (isspace(*buffer_ptr)) {
                buffer_ptr++;
                continue;
            }

            if (even) {
                if (*buffer_ptr == 'l') {
                    result = (result * 2 - 1) % MOD;
                } else {
                    result = (result * 2 + 1) % MOD;
                }
            } else {
                if (*buffer_ptr == 'l') {
                    result = result * 2 % MOD;
                } else {
                    result = (result * 2 + 2) % MOD;
                }
            }
            even = !even;
            buffer_ptr++;
        }
        printf("%d\n", result);
    }

    return 0;
}