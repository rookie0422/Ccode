#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// 线程函数1
void *thread_function1(void *arg)
{
    printf("Thread 1 is start\n");
    // 执行一些任务...
    while (1) {
        printf("Thread 1 is running\n");
        sleep(1);
    }

    printf("Thread 1 is exiting\n");
    pthread_exit(NULL);
}

// 线程函数2
void *thread_function2(void *arg)
{
    printf("Thread 2 is start\n");
    // 执行一些任务...
    while (1) {
        printf("Thread 2 is running\n");
        sleep(5);
    }

    printf("Thread 2 is exiting\n");
    pthread_exit(NULL);
}

int main()
{
    pthread_t thread1, thread2;
    int ret1, ret2;

    // 创建线程1
    ret1 = pthread_create(&thread1, NULL, thread_function1, NULL);
    if (ret1) {
        fprintf(stderr, "Error - pthread_create() return code: %d\n", ret1);
        return 1;
    }

    // 创建线程2
    ret2 = pthread_create(&thread2, NULL, thread_function2, NULL);
    if (ret2) {
        fprintf(stderr, "Error - pthread_create() return code: %d\n", ret2);
        return 1;
    }

    // 等待线程1结束
    ret1 = pthread_join(thread1, NULL);
    if (ret1) {
        fprintf(stderr, "Error - pthread_join() return code: %d\n", ret1);
        return 1;
    }

    // 等待线程2结束
    ret2 = pthread_join(thread2, NULL);
    if (ret2) {
        fprintf(stderr, "Error - pthread_join() return code: %d\n", ret2);
        return 1;
    }

    printf("Both threads have finished execution\n");
    return 0;
}
