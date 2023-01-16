#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int autentication = 0;
    //Variables login
    char login[30];
    char password[30];
    
    int p;
    
    while(1)
    {
    	printf("Login as: ");
        scanf("%s",login);
        printf("Password: ");
        scanf("%s",password);
        if(!(strcmp(login,"Pepito")) && !(strcmp(password,"12345")))
        {
            p = fork();
            if(p == 0)
            {
                execlp("./shell","./shell",argv[1],NULL);
            }
            wait(NULL); 
            
        }
        else
        {
            printf("Usuario o contraseña no válidos\n");
            continue;
        }
        
    }
}
