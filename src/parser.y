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

func:         header comm_block 
		;

header:		  '(' par_list ')' TK_OC_OR type '/' TK_IDENTIFICADOR{$$ = $0;}
			| '(' ')' TK_OC_OR type '/' TK_IDENTIFICADOR{$$ = $0;}
		;

par_list:	  par_list ';' type TK_IDENTIFICADOR {$$ = $0;}
		| type TK_IDENTIFICADOR {$$ = $0;}
		;

comm_block:	  '{' '}'	/*vírgula?*/
	     	| '{' comm_lst '}' /*vírgula?*/
		;

comm_lst:	  comm ','
	     	| comm_lst  comm ','
		;

comm:  		  comm_block 
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
			| TK_IDENTIFICADOR '(' ')'{$$ = $0;}
	 	;

arg_list: exp
		| arg_list ';' exp
		;

ret_comm:	  TK_PR_RETURN exp{$$ = $0;}
		;

flux_ctrl:     	  TK_PR_IF '(' exp ')' comm_block TK_PR_ELSE comm_block {$$ = $0;} 
		| TK_PR_IF '(' exp ')' comm_block {$$ = $0;}
		| TK_PR_WHILE '(' exp ')' comm_block {$$ = $0;}
		;

exp: 		  or_exp

or_exp:   or_exp TK_OC_OR and_exp 
		| and_exp
	      	;

and_exp:   and_exp TK_OC_AND eq_exp
		| eq_exp
       	;

eq_exp:   eq_exp TK_OC_EQ comp_exp
         | eq_exp TK_OC_NE comp_exp
		 | comp_exp
         ;

comp_exp:   comp_exp '<' sum_exp
         | comp_exp '>' sum_exp
         | comp_exp TK_OC_LE sum_exp
         | comp_exp TK_OC_GE sum_exp
		 | sum_exp
         ;

sum_exp:   sum_exp '+' mult_exp
         | sum_exp '-' mult_exp
		 | mult_exp
         ;

mult_exp:   mult_exp '*' un_exp
         | mult_exp '/' un_exp
         | mult_exp '%' un_exp
		 | un_exp
         ; 

un_exp:  '-' operand
     	| '!' operand
		| operand
         ;

operand:	  TK_IDENTIFICADOR
		| lit
		| func_call
		| '(' exp ')'
		;


id_list:         TK_IDENTIFICADOR 
                |id_list ';' TK_IDENTIFICADOR  
                ;

lit:		  TK_LIT_INT    
                | TK_LIT_FLOAT  
                | TK_LIT_FALSE  
                | TK_LIT_TRUE   
		;


type:             TK_PR_INT   
                | TK_PR_FLOAT 
                | TK_PR_BOOL  
                ;   
%%
