#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../Header/Lire_commande.h"
#define CHAR_MAX 100
#define COM_MAX 100


void Lire_commande(char *cmd, char**com){
    int deb=0;
    int fin=0;
    int comptcom=0;
    int i=0;
    int k;
    for(int l=0; l<COM_MAX+2; l++) com[l]=NULL;
    while(cmd[i] != '\0' && cmd[i] != '\n'){
        if (cmd[i] == ' ' || cmd[i+1]=='\0' || cmd[i+1]=='\n'){
            fin=(cmd[i]==' ') ? i : i+1;
            com[comptcom] = malloc(sizeof(char) * (fin-deb));
            k=0;
            for (int j=deb; j < fin; j++){    //for de deb a fin - 1
                com[comptcom][k] = cmd[j];
                k++;
            }
            deb = i+1;
            comptcom++;
        }
        i++;
    }
}
