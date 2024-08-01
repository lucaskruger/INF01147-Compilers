#include "../include/iloc.h"

#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#include<string.h>

// concatenates any number of strings. NULL MUST be passed as the last argument
char *concat(char *first_string, ...){
    va_list args;
    va_start(args, first_string);

    char *str;
    int final_string_length = 0;

    // determining length of the final string
    for(str = first_string; str != NULL; str = va_arg(args, char*)){
        final_string_length += strlen(str);
    }

    va_end(args);

    // allocate space for the concatenated string
    char *final_string = calloc(final_string_length + 1, sizeof(char));
    if(!final_string){
        printf("Memory allocation for concatenation failed");
        return NULL;
    }

    va_start(args, first_string);

    // run strcat for each argument passed, and free pointers to the strings
    for(str = first_string; str!=NULL; str = va_arg(args, char*)){
        strcat(final_string, str);
    }

    va_end(args);
    return final_string;
}

iloc_comm *gen_comm(iloc_operator op, char* arg1, char *arg2, char *arg3){
    // Allocate memory for the new iloc_comm structure
    iloc_comm *command = malloc(sizeof(iloc_comm));
    if(!command){
        printf("Memory allocation for iloc_comm failed");
        return NULL;
    }

    // Set the fields of the iloc_comm structure
    command->op = op;
    command->arg1 = arg1;
    command->arg2 = arg2;
    command->arg3 = arg3;

    return command;
}

char *gen_comm_str(iloc_comm *command, char *constant, char *label_t, char *label_f){
    iloc_operator op = command->op;
    char *arg1 = command->arg1;
    char *arg2 = command->arg2;
    char *arg3 = command->arg3;

    char *comm_str = NULL;

    switch (op)
    {
    case NOP:
        comm_str = strdup("nop");
        break;

    case ADD:
        comm_str = concat("add\t", arg1, ", ", arg2, " => ", arg3, NULL);
        break;

    case SUB:
        comm_str = concat("sub\t", arg1, ", ", arg2, " => ", arg3, NULL);
        break;

    case MULT:
        comm_str = concat("mult\t", arg1, ", ", arg2, " => ", arg3, NULL);
        break;

    case DIV:
        comm_str = concat("div\t", arg1, ", ", arg2, " => ", arg3, NULL);
        break;

    case ADDI:
        if(!constant){
            printf("Constant must be provided for ADDI\n");
            return NULL;
        }
        comm_str = concat("addI\t", arg1, ", ", constant, " => ", arg3, NULL);
        break;

    case SUBI:
        if(!constant){
            printf("Constant must be provided for SUBI\n");
            return NULL;
        }
        comm_str = concat("subI\t", arg1, ", ", constant, " => ", arg3, NULL);
        break;

    case RSUBI:
        if(!constant){
            printf("Constant must be provided for RSUBI\n");
            return NULL;
        }
        comm_str = concat("rsubI\t", arg1, ", ", constant, " => ", arg3, NULL);
        break;

    case MULTI:
        if(!constant){
            printf("Constant must be provided for MULTI\n");
            return NULL;
        }
        comm_str = concat("multI\t", arg1, ", ", constant, " => ", arg3, NULL);
        break;

    case DIVI:
        if(!constant){
            printf("Constant must be provided for DIVI\n");
            return NULL;
        }
        comm_str = concat("divI\t", arg1, ", ", constant, " => ", arg3, NULL);
        break;

    case RDIVI:
        if(!constant){
            printf("Constant must be provided for RDIVI\n");
            return NULL;
        }
        comm_str = concat("rdivI\t", arg1, ", ", constant, " => ", arg3, NULL);
        break;

    case LSHIFT:
        comm_str = concat("lshift\t", arg1, ", ", arg2, " => ", arg3, NULL);
        break;

    case LSHIFTI:
        if(!constant){
            printf("Constant must be provided for LSHIFTI\n");
            return NULL;
        }
        comm_str = concat("lshiftI\t", arg1, ", ", constant, " => ", arg3, NULL);
        break;

    case RSHIFT:
        comm_str = concat("rshift\t", arg1, ", ", arg2, " => ", arg3, NULL);
        break;

    case RSHIFTI:
        if(!constant){
            printf("Constant must be provided for RSHIFTI\n");
            return NULL;
        }
        comm_str = concat("rshiftI\t", arg1, ", ", constant, " => ", arg3, NULL);
        break;

    case AND:
        comm_str = concat("and\t", arg1, ", ", arg2, " => ", arg3, NULL);
        break;

    case ANDI:
        if(!constant){
            printf("Constant must be provided for ANDI\n");
            return NULL;
        }
        comm_str = concat("andI\t", arg1, ", ", constant, " => ", arg3, NULL);
        break;

    case OR:
        comm_str = concat("or\t", arg1, ", ", arg2, " => ", arg3, NULL);
        break;

    case ORI:
        if(!constant){
            printf("Constant must be provided for ORI\n");
        }
        comm_str = concat("orI\t", arg1, ", ", constant, " => ", arg3, NULL);
        break;

    case XOR:
        comm_str = concat("xor\t", arg1, ", ", arg2, " => ", arg3, NULL);
        break;

    case XORI:
        if(!constant){
            printf("Constant must be provided for XORI\n");
            return NULL;
        }
        comm_str = concat("xorI\t", arg1, ", ", constant, " => ", arg3, NULL);
        break;

    case LOADI:
        if(!constant){
            printf("Constant must be provided for LOADI\n");
            return NULL;
        }
        comm_str = concat("loadI\t", constant, " => ", arg2, NULL);
        break;

    case LOAD:
        comm_str = concat("load\t", arg1, " => ", arg2, NULL);
        break;

    case LOADAI:
        if(!constant){
            printf("Constant must be provided for LOADAI\n");
            return NULL;
        }
        comm_str = concat("loadAI\t", arg1, ", ", constant, " => ", arg3, NULL);
        break;

    case LOADA0:
        comm_str = concat("loadA0\t", arg1, ", ", arg2, " => ", arg3, NULL);
        break;

    case CLOAD:
        comm_str = concat("cload\t", arg1, " => ", arg2, NULL);
        break;

    case CLOADAI:
        if(!constant){
            printf("Constant must be provided for CLOADAI\n");
            return NULL;
        }
        comm_str = concat("cloadAI\t", arg1, ", ", constant, " => ", arg3, NULL);
        break;

    case CLOADA0:
        comm_str = concat("cloadA0\t", arg1, ", ", arg2, " => ", arg3, NULL);
        break;

    case STORE:
        comm_str = concat("store\t", arg1, " => ", arg2, NULL);
        break;

    case STOREAI:
        if(!constant){
            printf("Constant must be provided for STOREAI\n");
            return NULL;
        }
        comm_str = concat("storeAI\t", arg1, " => ", arg2, ", " , constant, NULL);
        break;

    case STOREAO:
        comm_str = concat("storeAO\t", arg1, " => ", arg2, ", " , arg3, NULL);
        break;

    case CSTORE:
        comm_str = concat("cstore\t", arg1, " => ", arg2, NULL);
        break;

    case CSTOREAI:
        if(!constant){
            printf("Constant must be provided for CSTOREAI\n");
            return NULL;
        }
        comm_str = concat("cstoreAI\t", arg1, " => ", arg2, ", " , constant, NULL);
        break;

    case CSTOREAO:
        comm_str = concat("cstoreAO\t", arg1, " => ", arg2, ", " , arg3, NULL);
        break;

    case I2I:
        comm_str = concat("i2i\t", arg1, " => ", arg2, NULL);
        break;

    case C2C:
        comm_str = concat("c2c\t", arg1, " => ", arg2, NULL);
        break;

    case C2I:
        comm_str = concat("c2i\t", arg1, " => ", arg2, NULL);
        break;

    case I2C:
        comm_str = concat("i2c\t", arg1, " => ", arg2, NULL);
        break;

    case JUMPI:
        if(!label_t){
            printf("Label_t must be provided for JUMPI\n");
            return NULL;
        }
        comm_str = concat("jumpI\t", " -> ", label_t, NULL);
        break;

    case JUMP:
        comm_str = concat("jump\t", " -> ", arg1, NULL);
        break;

    case CBR:
        if(!label_t || !label_f){
            printf("Label_t and label_f must be provided for CBR\n");
            return NULL;
        }
        comm_str = concat("cbr\t", arg1, " -> ", label_t, ", ", label_f, NULL);
        break;

    case CMP_LT:
        comm_str = concat("cmp_LT\t", arg1, ", ", arg2, " => ", arg3, NULL);
        break;

    case CMP_LE:
        comm_str = concat("cmp_LE\t", arg1, ", ", arg2, " => ", arg3, NULL);
        break;

    case CMP_EQ:
        comm_str = concat("cmp_EQ\t", arg1, ", ", arg2, " => ", arg3, NULL);
        break;

    case CMP_GE:
        comm_str = concat("cmp_GE\t", arg1, ", ", arg2, " => ", arg3, NULL);
        break;

    case CMP_GT:
        comm_str = concat("cmp_GT\t", arg1, ", ", arg2, " => ", arg3, NULL);
        break;

    case CMP_NE:
        comm_str = concat("cmp_NE\t", arg1, ", ", arg2, " => ", arg3, NULL);
        break;

    default:
        printf("ILLEGAL OPERATOR\n");
        return NULL;
        break;
    }

    return comm_str;
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

    // create label
    char *label_str = concat("L", label_num_str, NULL);
    free(label_num_str);

    ++label_num;

    return label_str;

}