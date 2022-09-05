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
    for(int i = 1; i < 6; i++)
    {
        char* argument_list[] = {"ls", "-tr", NULL}; // NULL terminated array of char* strings
        int exploreNum = (rand() % 6);
        if (fork() == 0)
        {
           
            printf("Selection: %d \n", i);
            if(chdir(directories[exploreNum])!= 0) perror("chdir failed");
            if (getcwd(cwd, sizeof(cwd)) == NULL) 
                perror("getcwd() error");
            else
                printf("current working directory is: %s\n", cwd);
                execvp("ls", argument_list);
        }
        exit(0);
    }
    for (int i = 0; i < 6; i++)
    {
        wait(NULL);
    }
    return 0;
}