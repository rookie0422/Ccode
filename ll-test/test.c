#include <stdio.h>
#include <assert.h>
char *func(char *str, int *max)
{
    char *loc = NULL;
    char *s;
    int temp = 0;
    *max     = 0;

    assert(str != NULL);

    while (*str != '\0') {
        s = str;
        if ((*s >= '0') && (*s <= '9')) {
            temp++;
            s++;
            while ((*s >= '0') && (*s <= '9')) {
                temp++;
                s++;
            }

            if (temp > *max) {
                *max = temp;
                loc  = str;
            }

            str  = s;
            temp = 0;
            continue;
        }
        str++;
    }
    printf("max = %d\n", *max);
    return loc;
}

int main()
{
    char str[] = "abc111a2222";
    int size   = 0;
    // char *loc = NULL;
    // loc = func(str, &size);
    printf("%d , %s\n", size, func(str, &size));
}
