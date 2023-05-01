#include <stdio.h>
#include <string.h>

/*print char by char the content of the text file indicated*/
int print_file_text(FILE *file)
{
    int c = 0;
    while ((c = fgetc(file)) != EOF)
    {
        printf("%c", c);
    }
    return 0;
}

/*help function indicates and prints which file to read depending on the keyword*/
int help(int argc, char **argv)
{
    FILE *file;
    int c = 0;
    char *keyword = argv[1];
    /*if keyword is NULL, then it prints generalhelp file*/
    if (!keyword)
    {
        file = fopen("help/generalhelp.txt", "r");
    }
    else
    {
        char buffer[100];
        strcat(strcpy(buffer, "help/"), keyword);
        strcat(buffer, ".txt");
        file = fopen(buffer, "r");

        /*if file is NULL it means that doesn't exist a file with the keyword indicated*/
        if (!file)
        {
            printf("Keyword no válida \n");
            return 1;
        }
    }
    print_file_text(file);
    fclose(file);
    return 0;
}