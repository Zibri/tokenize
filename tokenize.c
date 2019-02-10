/*
Tokenize string considering also quotes.
By Zibri <zibri AT zibri DOT org>
https://github.com/Zibri/tokenize
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
  char *str1, *token;
  int j;
  char *qstart = NULL;
  bool quoted = false;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s string\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  for (j = 1, str1 = argv[1];; j++, str1 = NULL) {
    token = strtok(str1, " ");
    if (token == NULL)
      break;
    if ((token[0] == 0x27) || (token[0] == 0x22)) {
      qstart = token + 1;
      quoted = true;
    }
    if ((token[strlen(token) - 1] == 0x27) || (token[strlen(token) - 1] == 0x22)) {
      quoted = false;
      token[strlen(token) - 1] = 0;
      printf("%d: %s\n", j, qstart);
    } else {
      if (quoted) {
        token[strlen(token)] = 0x20;
        j--;
      } else
        printf("%d: %s\n", j, token);
    }
  }

  if (quoted) {
    fprintf(stderr, "String quoting error\n");
    return EXIT_FAILURE;
  } else
    return EXIT_SUCCESS;
}
