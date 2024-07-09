/*
 *  mysystem.c : system 関数のクローン
 */

#include <stdio.h>
#include <stdlib.h>    // exit, system のため
#include <unistd.h>    // fork, execXX のため
#include <sys/wait.h>  // wait のため
#include "mysystem.h"  // インタフェース

char *execpath = "/bin/sh";

// system関数のクローン
int mysystem(char *command) {
  int status = 0;
  int pid;

  pid= fork();
  if(pid<0){
    return -1;
  }
  if (command==NULL) {
    return 1;
  }
  if(pid!=0){
    while(wait(&status)!=pid);
  }
  else{
    execl(execpath,"sh","-c",command,NULL); 
    exit(127);
  }
  return status;
}

/* 実行例
% make
cc -Wall -std=c99 -o mysysmain mysysmain.c  mysystem.c

ここに実行例を書く

 % ./mysysmain "ls -l"
mysystem:
total 616
-rw-r--r--  1 kanzakikazuma  staff     143  7  4 09:45 Makefile
-rw-r--r--  1 kanzakikazuma  staff    2795  7  4 09:45 README.md
-rw-r--r--@ 1 kanzakikazuma  staff  238232  7  4 09:45 README.pdf
-rwxr-xr-x  1 kanzakikazuma  staff   50392  7  9 10:07 mysysmain
-rw-r--r--  1 kanzakikazuma  staff     925  7  4 09:45 mysysmain.c
-rw-r--r--@ 1 kanzakikazuma  staff     720  7  9 10:07 mysystem.c
-rw-r--r--  1 kanzakikazuma  staff      90  7  4 09:45 mysystem.h
retval = 00000000
system:
total 616
-rw-r--r--  1 kanzakikazuma  staff     143  7  4 09:45 Makefile
-rw-r--r--  1 kanzakikazuma  staff    2795  7  4 09:45 README.md
-rw-r--r--@ 1 kanzakikazuma  staff  238232  7  4 09:45 README.pdf
-rwxr-xr-x  1 kanzakikazuma  staff   50392  7  9 10:07 mysysmain
-rw-r--r--  1 kanzakikazuma  staff     925  7  4 09:45 mysysmain.c
-rw-r--r--@ 1 kanzakikazuma  staff     720  7  9 10:07 mysystem.c
-rw-r--r--  1 kanzakikazuma  staff      90  7  4 09:45 mysystem.h
retval = 00000000

% ./mysysmain
使い方 : ./mysysmain コマンド文字列




*/
