#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../Header/commande_externe.h"
#define CHAR_MAX 100
#define COM_MAX 100

int commande_externe(char*com[], int *f, int pipe_entree, int pipe_sortie){
      int i=0,bool_et=0;
      while(com[i]!=NULL)i++;
      if(strcmp(com[i-1],"&") == 0){
         bool_et=1;
         com[i-1]=NULL;
      }
      int f2[2];
      pipe(f2);
      int no, n1, status=0;
      /* Pour les autres: */
      switch (n1=fork()){
        case -1:
        perror("fork");
        exit(-1);
        case 0:
        if(pipe_entree){
          close(0);       // pipe entree
          dup(f[0]);     // *
          close(f[1]);   // *
          close(f[0]);   // pipe entree
        }
        if(pipe_sortie){
          close(1);       // pipe sortie
          dup(f2[1]);     // *
          close(f2[1]);   // *
          close(f2[0]);   // pipe sortie
        }
        signal(SIGINT,SIG_DFL);
        signal(SIGQUIT,SIG_DFL);
        execvp(com[0], com);
        exit(-1);
        default:

          if(pipe_entree){
            close(f[0]);
            close(f[1]);   // pipe entree
          }

        do{
            if(!bool_et)no = wait(&status);
        }while(no!=n1&&!bool_et);
        if(status&&status!=2&&status!=131) fprintf(stderr, "%s n'est pas une commande valide\n", com[0]);
        //traite_status(no,status);
      }
      //printf("f:%d\n", &f);
      //printf("f2:%d\n", &f2);
      //if(pipe_sortie)f=(int *)&f2;
      //printf("f après modif:%d\n", &f);
      return status;
    }
