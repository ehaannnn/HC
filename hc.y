%{
  #include <cstdio>
  #include "hc.h"

  Program *root;
  int yylex();
  int yyerror(const char *msg);
%}

%union {
  char *sval;
  int ival;
  Program *pval;
}

%type <pval> program
%type <pval> function
%type <pval> mainFun
%type <pval> statementList
%type <pval> statement
%type <pval> expression
%type <pval> ifStmt loopStmt returnStmt
%type <pval> varDeclaration
%type <pval> type
%type <pval> var 
%type <pval> funCall funParam param dotOp

%token <sval> PLUSASSIGN MINUSASSIGN DIVASSIGN REMASSIGN ASSIGN MULASSIGN
%token <sval> SHIFTL SHIFTR
%token <sval> LESS GRET LESSEQ GRETEQ EQUAL NEQUAL
%token <ival> NUM
%token <sval> INC DEC
%token <sval> ID
%token <sval> INT CHAR VOID VECTOR BYTE
%token <sval> IF ELSE MAIN FOR IN WHILE
%token <sval> FIRST SECOND LENGTH REVERSE PUSHBACK DELETE
%token <sval> RETURN

%right PLUSASSIGN MINUSASSIGN DIVASSIGN REMASSIGN ASSIGN MULASSIGN
%left '<' '>' LESSEQ GRETEQ EQUAL NEQUAL
%left '+' '-'
%left '*' '/' '%'
%left '&' '|' '^' SHIFTL SHIFTR

%right UMINUS INC DEC

%%
program : function program                        { root = new SubProgram($1,$2); }
        | mainFun                                 { root = $1; }
        ;

function : type ID '(' ')' '{' statementList '}'           { $$ = new Function($1, new Id($2), $6); }
         | type ID '(' funParam ')' '{' statementList '}'  { $$ = new Function($1, new Id($2),$4 ,$7); }
         ;

mainFun : INT MAIN '(' ')' '{'  statementList '}' { $$ = new MainFunction($6); }
    ;

statementList : statement ';' statementList       { $$ = new Statement($1,$3); }
        | statement ';'                           { $$ = new Statement($1); }
        ;

statement : expression                    { $$ = $1; }
      | loopStmt                          { $$ = $1; }
      | ifStmt                            { $$ = $1; }
      | returnStmt                        { $$ = $1; }
      | varDeclaration                    { $$ = $1; }
      ;

expression : var PLUSASSIGN expression      { $$ = new AssignExpression("+=",$1,$3); }
           | var MINUSASSIGN expression     { $$ = new AssignExpression("-=",$1,$3); }
           | var MULASSIGN expression       { $$ = new AssignExpression("*=",$1,$3); }
           | var DIVASSIGN expression       { $$ = new AssignExpression("/=",$1,$3); }
           | var REMASSIGN expression       { $$ = new AssignExpression("%=",$1,$3); }
           | var ASSIGN expression          { $$ = new AssignExpression("=",$1,$3); }
           | varDeclaration ASSIGN expression {$$ = new AssignExpression("=",$1,$3);}
           | var                            { $$ = $1; }
           | expression '+' expression      { $$ = new BinExpression("+",$1,$3); }
           | expression '-' expression      { $$ = new BinExpression("-",$1,$3); }
           | expression '*' expression      { $$ = new BinExpression("*",$1,$3); }
           | expression '/' expression      { $$ = new BinExpression("/",$1,$3); }
           | expression '%' expression      { $$ = new BinExpression("%",$1,$3); }
           | expression '&' expression      { $$ = new BinExpression("&",$1,$3); }
           | expression '|' expression      { $$ = new BinExpression("|",$1,$3); }
           | expression '^' expression      { $$ = new BinExpression("^",$1,$3); } 
           | expression SHIFTL expression   { $$ = new BinExpression($2,$1,$3); }
           | expression SHIFTR expression   { $$ = new BinExpression($2,$1,$3); }
           | expression '<' expression      { $$ = new BinExpression("<",$1,$3); }
           | expression '>' expression      { $$ = new BinExpression(">",$1,$3); }
           | expression LESSEQ expression   { $$ = new BinExpression($2,$1,$3); }
           | expression GRETEQ expression   { $$ = new BinExpression($2,$1,$3); }
           | expression EQUAL expression    { $$ = new BinExpression($2,$1,$3); }
           | expression NEQUAL expression   { $$ = new BinExpression($2,$1,$3); }
           | '-' expression  %prec UMINUS   { $$ = new UnaryExpression("-",$2); }
           | INC expression                 { $$ = new UnaryExpression($1,$2); }
           | DEC expression                 { $$ = new UnaryExpression($1,$2); }
           | '~' expression  %prec UMINUS   { $$ = new UnaryExpression("~",$2); }
           | '(' expression ')'             { $$ = $2; }
           | NUM                            { $$ = new Num($1); }
           | funCall                        { $$ = $1; }
           ;

funCall : ID '(' expression ')'             { $$ = new FunCall(new Id($1),$3); }
        | ID '(' ')'                        { $$ = new FunCall(new Id($1)); }
        ;

varDeclaration : type ID                { $$ = new VarDecl($1,new Id($2));}
               | type ID '['NUM']'      { $$ = new VarDecl($1,new Id($2),new Num($4)); }
               ;

var : ID                                    { $$ = new Id($1); }
    | ID '[' NUM ']'                        { $$ = new Var(new Id($1),new Num($3)); }
    | ID '[' expression ':' expression ']'  { $$ = new Var(new Id($1),$3,$5); }
    | ID '.' dotOp                          { $$ = new Var(new Id($1),$3); }
    ;

loopStmt : FOR '(' expression ';' expression ';' expression ')' '{'  statementList '}'  { $$ = new ForExp($3,$5,$7,$10); }
       | FOR '(' expression IN var ')' '{'  statementList '}'             { $$ = new ForExp($3,$5,$8); }
       | WHILE '(' expression ')' '{'  statementList '}'                { $$ = new WhileExp($3, $6); }
       ;

ifStmt : IF '(' expression ')' '{' statementList '}'      { $$ = new IfStmt($3,$6); }
     | IF '(' expression ')' '{' statementList '}' ELSE '{' statementList '}' { $$ = new IfStmt($3,$6,$10); }
     | IF '(' expression ')' '{' statementList '}' ELSE ifStmt  { $$ = new IfStmt($3,$6,$9); }
     ;

funParam : param                          { $$ = $1; }
     | param ',' funParam                 { $$ = new FunParam($1,$3); }
     ;

param : type ID       { $$ = new Param($1,new Id($2)); }
    | type ID '[' ']' { $$ = new Param($1,new Id($2)); }  
    ;

dotOp : FIRST '(' ')'          { $$ = new DotOp($1); }
      | SECOND '(' ')'         { $$ = new DotOp($1); }
      | REVERSE '(' ')'        { $$ = new DotOp($1); }
      | LENGTH '(' ')'         { $$ = new DotOp($1); }
      | PUSHBACK '(' NUM ')'   { $$ = new DotOp($1,new Num($3)); }
      | DELETE '(' NUM ')'     { $$ = new DotOp($1,new Num($3)); }
      ;

returnStmt : RETURN              { $$ = new ReturnExp(); }
       | RETURN expression   { $$ = new ReturnExp($2); }
       ;

type  : INT                    { $$ = new Type($1); }
    | VOID                     { $$ = new Type($1); }
    | CHAR                     { $$ = new Type($1); }
    | BYTE                     { $$ = new Type($1); }
    | VECTOR '<' type '>'      { $$ = new Type($1,$3); }
    ;

%%
int main () {
  yyparse();
  printTree(root);
  return 0;
}

int yyerror(const char *s) {
    printf("Error: %s\n", s);
}