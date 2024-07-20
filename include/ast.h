// /include/ast.h
// Lucas Kruger e Nikolas Tesche

#ifndef AST_H
#define AST_H

#include<stdio.h>
#include"symbol_table.h"

typedef enum token_type { ID, LIT } tk_t;

typedef struct lexical_value {
  int line_number;
  tk_t tk_type;
  char *tk_value;
} lex_val_t;

typedef struct asl_node_type {
  lex_val_t *lex_val; 
  char *label;
  entry_type data_type;
  int number_of_children;
  struct asl_node_type **children;
  struct asl_node_type *parent;
} node_t;

typedef struct node_stack {
  node_t *node_data;
  struct node_stack *prev_node;
} node_s;

extern void exporta(void *arvore);

lex_val_t *create_lex_val(int line, tk_t type, char *value);
node_t *create_node(const lex_val_t *val);
void update_label(node_t *node, char *name);
void update_type(node_t *node, entry_type new_type);
void add_child(node_t *par, node_t *child);
void free_node(node_t *node);
void print_tree(node_t *node);
void print_tree(node_t *node);
node_t *node_stack_pop(node_s **node_stack);
void node_stack_push(node_s **node_stack, node_t *new_node);
void node_stack_print(node_s *head);

#endif
