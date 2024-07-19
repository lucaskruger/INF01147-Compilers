#include <stdio.h>
#include "../include/symbol_table.h"
extern int yyparse(void);
extern int yylex_destroy(void);
void *arvore = NULL;
void exporta(void *arvore);

int main(int argc, char **argv) {
  int ret = yyparse();
  //exporta(arvore);
  yylex_destroy();
  return ret;

  /*symbol_table *testTable;

  initialize_symbol_table(&testTable);

  symbol_table_entry new_entry = create_table_entry("entry1", 10, IDENTIFIER, BOOL, NULL);

  insert_symbol_table(testTable, new_entry);

  new_entry = create_table_entry("entry2", 11, IDENTIFIER, INT, "50");

  insert_symbol_table(testTable, new_entry);

  new_entry = create_table_entry("entry3", 12, FUNCTION, FLOAT, "100");

  insert_symbol_table(testTable, new_entry);

  print_symbol_table(testTable);

  symbol_table_entry *searched_entry = search_symbol_table(testTable, "toast");

  if(searched_entry != NULL)
  {
    printf("%s\n", searched_entry->value);
  }
  else{
    printf("ENTRY NOT FOUND\n");
  }

  free_symbol_table(testTable);*/
}
