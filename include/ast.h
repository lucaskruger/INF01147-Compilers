#ifndef AST_H
#define AST_H

#include "data.h"

extern void exporta(void *arvore);

node_t *create_tree();
node_t *create_node(lex_val_t *val);
int insert_node(node_t *node, node_t *par, int pos);
int delete_node(node_t *node);
int print_tree();

#endif
