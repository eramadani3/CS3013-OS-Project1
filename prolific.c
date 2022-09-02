#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

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
    int children = (rand() % (11 - 5 + 1)) + 5;
    int* pids = (int*) malloc(children * sizeof(int));
    printf("Random seed value (converted to integer): %d \n", number);
    printf("Random child count: %d \n", children);
    printf("Im feeling prolific! \n");
    for (int i =0; i < children; i++){
        pids[i] = rand();
    }
    for (int i = 0; i < children; i++)
    {
        if (fork() == 0)
        {
            int exitNum = ((pids[i] % 50) + 1);
            int exitTime = ((pids[i] % 3) + 1);
            printf("[Parent]: I am waiting for PID %d to finish \n", getpid());
            printf("\t [Child, PID: %d]: I am the child and I will wait %d seconds and exit with code %d\n", getpid(), exitTime, exitNum);
            printf("\t [Child, PID: %d]: Now exiting... \n", getpid());
            printf("[Parent]: Child %d finished with status code %d. Onward! \n", getpid(), exitNum);
            exit(0);
        }
    }
    for (int i = 0; i < children; i++)
    {
        wait(NULL);
    }
    return 0;
}