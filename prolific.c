#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char *argv[])
{
    printf("hello world (pid:%d) \n", (int)getpid());
    char *filename = "seed.txt";
    int number;
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error: could not open file %s", filename);
        return 1;
    }

    fscanf(fp, "%d", &number);
    fclose(fp);
    srand(number * getpid());
    int children = (rand() % (11 - 5 + 1)) + 5;
    printf("%d \n", children);
    for (int i = 0; i < children; i++)
    {
        if (fork() == 0)
        {
            printf("hello, I am child (pid:%d)\n", (int)getpid());
            exit(1);
        }
    }
    for (int i = 0; i < children; i++)
    {
        wait(NULL);
    }
    return 0;
}