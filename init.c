#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define NPROCS 6
int pID[NPROCS];
void signalHandler(int signal)
{
    printf("KILL PROCESS\n");
    for(int i = 0; i < NPROCS; i++)
    {
    	kill(pID[i],SIGKILL);
    }
}
int main()
{
    
    int newP;
    char pid[6];
    

    signal(SIGUSR1,signalHandler);
    
    sprintf(pid,"%d",getpid());

    for(int i = 0; i < NPROCS; i++)
    {
    	newP = fork();
        if(newP == 0)
        {
            execlp("xterm","xterm","-e","./getty",pid,NULL);
        }
        pID[i] = newP;
    }

    for(int i = 0; i < NPROCS; i++)
    {
        wait(NULL);
        //si un proceso xterm termina, hay que lanzar otro
    }
}
