#include <stdio.h>
#include <string.h>

// 九宫格对应的字母表
char *numToChars[] = {
    "",     // 0
    "",     // 1
    "abc",  // 2
    "def",  // 3
    "ghi",  // 4
    "jkl",  // 5
    "mno",  // 6
    "pqrs", // 7
    "tuv",  // 8
    "wxyz"  // 9
};

int count = 1;

// 递归函数生成排列组合

/// @brief
/// @param digits 数字
/// @param index 第几个数字
/// @param current 当前的字符串组合
/// @param length 数字的长度
void generateCombinations(char *digits, int index, char *current, int length)
{
    // printf("第%d次执行： digits = %s, current = %s, index = %d, length = %d, \n", count, digits, current, index, length);
    printf("第%d次执行：  current = %s, index = %d \n", count, current, index);
    count++;
    if (index == length) {
        printf("%s\n", current); // 打印当前排列组合
        return;
    }

    char *letters = numToChars[digits[index] - '0']; // 获取当前数字对应的字母
    for (int i = 0; i < strlen(letters); i++) {
        
        current[index] = letters[i];                              // 将当前字母放入结果中
        // printf("循环： i = %d , index = %d\n", i, index);
        generateCombinations(digits, index + 1, current, length); // 递归处理下一个数字

    }
    count = 1;
}

// 主函数
int main()
{
    char digits[100];
    printf("请输入数字：");
    scanf("%s", digits); // 输入数字字符串

    int length = strlen(digits);
    if (length == 0) {
        return 0; // 输入为空时直接返回
    }

    char current[length + 1];
    current[length] = '\0'; // 设置字符串结束符

    generateCombinations(digits, 0, current, length); // 生成排列组合

    return 0;
}
