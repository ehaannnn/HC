%{
    #include <stdlib.h>
    #include <stdio.h>
    #include "hc.h"
    #include "y.tab.h"
%}
alpha 		[_a-zA-Z][_a-zA-Z0-9]*
%%

"int"       {  yylval.sval = strdup(yytext); return INT; }
"char"      {  yylval.sval = strdup(yytext); return CHAR; }
"byte"      {  yylval.sval = strdup(yytext); return BYTE; }
"void"      {  yylval.sval = strdup(yytext); return VOID; }
"vector"    {  yylval.sval = strdup(yytext); return VECTOR; }

"while"     { yylval.sval = strdup(yytext); return WHILE; }
"if"        { yylval.sval = strdup(yytext); return IF; }
"return"    { yylval.sval = strdup(yytext); return RETURN; }
"else"      { yylval.sval = strdup(yytext); return ELSE; }
"main"		{ yylval.sval = strdup(yytext); return MAIN; }
"for"		{ yylval.sval = strdup(yytext); return FOR; }
"in"        { yylval.sval = strdup(yytext); return IN; }
"first"     { yylval.sval = strdup(yytext); return FIRST; }
"second"    { yylval.sval = strdup(yytext); return SECOND; }

"reverse"   { yylval.sval = strdup(yytext); return REVERSE; }
"pushback"  { yylval.sval = strdup(yytext); return PUSHBACK; }
"delete"    { yylval.sval = strdup(yytext); return DELETE; }


"//".*      {   printf("ONE LINE COMMENT\n");   }
\/\*(\/|[^\/\*]|\**[^\/\*]+)*\*+\/	{	printf("COMMENT\n");	}

[0-9]+      {   yylval.ival = atoi(yytext); return NUM; }
{alpha}    { yylval.sval = strdup(yytext); return ID; }

"+"         {   return '+'; }
"-"         {   return '-'; }
"*"         {   return '*'; }
"/"         {   return '/'; }
"%"         {   return '%'; }
"&"         {   return '&'; }
"|"         {   return '|'; }
"^"         {   return '^'; }
"~"         {   return '~'; }
"++"        { yylval.sval = strdup(yytext);  return INC; }
"--"        { yylval.sval = strdup(yytext);  return DEC; }
"<="        { yylval.sval = strdup(yytext); return LESSEQ; }
">="        { yylval.sval = strdup(yytext); return GRETEQ; }
"=="        { yylval.sval = strdup(yytext); return EQUAL; }
"!="        { yylval.sval = strdup(yytext); return NEQUAL; }
"<<"        { yylval.sval = strdup(yytext); return SHIFTL; }
">>"        { yylval.sval = strdup(yytext); return SHIFTR; }
"+="        { yylval.sval = strdup(yytext); return PLUSASSIGN; }
"-="        { yylval.sval = strdup(yytext); return MINUSASSIGN; }
"*="        { yylval.sval = strdup(yytext); return MULASSIGN; }
"/="        { yylval.sval = strdup(yytext); return DIVASSIGN; }
"%="        { yylval.sval = strdup(yytext); return REMASSIGN; }
"="         { yylval.sval = strdup(yytext); return ASSIGN; }

"("         {   return '('; }
")"         {   return ')'; }
"{"         {   return '{'; }
"}"         {   return '}'; }
"["         {   return '['; }
"]"         {   return ']'; }
":"         {   return ':'; }
";"         {   return ';'; }
","         {   return ','; }
"."         {   return '.'; }

"<"         {   return '<'; }
">"         {   return '>'; }
[ \t\r\n]		;
.            { return -1;}

%%
int yywrap() {
    return 1;
}
