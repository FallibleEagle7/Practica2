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
int splitString(char *s, char (*s2)[20])
{
    int i, j, ctr;
    j = 0;
    ctr = 0;
    for(i = 0; i <= (strlen(s)); i++)
    {
        if(s[i] == ' ' || s[i] == '\0')
        {
            s2[ctr][j] = '\0';
            ctr++;
            j = 0;
        }
        else
        {
            s2[ctr][j] = s[i];
            j++;
        }
    }
    return ctr;
}

int main(int argc, char *argv[])
{
    char command[80];
    char commands[5][20];
    int p;
    int exitProg = 0;
    int pidInit = atoi(argv[1]);
    int count;
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
        count = splitString(command,commands);
        printf("%d\n",count);
        char *args[count + 1];
        for(int i = 0; i < count; i++)
        {
            args[i] = commands[i];
        }
        args[count] = NULL;
        p = fork();
        if(p == 0)
        {
            execvp(commands[0],args);
            exit(0);
        }
        wait(NULL);
        //No usar system, hay que usar exec, 
        //separar parámetros con los espacios
        //Si el comando que teclea el usuario termina con un &
        //La ejecución se hace en segundo plano
        //Cuando se hace la ejecución en segundo plano, el shell no espera
        //la terminación del programa
        //system(command);
        
        
    }
}
