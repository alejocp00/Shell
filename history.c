#include<stdio.h>
#include<stdlib.h>

//(sin terminar)

/*Add to the history file the command*/
int add_to_history(char *command)
{
  FILE *file = fopen("history/history.txt", "a");
  rewind(file);
  fputs(command, file);
}

/*prints 10 last commands*/
int history(int argc, char **argv)
{
  /*count of the lines*/
  int count = 0;

  /*max lines of history that it will showed*/
  int max_lines = 10;

  /*stores the string of each line to read*/
  char text_string[1030];

  FILE *file = fopen("aux.txt", "a+");

  if(!file) return 1;

  /*puts the cursor at the beginning of the file*/
  rewind(file);

  while(count < max_lines)
  {
    /*takes the corresponding line and stores it in the text_string variable*/
    fgets(text_string,1030,file);
    
    printf("%d %s\n", count+1, text_string);
    count++;
  }
  fclose(file);
  return 0;
}