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
    int bufSize=32;
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error: could not open file %s", filename);
        return 1;
    }
    fscanf(fp, "%d", &number);
    fclose(fp);
    srand(number * getpid());
    char* directories[6] = {"/home", "/proc", "proc/sys", "/usr", "/boot", "/sbin"};
    char cwd[256];  
    
    

    printf("Random seed value (converted to integer): %d \n", number);
    printf("It's time to see the world/file system! \n");
    for(int i = 0; i < 5; i++)
    {
        int exploreNum = (rand() % 6);
        if(chdir(directories[exploreNum])!= 0){
            perror("chdir failed");
            continue;
        } 
        if (getcwd(cwd, sizeof(cwd)) == NULL) perror("getcwd() error");
            printf("Selection #%d: %s [SUCCESS]\n", i+1, cwd);
            printf("Current reported directory is: %s\n", getcwd(cwd,bufSize));
        if (fork() == 0)
        {
            printf("[Parent]: I am waiting for PID %d to finish \n", (int) getpid());
            printf("\t [Child, PID: %d]: Executing 'ls -tr' command... \n",(int) getpid());
            char* argument_list[] = {"ls", "-tr", NULL}; // NULL terminated array of char* strings
            execvp("ls", argument_list);
            exit(0);
        }
        else{
            wait(NULL);
        }
    }
    return 0;
}