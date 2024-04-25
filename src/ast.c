#include "../include/ast.h"
#include "../include/data.h"
#include <stdio.h>
#include <stdlib.h>

node_t *create_tree() { return 0; }
node_t *create_node(lex_val_t *val) {
  node_t *node = (node_t *)calloc(sizeof(node_t), 0);
  node->lex_val = val;
  // TODO: node_t type?
  return 0;
}

int insert_node() { return 0; }
int delete_node() { return 0; }
int print_tree() { return 0; }
void exporta(void *arvore) { printf("hello"); }
