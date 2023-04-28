#include <stdio.h>
#include <string.h>

int print_file_text(FILE *file)
{
    int c = 0;
    while((c = fgetc(file)) != EOF)
    {
        printf("%c", c);
    }
    return 0;
}

int help(char *keyword)
{
    FILE *file;
    int c = 0;
    if(!keyword)
    {
        file = fopen("help/generalhelp.txt", "r");
    }
    else
    {
       char buffer[100];
       strcat(strcpy(buffer, "help/"), keyword);
       strcat(buffer, ".txt");
       file = fopen(buffer, "r");
       
       if(!file)
       {
        printf("Keyword no válida \n");
        return 1;
       }
      
    }
     print_file_text(file);
       fclose(file);
       return 0;
}