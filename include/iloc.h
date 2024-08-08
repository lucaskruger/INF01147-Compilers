// /include/iloc.h
// Lucas Kruger e Nikolas Tesche

#ifndef ILOC_H
#define ILOC_H

#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#include<string.h>

/*
nop // não faz nada
add r1, r2 => r3 // r3 = r1 + r2
sub r1, r2 => r3 // r3 = r1 - r2
mult r1, r2 => r3 // r3 = r1 * r2
div r1, r2 => r3 // r3 = r1 / r2
addI r1, c2 => r3 // r3 = r1 + c2
subI r1, c2 => r3 // r3 = r1 - c2
rsubI r1, c2 => r3 // r3 = c2 - r1
multI r1, c2 => r3 // r3 = r1 * c2
divI r1, c2 => r3 // r3 = r1 / c2
rdivI r1, c2 => r3 // r3 = c2 / r1
lshift r1, r2 => r3 // r3 = r1 << r2
lshiftI r1, c2 => r3 // r3 = r1 << c2
rshift r1, r2 => r3 // r3 = r1 >> r2
rshiftI r1, c2 => r3 // r3 = r1 >> c2
and r1, r2 => r3 // r3 = r1 && r2
andI r1, c2 => r3 // r3 = r1 && c2
or r1, r2 => r3 // r3 = r1 || r2
orI r1, c2 => r3 // r3 = r1 || c2
xor r1, r2 => r3 // r3 = r1 xor r2
xorI r1, c2 => r3 // r3 = r1 xor c2
loadI c1 => r2 // r2 = c1
load r1 => r2 // r2 = Memoria(r1)
loadAI r1, c2 => r3 // r3 = Memoria(r1 + c2)
loadA0 r1, r2 => r3 // r3 = Memoria(r1 + r2)
cload r1 => r2 // caractere load
cloadAI r1, c2 => r3 // caractere loadAI
cloadA0 r1, r2 => r3 // caractere loadA0
store r1 => r2 // Memoria(r2) = r1
storeAI r1 => r2, c3 // Memoria(r2 + c3) = r1
storeAO r1 => r2, r3 // Memoria(r2 + r3) = r1
cstore r1 => r2 // caractere store
cstoreAI r1 => r2, c3 // caractere storeAI
cstoreAO r1 => r2, r3 // caractere storeAO
i2i r1 => r2 // r2 = r1 para inteiros
c2c r1 => r2 // r2 = r1 para caracteres
c2i r1 => r2 // converte um caractere para um inteiro
i2c r1 => r2 // converte um inteiro para caractere
jumpI -> l1 // PC = endereço(l1)
jump -> r1 // PC = r1
cbr r1 -> l2, l3 // PC = endereço(l2) se r1 = true, senão PC = endereço(l3)
cmp_LT r1, r2 -> r3 // r3 = true se r1 < r2, senão r3 = false
cmp_LE r1, r2 -> r3 // r3 = true se r1 \leq r2, senão r3 = false
cmp_EQ r1, r2 -> r3 // r3 = true se r1 = r2, senão r3 = false
cmp_GE r1, r2 -> r3 // r3 = true se r1 \geq r2, senão r3 = false
cmp_GT r1, r2 -> r3 // r3 = true se r1 > r2, senão r3 = false
cmp_NE r1, r2 -> r3
*/

typedef enum operators{
    NOP,
    ADD, SUB, MULT, DIV, ADDI, SUBI, RSUBI, MULTI, DIVI, RDIVI,
    LSHIFT, LSHIFTI, RSHIFT, RSHIFTI,
    AND, ANDI, OR, ORI, XOR, XORI,
    LOADI, LOAD, LOADAI, LOADA0, CLOAD, CLOADAI, CLOADA0,
    STORE, STOREAI, STOREAO, CSTORE, CSTOREAI, CSTOREAO,
    I2I, C2C, C2I, I2C,
    JUMPI, JUMP, CBR,
    CMP_LT, CMP_LE, CMP_EQ, CMP_GE, CMP_GT, CMP_NE,
    RETURN
} iloc_operator;

typedef struct{
    iloc_operator op;
    char *arg1;
    char *arg2;
    char *arg3;
} iloc_comm;

typedef struct comm_list{
    iloc_comm *current_comm;
    struct comm_list *next_comm;
}iloc_comm_list;

char *concat(char *first_string, ...);  // NULL MUST be passed as the last argument
iloc_comm *gen_comm(iloc_operator op, char* arg1, char *arg2, char *arg3);
char *gen_comm_str(iloc_comm *command, char *constant, char *label_t, char *label_f);
char *gen_label();
char *gen_temp();
char *int_to_str(int num);


#endif