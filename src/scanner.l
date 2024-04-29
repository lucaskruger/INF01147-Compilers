/* Lucas Kruger e Nicolas Tesche*/

%{
#include <stdio.h>
#include <string.h>
#include "parser.tab.h"
#include "../include/ast.h"
int get_line_number(void);
%}

%option yylineno
%option noyywrap

%x BLOCK_COMMENT
LETTER	[a-z]
DIGIT	[0-9]

%%

 /*  reserved words */

int 	{return TK_PR_INT;}
float 	{return TK_PR_FLOAT;}
bool 	{return TK_PR_BOOL;}
if 	{return TK_PR_IF;}
else 	{return TK_PR_ELSE;}
while 	{return TK_PR_WHILE;}
return 	{return TK_PR_RETURN;}


 /*int and flat numbers */  

{DIGIT}+	{ return TK_LIT_INT;}
{DIGIT}*\.{DIGIT}+	{return TK_LIT_FLOAT;}


 /* booleans */

true	{return TK_LIT_TRUE;}
false	{return TK_LIT_FALSE;}


 /*binary operators */  

"<="	{return TK_OC_LE;}
">="	{return TK_OC_GE;}
"=="	{return TK_OC_EQ;}
"!="	{return TK_OC_NE;}
"&"		{return TK_OC_AND;}
"|"		{return TK_OC_OR;}


 /*returns the charact's asci number */

[-!*/%+<>{}()=,;]	{return (int)yytext[0];}
(_|{LETTER})(_|{LETTER}|{DIGIT})*	{yylval.node = create_node(create_lex_val(1,ID,strdup(yytext))); return TK_IDENTIFICADOR;} 
"//"(.)*\n	


 /*different rules for entering multiline comment mode */

<INITIAL>"/*"	{BEGIN(BLOCK_COMMENT);}
<BLOCK_COMMENT>"*/" {BEGIN(INITIAL);}
<BLOCK_COMMENT>.|\n
\n|" "|\t


 /*if it's not a id'ed by the rules above it is an error */

.		{return TK_ERRO;}
%%


 /* consults lexx line conter */    

extern int get_line_number(void){
	return yylineno;
}

