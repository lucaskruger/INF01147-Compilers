// /include/iloc.h
// Lucas Kruger e Nikolas Tesche

#ifndef ILOC_H
#define ILOC_H

#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#include<string.h>

typedef struct{
    char *op;
    char *arg1;
    char *arg2;
    char *arg3;
} iloc_comm;

typedef struct comm_list{
    iloc_comm *current_comm;
    struct comm_list *next_comm;
}iloc_comm_list;

char *concat(char *first_string, ...);
char *gen_label();


#endif