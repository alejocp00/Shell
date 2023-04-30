#include <unistd.h>
#include <stdio.h>
#include "built-ins/builtins.h"

/**
 * @brief This method execute the > function
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
Builtins retofile_struct = {">", retofile};
/**
 * @brief This method execute the >> function
 *
 * @param argc
 * @param argv
 * @return int
 */
int retofileap(int argc, char **argv)
{
  FILE *fp;

  fp = fopen(argv[1], "a");

  if (fp == NULL)
  {
    return 1;
  }

  // fprintf(fp, argv[0]);

  fclose(fp);

  return 0;
}
Builtins retofileap_struct = {">>", retofileap};
/**
 * @brief This method execute the < function
 *
 * @param argc
 * @param argv
 * @return int
 */
int refromfile(int argc, char **argv) // como entrarselo a la otra función
{
  FILE *fp;

  fp = fopen(argv[1], "r");

  if (fp == NULL)
  {
    return 1;
  }

  fclose(fp);

  return 0;
}
Builtins refromfile_struct = {"<", refromfile};