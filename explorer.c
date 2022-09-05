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
    const char directories[6];
    directories[0]="/home"
    directories[1]="/proc"
    directories[2]="proc/sys"
    directories[3]="/usr"
    directories[4]="/boot"
    directories[5]="/sbin"
    printf("Random Number: %d \n",exploreNum);
    exit(0);
}
