// Lucas Kruger e Nikolas Tesche
#include "../include/symbol_table.h"
#include <stdio.h>
#include <stdlib.h>

// returns a pointer to the top table, and removes it from the stack
symbol_table *table_stack_pop(table_stack **stack){
    if(stack == NULL || *stack == NULL){
        //printf("STACK EMPTY ALREADY\n"); // ------------------------------------------ REMOVE OR COMMENT LATER -------------------------------------------------
        return NULL;    // return NULL if there's nothing to pop
    }

    table_stack *top_element = *stack;              // reference for top element
    symbol_table *top_table = top_element->table;     // acquire table from top element

    //printf("POPPING: %d\n", top_table->value); // ------------------------------------------ REMOVE OR COMMENT LATER -------------------------------------------------

    *stack = top_element->prev_table;               // define stack top as second to last element
    free(top_element);

    return top_table;
}

// returns a pointer to the top table, without removing it from the stack
symbol_table *table_stack_peek(table_stack **stack){
    if(stack == NULL || *stack == NULL){
        return NULL;    // return NULL if there's nothing to peek
    }

    table_stack *top_element = *stack;
    symbol_table *top_table = top_element->table;

    //printf("PEEKING AT: %d\n", top_table->value); // ------------------------------------------ REMOVE OR COMMENT LATER -------------------------------------------------

    return top_table;
}

// adds a new table to the stack
void table_stack_push(table_stack **stack, symbol_table *table){
    table_stack *stack_entry = calloc(1, sizeof(table_stack));
    if (stack_entry == NULL) {
        // printf("Erro: falha ao alocar espaço para a pilha de nodes\n");
    }

    stack_entry->table = table;         // enter table contents into entry
    stack_entry->prev_table = *stack;   // define entry's previous table
    *stack = stack_entry;               // redefine top of stack as new entry

    //printf("ENTERED: %d\n", table->value); // ------------------------------------------ REMOVE OR COMMENT LATER -------------------------------------------------

    return;
}

void table_stack_print(table_stack *stack){
    table_stack *current = stack;       // set pointer to top of stack
    printf("Table Stack Contents:\n");

    while(current != NULL){
        printf("Table Entry:\n");

        if(current->table != NULL){     // print table at pointer
            //print_symbol_table(*(current->table));
        }
        else{
            printf("NULL\n");
        }

        current = current->prev_table;  // lower pointer by one entry
    }
}

symbol_table *table_stack_base(table_stack **stack){
    table_stack *base = *stack;

    while (base->prev_table != NULL){
        base = base->prev_table;        // find base of the stack
    }

    symbol_table *base_table = base->table;
    return base_table;
}