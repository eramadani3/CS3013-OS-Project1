#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char *argv[])
{
    char number_buff[32];
    int* pids[4];
    for (int i = 0; i < 4; i++)
    {
        int cpid = fork();
        if (cpid == 0)
        {
            char* argument_list[3];
            sprintf(number_buff, "%d", i+1);
            argument_list[0] = "./slug";
            argument_list[1]=number_buff;
            argument_list[2]=NULL;
            printf("\t [Child, PID: %d]: Executing './slug %d' command... \n", getpid(),i+1);
            execvp("./slug",argument_list);
        }else{
            pids[i] = cpid;
            printf("[Parent]: I forked off child %d \n", getpid());
        }
    }

    int unfinished =4;
    while(unfinished > 0)
    {
        int status;
        int finishedID=waitpid(-1,&status,WNOHANG);
        if(finishedID==0){
            usleep(200000);
            printf("The race is ongoing. The following children are still racing: ");
            for(int j =0; j < 4; j++){
                if(pids[j] !=-1){
                    printf("%d ", pids[j]);
                }
            }
            printf("\n");
        }else{
            --unfinished;
            for(int i =0; i < 4; i ++){
                if(pids[i] == finishedID){
                    pids[i] = -1;
                }
            }
            printf("Child %d has crossed the finish line! \n", finishedID);
        }
    }
    return 0;
}

