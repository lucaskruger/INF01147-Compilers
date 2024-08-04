#include <unistd.h>
#include <stdio.h>

#include "../include/ast.h"
#include "../include/symbol_table.h"
#include "../include/iloc.h"

extern int yyparse(void);
extern int yylex_destroy(void);
void *arvore = NULL;
void exporta(void *arvore);

int main(int argc, char **argv) {

  FILE *output_file = stdout;

  if (argc > 1) {
    output_file = fopen(argv[1], "w");
    if (!output_file) {
      perror("Error opening output file");
      return 1;
    }
  }

  if (output_file != stdout) {
    dup2(fileno(output_file), fileno(stdout));
  }

  int ret = yyparse();
  //exporta(arvore);

  if (output_file != stdout) {
    fclose(output_file);
  }

  yylex_destroy();
  return ret;

}
