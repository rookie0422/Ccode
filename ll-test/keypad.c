#include <stdio.h>
#include <string.h>

// �Ź����Ӧ����ĸ��
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

// �ݹ麯�������������

/// @brief
/// @param digits ����
/// @param index �ڼ�������
/// @param current ��ǰ���ַ������
/// @param length ���ֵĳ���
void generateCombinations(char *digits, int index, char *current, int length)
{
    // printf("��%d��ִ�У� digits = %s, current = %s, index = %d, length = %d, \n", count, digits, current, index, length);
    printf("��%d��ִ�У�  current = %s, index = %d \n", count, current, index);
    count++;
    if (index == length) {
        printf("%s\n", current); // ��ӡ��ǰ�������
        return;
    }

    char *letters = numToChars[digits[index] - '0']; // ��ȡ��ǰ���ֶ�Ӧ����ĸ
    for (int i = 0; i < strlen(letters); i++) {
        
        current[index] = letters[i];                              // ����ǰ��ĸ��������
        // printf("ѭ���� i = %d , index = %d\n", i, index);
        generateCombinations(digits, index + 1, current, length); // �ݹ鴦����һ������

    }
    count = 1;
}

// ������
int main()
{
    char digits[100];
    printf("���������֣�");
    scanf("%s", digits); // ���������ַ���

    int length = strlen(digits);
    if (length == 0) {
        return 0; // ����Ϊ��ʱֱ�ӷ���
    }

    char current[length + 1];
    current[length] = '\0'; // �����ַ���������

    generateCombinations(digits, 0, current, length); // �����������

    return 0;
}
