%define parse.error detailed
%{
#include <stdio.h>
int yylex(void);
void yyerror (char const *mensagem){
fprintf (stderr, "%s\n", mensagem);
}
%}

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

programa:         /* empty */
                | global_var programa   
                | function programa    
                ;    

global_var:      type id_list ','
                ;

function:


id_list:         id
                |id';'id_list  
                ;


id:               TK_IDENTIFICADOR 
                ;
type:             int   
                | float 
                | bool  
                ;   
int:    TK_PR_INT        {$$ = $0;}
float:   TK_PR_FLOAT       {$$ = $0;}
bool:    TK_PR_BOOL    {$$ = $0;}    
%%
