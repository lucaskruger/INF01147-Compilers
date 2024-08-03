#include <stdio.h>
#include "../include/ast.h"
#include "../include/symbol_table.h"
#include "../include/iloc.h"
extern int yyparse(void);
extern int yylex_destroy(void);
void *arvore = NULL;
void exporta(void *arvore);

int main(int argc, char **argv) {
  int ret = yyparse();
  //exporta(arvore);
  yylex_destroy();
  return ret;
}
