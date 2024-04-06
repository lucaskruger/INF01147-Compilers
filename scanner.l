%{
#include <stdio.h>
#include "tokens.h"
%}

%option yylineno
%x BLOCK_COMMENT
LETTER	[a-z]
DIGIT	[0-9]

%%
int 	{return TK_PR_INT;}
float 	{return TK_PR_FLOAT;}
bool 	{return TK_PR_BOOL;}
if 		{return TK_PR_IF;}
else 	{return TK_PR_ELSE;}
while 	{return TK_PR_WHILE;}
return 	{return TK_PR_RETURN;}
{DIGIT}+	{return TK_LIT_INT;}
{DIGIT}+\.{DIGIT}+	{return TK_LIT_FLOAT;}
true	{return TK_LIT_TRUE;}
false	{return TK_LIT_FALSE;}
"<="	{return TK_OC_LE;}
">="	{return TK_OC_GE;}
"=="	{return TK_OC_EQ;}
"!="	{return TK_OC_NE;}
"&"		{return TK_OC_AND;}
"|"		{return TK_OC_OR;}
[-!*/%+<>{}()=,;]	{return (int)yytext[0];}
(_|{LETTER})(_|{LETTER}|{DIGIT})*	{return TK_IDENTIFICADOR;}
"//"(.)*\n	
<INITIAL>"/*"	{BEGIN(BLOCK_COMMENT);}
<BLOCK_COMMENT>"*/" {BEGIN(INITIAL);}
<BLOCK_COMMENT>.|\n
\n|" "|\t
.		{return TK_ERRO;}
%%

int get_line_number(void){
	return yylineno;
}

