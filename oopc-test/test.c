#include <stdio.h>
#include <string.h>
#include <ctype.h>

// 函数声明
int check_password_strength(char *username, char *password);

char * strrev(char* str) {
    int length = strlen(str);
    int i, j;
    char temp;

    for (i = 0, j = length - 1; i < j; ++i, --j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
    return str;
}

int main() {
    char username[50];
    char password[50];
    
    // 输入用户名和密码
    printf("请输入用户名：");
    scanf("%s", username);
    printf("请输入密码：");
    scanf("%s", password);
    
    // 检查密码强度并输出结果
    int strength = check_password_strength(username, password);
    switch(strength) {
        case 0:
            printf("密码强度为：0，密码不符合规定\n");
            break;
        case 1:
            printf("密码强度为：1，密码强度较低\n");
            break;
        case 2:
            printf("密码强度为：2，密码强度中等\n");
            break;
        case 3:
            printf("密码强度为：3，密码强度较高\n");
            break;
        default:
            printf("密码不符合要求\n");
    }
    
    return 0;
}

// 检查密码强度的函数
int check_password_strength(char *username, char *password) {
    // 强度0：密码长度小于8|用户名与密码相同|用户名与密码相反
    if (strlen(password) < 8 || strcmp(password, username) == 0 || strcmp(password, strrev(username)) == 0) {
        return 0;
    }
    
    // 强度1：密码长度大于8&密码只包含数字与小写字母组合或数字与大写字母组合
    int digit = 0, lowercase = 0, uppercase = 0, special = 0;
    for (int i = 0; password[i] != '\0'; i++) {
        if (isdigit(password[i])) {
            digit = 1;
        } else if (islower(password[i])) {
            lowercase = 1;
        } else if (isupper(password[i])) {
            uppercase = 1;
        } else {
            special = 1;
        }
        
    }
    
    if (strlen(password) > 8) {
        if (((digit + lowercase==2) && uppercase == 0) || ((digit + uppercase==2) && lowercase == 0)){
            return 1;
        } else if (digit + lowercase + uppercase + special > 3) {
            return 3;
        } else {
            return 2;
        }
    }
    // 默认情况
    return -1;
}
