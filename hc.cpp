#include "hc.h"
const int INDENT_LEVEL = 4;

SubProgram::SubProgram(Program *prog1, Program *prog2) {
	this->prog1 = prog1;
	this->prog2 = prog2;
}

void SubProgram::print(int lmargin) {
	this->prog1->print(lmargin+INDENT_LEVEL);
	this->prog2->print(lmargin+INDENT_LEVEL);
}

Function::Function(Program *type, Program *id, Program *stmtList, Program *funParam) {
	this->type = type;
	this->id = id;
	this->stmtList = stmtList;
	this->funParam = funParam;
}
Function::Function(Program *type, Program *id, Program *stmtList) {
	this->type = type;w
	this->id = id;
	this->stmtList = stmtList;
	this->funParam = NULL;
}

void Function::print(int lmargin) {
	this->type->print(lmargin+INDENT_LEVEL);
	this->id->print(lmargin+INDENT_LEVEL);
	this->stmtList->print(lmargin+INDENT_LEVEL);
	if (funParam!=NULL) this->funParam->print(lmargin+INDENT_LEVEL);

}

MainFunction::MainFunction(Program *stmtList) {
	this->stmtList = stmtList;
}

void MainFunction::print(int lmargin) {
	indent(lmargin);
	printf("main function\n");
	this->stmtList->print(lmargin+INDENT_LEVEL);
}

Statement::Statement(Program *stmt) {
	this->stmt = stmt;
	this->stmtList = NULL;
}
Statement::Statement(Program *stmt, Program *stmtList) {
	this->stmt = stmt;
	this->stmtList = stmtList;
}

void Statement::print(int lmargin) {
	indent(lmargin);
	printf("statement\n");
	stmt->print(lmargin+INDENT_LEVEL);
	if (stmtList!=NULL) stmtList->print(lmargin+INDENT_LEVEL);
}
BinExpression::BinExpression(char *op, Program *left,Program *right) {
	this->op = strdup(op);
	this->left = left;
	this->right = right;
}
void BinExpression::print(int lmargin) {
	indent(lmargin);
	printf("Op(%s)\n",this->op);
	this->left->print(lmargin+INDENT_LEVEL);
	this->right->print(lmargin+INDENT_LEVEL);
}

UnaryExpression::UnaryExpression(char *op, Program *son) {
	this->op = strdup(op);
	this->son = son;
}
void UnaryExpression::print(int lmargin) {
	indent(lmargin);
	printf("Op(%s)\n",this->op);
	this->son->print(lmargin+INDENT_LEVEL);
}

AssignExpression::AssignExpression(char *op, Program *left, Program *right) {
	this->op = strdup(op);
	this->left = left;
	this->right = right;
}
void AssignExpression::print(int lmargin) {
	indent(lmargin);
	printf("Op(%s)\n",this->op);
	this->left->print(lmargin+INDENT_LEVEL);
	this->right->print(lmargin+INDENT_LEVEL);
}

IfStmt::IfStmt(Program *exp, Program *stmt1, Program *stmt2) {
	this->exp = exp;
	this->stmt1 = stmt1;
	this->stmt2 = stmt2;
}

IfStmt::IfStmt(Program *exp, Program *stmt1) {
	this->exp = exp;
	this->stmt1 = stmt1;
	this->stmt2 = NULL;
}
void IfStmt::print(int lmargin) {
	this->exp->print(lmargin+INDENT_LEVEL);
	this->stmt1->print(lmargin+INDENT_LEVEL);
	if (this->stmt2!=NULL) this->stmt2->print(lmargin+INDENT_LEVEL);
}

VarDecl::VarDecl(Program *type, Program *id) {
	this->type = type;
	this->id = id;
	this->num = NULL;
}
VarDecl::VarDecl(Program *type, Program *id, Program *num) {
	this->type = type;
	this->id = id;
	this->num = num;
}
void VarDecl::print(int lmargin) {
	indent(lmargin);
	printf("variable declaration\n");
	this->type->print(lmargin+INDENT_LEVEL);
	this->id->print(lmargin+INDENT_LEVEL);
	if (num!=NULL) this->num->print(lmargin+INDENT_LEVEL);
}

FunCall::FunCall(Program *id, Program *exp) {
	this->id = id;
	this->exp = exp;
}
FunCall::FunCall(Program *id) {
	this->id = id;
	this->exp = NULL;
}

void FunCall::print(int lmargin) {
	this->id->print(lmargin+INDENT_LEVEL);
	if (this->exp!=NULL) this->exp->print(lmargin+INDENT_LEVEL);
}

Type::Type(char *type, Program *vectorType) {
	this->type = strdup(type);
	this->vectorType = vectorType;
}

Type::Type(char *type) {
	this->type = strdup(type);
	this->vectorType = NULL;
}

void Type::print(int lmargin) {
	indent(lmargin);
	printf("type(%s)\n",type);
	if (vectorType!=NULL) this->vectorType->print(lmargin+INDENT_LEVEL);
}

Id::Id(char *id) {
	this->id = strdup(id);
}

void Id::print(int lmargin) {
	indent(lmargin);
	printf("Id(%s)\n",this->id);
}


Num::Num(int num) {
	this->num = num;
}

void Num::print(int lmargin) {
	indent(lmargin);
	printf("INT(%d)\n",this->num);
}

Var::Var(Id *id, Num* num) {
	this->id = id;
	this->dotop = NULL;
	this->num = num;
	this->num1 = NULL;
	this->num2 = NULL;
	this->num3 = NULL;
	this->exp1 = NULL;
	this->exp2 = NULL;
}

Var::Var(Id *id, Program *exp1, Program *exp2) {
	this->id = id;
	this->dotop = NULL;
	this->num = NULL;
	this->num1 = NULL;
	this->num2 = NULL;
	this->num3 = NULL;
	this->exp1 = exp1;
	this->exp2 = exp2;
}
Var::Var(Id *id, Program *dotOp) {
	this->id = id;
	this->dotop = dotop;
	this->num = NULL;
	this->num1 = NULL;
	this->num2 = NULL;
	this->num3 = NULL;
	this->exp1 = exp1;
	this->exp2 = exp2;
}
Var::Var(Id *id, Num *num1, Num *num2, Num *num3) {
	this->id = id;
	this->dotop = NULL;
	this->num = NULL;
	this->num1 = num1;
	this->num2 = num2;
	this->num3 = num3;
	this->exp1 = NULL;
	this->exp2 = NULL;
}
void Var::print(int lmargin) {
	if (id!=NULL) id->print(lmargin+INDENT_LEVEL);
	if (dotop != NULL) dotop->print(lmargin+INDENT_LEVEL);
	if (num !=NULL) num->print(lmargin+INDENT_LEVEL);
	if (num1 !=NULL) num1->print(lmargin+INDENT_LEVEL);
	if (num2 !=NULL) num2->print(lmargin+INDENT_LEVEL);
	if (num3 !=NULL) num3->print(lmargin+INDENT_LEVEL);
	if (exp1 !=NULL) exp1->print(lmargin+INDENT_LEVEL);
	if (exp2 !=NULL) exp2->print(lmargin+INDENT_LEVEL);
}

ForExp::ForExp(Program *exp1,Program *exp2,Program *exp3,Program *stmtList) {
	this->exp1 = exp1;
	this->exp2 = exp2;
	this->exp3 = exp3;
	this->stmtList = stmtList;
	this->var = NULL;
}
ForExp::ForExp(Program *exp1,Program *var, Program *stmtList) {
	this->exp1 = exp1;
	this->exp2 = NULL;
	this->exp3 = NULL;
	this->stmtList = stmtList;
	this->var = var;
}
void ForExp::print(int lmargin) {
	if (exp1 !=NULL) exp1->print(lmargin+INDENT_LEVEL);
	if (exp2 != NULL) exp2->print(lmargin+INDENT_LEVEL);
	if (exp3 !=NULL) exp3->print(lmargin+INDENT_LEVEL);
	if (var !=NULL) var->print(lmargin+INDENT_LEVEL);
	if (stmtList !=NULL) stmtList->print(lmargin+INDENT_LEVEL);
}
WhileExp::WhileExp(Program *exp,Program *stmtList) {
	this->exp = exp;
	this->stmtList = stmtList;
}
void WhileExp::print(int lmargin) {
	exp->print(lmargin+INDENT_LEVEL);
	stmtList->print(lmargin+INDENT_LEVEL);
}
FunParam::FunParam(Program *param,Program *funParam=NULL) {
	this->param = param;
	if (funParam!=NULL) this->funParam = funParam;
}
void FunParam::print(int lmargin) {
	param->print(lmargin+INDENT_LEVEL);
	if (funParam!=NULL) funParam->print(lmargin+INDENT_LEVEL);
}

Param::Param(Program *type,Program *id) {
	this->type;
	this->id;
}
void Param::print(int lmargin) {
	type->print(lmargin+INDENT_LEVEL);
	id->print(lmargin+INDENT_LEVEL);
}
DotOp::DotOp(char *op,Program *num) {
	this->op = strdup(op);
	this->num = num;
}
DotOp::DotOp(char *op) {
	this->op = strdup(op);
	this->num = NULL;
}

void DotOp::print(int lmargin) {
	indent(lmargin);
	printf("dotOp(%s)\n",op);
	if (num!=NULL) num->print(lmargin+INDENT_LEVEL);
}

ReturnExp::ReturnExp() {
	this->exp = NULL;
}
ReturnExp::ReturnExp(Program *exp) {
	this->exp =exp;
}
void ReturnExp::print(int lmargin) {
	indent(lmargin);
	printf("return statement\n");
	if (exp!=NULL) exp->print(lmargin+INDENT_LEVEL);
}

void printTree(Program *root)
{
    if (root == NULL) {
    	printf("NULL\n");
    	return;
    }
    root->print(0);
}

void indent(int n)
{
    if (n > 0) {
        printf(" ");
        indent(--n);
    }
}

