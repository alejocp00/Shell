#include<stdio.h>
#include<stdlib.h>

//(sin terminar)

int add_to_history(char *command)
{
  FILE *file = fopen("history/history.txt", "a");
  fputs(command, file);
}