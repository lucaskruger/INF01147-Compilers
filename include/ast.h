#ifndef AST_H
#define AST_H

#include "data.h"

extern void exporta(void *arvore);

struct asl_node_type *create_tree();
struct asl_node_type *create_node(struct lexical_value_type *val);
int insert_node();
int delete_node();
int print_tree();

#endif
