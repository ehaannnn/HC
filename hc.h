#include <cstdio>
#include <string.h>
#include <vector>

class Program {
public:
	virtual void print(int lmargin) = 0;
};

class SubProgram : public Program {
public:
	virtual void print(int lmargin);
	SubProgram(Program *prog1, Program *prog2);
private:
	Program *prog1;
	Program *prog2;
};

class Function : public Program {
public:
	virtual void print(int lmargin);
	Function(Program *type, Program *id, Program *stmtList, Program *funParam);
	Function(Program *type, Program *id, Program *stmtList);
private:
	Program *type;
	Program *id;
	Program *stmtList;
	Program *funParam;
};

class MainFunction : public Program {
public:
	virtual void print(int lmargin);
	MainFunction(Program *stmtList);
private:
	Program *stmtList;
};

class Statement : public Program {
public:
	virtual void print(int lmargin);
	Statement(Program *stmt, Program *stmtList);
	Statement(Program *stmt);
private:
	Program *stmt;
	Program *stmtList;
};

class BinExpression : public Program {
public:
	BinExpression(char *op, Program *left,Program *right);
	virtual void print(int lmargin);
private:
	char *op;
	Program *left;
	Program *right;
};

class UnaryExpression : public Program {
public:
	UnaryExpression(char *op, Program *son);
	virtual void print(int lmargin);
private:
	char *op;
	Program *son;
};

class AssignExpression : public Program {
public:
	AssignExpression(char *op, Program *left, Program *right);
	virtual void print(int lmargin);
private:
	char *op;
	Program *left;
	Program *right;
};

class IfStmt : public Program {
public:
	IfStmt(Program *exp, Program *stmt1, Program *stmt2);
	IfStmt(Program *exp, Program *stmt1);
	virtual void print(int lmargin);
private:
	Program *exp;
	Program *stmt1;
	Program *stmt2;
};

class VarDecl : public Program {
public:
	VarDecl(Program *type, Program *id);
	VarDecl(Program *type, Program *id, Program *num);
	virtual void print(int lmargin);
private:
	Program *type;
	Program *id;
	Program *num;
};

class FunCall : public Program {
public:
	FunCall(Program *id, Program *exp);
	FunCall(Program *id);
	virtual void print(int lmargin);
private:
	Program *id;
	Program *exp;
};

class Type : public Program {
public:
	Type(char *type,Program *vectorType);
	Type(char *type);
	virtual void print(int lmargin);
private:
	char *type;
	Program *vectorType;
};

class Id : public Program {
public:
	Id(char *id);
	virtual void print(int lmargin);
private:
	char *id;
};

class Num : public Program {
public:
	Num(int num);
	virtual void print(int lmargin);
private:
	int num;
};

class DotOp : public Program{
public:
	DotOp(char *op,Program *num);
	DotOp(char *op);
	virtual void print(int lmargin);
private:
	char *op;
	Program *num;
};

class Var : public Program {
public:
	Var(Id *id, Num* num);
	Var(Id *id, Program *exp1, Program *exp2);
	Var(Id *id, Program* prog);
	Var(Id *id, Num *num1, Num *num2, Num *num3);
	virtual void print(int lmargin);
private:
	Id *id;
	DotOp *dotop;
	Num *num;
	Num *num1;
	Num *num2;
	Num *num3;
	Program *exp1;
	Program *exp2;
};

class ForExp : public Program {
public:
	ForExp(Program *exp1,Program *exp2,Program *exp3,Program *stmtList);
	ForExp(Program *exp1,Program *var, Program *stmtList);
	virtual void print(int lmargin);
private:
	Program *exp1;
	Program *exp2;
	Program *exp3;
	Program *stmtList;
	Program *var;
};
class WhileExp : public Program {
public:
	WhileExp(Program *exp,Program *stmtList);
	
	virtual void print(int lmargin);
private:
	Program *exp;
	Program *stmtList;
};
class FunParam : public Program {
public:
	FunParam(Program *param,Program *funParam);
	
	virtual void print(int lmargin);
private:
	Program *param;
	Program *funParam;
};
class Param : public Program {
public:
	Param(Program *type,Program *id);
	
	virtual void print(int lmargin);
private:
	Program *type;
	Program *id;
};

class ReturnExp : public Program {
public:
	ReturnExp();
	ReturnExp(Program *exp);
	virtual void print(int lmargin);
private:
	Program *exp;
};


void printTree(Program *root);
void indent(int n);
