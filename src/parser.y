%define parse.error verbose
%{
#include <stdio.h>
int yylex(void);
extern int get_line_number();
void yyerror (char const *mensagem){
fprintf (stderr, "%s line: %d\n", mensagem, get_line_number());
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

program:          /* empty */
                | global_var program   
                | func program    
                ;    

global_var:       type id_list ','
                ;

func:         header '{' comm_block '}'
		;

header:		  '(' par_list ')' TK_OC_OR type '/' TK_IDENTIFICADOR{$$ = $0;}
		;

par_list:	  /* empty */  	
		| par_list ';' type TK_IDENTIFICADOR {$$ = $0;}
		| type TK_IDENTIFICADOR {$$ = $0;}
		;

comm_block:	  /* empty */
	        | comm ','
	     	| comm_block  comm ','
		;

comm:  		 '{' comm_block '}'
       		| var_decl
		| attrib_comm	
		| func_call
		| ret_comm
		| flux_ctrl
		;

var_decl: 	  type id_list 
		;

attrib_comm:	  TK_IDENTIFICADOR '=' exp	{$$ = $0;}
	   	;

func_call:	  TK_IDENTIFICADOR '(' arg_list ')'{$$ = $0;}
	 	;

arg_list:	  /* empty */
		| exp ';'
		| arg_list exp
		;

ret_comm:	  TK_PR_RETURN exp{$$ = $0;}
		;

flux_ctrl:     	  TK_PR_IF '(' exp ')' '{' comm_block '}' TK_PR_ELSE '{' comm_block '}' {$$ = $0;} 
		| TK_PR_IF '(' exp ')' '{'comm_block '}' {$$ = $0;}
		| TK_PR_WHILE '(' exp ')' '{'comm_block '}' {$$ = $0;}
		;

exp: 		  exp bi_op_7 exp
   		| exp bi_op_6 exp
   		| exp bi_op_5 exp
   		| exp bi_op_4 exp
   		| exp bi_op_3 exp
   		| exp bi_op_2 exp
		| un_op_1 exp
		| operand
		;

operand:	  TK_IDENTIFICADOR{$$ = $0;}
		| lit
		| func_call
		;

un_op_1:	  '-'{$$ = $0;}
     	| '!'{$$ = $0;}
         ;


bi_op_2:   '*'{$$ = $0;}
         | '/'{$$ = $0;}
         | '%'{$$ = $0;}
         ; 

bi_op_3:   '+'{$$ = $0;}
         | '-'{$$ = $0;}
         ;

bi_op_4:   '<'{$$ = $0;}
         | '>'{$$ = $0;}
         | TK_OC_LE{$$ = $0;}
         | TK_OC_GE{$$ = $0;}
         ;

bi_op_5:   TK_OC_EQ{$$ = $0;}
         | TK_OC_NE{$$ = $0;}
         ;

bi_op_6:   TK_OC_AND{$$ = $0;}
       	;

bi_op_7:   TK_OC_OR {$$ = $0;}
	      	;

id_list:         TK_IDENTIFICADOR {$$ = $0;} 
                |id_list ';' TK_IDENTIFICADOR  
                ;

lit:		  TK_LIT_INT    {$$ = $0;}
                | TK_LIT_FLOAT  {$$ = $0;}
                | TK_LIT_FALSE  {$$ = $0;}
                | TK_LIT_TRUE   {$$ = $0;}
		;


type:             TK_PR_INT   {$$ = $0;} 
                | TK_PR_FLOAT {$$ = $0;}
                | TK_PR_BOOL  {$$ = $0;}
                ;   
%%
