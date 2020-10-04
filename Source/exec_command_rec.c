#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../Header/commande_externe.h"
#include "../Header/commande_interne.h"
#include "../Header/exec_command_rec.h"
#define CHAR_MAX 100
#define COM_MAX 100

void exec_command_rec(char*tab[],int i, int pipe_entree, int *f){
  int pipe_sortie=0;
  int status = 0;
  int j=i;
  int k=0;
  char* com[COM_MAX];
  for(int l=0; l<COM_MAX; l++) com[l]=NULL;
  while (tab[j]!=NULL && strcmp(tab[j],";") != 0
    && strcmp(tab[j],"|") != 0
    && strcmp(tab[j],"||") != 0
    && strcmp(tab[j],"&&") != 0)
{
    com[k]=tab[j];
    k++;
    j++;
  }
  if(tab[j]!=NULL&&strcmp(tab[j],"|") == 0) pipe_sortie=1;
  if(com[0]!=NULL){
    if(!commande_interne(com,f))status=commande_externe(com,f,pipe_entree,pipe_sortie);
    if(tab[j]!=NULL
      &&(strcmp(tab[j],";") == 0
        || strcmp(tab[j],"|") == 0
        || (strcmp(tab[j],"||") == 0 && status)
        || (strcmp(tab[j],"&&") == 0 && !status)))
      exec_command_rec(tab,j+1,pipe_sortie,f);
  }
}
