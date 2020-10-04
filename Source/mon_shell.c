#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../Header/exec_command_rec.h"
#include "../Header/Lire_commande.h"
#include "../Header/mon_shell.h"
#define CHAR_MAX 100
#define COM_MAX 100



void mon_shell(){

    int f[2];
    pipe(f);
    int no, status, i;
    char cmd[CHAR_MAX+1];
    char *com[COM_MAX+2];
    char Pwd[100];

    signal(SIGINT,SIG_IGN);
    signal(SIGQUIT,SIG_IGN);
    printf("Voici mon shell, taper Q pour sortir\n");
    do{
        getcwd(Pwd, 100);
        printf("\033[0;34m");
        printf("%s\n",Pwd);
        printf("\033[0m");
        printf("\033[0;32m");
        printf("%s>>", getenv("USER"));
        printf("\033[0m");
        fgets(cmd,CHAR_MAX, stdin);
        if(cmd[0]=='\n') {
          cmd[0]=' ';
        }
        else{
            Lire_commande(cmd, com);
            /* Pourles commandes internes: */

            com[0]=(strcmp(com[0],"exit")==0)?"Q":com[0];  //commande EXIT
            if(strcmp(com[0],"Q")!=0) exec_command_rec(com,0,0,f);
          }

    }while(strcmp(com[0],"Q")!=0);
}
