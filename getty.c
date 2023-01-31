#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

#define LONGITUD 30

int main(int argc, char *argv[])
{
    //Variables login
    char user[LONGITUD];
    char password[LONGITUD];
    char login[2*LONGITUD];
    int log_flag = 0;
    int j = 0;
    
    //Variables lectura de archivo
    char caracter;
    int u = 0;
    int i = 0;
    char contenido[LONGITUD][LONGITUD];
    FILE *archivo;
    
    //Variable fork
    int p;
    
    //Lectura de archivo
    archivo = fopen("passwd","r");
    while((caracter = fgetc(archivo)) != EOF)
    {
        if(caracter != '\n')
        {
            contenido[u][i] = caracter;
            i++;
        }
        else
        {
            contenido[u][i] = '\0';
            i = 0;
            u++;
        }
    }
    
    
    while(1)
    {
        log_flag = 0;
        j = 0;
    	printf("Login as: ");
        scanf("%s",user);
        printf("Password: ");
        scanf("%s",password);
        strcpy(login,user);
    	strcat(login,":");
    	strcat(login,password);
    	while(j < u && !log_flag)
    	{
            if(!(strcmp(login,contenido[j])))
            {
                log_flag = 1;
                continue;
            }
            j+=1;
    	}
    	if(log_flag == 1)
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
