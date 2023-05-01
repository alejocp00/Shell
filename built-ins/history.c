#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../REPL/source.h"
#include "../REPL/shell.h"

/*Add to the history file the command*/
int add_to_history(char *command)
{
  FILE *file = fopen("history/history.txt", "a");

  if (!file)
    return 1;

  /*puts the cursor at the beginning of the file*/
  rewind(file);

  fputs(command, file);
  return 0;
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

  FILE *file = fopen("aux.txt", "r");

  if (!file)
    return 1;

  /*puts the cursor at the beginning of the file*/
  rewind(file);

  while (count < max_lines)
  {
    /*takes the corresponding line and stores it in the text_string variable*/
    fgets(text_string, 1030, file);

    printf("%d %s\n", count + 1, text_string);
    count++;
  }
  fclose(file);
  return 0;
}

/*Executes the command that occupies the number indicated in the history*/
int again(int argc, char **argv)
{
  /*store the number of the command selected*/
  char *s = argv[0];
  /*store the command selected*/
  char *command;

  /* if(!isdigit(s))
   {
     return 1;
   }*/

  int line_number = atoi(s);

  if (line_number <= 0)
    return 1;

  int count = 0;
  char text_string[1030];
  FILE *file = fopen("aux.txt", "a+");

  /*Verify if the file was opened*/
  if (!file)
    return 1;

  /*Puts the cursor at the beginning of the file*/
  rewind(file);

  while (count < line_number)
  {
    if ((fgets(text_string, 1030, file)) == NULL)
    {
      fclose(file);
      return 1;
    }
    else
      count++;
  }

  fclose(file);
  command = text_string;

  /*Initialize Source*/
  Source source;
  source.in_text = command;
  source.size = sizeof(command);
  source.position = INIT_SRC_POS;
  /*send parse and execute the command selected*/
  parse_and_execute(&source);

  return 0;
}
