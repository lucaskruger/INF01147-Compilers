// Lucas Kruger e Nikolas Tesche

%define parse.error verbose
//%define api.value.type {int } 
%{
#include "../include/ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yylex(void);
extern int get_line_number();
extern void *arvore;
void yyerror (char const *mensagem);
void yylex_destroy();
node_s *head = NULL;
%}

%union{
  struct lexical_value_type* lex_val; 
  struct asl_node_type*  node;
  int filler;
}

%type<node> program comm_block comm_lst comm var_decl id_list
%type<node> global_var attrib_comm exp ret_comm flux_ctrl
%type<node> or_exp un_exp sum_exp and_exp comp_exp mult_exp
%type<node> func func_call arg_list par_list header eq_exp
%type<node> lit operand
%type<node> '=''<''>''+''-''*''/''%''!'
%type<filler> type

%token<filler> TK_PR_INT
%token<filler> TK_PR_FLOAT
%token<filler> TK_PR_BOOL
%token<node> TK_PR_IF
%token<node> TK_PR_ELSE
%token<node> TK_PR_WHILE
%token<node> TK_PR_RETURN
%token<node> TK_OC_LE
%token<node> TK_OC_GE
%token<node> TK_OC_EQ
%token<node> TK_OC_NE
%token<node> TK_OC_AND
%token<node> TK_OC_OR
%token<node> TK_IDENTIFICADOR
%token<node> TK_LIT_INT
%token<node> TK_LIT_FLOAT
%token<node> TK_LIT_FALSE
%token<node> TK_LIT_TRUE
%token<filler> TK_ERRO

%%
//initial non terminal

program:          {$$ = NULL;}/* empty */
                | global_var program{
                    if($2 != NULL){
                      $$ = $2;
                    }else {
                      $$ = NULL;
                    }
                  }

                | func program{
                    if($2 != NULL)
                      add_child($1,$2);
                    $$ = $1;
                    arvore = (void*) $$;
                    }
                ;

// 3.1 Variable declaration

global_var:       var_decl ','{
                    $$ = NULL;
                    }
                ;

                // 3.2 Function definition

func:             header comm_block {
                    add_child($1, $2);
                    $$ = $1;
                    }
                ;

header:    '(' par_list ')' TK_OC_OR type '/' TK_IDENTIFICADOR {
                    //add_child($7,$2);
                    update_label($7,$7->lex_val->tk_value);
                    $$ = $7;
                    }

                | '(' ')' TK_OC_OR type '/' TK_IDENTIFICADOR {
                    update_label($6,$6->lex_val->tk_value);
                    $$ = $6;
                    }
                ;

par_list:         par_list ';' type TK_IDENTIFICADOR {
                    //add_child($1,$4);
                    $$ = $1;
                    }

                | type TK_IDENTIFICADOR {
                    $$ = $2;
                    }
                ;

arg_list:         exp{
                    node_stack_push(&head,$1);
                    $$ = $1;
                    }
                | arg_list ';' exp {
                    add_child(node_stack_pop(&head), $3);
                    node_stack_push(&head, $3);
                    $$ = $1;
                    }
                ;

ret_comm:         TK_PR_RETURN exp {
                    update_label($1,"return");
                    add_child($1,$2);
                    $$ = $1;
                    } 
                ;

// 3.3 Command Block

comm_block:       '{' '}' {
                    $$ = NULL;
                    }// if empty 1 child

                | '{' comm_lst '}' {
                    $$ = $2;
                    }
                ;

comm_lst:       comm ',' {
                  $$ = $1;
                  if($1 != NULL){
                    node_stack_push(&head, $1);
                  }
                  }

                  //comm ',' comm_lst
               |  comm_lst comm ','{// one conflict 
                    if($2 == NULL){//FIX: oof
                      if($1 == NULL){
                        $$ = NULL;
                      }else
                        $$ = $1;
                    }else {
                      if($1 == NULL){
                        $$ = $2;
                        node_stack_push(&head, $2);
                      }else{
                        add_child(node_stack_pop(&head), $2);
                        //add_child($1, $2);
                        node_stack_push(&head, $2);
                        $$ = $1;
                      }
                    }
                  }
                ;

// 3.4 Simple Command 

comm:             comm_block {
                    $$ = $1;
                    } 

                | var_decl {
                     $$ = NULL;
                    }

                | attrib_comm	{
                    $$ = $1;
                    }

                | func_call{
                    $$ = $1;
                    }

                | ret_comm{
                    $$ = $1;
                    }

                | flux_ctrl{
                    $$ = $1;
                    } 
                ;

var_decl:         type id_list {$$ = NULL;}//var_decl should not be on the ast
                ;

attrib_comm:      TK_IDENTIFICADOR '=' exp	{
                      add_child($2,$1);
                      add_child($2,$3);
                      update_label($2,"=");
                      $$ = $2;
                      }
                ;

func_call:        TK_IDENTIFICADOR '(' arg_list ')' {
                      add_child($1,$3);
                      char *funcName = calloc(
                        1,sizeof(char) * (strlen(
                          $1->lex_val->tk_value) + 5 * sizeof(
                            char)));
                      strcpy(funcName, "call ");
                      strcat(funcName, $1->lex_val->tk_value);
                      update_label($1,funcName); $$ = $1;
                      }

                | TK_IDENTIFICADOR '(' ')' {
                      $$ = $1;
                      }
                ;

flux_ctrl:        TK_PR_IF '(' exp ')' comm_block TK_PR_ELSE comm_block {
                  update_label($1,"if");
                  add_child($1,$3);
                  if($5 != NULL) {
                    add_child($1,$5);
                    node_stack_pop(&head);
                  }
                  if($7 != NULL) {
                    add_child($1,$7);
                    node_stack_pop(&head);
                  }
                  $$ = $1;
                  }
                | TK_PR_IF '(' exp ')' comm_block {
                  update_label($1,"if");
                  add_child($1,$3);
                  if($5 != NULL) {
                    add_child($1,$5);
                    node_stack_pop(&head);
                  };
                  $$ = $1;
                  }
                | TK_PR_WHILE '(' exp ')' comm_block {
                  update_label($1,"while");
                  add_child($1,$3);
                  if($5 != NULL) {
                    add_child($1,$5);
                    node_stack_pop(&head);
                  };
                  $$ = $1;}
                ;

// 3.5 Expressions

exp:              or_exp {
                    $$ = $1;
                    }
                ;

or_exp:           or_exp TK_OC_OR and_exp {
                    add_child($2,$1);
                    add_child($2,$3);
                    update_label($2,"|");
                    $$ = $2;
                    }

                | and_exp{
                    $$ = $1;
                    }
                ;

and_exp:          and_exp TK_OC_AND eq_exp{
                    add_child($2,$1);
                    add_child($2,$3);
                    update_label($2,"&");
                    $$ = $2;
                    }

                | eq_exp{
                      $$ = $1;
                      }
                ;

eq_exp:           eq_exp TK_OC_EQ comp_exp{
                    add_child($2,$1);
                    add_child($2,$3);
                    update_label($2,"==");
                    $$ = $2;
                    }

                | eq_exp TK_OC_NE comp_exp{
                    add_child($2,$1);
                    add_child($2,$3);
                    update_label($2,"!=");
                    $$ = $2;
                    }

                | comp_exp{$$ = $1;}
                ;

comp_exp:         comp_exp '<' sum_exp{
                    add_child($2,$1);
                    add_child($2,$3);
                    update_label($2,"<");
                    $$ = $2;
                    }

                | comp_exp '>' sum_exp{
                    add_child($2,$1);
                    add_child($2,$3);
                    update_label($2,">");
                    $$ = $2;
                    }

                | comp_exp TK_OC_LE sum_exp{
                    add_child($2,$1);
                    add_child($2,$3);
                    update_label($2,"<=");
                    $$ = $2;
                    }

                | comp_exp TK_OC_GE sum_exp{
                    add_child($2,$1);
                    add_child($2,$3);
                    update_label($2,">=");
                    $$ = $2;
                    }

                | sum_exp{$$ = $1;}
                ;

sum_exp:          sum_exp '+' mult_exp{
                    add_child($2,$1);
                    add_child($2,$3);
                    update_label($2,"+");
                    $$ = $2;
                    }

                | sum_exp '-' mult_exp{
                    add_child($2,$1);
                    add_child($2,$3);
                    update_label($2,"-");
                    $$ = $2;
                    }

                | mult_exp{
                      $$ = $1;
                      }
                ;

mult_exp:         mult_exp '*' un_exp{
                    add_child($2,$1);
                    add_child($2,$3);
                    update_label($2,"*");
                    $$ = $2;
                    }

                | mult_exp '/' un_exp{
                    add_child($2,$1);
                    add_child($2,$3);
                    update_label($2,"/");
                    $$ = $2;
                    }

                | mult_exp '%' un_exp{
                    add_child($2,$1);
                    add_child($2,$3);
                    update_label($2,"%");
                    $$ = $2;
                    }

                | un_exp{
                    $$ = $1;
                    }
                ;

un_exp:           '-' un_exp{
                    add_child($1, $2);
                    update_label($1,"-");
                    $$ = $1;
                    }

                | '!' un_exp{add_child($1, $2);
                    update_label($1,"!");
                    $$ = $1;
                    }

                | operand{
                    $$ = $1;
                    }
                ;

operand:          TK_IDENTIFICADOR{
                    $$ = $1;
                    }

                | lit{
                    $$ = $1;
                    }

                | func_call {
                    $$ = $1;
                    }

                | '(' exp ')'{
                    $$ = $2;
                    }
                ;

// Misc: Types, Literals and Identifiers

id_list:          TK_IDENTIFICADOR {
                    update_label($1,$1->lex_val->tk_value);
                    $$ = $1;
                    }

                | id_list ';' TK_IDENTIFICADOR {
                    update_label($3,$3->lex_val->tk_value);
                    add_child($1, $3);
                    $$ = $1;
                    }
                ;

lit:              TK_LIT_INT{
                    $$ = $1;
                    }

                | TK_LIT_FLOAT{
                    $$ = $1;
                    }

                | TK_LIT_FALSE{
                    $$ = $1;
                    }

                | TK_LIT_TRUE{
                    $$ = $1;
                    }
                ;


type:             TK_PR_INT {
                    NULL;
                    }

                | TK_PR_FLOAT{
                    NULL;
                    }

                | TK_PR_BOOL{
                    NULL;
                    }
                ;
%%

void yyerror (char const *mensagem){
fprintf (stderr, "%s line: %d\n", mensagem, get_line_number());
}

