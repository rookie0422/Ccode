#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main()
{
    char *str = malloc(0);
    if (str == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    strcpy(str, "hello");
    printf("str_p == %p\n", str);
    printf("str == %s\n", str);
    printf("str_size == %ld\n", sizeof(str));
    free(str);
    return 0;
}
