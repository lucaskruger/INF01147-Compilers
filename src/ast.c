#include "../include/ast.h"
#include "../include/iloc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OUTPUT_FILE "ast.dot"

lex_val_t *create_lex_val(int line, tk_t type, char *value) {
  lex_val_t *lex_val = NULL;
  lex_val = (lex_val_t *)calloc(1, sizeof(lex_val_t));
  if (lex_val != NULL) {
    lex_val->line_number = line;
    lex_val->tk_type = type;
    if (value != NULL) {
      lex_val->tk_value = calloc(1, (strlen(value) + 1) * sizeof(char));
    }
    lex_val->tk_value = strdup(value);
  } else {
    // fprintf(stderr, "Error: %s got parameters = %d/ %u / %s",
    // __FUNCTION__,line, type, value);
  }
  return lex_val;
}

node_t *create_node(const lex_val_t *val) {
  node_t *node = NULL;
  node = calloc(1, sizeof(node_t));
  if (node != NULL) {
    node->number_of_children = 0;
    if (val != NULL) {
      node->lex_val = (lex_val_t *)calloc(1, sizeof(lex_val_t));
      if (node->lex_val != NULL) {
        node->lex_val->line_number = val->line_number;
        node->lex_val->tk_type = val->tk_type;
        node->lex_val->tk_value = strdup(val->tk_value);
        update_label(node, node->lex_val->tk_value);
      }
    }
  }
  return node;
}

void update_label(node_t *node, char *name) {
  if (node != NULL) {
    node->label = calloc(1, (strlen(name) + 1) * sizeof(char));
    if (node->label != NULL) {
      node->label = strdup(name);
    }
  } else {
    // fprintf(stderr, "Error: %s got parameters = %p/ %s", __FUNCTION__,
    // node,name);
  }
}

void update_type(node_t *node, entry_type new_type) {
  if (node != NULL) {
    node->data_type = new_type;
  } else {
    // fprintf(stderr, "Error: %s got parameters = %p/ %s", __FUNCTION__,
    // node,name);
  }
}

void add_child(node_t *par, node_t *child) {
  if (par != NULL && child != NULL) {
    par->number_of_children++;
    par->children =
        realloc(par->children, par->number_of_children * sizeof(node_t *));
    par->children[par->number_of_children - 1] = child;

  } else {
    // fprintf(stderr, "Error: %s got parameters = %s / %p.\n",
    // __FUNCTION__,par->label, child);
  }
}

void free_node(node_t *node) {
  if (node != NULL) {
    for (int i = 0; i < node->number_of_children; i++) {
      free_node(node->children[i]);
    }
    free(node->children);
    free(node->label);
    free(node->temp);
    free(node->lex_val->tk_value);
    free(node->lex_val);
    free(node);
  } else {
    // fprintf(stderr, "Error: %s got parameters = %p", __FUNCTION__, node);
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
    // printf("Erro: %s recebeu parâmetro node = %p.\n", __FUNCTION__, node);
  }
}

void print_tree(node_t *node) {
  FILE *foutput = stderr;
  if (node != NULL) {
    _print_tree(foutput, node, 0);
  } else {
    // printf("Erro: %s recebeu parâmetro node = %p.\n", __FUNCTION__, node);
  }
}

static void _exporta(node_t *node) {
  int i;
  if (node != NULL) {
    printf("  %ld [ label=\"%s\" ];\n", (long)node, node->label);
    for (i = 0; i < node->number_of_children; i++) {
      printf("  %ld -> %ld;\n", (long)node, (long)node->children[i]);
      _exporta(node->children[i]);
    }
  } else {
    // printf("Erro: %s recebeu parâmetro node = %p.\n", __FUNCTION__, node);
  }
}

extern void exporta(void *node) {
  if (node != NULL) {
    // printf("AST{\n");
    _exporta(node);
    // printf("}\n");
  } else {
    // printf("Erro: %s recebeu parâmetro node = %p.\n", __FUNCTION__, node);
  }
}

node_t *node_stack_pop(node_s **head) {
  if (head == NULL || *head == NULL) {
    // printf("Erro: Pilha já está vazia.\n");
    return NULL; // Return NULL if there's nothing to pop
  }

  node_s *top_node = *head;
  node_t *data = top_node->node_data;

  *head = top_node->prev_node;
  free(top_node);

  return data;
}

void node_stack_push(node_s **head, node_t *new_node) {

  // Allocate space for the new node
  node_s *stack_entry = calloc(1, sizeof(node_s));
  if (stack_entry == NULL) {
    // printf("Erro: falha ao alocar espaço para a pilha de nodes\n");
  }

  stack_entry->prev_node = *head;    // Point to the previous node in the stack
  stack_entry->node_data = new_node; // Point to the node
  *head = stack_entry; // Change head so it points to the newly created entry
}

// Print stack for debugging purposes
void node_stack_print(node_s *head) {
  node_s *current = head;
  printf("Stack contents:\n");
  while (current != NULL) {
    if (current->node_data != NULL) {
      printf("\tstack: %s\n", current->node_data->label);
    } else {
      printf("NULL\n");
    }
    current = current->prev_node;
  }
}
