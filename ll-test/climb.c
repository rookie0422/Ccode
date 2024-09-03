#include <stdio.h>

int climb(int n) {
    // Base cases
    if (n == 1) {
        return 1;
    }
    if (n == 2) {
        return 2;
    }
    if (n <= 0) {
        return 0;
    }

    // Recursive cases
    return climb(n - 1) + climb(n - 2);
}

int main() {
    int n = 0;
    scanf("%d", &n);
    int num = climb(n);
    printf("%d\n",num);
    return 0;
    
}