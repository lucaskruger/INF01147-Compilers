// /include/assembly.h
// Lucas Kruger e Nikolas Tesche


#ifndef ASSEMBLY_H
#define ASSEMBLY_H

#include <stdbool.h>

typedef struct register_info_element{
    int register_number;
    int first_line;
    int last_line;

    struct register_info_element *next;

} register_info_list;

extern int iloc_lines;
extern int iloc_registers;
extern register_info_list *reg_lst_start;
extern register_info_list *reg_lst_end;

void parse_through_iloc_file();
bool **create_registers_table();
int get_iloc_index(char *register_name);
void print_lines();
void print_registers_table(bool **table);
void fill_registers_table(bool **table);

void add_register_info(char *register_label, int first_line);
void update_register_line(char *register_label, int last_line);
void print_register_info_line();

#endif