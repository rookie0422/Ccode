#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char *del_string(char *str)
{
    int length     = strlen(str);
    
    char *curr_str = (char *)malloc((length + 1) * sizeof(char));
    int index      = 0;

    for (int i = 0; i < length; i++) {
        if (str[i] != str[i + 1]) {
            curr_str[index] = str[i];
            index++;
        }else {
            i++;
        }
    }
    curr_str[index] = '\0';

    // 检查生成的新字符串中是否还有连续重复的字符
    for (int i = 0; i < strlen(curr_str) - 1; i++) {
        if (curr_str[i] == curr_str[i + 1]) {
            char *new_str = del_string(curr_str);
            free(curr_str); // 释放之前分配的内存
            return new_str;
        }
    }

    return curr_str;
}

int main()
{
    char str[100];
    scanf("%s", str);
    int length = strlen(str);
    if (length <=1 || length >=20000) {
        return -1;
    }
    for (int i = 0;i<length;i++) {
        if(isupper(str[i])) {
            return -1;
        }
    }
    char *curr_str = del_string(str);
    printf("%s\n", curr_str);
    free(curr_str); // 释放分配的内存
    return 0;
}
