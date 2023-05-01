#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../REPL/source.h"
#include "../REPL/shell.h"

int add_to_history(char *command)
{
  FILE *file = fopen("aux.txt", "r+");
  if (!file)
    return 1;

  /*Puts the cursor at the begining of the file*/
  fseek(file, 0, SEEK_SET);

  /*Storage the original data in a temporal variable*/
  char buffer[10000];
  size_t len = fread(buffer, 1, sizeof(buffer), file);

  /*Puts the cursosr at the begining of the file*/
  fseek(file, 0, SEEK_SET);

  char *command_n[strlen(command)+2];
  strcpy(command_n, command);
  strcat(command_n, "\n");

  /*Write the command at the begining of the file*/
  fputs(command_n, file);

  /*Write the original data after*/
  fwrite(buffer, 1, len, file);

  fclose(file);
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
