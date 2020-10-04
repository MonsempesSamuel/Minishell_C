#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../Header/commande_interne.h"
#define CHAR_MAX 100
#define COM_MAX 100

int commande_interne(char*com[], int *f){
  int ret = 1;
  int i=1;
  if(com[0]!=NULL){
    if (strcmp(com[0],"cd")==0) {
      if (com[1]==NULL || strcmp(com[1], "~") == 0) {
        chdir(getenv("HOME"));
      }else {
        if (chdir(com[1])==-1) {
          perror(com[1]);
        }
      }

    }else if(strcmp(com[0],"echo")==0){
      while(com[i]!=NULL){
        printf("%s ", com[i]);
        i++;
      }
      printf("\n");
    }else if (strcmp(com[0],"setenv")==0){
      if (com[1] != NULL && com[2] != NULL){
        setenv(com[1], com[2], 1);
      }
    }else if (strcmp(com[0],"getenv")==0) {
      if (com[1] != NULL){
        printf("%s=%s\n", com[1], getenv(com[1]));
      }
    }else{
      ret=0;
    }
    return ret;
  }
}
