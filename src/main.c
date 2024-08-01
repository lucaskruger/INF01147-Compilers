#include <stdio.h>
#include "../include/symbol_table.h"
#include "../include/iloc.h"
extern int yyparse(void);
extern int yylex_destroy(void);
void *arvore = NULL;
void exporta(void *arvore);

int main(int argc, char **argv) {
  /*int ret = yyparse();
  //exporta(arvore);
  yylex_destroy();
  return ret;*/

  char *label1 = gen_label();
  char *label2 = gen_label();
  char *label3 = gen_label();

  printf("%s\n%s\n%s\n", label1, label2, label3);

  free(label1);
  free(label2);
  free(label3);
}
