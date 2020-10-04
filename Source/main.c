#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../Header/mon_shell.h"
#define CHAR_MAX 100
#define COM_MAX 100

int main(int argc,char *argv[],char *arge[]){
    mon_shell();
    return 0;
}
