#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <ctype.h>

#define BUFSZ           256
#define CLIENT_COUNT    3

typedef struct message_t {
    char msg_type[BUFSZ];
    char msg_text[BUFSZ];
}message_t;


void trim(char *str);

void *srv_task(void *arg)
{
    // 执行一些任务...
    int srv_qid, send_qid;
    key_t srv_key, send_key;
    message_t msg;

    if ((srv_key = ftok(".", 'c')) == -1)
        perror("ftok");

    if ((srv_qid = msgget(srv_key, IPC_CREAT | 0666)) == -1)
        perror("msgget");

    if ((send_key = ftok(".", 's')) == -1)
        perror("ftok");

    if ((send_qid = msgget(send_key, IPC_CREAT | 0666)) == -1)
        perror("msgget");

    while (1) {
        if (msgrcv(srv_qid, &msg, sizeof(message_t), 0, 0) == -1)
            perror("msgrcv");

        printf("%s: %s", msg.msg_type, msg.msg_text);

        for (int i = 0;i < CLIENT_COUNT;i++) {
            if (msgsnd(send_qid, &msg, sizeof(message_t), 0) == -1)
                perror("msgsnd");
        }


        trim(msg.msg_text);

        if (!strcmp(msg.msg_text, "exit"))
            exit(0);
    }

    printf("Thread 1 is exiting\n");
    pthread_exit(NULL);

}

// 去除字符串中的空白字符
void trim(char *str)
{
    int len = strlen(str);
    while (len > 0 && isspace(str[len - 1])) {
        str[len - 1] = '\0';
        len--;
    }
}

int main()
{
    pthread_t send_thread, srv_thread;
    int ret2;

    // 创建线程2
    ret2 = pthread_create(&srv_thread, NULL, srv_task, NULL);
    if (ret2) {
        fprintf(stderr, "Error - pthread_create() return code: %d\n", ret2);
        return 1;
    }

    // 等待线程2结束
    ret2 = pthread_join(srv_thread, NULL);
    if (ret2) {
        fprintf(stderr, "Error - pthread_join() return code: %d\n", ret2);
        return 1;
    }

    return 0;
}