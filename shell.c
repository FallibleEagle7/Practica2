#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

void readString(char *s)
{
    int i = 0;
    fgets(s,80,stdin);
    while(s[i] != '\n' && s[i] != '\r')
        i++;
    s[i] = '\0';
}
int main(int argc, char *argv[])
{
    char command[80];
    int exitProg = 0;
    int pidInit = atoi(argv[1]);
    while(!exitProg)
    {
        printf(">");
        readString(command);
        if(strcmp(command,"exit") == 0)
        {
            exitProg = 1;
            continue;
        }
        if(strcmp(command,"shutdown") == 0)
        {
            kill(pidInit,SIGUSR1);
            exit(0);
        }
        //No usar system, hay que usar exec, 
        //separar parámetros con los espacios
        //Si el comando que teclea el usuario termina con un &
        //La ejecución se hace en segundo plano
        //Cuando se hace la ejecución en segundo plano, el shell no espera
        //la terminación del programa
        system(command);
        
    }
}
