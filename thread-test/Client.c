#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <ctype.h>

#define BUFSZ 256

void trim(char *str);

typedef struct message_t {
    char msg_type[BUFSZ];
    char msg_text[BUFSZ];
}message_t;

void *send_task(void *arg)
{
    int qid;
    key_t key;
    message_t *msg = (message_t *)arg;

    if ((key = ftok(".", 'c')) == -1)
        perror("ftok");

    if ((qid = msgget(key, IPC_CREAT | 0666)) == -1)
        perror("msgget");

    printf("Enter your client type: ");
    fgets(msg->msg_type, BUFSZ, stdin);
    trim(msg->msg_type);

    while (1) {
        // printf("\nEnter message: ");
        fgets(msg->msg_text, BUFSZ, stdin);

        if (msgsnd(qid, msg, sizeof(message_t), 0) == -1)
            perror("msgsnd");

        trim(msg->msg_text);

        if (!strcmp(msg->msg_text, "exit"))
            exit(0);
    }

    printf("Thread 1 is exiting\n");
    pthread_exit(NULL);
}

void *srv_task(void *arg)
{
    int qid;
    key_t key;
    message_t rsv_msg;
    message_t *msg = (message_t *)arg;

    if ((key = ftok(".", 's')) == -1)
        perror("ftok");

    if ((qid = msgget(key, IPC_CREAT | 0666)) == -1)
        perror("msgget");

    while (1) {
        if (msgrcv(qid, &rsv_msg, sizeof(message_t), 0, 0) == -1)
            perror("msgrcv");

        trim(msg->msg_type);
        trim(rsv_msg.msg_type);
        if (strcmp(msg->msg_type, rsv_msg.msg_type))
            printf("\r\n%s: %s", rsv_msg.msg_type, rsv_msg.msg_text);


        trim(rsv_msg.msg_text);
        if (!strcmp(rsv_msg.msg_text, "exit"))
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
    int ret1, ret2;
    message_t msg;
    // 创建线程1
    ret1 = pthread_create(&send_thread, NULL, send_task, &msg);
    if (ret1) {
        fprintf(stderr, "Error - pthread_create() return code: %d\n", ret1);
        return 1;
    }

    // 创建线程2
    ret2 = pthread_create(&srv_thread, NULL, srv_task, &msg);
    if (ret2) {
        fprintf(stderr, "Error - pthread_create() return code: %d\n", ret2);
        return 1;
    }

    // 等待线程1结束
    ret1 = pthread_join(send_thread, NULL);
    if (ret1) {
        fprintf(stderr, "Error - pthread_join() return code: %d\n", ret1);
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