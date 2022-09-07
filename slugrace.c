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
    char number_buff[32];
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
            char* argument_list[2];
            sprintf(number_buff, "%d", i);
            argument_list[0] = number_buff;
            argument_list[1]=NULL;
            pids[i] = (int) getpid();
            printf("[Parent]: I forked off child %d \n", getpid());
            printf("\t [Child, PID: %d]: Executing './slug %d' command... \n", getpid(),i);
            execv(".",argument_list);
            exit(0);
        }
    }
    for(int i =0; i < 4; i++){
        int status;
        if(waitpid(-1,NULL,WNOHANG)){
            printf("Child finished \n");
        }else{
            usleep(20);
            printf("The race is ongoing. The following children are still racing: \n");
        }
    }
    return 0;
}

