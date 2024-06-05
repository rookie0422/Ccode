#include<stdio.h>
#include<unistd.h>
#include<time.h>
#include<string.h>

int main(int argc, const char *argv[])
{
    long int clock;
    struct tm *clocktim;
    int order = 1;
    char str[32] = { 0 };
    FILE *p = fopen("demo1.txt", "a+");
    if (p == NULL) {
        perror("fopen:");
        return -1;
    }

    while (fgets(str, 32, p)) {
        if (str[strlen(str) - 1] == '\n') {
            order++;
        }
    }
    while (1) {
        clock = time(NULL);
        clocktim = localtime(&clock);

        printf("%04d-%02d-%02d %02d:%02d:%02d\n", clocktim->tm_year + 1900, clocktim->tm_mon + 1, clocktim->tm_mday,
            clocktim->tm_hour, clocktim->tm_min, clocktim->tm_sec);

        fprintf(p, "%d.\t%04d-%02d-%02d %02d:%02d:%02d\n", order, clocktim->tm_year + 1900, clocktim->tm_mon + 1,
            clocktim->tm_mday, clocktim->tm_hour, clocktim->tm_min, clocktim->tm_sec);

        fflush(p);

        order++;

        sleep(1);
    }

    fclose(p);

    return 0;
}
