#include <unistd.h>
#include <stdio.h>
#include "builtins.h"

/**
 * @brief This method excecute the > function
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int retofile(int argc, char **argv)
{
    FILE *fp;
        fp = fopen(argv[1], "w+");
        fprintf(fp, "%s", argv[0]);
        fclose(fp);
}
Builtins cd_struct = {">", retofile};
/**
 * @brief This method excecute the >> function
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int retofileap(int argc, char **argv)
{
    return chdir(argv);
}
Builtins cd_struct = {">>", retofileap};
/**
 * @brief This method excecute the < function
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int refromfile(int argc, char **argv)
{
    return chdir(argv);
}
Builtins cd_struct = {"<", refromfile};