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
if 	{ yylval.node = create_node(NULL); return TK_PR_IF;}
else 	{ yylval.node = create_node(NULL); return TK_PR_ELSE;}
while 	{ yylval.node = create_node(NULL); return TK_PR_WHILE;}
return 	{ yylval.node = create_node(NULL); return TK_PR_RETURN;}


 /*int and flat numbers */  

{DIGIT}+	{ yylval.node = create_node(create_lex_val(get_line_number(),LIT,strdup(yytext))); return TK_LIT_INT;}
{DIGIT}*\.{DIGIT}+	{ yylval.node = create_node(create_lex_val(get_line_number(),LIT,strdup(yytext))); return TK_LIT_FLOAT;}


 /* booleans */

true	{ yylval.node = create_node(create_lex_val(get_line_number(),LIT,strdup(yytext))); return TK_LIT_TRUE;}
false	{ yylval.node = create_node(create_lex_val(get_line_number(),LIT,strdup(yytext))); return TK_LIT_FALSE;}


 /*binary operators */  

"<="	{yylval.node = create_node(NULL);return TK_OC_LE;}
">="	{yylval.node = create_node(NULL);return TK_OC_GE;}
"=="	{yylval.node = create_node(NULL);return TK_OC_EQ;}
"!="	{yylval.node = create_node(NULL);return TK_OC_NE;}
"&"		{yylval.node = create_node(NULL);return TK_OC_AND;}
"|"		{yylval.node = create_node(NULL);return TK_OC_OR;}


 /*returns the ascii char as a number */

[-!*/%+<>=]	{ yylval.node = create_node(NULL); return (int)yytext[0];}
[{}(),;] { return (int)yytext[0];}
(_|{LETTER})(_|{LETTER}|{DIGIT})*  { yylval.node = create_node(create_lex_val(get_line_number(),ID,strdup(yytext))); return TK_IDENTIFICADOR;}

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

