#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define ARR_SIZE(arr) (sizeof((arr)) / sizeof((arr[0])))

// bool *camelMatch(char **queries, int queriesSize, char *pattern, int *returnSize)
// {
//     int n = queriesSize;

//     bool *res = (bool *)malloc(n * sizeof(bool));
//     for (int i = 0; i < n; i++) {
//         res[i] = true;
//         int p = 0;
//         for (int j = 0; queries[i][j] != '\0'; j++) {
//             if (p < strlen(pattern) && pattern[p] == queries[i][j]) {
//                 p++;
//             } else if (isupper(queries[i][j])) {
//                 res[i] = false;
//                 break;
//             }
//         }
//         if (p < strlen(pattern)) {
//             res[i] = false;
//         }
//     }
//     *returnSize = n;
//     return res;
// }

bool *camelMatch(char **queries, int queriesSize, char *pattern, int *returnSize)
{
    bool *result = (bool *)malloc(queriesSize * sizeof(bool));

    for (int i = 0; i < queriesSize; i++) {
        int pattern_index = 0;
        result[i] = true;
        for (int j = 0; j < strlen(queries[i]); j++) {
            if ((pattern_index < strlen(pattern)) && (pattern[pattern_index] == queries[i][j])) {
                pattern_index++;
            } else {
                if (isupper(queries[i][j])) {
                    result[i] = false;
                    break;
                }
            }
        }

        if (pattern_index < strlen(pattern)) {
            result[i] = false;
        }
    }
    *returnSize = queriesSize;
    return result;
}


int main(void)
{
#if 0
    int a = 3;
    int b = 2;
    int arr[4] = { 1,2,3,4 };
    printf("max = %d\r\n", MAX(a, b));
    printf("min = %d\r\n", MIN(a, b));
    printf("arr_size = %d\r\n", ARR_SIZE(arr));

    if (check_cpu_mode() == 1) {
        printf("big\r\n");
    } else if (check_cpu_mode() == 2) {
        printf("little\r\n");
    } else {
        printf("undef\r\n");
    }
#endif

    char *queries[] = { "FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack" };
    char *pattern = "FB";

    int *returnSize = (int *)malloc(sizeof(returnSize));


    bool *result = (bool *)malloc(sizeof(result));
    result = camelMatch(queries, 5, pattern, returnSize);

    printf("[%d,%d,%d,%d,%d]\r\n", result[0], result[1], result[2], result[3], result[4]);

}



