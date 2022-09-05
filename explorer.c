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
    int exploreNum = (rand() % 6);
    
    char cwd[256];  
    char* directories[6];
    directories[0]="/home";
    directories[1]="/proc";
    directories[2]="proc/sys";
    directories[3]="/usr";
    directories[4]="/boot";
    directories[5]="/sbin";


    char* argument_list[] = {"ls", "-l", NULL}; // NULL terminated array of char* strings
    printf("Random seed value (converted to integer): %d \n", number);
    printf("Random explorer number: %d \n", exploreNum);
    if (fork() == 0)
    {
        if(chdir(directories[exploreNum])!= 0) perror("chdir failed");
        if (getcwd(cwd, sizeof(cwd)) == NULL) 
            perror("getcwd() error");
        else
            printf("current working directory is: %s\n", cwd);
            execvp("ls", argument_list);
    }
    wait(NULL);
    return 0;
}