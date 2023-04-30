#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "node.h"

/**
 * @brief This method excecute the > function
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int retofile(Node *argv)
{
    // FILE *fp;
    //     fp = fopen(argv->right_child-> value.str , "w+");
    //     fprintf(fp, "%s", argv->left_child->value.str);
    //     fclose(fp);
    char *end_ptr = 0;
  //int fd = open(argv->right_child, O_WRONLY | O_TRUNC | O_CREAT, 0600);
    int fd = (int) strtol(argv->right_child, &end_ptr, 10);
     if (*(end_ptr + 1) != '\0') {
        fd = open(argv->right_child, O_WRONLY | O_TRUNC | O_CREAT, 0600);
    }
    return fd;
}

/**
 * @brief This method excecute the >> function
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int retofileap(Node *argv)
{
  //   FILE *fp;

  // fp = fopen(argv[1], "a");

  // if (fp == NULL) {
  //   return 1;
  // }

  // fprintf(fp, argv[0]);

  // fclose(fp);

  // return 0;
   char *end_ptr = 0;
  //int fd = open(argv->right_child, O_WRONLY | O_APPEND  | O_CREAT, 0600);
    int fd = (int) strtol(argv->right_child, &end_ptr, 10);
     if (*(end_ptr + 1) != '\0') {
        fd = open(argv->right_child, O_WRONLY | O_APPEND  | O_CREAT, 0600);
    }
    return fd;
}

/**
 * @brief This method excecute the < function
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int refromfile(Node *argv)
{
  // FILE *fp;

  // fp = fopen(argv[1], "r");

  // if (fp == NULL) {
  //   return 1;
  // }

  // fclose(fp);

  // return 0;
  char *end_ptr = 0;
  //int fd = open(argv->right_child, O_WRONLY | O_APPEND  | O_CREAT, 0600);
    int fd = (int) strtol(argv->right_child, &end_ptr, 10);
     if (*(end_ptr + 1) != '\0') {
        fd = open(argv->right_child, O_RDONLY);
    }
    return fd;
}
