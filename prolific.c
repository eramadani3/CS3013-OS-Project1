#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char *argv[])
{
    printf("hello world (pid:%d) \n", (int)getpid());
    int range = 11 + 1 - 5;
    int children = 5 + (rand() % range);
    printf("%d \n", children);
    for (int i = 0; i < children; i++)
    {
        if (fork() == 0)
        {
            printf("hello, I am child (pid:%d)\n", (int)getpid());
            exit(0);
        }
    }
    for (int i = 0; i < children; i++)
    {
        wait(NULL);
    }
    return 0;
}