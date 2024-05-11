#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "student.h"

// 回调函数应接受 student_t 指针
void student_show_callback(void *data)
{
    student_t *stu = (student_t *)data; // 类型转换为 student_t 指针
    printf("This student's number is %d\n", stu->number);
    printf("This student's name is %s\n", stu->name);
    printf("This student's phone number is %d\n", stu->phone);
}

// 传递指针，并确保内存管理正确
int student_init(student_t *stu, const char *name, int number, int phone, student_show_callback_t show)
{
    if (stu == NULL || name == NULL)
        return -1;

    stu->name = strdup(name); // 复制字符串
    if (stu->name == NULL)
        return -1; // 字符串复制失败

    stu->number = number;
    stu->phone = phone;
    stu->show = show;
    return 0;
}

int main()
{
    student_t stu;

    // 初始化 student_t 结构体
    if (student_init(&stu, "rookie", 321, 11, student_show_callback) == 0) // 初始化并检查成功
    {
        stu.show(&stu); // 传递 student_t 指针
        free(stu.name); // 释放分配的内存
    }
    return 0;
}
