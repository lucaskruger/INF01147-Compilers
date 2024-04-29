// /include/ast.h
// Lucas Kruger e Nicolas Tesche

#ifndef AST_H
#define AST_H

typedef enum token_type { ID, LIT } tk_t;

typedef struct lexical_value {
  int line_number;
  tk_t tk_type;
  char *tk_value; // TODO: is this the label?
} lex_val_t;

typedef struct asl_node_type {
  lex_val_t *lex_val;
  int number_of_children;
  struct asl_node_type **children;
  struct asl_node_type *parent;
} node_t;

extern void exporta(void *arvore);

lex_val_t *
create_lex_val(int line, tk_t type,
               char *value); // WARNING: value *char for testings only
node_t *create_node(const lex_val_t *val);
int insert_node(node_t *node, node_t *par, int pos);
int delete_node(node_t *node);
void print_tree(node_t *node);
void print_tree(node_t *node);

#endif
