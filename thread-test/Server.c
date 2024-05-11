#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <ctype.h>

#define BUFSZ 256

// 去除字符串中的空白字符
void trim(char *str)
{
    int len = strlen(str);
    while (len > 0 && isspace(str[len - 1]))
    {
        str[len - 1] = '\0';
        len--;
    }
}

typedef struct message_t {
    char msg_type[BUFSZ];
    char msg_text[BUFSZ];
}message_t;

int main()
{
    int qid;
    key_t key;
    message_t msg;

    if ((key = ftok(".", 'a')) == -1)
        perror("ftok");

    if ((qid = msgget(key, IPC_CREAT | 0666)) == -1)
        perror("msgget");

    while (1)
    {
        if (msgrcv(qid, &msg, sizeof(message_t), 0, 0) == -1)
            perror("msgrcv");
        
        printf("%s: %s", msg.msg_type, msg.msg_text);
        
        trim(msg.msg_text);

        if(!strcmp(msg.msg_text, "exit"))
            exit(0);
    }

    return 0;
}