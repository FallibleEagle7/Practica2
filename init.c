#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define NPROCS 6
void signalHandler(int signal)
{
    printf("Matar a los procesos creados");
}
int main()
{
    char pid[7];

    signal(SIGUSR1,signalHandler);

    sprintf(pid,"%d",getpid());

    for(int i = 0; i < NPROCS; i++)
    {
        if(fork() == 0)
        {
            execlp("xterm","xterm","-e","./getty",pid,NULL);
        }
    }

    for(int i = 0; i < NPROCS; i++)
    {
        wait(NULL);
        //si un proceso xterm termina, hay que lanzar otro
    }
}
