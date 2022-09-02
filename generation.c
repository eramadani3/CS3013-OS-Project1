#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

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
    int pids[11];
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error: could not open file %s", filename);
        return 1;
    }

    fscanf(fp, "%d", &number);
    fclose(fp);
    srand(number * getpid());
    int lifespan = (rand() % (14 - 8 + 1)) + 8;
    int children = (rand() % (11 - 5 + 1)) + 5;
    printf("Random seed value (converted to integer): %d \n", number);
    printf("Random child count: %d \n", children);

    return helper(lifespan, children);
}

int helper(int lifespan, int children){
    if(lifespan <= 0){
        exit(0);
    }else{
        if (fork() == 0)
        {
            lifespan--;
            pids[i] = (int)getpid();
            printf("pids of i : %d", pids[i]);
            printf("[Parent]: I am waiting for PID %d to finish \n", (int)getpid());
            printf("\t [Child, PID: %d]: I am the child\n", (int)getpid());
            printf("\t [Child, PID: %d]: Now exiting... \n", (int)getpid());
            printf("[Parent]: Child %d finished, onwards! \n", (int)getpid());
            helper(lifespan, children);
        }

        for (int i = 0; i < children; i++){
        wait(NULL);
    }
    return 0;
    }

}

// int main(int argc, char *argv[])
// {
//     char *filename = "seed.txt";
//     int number;
//     FILE *fp = fopen(filename, "r");
//     if (fp == NULL)
//     {
//         printf("Error: could not open file %s", filename);
//         return 1;
//     }

//     fscanf(fp, "%d", &number);
//     fclose(fp);
//     srand(number * getpid());
//     int lifespan = (rand() % (14 - 8 + 1)) + 8;
//     int children = (rand() % (11 - 5 + 1)) + 5;
//     printf("Random seed value (converted to integer): %d \n", number);
//     printf("Random child count: %d \n", children);
//     printf("Im feeling prolific! \n");
//     for (int i = 0; i < children; i++)
//     {
//         if (fork() == 0)
//         {
//             lifespan--;
//             for(int i = 0; i < lifespan; i++){
//                 lifespan--;
//                 if(fork() == 0) {
//                 printf("[Parent]: I am waiting for PID %d to finish \n", (int)getpid());
//                 printf("\t [Child, PID: %d]: I am the child\n", (int)getpid());
//                 printf("\t [Child, PID: %d]: Now exiting... \n", (int)getpid());
//                 printf("[Parent]: Child %d finished, onwards! \n", (int)getpid());
//                 exit(0);
//             };
//             };
            

//             printf("[Parent]: I am waiting for PID %d to finish \n", (int)getpid());
//             printf("\t [Child, PID: %d]: I am the child\n", (int)getpid());
//             printf("\t [Child, PID: %d]: Now exiting... \n", (int)getpid());
//             printf("[Parent]: Child %d finished, onwards! \n", (int)getpid());
//             exit(0);
//         }
//     }
//     for (int i = 0; i < children; i++)
//     {
//         wait(NULL);
//     }
//     return 0;
// }