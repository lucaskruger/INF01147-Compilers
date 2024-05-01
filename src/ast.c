#include "../include/ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OUTPUT_FILE "ast.txt"
// TODO: check if label and tk_value need to be kept in different registers

lex_val_t *create_lex_val(int line, tk_t type, char *value) {
  lex_val_t *lex_val = NULL;
  lex_val = calloc(1, sizeof(lex_val_t));
  if (lex_val != NULL) {
    lex_val->line_number = line;
    lex_val->tk_type = type;
    if (value != NULL) {
      lex_val->tk_value = calloc(1, (strlen(value) + 1) * sizeof(char));
    }
    lex_val->tk_value = strdup(value);
  } else {
    fprintf(stderr, "Error: %s got parameters = %d/ %u / %s", __FUNCTION__,
            line, type, value);
  }
  return lex_val;
}

node_t *create_node(const lex_val_t *val) {
  node_t *node = NULL;
  node = calloc(1, sizeof(node_t));
  if (node != NULL) {
    node->number_of_children = 0;
    node->lex_val = (lex_val_t *)calloc(sizeof(lex_val_t), 0);
    if (node->lex_val != NULL) {
      node->lex_val->line_number = val->line_number;
      node->lex_val->tk_type = val->tk_type;
      node->lex_val->tk_value = strdup(val->tk_value);
    }
  }
  return node;
}

void update_label(node_t *node, char *name) {
  if (node != NULL) {
    node->lex_val->tk_value =
        realloc(node->lex_val->tk_value, (strlen(name) + 1) * sizeof(char));
    if (node->lex_val->tk_value != NULL) {
      node->label = strdup(name);
    }
  } else {
    fprintf(stderr, "Error: %s got parameters = %p/ %s", __FUNCTION__, node,
            name);
  }
}

void add_child(node_t *par, node_t *child) {
  if (par != NULL && child != NULL) {
    par->number_of_children++;
    par->children =
        realloc(par->children, par->number_of_children * sizeof(node_t *));
    par->children[par->number_of_children - 1] = child;
  } else {
    fprintf(stderr, "Error: %s got parameters = %p / %p. \n", __FUNCTION__, par,
            child);
  }
}

void free_node(node_t *node) {
  if (node != NULL) {
    for (int i = 0; i < node->number_of_children; i++) {
      free_node(node->children[i]);
    }
    free(node->children);
    free(node->lex_val); // TODO: make is so it frees the whole struct
    free(node);
  } else {
    fprintf(stderr, "Error: %s got parameters = %p", __FUNCTION__, node);
  }
}

static void _print_tree(FILE *foutput, node_t *node, int profundidade) {
  int i;
  if (node != NULL) {
    fprintf(foutput, "%d%*s: Nó '%s' tem %d filhos:\n", profundidade,
            profundidade * 2, "", node->lex_val->tk_value,
            node->number_of_children);
    for (i = 0; i < node->number_of_children; i++) {
      _print_tree(foutput, node->children[i], profundidade + 1);
    }
  } else {
    printf("Erro: %s recebeu parâmetro node = %p.\n", __FUNCTION__, node);
  }
}

void print_tree(node_t *node) {
  FILE *foutput = stderr;
  if (node != NULL) {
    _print_tree(foutput, node, 0);
  } else {
    printf("Erro: %s recebeu parâmetro node = %p.\n", __FUNCTION__, node);
  }
}

static void _exporta(FILE *foutput, node_t *node) {
  int i;
  if (node != NULL) {
    fprintf(foutput, "  %ld [ label=\"%s\" ];\n", (long)node,
            node->lex_val->tk_value);
    for (i = 0; i < node->number_of_children; i++) {
      fprintf(foutput, "  %ld -> %ld;\n", (long)node, (long)node->children[i]);
      _exporta(foutput, node->children[i]);
    }
  } else {
    printf("Erro: %s recebeu parâmetro node = %p.\n", __FUNCTION__, node);
  }
}

extern void exporta(void *node) {
  FILE *foutput = fopen(OUTPUT_FILE, "w+");
  if (foutput == NULL) {
    printf("Erro: %s não pude abrir o arquivo [%s] para escrita.\n",
           __FUNCTION__, OUTPUT_FILE);
  }
  if (node != NULL) {
    fprintf(foutput, "AST NODES {\n");
    _exporta(foutput, node);
    fprintf(foutput, "}\n");
    fclose(foutput);
  } else {
    printf("Erro: %s recebeu parâmetro node = %p.\n", __FUNCTION__, node);
  }
}
