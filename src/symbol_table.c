// Lucas Kruger e Nikolas Tesche
#include "../include/symbol_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// initializes a symbol table
void initialize_symbol_table(symbol_table **table){
    *table = (symbol_table*)calloc(1, sizeof(symbol_table));
    (*table)->entry.identifier = NULL;
    (*table)->next_entry = NULL;
}

// inserts a new entry to the end of the table
void insert_symbol_table(symbol_table *table, symbol_table_entry new_entry){
    if (table == NULL){
        //printf("INVALID NULL TABLE\n");
        return;
    }

    // first table insertion
    if(table->entry.identifier == NULL){
        table->entry.identifier = strdup(new_entry.identifier);
        table->entry.line = new_entry.line;
        table->entry.nature = new_entry.nature;
        table->entry.data_type = new_entry.data_type;
        if(table->entry.value != NULL){
            table->entry.value = strdup(new_entry.value);
        }
        else
        {
            table->entry.value = strdup("");
        }
        table->next_entry = NULL;

        return;
    }

    symbol_table *current = table;
    while(current->next_entry != NULL){ // look for the end of the list
        current = current->next_entry;
    }

    
    current->next_entry = (symbol_table*)calloc(1, sizeof(symbol_table));   // allocate space for new entry
    if(current->next_entry){
        current = current->next_entry;
        current->entry.identifier = strdup(new_entry.identifier);               // copy all entry fields into table
        current->entry.line = new_entry.line;
        current->entry.nature = new_entry.nature;
        current->entry.data_type = new_entry.data_type;
        if(current->entry.value != NULL){
            current->entry.value = strdup(new_entry.value);
        }
        else
        {
            current->entry.value = strdup("");
        }
        current->next_entry = NULL;
    }
    
}

// searches for an entry in the table returning its identifier, returns NULL if nothing is found
symbol_table_entry *search_symbol_table(symbol_table *table, char *key){

    if(key == NULL){
        fprintf(stderr, "Invalid key in search_symbol_table function.\n");
        return NULL;    // error due to invalid key
    }
    if(table->entry.identifier == NULL){
        return NULL;    // table is empty
    }

    symbol_table *current = table;

    while (current != NULL) {
        if (strcmp(key, current->entry.identifier) == 0) {
            return &current->entry;     // matching entry found
        }
        current = current->next_entry;
    }

    return NULL;    // entry not in table
}

// prints the table line by line to the terminal
void print_symbol_table(symbol_table *table){

    if(table == NULL){
        printf("NULL TABLE");
        return;
    }

    if(table->entry.identifier == NULL){
        printf("EMTPY TABLE\n");
        return;
    }

    symbol_table *current = table;

    while(current != NULL){
        char natureString[11];
        char typeString[6];

        switch (current->entry.nature)
        {
        case IDENTIFIER:
            strcpy(natureString, "IDENTIFIER");
            break;
        
        case FUNCTION:
            strcpy(natureString, "FUNCTION");
            break;
        
        default:
            strcpy(natureString, "??????????");
            break;
        }

        switch (current->entry.data_type)
        {
        case INT:
            strcpy(typeString, "INT");
            break;
        
        case FLOAT:
            strcpy(typeString, "FLOAT");
            break;

        case BOOL:
            strcpy(typeString, "BOOL");
            break;
        
        default:
            strcpy(typeString, "?????");
            break;
        }

        printf("%s | %d | %s | %s | %s \n", current->entry.identifier, current->entry.line, natureString, typeString, current->entry.value);

        current = current->next_entry;
    }
}

// frees all pointers stored in the table
void free_symbol_table(symbol_table *table){
    symbol_table *current = table;
    while(current != NULL){
        symbol_table *next = current->next_entry;

        free(current->entry.identifier);
        free(current->entry.value);

        free(current);

        current = next;
    }
}

symbol_table_entry create_table_entry(char* identifier, int line, entry_nature nature, entry_type data_type, char* value){
    symbol_table_entry new_entry;
    new_entry.identifier = identifier;
    new_entry.line = line;
    new_entry.nature = nature;
    new_entry.data_type = data_type;
    new_entry.value = value;
    return new_entry;
}

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
void table_stack_push(table_stack **stack, symbol_table *new_table){
    table_stack *stack_entry = calloc(1, sizeof(table_stack));
    if (stack_entry == NULL) {
        return;
    }

    stack_entry->table = new_table;         // enter table contents into entry
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

// Finds and returns the first match of a key on a stack of tables, returns NULL if nothing is found
symbol_table_entry *search_table_stack(table_stack **stack, char *key){
    if(stack == NULL || *stack == NULL){
        printf("Warning: Searched an invalid stack\n");
        return NULL;    // return NULL if there's nothing in the stack
    }

    table_stack *current_element = *stack;

    while(current_element != NULL){
        symbol_table *current_table = current_element->table; // get table on top of the stack
        symbol_table_entry *current_entry = search_symbol_table(current_table, key); // look for a matching entry in the current table

        if(current_entry != NULL){
            return current_entry;   // found a key match
        }

        current_element = current_element->prev_table;  // go to previous table in the stack
    }

    return NULL; // found no match
}