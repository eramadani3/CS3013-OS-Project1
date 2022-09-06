#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char *argv[])
{
    char* filenames[4] = {"seed_slug_1.txt", "seed_slug_2.txt", "seed_slug_3.txt", "seed_slug_4.txt"};
    int* pids = (int*) malloc(4 * sizeof(int));
    for (int i = 1; i <= 4; i++)
    {
        char *filename = filenames[i-1];
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
        printf("Random seed value (converted to integer): %d \n", number);
        if (fork() == 0)
        {
            pids[i] = (int) getpid();
            printf("[Parent]: I am waiting for PID %d to finish \n", getpid());
            printf("\t [Child, PID: %d]: Now exiting... \n", getpid());
            exit(0);
        }else{
            
        }
    }
    for (int i = 0; i < 4; i++)
    {
        if(wait(NULL)){
            printf("Child finished \n");
        }else{
            usleep(20);
        }
    }
    return 0;
}

