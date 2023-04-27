%code requires {
  #include <memory>
  #include <string>
  #include "headers/ast.h"
}

%{
#include <iostream>
#include <memory>
#include <string>
#include "headers/ast.h"
#include "headers/position.h"
extern pos_t cur_pos;
BaseAST *root;
using namespace std;
int yylex(void);
void yyerror(char *str);
%}



%union {
  std::string *str_val;
  int int_val;
  BaseAST* ast_val;
}

// lexer 返回的所有 token 种类的声明
// 注意 IDENT 和 INT_CONST 会返回 token 的值, 分别对应 str_val 和 int_val
%token INT BOOL VOID IF ELSE WHILE BREAK MAIN CONTINUE RETURN CONST
%token <str_val> IDENT
%token <int_val> INT_CONST

// 非终结符的类型定义, 
// the type definition here means the type of the value returned 
// when parsing of this non-terminal is over.
%type <ast_val> CompUnit Decl ConstDecl BType ConstDef ConstInitVal VarDecl VarDef InitVal
FuncType FuncFParams FuncFParam Block BlockItem Stmt Exp Cond LVal PrimaryExp UnaryExp UnaryOp 
FuncRParams MulExp AddExp RelExp EqExp LAndExp LOrExp ConstExp  Constdecl FuncDef
%type <int_val> Number
%start CompUnit
%%
    CompUnit: CompUnit Decl {
        auto ast = reinterpret_cast<CompUnitAST*>($1);
        ast->decl_list.push_back($2);
        root = ast;
        $$ = ast;
        $$->position.line = cur_pos.line; $$->position.column = cur_pos.column;
    }
  | CompUnit FuncDef {
        auto ast = reinterpret_cast<CompUnitAST*>($1);
        ast->decl_list.push_back($2);
        root = ast;
        $$ = ast;
        $$->position.line = cur_pos.line; $$->position.column = cur_pos.column;
    }
  | Decl {
        auto ast = new CompUnitAST();
        ast->decl_list.push_back($1);
        root = ast;
        $$ = ast;
        $$->position.line = cur_pos.line; $$->position.column = cur_pos.column;
  }
  | FuncDef{
        auto ast = new CompUnitAST();
        ast->decl_list.push_back($1);
        root = ast;
        $$ = ast;
        $$->position.line = cur_pos.line; $$->position.column = cur_pos.column;
  }
  ;

        Decl: ConstDecl {
          auto ast = new DeclAST();
          ast->const_or_var_decl = $1;
          $$ = ast;
          $$->position.line = cur_pos.line; $$->position.column = cur_pos.column;
          }
            | VarDecl{
          auto ast = new DeclAST();
          ast->const_or_var_decl = $1;
          $$ = ast;
          $$->position.line = cur_pos.line; $$->position.column = cur_pos.column;
            }
            ;
   ConstDecl: Constdecl ';' {}
            ;
    Constdecl: CONST BType ConstDef {}
            | Constdecl ',' ConstDef {}
            ;
       BType: INT {}
            | BOOL {}
            ;
    ConstDef: Constdef '=' ConstInitVal  {}
            ;
    Constdef: IDENT  {}
            | Constdef '[' ConstExp ']' {}
            ;
ConstInitVal: ConstExp {}
            | '{' '}' {}
            | '{' Constinitval '}' {}
            ;
Constinitval: ConstInitVal {}
            | Constinitval ',' ConstInitVal {}
            ;
     VarDecl: Vardecl ',' {}
            ;
     Vardecl: BType VarDef {}
            | Vardecl ',' VarDef {}
            ;
      VarDef: Vardef {}
            | Vardef '=' InitVal {}
            ;
      Vardef: IDENT  {}
            | Vardef '[' Exp ']' {}
            ;
     InitVal: Exp {}
            | '{' '}' {}
            | '{' Initval '}' {}
            ;
     Initval: InitVal {}
            | Initval ',' InitVal {}
            ;   
     FuncDef: FuncType IDENT '(' ')' Block {}
            | FuncType IDENT '(' FuncFParams ')' Block {}
            ;
    FuncType: INT  {}
    | VOID  {}
    | BOOL {}
            ;
 FuncFParams: FuncFParam {}
            | FuncFParams ',' FuncFParam {}
            ;
  FuncFParam: BType IDENT {}
            | Funcfparam {}
            ;
  Funcfparam: BType IDENT '[' ']' {}
            | Funcfparam '[' Exp ']'         {}
            ;
       Block: '{' block '}' {}
            ;
       block: BlockItem {}
            | block BlockItem {}
            ;
   BlockItem: Decl {}
            | Stmt {}
            ;
        Stmt: LVal '=' Exp ';' {}
            | Exp ';' {}
            | Block {}
            | IF '(' Cond ')' Stmt {}
            | IF '(' Cond ')' Stmt ELSE Stmt {}
            | WHILE '(' Cond ')' Stmt {}
            | BREAK ';' {}
            | CONTINUE ';' {}
            | RETURN ';' {}
            | RETURN Exp ';' {}
            ;
         Exp: AddExp {}
            ;
        Cond: LOrExp {}
            ;
        LVal: IDENT {}
            | LVal '[' Exp ']' {}
            ;
  PrimaryExp: '(' Exp ')' {}
            | LVal {}
            | Number {}
            ;
      Number: INT_CONST {}
            ;
    UnaryExp: PrimaryExp {}
            | IDENT '(' ')' {}
            | IDENT '(' FuncRParams ')' {}
            | UnaryOp UnaryExp {}
            ;
     UnaryOp: '+' {}
            | '-' {}
            | '!' {}
            ;
 FuncRParams: Exp {}
            | FuncRParams ',' Exp {}
            ;
      MulExp: UnaryExp {}
            | MulExp '*' UnaryExp {}
            | MulExp '/' UnaryExp {}
            | MulExp '%' UnaryExp {}
            ;
      AddExp: MulExp {}
            | AddExp '+' MulExp {}
            | AddExp '-' MulExp {}
            ;
      RelExp: AddExp {}
            | RelExp '<' AddExp {}
            | RelExp '>' AddExp {}
            | RelExp '<''=' AddExp {}
            | RelExp '>''=' AddExp {}
            ;
       EqExp: RelExp {}
            | EqExp '=' RelExp {}
            | EqExp '!' '=' RelExp {}
            ;
     LAndExp: EqExp {}
            | LAndExp '&' '&' EqExp {}
            ;
      LOrExp: LAndExp {}
            | LOrExp '|' '|' LAndExp {}
            ;
    ConstExp: AddExp {}
            ;
      
    

%%
void yyerror(char *str){
    fprintf(stderr,"error:%s\n",str);
}

int yywrap(){
    return 1;
}
int main()
{
    
    yyparse();
}
