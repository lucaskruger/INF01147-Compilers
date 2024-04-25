#ifndef DATA_H
#define DATA_H

#define MAX_CHILDREN 4

typedef enum token_type { ID, LIT } tk_t;
// hello
typedef struct lexical_value_type {
  int line_number;
  tk_t tk_type;
  char *tk_value;
} lex_val_t;

typedef struct asl_node_type {
  lex_val_t *lex_val;
  struct asl_node_type *children[MAX_CHILDREN];
  struct asl_node_type *parent;
} node_t;

#endif
