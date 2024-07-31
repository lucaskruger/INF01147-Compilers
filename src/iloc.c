#include "../include/iloc.h"

#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#include<string.h>

char *concat(char *first_string, ...){
    va_list args;
    va_start(args, first_string);

    char *str;
    int final_string_length = 0;

    // determining length of the final string
    for(str = first_string; str != NULL; str = va_arg(args, char*)){
        final_string_length = strlen(str);
    }

    va_end(args);

    // allocate space for the concatenated string
    char *final_string = calloc(final_string_length + 1, sizeof(char));
    if(!final_string){
        printf("Memory allocation for concatenation failed");
        return NULL;
    }

    va_start(args, first_string);

    // run strcat for each argument passed
    for(str = first_string; str!=NULL; va_arg(args, char*)){
        strcat(final_string, str);
    }

    va_end(args);
    return final_string;
}

char *gen_label(){
    static int label_num = 0;

    // get length of the current label number
    int num_length = snprintf(NULL, 0, "%d", label_num);

    // allocate and create label number string
    char *label_num_str = calloc(num_length + 1, sizeof(char));
    if(label_num_str == NULL){
        printf("Memory allocation for label generation failed");
        return NULL;
    }

    sprintf(label_num_str, "%d", label_num);

    char *label_str = concat("L", label_num_str, ":");
    ++label_num;

    return label_str;

}