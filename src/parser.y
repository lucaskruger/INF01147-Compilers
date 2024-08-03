// Lucas Kruger e Nikolas Tesche

%define parse.error verbose
//%define api.value.type {int } 
%{
#include "../include/ast.h"
#include "../include/symbol_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERR_UNDECLARED 10
#define ERR_DECLARED 11
#define ERR_VARIABLE 20
#define ERR_FUNCTION 21

entry_type scanner_data_type;

void parser_declare_identifier(symbol_table *table, char* identifier, entry_nature nature, entry_type data_type);
symbol_table_entry *parser_identifier_check(table_stack *table, char* identifier, entry_nature expected_nature);
entry_type type_inference(node_t *op1, node_t *op2);

struct id_stack{
    char *current_id;
    struct id_stack *next_id;
};

int yylex(void);
extern int get_line_number();
extern void *arvore;
void yyerror (char const *mensagem);
void yylex_destroy();

void parser_declare_identifier(symbol_table *table, char* identifier, entry_nature nature, entry_type data_type){

    if(search_symbol_table(table, identifier) != NULL){
        fprintf (stderr,"Line %d: ERROR (%d): Variable %s already declared in this scope.\n", get_line_number(), ERR_DECLARED, identifier);
        exit(ERR_DECLARED);
    }

    scanner_data_type = data_type;

    symbol_table_entry newEntry = create_table_entry(identifier, get_line_number(), nature, data_type, NULL);
    insert_symbol_table(table, newEntry);

    /*print_symbol_table(table);
    printf("\n");*/
}

// checks for ERR_UNDECLARED, ERR_VARIABLE or ERR_FUNCTION on a variable, ignores last two errors if expected_nature is -1. Returns the checked entry if it's valid
symbol_table_entry *parser_identifier_check(table_stack *table, char* identifier, entry_nature expected_nature){

    symbol_table_entry *searched_entry = search_table_stack(&table, identifier);

    if(searched_entry == NULL){
        fprintf (stderr,"Line %d: ERROR (%d): Undeclared identifier %s.\n", get_line_number(), ERR_UNDECLARED, identifier);
        exit(ERR_UNDECLARED);
    } else if(expected_nature != -1){
        if(expected_nature == FUNCTION && searched_entry->nature == IDENTIFIER){
            fprintf (stderr,"Line %d: ERROR (%d): Variable identifier %s used as function.\n", get_line_number(), ERR_VARIABLE, identifier);
            exit(ERR_VARIABLE);
        }
        if(expected_nature == IDENTIFIER && searched_entry->nature == FUNCTION){
            fprintf (stderr,"Line %d: ERROR (%d): Function identifier %s used as variable.\n", get_line_number(), ERR_FUNCTION, identifier);
            exit(ERR_FUNCTION);
        }
    }

    return searched_entry;
}

// returns an entry type based on the type_inference rules defined in the assignment
entry_type type_inference(node_t *op1, node_t *op2){

    entry_type t1 = op1->data_type;
    entry_type t2 = op2->data_type;

    if(t1 == t2){
        return t1;
    }

    if((t1 == FLOAT || t2 == FLOAT) && (t1 == INT || t2 == INT)){
        return FLOAT;
    }

    if((t1 == BOOL || t2 == BOOL) && (t1 == INT || t2 == INT)){
        return INT;
    }

    if((t1 == FLOAT || t2 == FLOAT) && (t1 == BOOL || t2 == BOOL)){
        return FLOAT;
    }
}

symbol_table globalTable = {
    .entry = {
        .identifier = NULL
    },
    .next_entry = NULL,
    .next_offset = 0
};

table_stack symbolTableStack = {
   .table = &globalTable,
   .prev_table = NULL,
};
table_stack *tableStackHead = &symbolTableStack;
table_stack *tableStackBase = &symbolTableStack;

node_s *head = NULL;

struct id_stack idStack = { .current_id = NULL, .next_id = NULL };
struct id_stack *idStackHead = &idStack;

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

func:             header comm_block cleanup_table{
                    add_child($1, $2);
                    $$ = $1;
                    }
                ;

header:    '(' new_table par_list ')' TK_OC_OR type {scanner_data_type = $6;} '/' TK_IDENTIFICADOR {
                //add_child($7,$2);
                update_label($9,$9->lex_val->tk_value);
                $$ = $9;

                symbol_table *baseTable = table_stack_base(&tableStackHead);
                parser_declare_identifier(baseTable, $9->lex_val->tk_value, FUNCTION, $6);

                }

            | '(' new_table ')' TK_OC_OR type {scanner_data_type = $5;} '/' TK_IDENTIFICADOR {
                update_label($8,$8->lex_val->tk_value);
                $$ = $8;

                symbol_table *baseTable = table_stack_base(&tableStackHead);
                parser_declare_identifier(baseTable, $8->lex_val->tk_value, FUNCTION, $5);
                }
            ;

par_list:   par_list ';' type {scanner_data_type = $3;} TK_IDENTIFICADOR {
                //add_child($1,$4);
                $$ = $1;
                parser_declare_identifier(tableStackHead->table, $5->lex_val->tk_value, IDENTIFIER, $3);
            }

            | type {scanner_data_type = $1;} TK_IDENTIFICADOR {
                $$ = $3;
                parser_declare_identifier(tableStackHead->table, $3->lex_val->tk_value, IDENTIFIER, $1);
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

comm:           new_table comm_block cleanup_table{
                    $$ = $2;
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

var_decl:         type {scanner_data_type = $1;} id_list {
                                //printf("IDs entered\n");
                                $$ = NULL;
                                do{
                                    //printf("idStackHead = %s\n", idStackHead->current_id);

                                    // create table entry from ID and insert it to table on top of stack
                                    parser_declare_identifier(tableStackHead->table, idStackHead->current_id, IDENTIFIER, $1);

                                    struct id_stack *nextHead = idStackHead->next_id;

                                    free(idStackHead->current_id);
                                    free(idStackHead);

                                    idStackHead = nextHead;
                                }
                                while(idStackHead->next_id != NULL);
                                }//var_decl should not be on the ast
                ;

attrib_comm:      TK_IDENTIFICADOR '=' exp	{
                      add_child($2,$1);
                      add_child($2,$3);
                      update_label($2,"=");
                      $$ = $2;
                      parser_identifier_check(tableStackHead, $1->lex_val->tk_value, IDENTIFIER);
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
                      parser_identifier_check(tableStackHead, $1->lex_val->tk_value, FUNCTION);
                      }

                | TK_IDENTIFICADOR '(' ')' {
                      $$ = $1;
                      parser_identifier_check(tableStackHead, $1->lex_val->tk_value, FUNCTION);
                      }
                ;

flux_ctrl:      TK_PR_IF '(' exp ')' new_table comm_block cleanup_table TK_PR_ELSE new_table comm_block cleanup_table{
                  update_label($1,"if");
                  add_child($1,$3);
                  if($6 != NULL) {
                    add_child($1,$6);
                    node_stack_pop(&head);
                  }
                  if($10 != NULL) {
                    add_child($1,$10);
                    node_stack_pop(&head);
                  }
                  $$ = $1;
                }

                | TK_PR_IF '(' exp ')' new_table comm_block cleanup_table{
                  update_label($1,"if");
                  add_child($1,$3);
                  if($6 != NULL) {
                    add_child($1,$6);
                    node_stack_pop(&head);
                  };
                  $$ = $1;
                }

                | TK_PR_WHILE '(' exp ')' new_table comm_block cleanup_table{
                  update_label($1,"while");
                  add_child($1,$3);
                  if($6 != NULL) {
                    add_child($1,$6);
                    node_stack_pop(&head);
                  };
                  $$ = $1;
                }
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
                    update_type($2, type_inference($1, $3));
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
                    update_type($2, type_inference($1, $3));
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
                    update_type($2, type_inference($1, $3));
                    $$ = $2;
                    }

                | eq_exp TK_OC_NE comp_exp{
                    add_child($2,$1);
                    add_child($2,$3);
                    update_label($2,"!=");
                    update_type($2, type_inference($1, $3));
                    $$ = $2;
                    }

                | comp_exp{$$ = $1;}
                ;

comp_exp:         comp_exp '<' sum_exp{
                    add_child($2,$1);
                    add_child($2,$3);
                    update_label($2,"<");
                    update_type($2, type_inference($1, $3));
                    $$ = $2;
                    }

                | comp_exp '>' sum_exp{
                    add_child($2,$1);
                    add_child($2,$3);
                    update_label($2,">");
                    update_type($2, type_inference($1, $3));
                    $$ = $2;
                    }

                | comp_exp TK_OC_LE sum_exp{
                    add_child($2,$1);
                    add_child($2,$3);
                    update_label($2,"<=");
                    update_type($2, type_inference($1, $3));
                    $$ = $2;
                    }

                | comp_exp TK_OC_GE sum_exp{
                    add_child($2,$1);
                    add_child($2,$3);
                    update_label($2,">=");
                    update_type($2, type_inference($1, $3));
                    $$ = $2;
                    }

                | sum_exp{$$ = $1;}
                ;

sum_exp:          sum_exp '+' mult_exp{
                    add_child($2,$1);
                    add_child($2,$3);
                    update_label($2,"+");
                    update_type($2, type_inference($1, $3));
                    $$ = $2;
                    }

                | sum_exp '-' mult_exp{
                    add_child($2,$1);
                    add_child($2,$3);
                    update_label($2,"-");
                    update_type($2, type_inference($1, $3));
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
                    update_type($2, type_inference($1, $3));
                    $$ = $2;
                    }

                | mult_exp '/' un_exp{
                    add_child($2,$1);
                    add_child($2,$3);
                    update_label($2,"/");
                    update_type($2, type_inference($1, $3));
                    $$ = $2;
                    }

                | mult_exp '%' un_exp{
                    add_child($2,$1);
                    add_child($2,$3);
                    update_label($2,"%");
                    update_type($2, type_inference($1, $3));
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
                    symbol_table_entry *entry = parser_identifier_check(tableStackHead, $1->lex_val->tk_value, IDENTIFIER);
                    update_type($1, entry->data_type);
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

                    //printf("Entering id to stack %s\n", $1->lex_val->tk_value);
                    struct id_stack *idStackEntry = malloc(sizeof(struct id_stack));
                    idStackEntry->current_id = strdup($1->lex_val->tk_value);
                    idStackEntry->next_id = idStackHead;
                    idStackHead = idStackEntry;
                    }

                | id_list ';' TK_IDENTIFICADOR {
                    update_label($3,$3->lex_val->tk_value);
                    add_child($1, $3);
                    $$ = $1;

                    //printf("Entering id to stack %s\n", $3->lex_val->tk_value);
                    struct id_stack *idStackEntry = malloc(sizeof(struct id_stack));
                    idStackEntry->current_id = strdup($3->lex_val->tk_value);
                    idStackEntry->next_id = idStackHead;
                    idStackHead = idStackEntry;
                    }
                ;

lit:              TK_LIT_INT{
                    update_type($1, INT);
                    $$ = $1;
                    }

                | TK_LIT_FLOAT{
                    update_type($1, FLOAT);
                    $$ = $1;
                    }

                | TK_LIT_FALSE{
                    update_type($1, BOOL);
                    $$ = $1;
                    }

                | TK_LIT_TRUE{
                    update_type($1, BOOL);
                    $$ = $1;
                    }
                ;


type:             TK_PR_INT {
                    $$ = INT;
                    }

                | TK_PR_FLOAT{
                    $$ = FLOAT;
                    }

                | TK_PR_BOOL{
                    $$ = BOOL;
                    }
                ;

new_table: { // initialize a new table and push it to stack
                    symbol_table *newTable;
                    initialize_symbol_table(&newTable);
                    table_stack_push(&tableStackHead, newTable);
                }

cleanup_table:  { // pop and free table
                    free_symbol_table(table_stack_pop(&tableStackHead));
                }
%%

void yyerror (char const *mensagem){
fprintf (stderr, "%s line: %d\n", mensagem, get_line_number());
}

