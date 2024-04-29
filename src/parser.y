// Lucas Kruger e Nikolas Tesche

%define parse.error verbose
//%define api.value.type { int } 
%{
#include "../include/ast.h"
#include <stdio.h>

int yylex(void);
extern int get_line_number();
extern void *arvore;
void yyerror (char const *mensagem);
void yylex_destroy();
%}

%union{
  struct lexical_value_type* lex_val; 
  struct asl_node_type*  node;
}

%type<node> TK_IDENTIFICADOR id_list
%type<lex_val> lit TK_LIT_INT TK_LIT_FLOAT TK_LIT_FALSE TK_LIT_TRUE  

%token TK_PR_INT
%token TK_PR_FLOAT
%token TK_PR_BOOL
%token TK_PR_IF
%token TK_PR_ELSE
%token TK_PR_WHILE
%token TK_PR_RETURN
%token TK_OC_LE
%token TK_OC_GE
%token TK_OC_EQ
%token TK_OC_NE
%token TK_OC_AND
%token TK_OC_OR
%token TK_IDENTIFICADOR
%token TK_LIT_INT
%token TK_LIT_FLOAT
%token TK_LIT_FALSE
%token TK_LIT_TRUE
%token TK_ERRO

%%
//initial non terminal

program:          /* empty */
                | global_var program   
                | func program
                ;    

// 3.1 Variable declaration

global_var:       type id_list ','
                ;

// 3.2 Function definition

func:             header comm_block 
                ;

header:           '(' par_list ')' TK_OC_OR type '/' TK_IDENTIFICADOR
                | '(' ')' TK_OC_OR type '/' TK_IDENTIFICADOR
                ;

par_list:         par_list ';' type TK_IDENTIFICADOR 
                | type TK_IDENTIFICADOR 
    ;

arg_list:         exp
                | arg_list ';' exp
                ;

ret_comm:         TK_PR_RETURN exp
                ;

// 3.3 Command Block

comm_block:       '{' '}'	
                | '{' comm_lst '}' 
    ;

comm_lst:         comm ','
                | comm_lst  comm ','
    ;

// 3.4 Simple Command 

comm:             comm_block 
                | var_decl
                | attrib_comm	
                | func_call
                | ret_comm
                | flux_ctrl
                ;

var_decl:         type id_list 
                ;

attrib_comm:      TK_IDENTIFICADOR '=' exp	
                ;

func_call:        TK_IDENTIFICADOR '(' arg_list ')'
                | TK_IDENTIFICADOR '(' ')'
    ;

flux_ctrl:        TK_PR_IF '(' exp ')' comm_block TK_PR_ELSE comm_block 
                | TK_PR_IF '(' exp ')' comm_block 
                | TK_PR_WHILE '(' exp ')' comm_block 
                ;

// 3.5 Expressions

exp:              or_exp
                ;

or_exp:           or_exp TK_OC_OR and_exp 
                | and_exp
                ;

and_exp:          and_exp TK_OC_AND eq_exp
                | eq_exp
                ;

eq_exp:           eq_exp TK_OC_EQ comp_exp
                | eq_exp TK_OC_NE comp_exp
                | comp_exp
                ;

comp_exp:         comp_exp '<' sum_exp
                | comp_exp '>' sum_exp
                | comp_exp TK_OC_LE sum_exp
                | comp_exp TK_OC_GE sum_exp
                | sum_exp
                ;

sum_exp:          sum_exp '+' mult_exp
                | sum_exp '-' mult_exp
                | mult_exp
                ;

mult_exp:         mult_exp '*' un_exp
                | mult_exp '/' un_exp
                | mult_exp '%' un_exp
                | un_exp
                ;

un_exp:           '-' un_exp
                | '!' un_exp
                | operand
                ;

operand:           TK_IDENTIFICADOR
                | lit
                | func_call
                | '(' exp ')'
                ;

// Misc: Types, Literals and Identifiers

id_list:          TK_IDENTIFICADOR {$$ = $1; arvore = (void*) $$;}
                | id_list ';' TK_IDENTIFICADOR {$$ = $3;}
                ;

lit:              TK_LIT_INT                      
                | TK_LIT_FLOAT
                | TK_LIT_FALSE
                | TK_LIT_TRUE
                ;


type:             TK_PR_INT
                | TK_PR_FLOAT
                | TK_PR_BOOL
                ;
%%

void yyerror (char const *mensagem){
fprintf (stderr, "%s line: %d\n", mensagem, get_line_number());
}

