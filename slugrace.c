#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char *argv[])
{
    
    srand(number * getpid());
    printf("Random seed value (converted to integer): %d \n", number);
    for (int i = 1; i <= 4; i++)
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
    for (int i = 0; i < 4; i++)
    {
        wait(NULL);
    }
    return 0;
}

