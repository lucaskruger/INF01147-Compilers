#include "../include/assembly.h"
#include "../include/iloc.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int iloc_lines = 0;
int iloc_registers = 0;

register_info_list *reg_lst_start = NULL;
register_info_list *reg_lst_end = NULL;

void parse_through_iloc_file() {
    bool **register_table = create_registers_table();

    fill_registers_table(register_table);
    print_register_info_line();

    print_registers_table(register_table);
}

bool **create_registers_table() {
    // get number of iloc registers
    iloc_registers = get_iloc_index(gen_temp());

    // number of iloc lines is calculated during source code parsing
    bool **table = calloc(iloc_lines, sizeof(bool*));
    for(int i = 0; i < iloc_lines; i++) {
        table[i] = calloc(iloc_registers, sizeof(bool));
    }

    return table;
}
int get_iloc_index(char *iloc_label) {

    // check if register or label exists
    if(!iloc_label){
        printf("Invalid NULL Register or Label\n");
        return -1;
    }

    // check if it's a register or label
    if(iloc_label[0] == 'r' || iloc_label[0] == 'L') {
        int i = 1;
        int number = 0;

        while(iloc_label[i] != '\0') {
            // check if register or label index is valid
            if(iloc_label[i] < '0' || iloc_label[i] > '9') {
                printf("Invalid Register or Label Index\n");
                return -1;
            }

            // enter index into number
            number = number * 10 + (iloc_label[i] - '0');
            i++;
        }

        return number;
    }
    else{
        printf("Invalid Register or Label Name\n");
        return -1;
    }

}

void print_lines() {
    printf("lines: %d\n", iloc_lines);
}

void print_registers_table(bool **table) {

    printf("--------------------------------------------------------------------------------------------------------------------------------------\n");
    // print table headers
    printf("LINES");
    for(int i = 0; i < iloc_registers; i++) {
        printf("  r%-2d", i);
    }
    printf("\n");

    // print table data
    for(int i = 0; i < iloc_lines; i++) {
        printf("%-5d", i);

        for(int j = 0; j < iloc_registers; j++) {
            if(table[i][j]){
                printf("  X  ");
            }
            else{
                printf("     ");
            }
        }
        printf("\n");
    }

    printf("--------------------------------------------------------------------------------------------------------------------------------------\n");
}

void fill_registers_table(bool **table) {

    register_info_list *aux = reg_lst_start;
    while(aux != NULL) {

        for(int i = aux->first_line; i < aux->last_line; i++) {
            table[i][aux->register_number] = true;
        }
        aux = aux->next;
    }
}

void add_register_info(char *register_label, int first_line){

    if(reg_lst_end == NULL) {

        // add first register
        reg_lst_end = malloc(sizeof(register_info_list));
        reg_lst_end->register_number = get_iloc_index(register_label);
        reg_lst_end->first_line = first_line;
        reg_lst_end->last_line = first_line;
        reg_lst_end->next = NULL;

        reg_lst_start = reg_lst_end;
        return;
    }

    // add new register
    register_info_list *new_item = malloc(sizeof(register_info_list));
    new_item->register_number = get_iloc_index(register_label);
    new_item->first_line = first_line;
    new_item->last_line = first_line;
    new_item->next = NULL;

    register_info_list *aux = reg_lst_end;
    while(aux->next != NULL) {
        aux = aux->next;
    }
    aux->next = new_item;
    reg_lst_end = new_item;

    return;

}

void update_register_line(char *register_label, int last_line){
    int key = get_iloc_index(register_label);

    register_info_list *aux = reg_lst_start;
    while(aux->register_number != key) {
        aux = aux->next;
    }
    aux->last_line = last_line;

    return;
}

void print_register_info_line() {
    register_info_list *aux = reg_lst_start;
    while(aux != NULL) {
        printf("Register %d: %d - %d\n", aux->register_number, aux->first_line, aux->last_line);
        aux = aux->next;
    }
}