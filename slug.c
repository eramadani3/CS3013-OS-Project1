#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char *argv[])
{
    char *filename = "seed.txt";
    char *a = argv[1];
    int filenumber = atoi(a);
    switch(filenumber){
        case 1:
            filename = "seed_slug_1.txt";
            break;
        case 2:
            filename = "seed_slug_2.txt";
            break;
        case 3:
            filename = "seed_slug_3.txt";
            break;
        case 4:
            filename = "seed_slug_4.txt";
            break;
        default:
            printf("Enter a number 1-4 \n");
    }
    printf("file name: %s, file number: %d \n", filename, filenumber);

    int number;
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error: could not open file %s \n", filename);
        return 1;
    }
    fscanf(fp, "%d", &number);
    fclose(fp);

    char* flipOptions[2] = {"last -i -x", "id --group"};
    srand(number * getpid());
    int slugTime = (rand() % (9 - 4 + 1)) + 4;
    int coinFlip = rand();
    sleep(slugTime);
    
   
    return 0;
}