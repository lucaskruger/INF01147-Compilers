#include "../include/ast.h"
#include "../include/data.h"
#include <stdio.h>
#include <stdlib.h>

node_t *create_tree() { return 0; }

node_t *create_node(lex_val_t *val) {
  node_t *node = (node_t *)calloc(sizeof(node_t), 0);
  node->lex_val = (lex_val_t *)calloc(sizeof(lex_val_t), 0);
  node->lex_val = val;
  // TODO: node_t.type needed?
  return node;
}

int insert_node(node_t *node, node_t *par, int pos) {
  par->children[pos] = node;
  node->parent = par;
  return 0;
}

// NOTE: will delete nodes with information and all it's children

int delete_node(node_t *node) {
  if (node != NULL) {
    for (int i = MAX_CHILDREN - 1; i >= 0; i--) {
      if (node->children[i] != NULL) {
        delete_node(node->children[i]);
      }
    }
  }
  // NOTE: this assumes children always get filled in order
  if (node->children[0] == NULL) {
    free(node->lex_val);
    free(node);
  }
  return 0;
}
int print_tree() { return 0; }
void exporta(void *arvore) { printf("hello"); }
