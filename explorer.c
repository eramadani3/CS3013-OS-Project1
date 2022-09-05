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

    char cwd[256];  
    char* directories[6];
    directories[0]="/home";
    directories[1]="/proc";
    directories[2]="proc/sys";
    directories[3]="/usr";
    directories[4]="/boot";
    directories[5]="/sbin";
    

    printf("Random seed value (converted to integer): %d \n", number);
    printf("It's time to see the world/file system! \n");
    for(int i = 1; i < 3; i++)
    {
        int exploreNum = (rand() % 6);
        if(chdir(directories[exploreNum])!= 0) perror("chdir failed");
        if (fork() == 0)
        {
            if (getcwd(cwd, sizeof(cwd)) == NULL) {
                perror("getcwd() error");
            }
            else{
                printf("Selection: %d \n", i);
                printf("Current working directory is: %s\n", cwd);
                printf("[Parent]: I am waiting for PID %d to finish \n", (int) getpid());
                printf("\t [Child, PID: %d]: Executing 'ls -tr' command... \n",(int) getpid());
                char* argument_list[] = {"ls", "-tr", NULL}; // NULL terminated array of char* strings
                execvp("ls", argument_list);
                
            }   
        }
    }
    for (int i = 1; i < 3; i++)
    {
        
        wait(NULL);
       
    }
    return 0;
}