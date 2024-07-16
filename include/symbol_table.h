// Lucas Kruger e Nikolas Tesche

#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

typedef enum nature_type { IDENTIFIER , FUNCTION } entry_nature;
typedef enum data_type { INT, FLOAT, BOOL } entry_type;

typedef struct{
    char *identifier;
    int line;
    entry_nature nature;
    entry_type data_type;
    char* value;
}symbol_table_entry;

typedef struct{
    symbol_table_entry entry;
    symbol_table_entry *next_entry;
} symbol_table;

typedef struct{
    int value;
} test_table;

typedef struct table_stack_element{
    symbol_table *table;
    struct table_stack_element *prev_table;
} table_stack;

void print_symbol_table(symbol_table table);
symbol_table *table_stack_pop(table_stack **stack);
symbol_table *table_stack_peek(table_stack **stack);
void table_stack_push(table_stack **node_stack, symbol_table *new_node);
void table_stack_print(table_stack *stack);
symbol_table *table_stack_base(table_stack **stack);

#endif