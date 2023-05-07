%error-verbose
%code requires {
  #include <memory>
  #include <string>
  #include "headers/ast.h"
  #include "headers/position.h"
}

%{
#include <iostream>
#include <memory>
#include <string>
#include "headers/ast.h"
#include "headers/position.h"
BaseAST *root;
extern pos_t cur_pos;
using namespace std;

// 声明 lexer 函数和错误处理函数
int yylex();
void yyerror(BaseAST* &ast, const char *s);
%}

%union
{
    std::string *str_val;
    int int_val;
    BaseAST *ast_val;
}

%parse-param { BaseAST* &ast }

%token _int _void _const
%token _if _else _while _break _continue _return
%token _equal _nequal _greater _less _greater_equal _less_equal _logical_and _logical_or
%token <str_val> _identifier _string
%token <int_val> _const_val
%type <ast_val> CompUnit Compunit FuncDef FuncType Block block BlockItem Stmt FuncFParam Decl
%type <ast_val> Exp UnaryExp PrimaryExp Number UnaryOp AddExp MulExp
%start CompUnit
%%
    CompUnit: Compunit
            {
                auto comp_unit = new CompUnitAST;
                // this one need to be transmitted to the argument
                // thus must generate uique_ptr version of pointer.
                comp_unit->comp_unit = $1;
                comp_unit->position.line = cur_pos.line; comp_unit->position.column = cur_pos.column;
                ast = move(comp_unit);
            }
    Compunit: /*Compunit Decl
            {
                auto ast = reinterpret_cast<CompunitAST*>($1);
                ast->decl_list.push_back($2);
                root = ast;
                $$ = ast;
                $$->position.line = cur_pos.line; $$->position.column = cur_pos.column;
            }*/
            | Compunit FuncDef
            {
                auto ast = reinterpret_cast<CompunitAST*>($1);
                ast->decl_list.push_back($2);
                root = ast;
                $$ = ast;
                $$->position.line = cur_pos.line; $$->position.column = cur_pos.column;
            }
            /*| Decl
            {
                auto ast = new CompunitAST();
                ast->decl_list.push_back($1);
                root = ast;
                $$ = ast;
                $$->position.line = cur_pos.line; $$->position.column = cur_pos.column;
            }*/
            | FuncDef
            {
                auto ast = new CompunitAST();
                ast->decl_list.push_back($1);
                root = ast;
                $$ = ast;
                $$->position.line = cur_pos.line; $$->position.column = cur_pos.column;
            }
            ;
        Decl: ConstDecl
            {
                /*auto ast = new DeclAST();
                ast->const_or_var_decl = $1;
                $$ = ast;
                $$->position.line = cur_pos.line; $$->position.column = cur_pos.column;*/
            }
            | VarDecl
            {
                /*auto ast = new DeclAST();
                ast->const_or_var_decl = $1;
                $$ = ast;
                $$->position.line = cur_pos.line; $$->position.column = cur_pos.column;*/
            }
            ;
   ConstDecl: Constdecl ';'
            ;
    Constdecl: _const BType ConstDef
            | Constdecl ',' ConstDef
            ;
       BType: _int
            ;
    ConstDef: Constdef '=' ConstInitVal
            ;
    Constdef: _identifier 
            | Constdef '[' ConstExp ']'
            ;
ConstInitVal: ConstExp
            | '{' '}'
            | '{' Constinitval '}'
            ;
Constinitval: ConstInitVal
            | Constinitval ',' ConstInitVal
            ;
     VarDecl: Vardecl ';'
            ;
     Vardecl: BType VarDef
            | Vardecl ',' VarDef
            ;
      VarDef: Vardef
            | Vardef '=' InitVal
            ;
      Vardef: _identifier 
            | Vardef '[' Exp ']'
            ;
     InitVal: Exp
            | '{' '}'
            | '{' Initval '}'
            ;
     Initval: InitVal
            | Initval ',' InitVal
            ;   
     FuncDef: FuncType _identifier '(' ')' Block
            {
                auto ast = new FuncDefAST();
                ast->func_type = $1;
                ast->ident = $2;
                ast->func_fparams = nullptr;
                ast->block = $5;
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            | FuncType _identifier '(' FuncFParams ')' Block
            {
                /*auto ast = new FuncDefAST();
                ast->func_type = $1;
                ast->ident = $2;
                ast->func_fparams = $4;
                ast->block = $6;
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;*/
            }
            ;
    FuncType: _int
            {
                auto ast = new FuncTypeAST();
                ast->type_ret = "int";
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            | _void
            {
                auto ast = new FuncTypeAST();
                ast->type_ret = "void";
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            ;
 FuncFParams: FuncFParam
            | FuncFParams ',' FuncFParam
            ;
  FuncFParam: BType _identifier
            | Funcfparam
            ;
  Funcfparam: BType _identifier '[' ']'
            | Funcfparam '[' Exp ']'        
            ;
       Block: '{' block '}'
            {
                auto ast = new BlockAST();
                ast->block = $2;
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            ;
       block: BlockItem
            {
                auto ast = new blockAST();
                ast->block_item.push_back($1);
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            | block BlockItem
            {
                auto ast = reinterpret_cast<blockAST*>($1);
                ast->block_item.push_back($2);
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            ;
   BlockItem: Decl
            | Stmt
            {
                auto ast = new BlockItemAST();
                ast->decl_or_stmt = $1;
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            ;
        Stmt: LVal '=' Exp ';'
            | Exp ';'
            | ';'
            | Block
            | _if '(' Cond ')' Stmt
            | _if '(' Cond ')' Stmt _else Stmt
            | _while '(' Cond ')' Stmt
            | _break ';'
            | _continue ';'
            | _return ';'
            /*| _return _const_val ';'
            {
                //temporary!!!
                auto ast = new StmtAST();
                ast->ret_string = "ret";
                ast->ret_number = $2;
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }*/
            | _return Exp ';'
            {
                auto ast = new StmtAST();
                ast->tp = "retexp";
                ast->ret_string = "ret";
                ast->ret_exp = $2;
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            ;
         Exp: AddExp
            {
                auto ast = new ExpAST();
                ast->add_exp = $1;
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }           
            ;
        Cond: LOrExp
            ;
        LVal: _identifier
            | LVal '[' Exp ']'
            ;
  PrimaryExp: '(' Exp ')'
            {
                auto ast = new PrimaryExpAST();
                ast->tp = "exp";
                ast->exp = $2;
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            | LVal
            | Number
            {
                auto ast = new PrimaryExpAST();
                ast->tp = "number";
                ast->number = $1;
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            ;
      Number: _const_val
            {
                auto ast = new NumberAST();
                ast->num = $1;
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            ;
    UnaryExp: PrimaryExp
            {
                auto ast = new UnaryExpAST();
                ast->tp = "primary";
                ast->primary_exp = $1;
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            | _identifier '(' ')'
            | _identifier '(' FuncRParams ')'
            | UnaryOp UnaryExp
            {
                auto ast = new UnaryExpAST();
                ast->tp = "op+exp";
                ast->unary_op = $1;
                ast->unary_exp = $2;
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            ;
     UnaryOp: '+'
            {
                auto ast = new UnaryOpAST();
                ast->op = "+";
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            | '-'
            {
                auto ast = new UnaryOpAST();
                ast->op = "-";
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            | '!'
            {
                auto ast = new UnaryOpAST();
                ast->op = "!";
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            ;
 FuncRParams: Exp
            | FuncRParams ',' Exp
            ;
      MulExp: UnaryExp
            {
                auto ast = new MulExpAST();
                ast->unary_exp.push_back($1);
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            | MulExp '*' UnaryExp
            {
                auto ast = reinterpret_cast<MulExpAST*>($1);
                ast->unary_exp.push_back($3);
                ast->op.push_back("*");
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            | MulExp '/' UnaryExp
            {
                auto ast = reinterpret_cast<MulExpAST*>($1);
                ast->unary_exp.push_back($3);
                ast->op.push_back("/");
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            | MulExp '%' UnaryExp
            {
                auto ast = reinterpret_cast<MulExpAST*>($1);
                ast->unary_exp.push_back($3);
                ast->op.push_back("%");
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            ;
      AddExp: MulExp
            {
                auto ast = new AddExpAST();
                ast->mul_exp.push_back($1);
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            | AddExp '+' MulExp
            {
                auto ast = reinterpret_cast<AddExpAST*>($1);
                ast->mul_exp.push_back($3);
                ast->op.push_back("+");
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            | AddExp '-' MulExp
            {
                auto ast = reinterpret_cast<AddExpAST*>($1);
                ast->mul_exp.push_back($3);
                ast->op.push_back("-");
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            ;
      RelExp: AddExp
            | RelExp _less AddExp
            | RelExp _greater AddExp
            | RelExp _less_equal AddExp
            | RelExp _greater_equal AddExp
            ;
       EqExp: RelExp
            | EqExp _equal RelExp
            | EqExp _nequal RelExp
            ;
     LAndExp: EqExp
            | LAndExp _logical_and EqExp
            ;
      LOrExp: LAndExp
            | LOrExp _logical_or LAndExp
            ;
    ConstExp: AddExp
            ;
      
    

%%
// 定义错误处理函数, 其中第二个参数是错误信息
// parser 如果发生错误 (例如输入的程序出现了语法错误), 就会调用这个函数
void yyerror(BaseAST* &ast, const char *s) {
  cerr << "error: " << s << endl;
}
