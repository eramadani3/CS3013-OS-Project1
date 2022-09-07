#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include "generation.h"

int main(int argc, char *argv[])
{
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
    int lifespan = (rand() % (14 - 8 + 1)) + 8;
    printf("Random seed value (converted to integer): %d \n", number);
    printf("Random Descendant count: %d \n", lifespan);
    printf("Time to meet the kids/grandkids/great grand kids/... \n");

    helper(lifespan);
    exit(0);
}

int helper(int lifespan)
{
    if (lifespan <= 0)
    {
        exit(0);
    }
    else
    {
        if (fork() == 0)
        {
            printf("[Parent: %d]: I am waiting for PID %d to finish \n", (int)getppid(), (int)getpid());
            printf("\t [Child, PID: %d]: I was called with the descendant count=%d. I'll have %d descendants(s)\n", (int)getpid(), lifespan, (lifespan - 1));
            lifespan--;
            helper(lifespan);
            exit(lifespan);
        }

        for (int i = 0; i < lifespan; i++)
        {
            wait(NULL);
            printf("[Parent, PID: %d]: Child %d finished with status code %d It's now my turn to exit. \n", (int)getppid(), (int)getpid(), lifespan-1);
            exit(lifespan);
        }
        return 0;
    }
}