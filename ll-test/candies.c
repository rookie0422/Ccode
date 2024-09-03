#include <stdio.h>
#include <stdlib.h>

// 比较函数，用于排序
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int min_steps(int *candies, int N) {
    // 对糖果袋数量进行排序
    qsort(candies, N, sizeof(int), compare);
    
    int steps = 0;
    int last_taken = 0;
    
    for (int i = 0; i < N; i++) {
        // 跳过空袋子
        if (candies[i] > last_taken) {
            steps++;
            last_taken = candies[i];
        }
    }
    
    return steps;
}

int main() {
    int N;
    scanf("%d", &N);
    
    int candies[N];
    
    for (int i = 0; i < N; i++) {
        scanf("%d", &candies[i]);
    }
    
    int result = min_steps(candies, N);
    
    printf("%d\n", result);
    
    return 0;
}
