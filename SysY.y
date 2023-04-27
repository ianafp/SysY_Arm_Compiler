%code requires {
  #include <memory>
  #include <string>
}

%{
#include <stdio.h>
#include <memory>
#include <string>
int yylex(void);
void yyerror(char *);
%}

%union {
  std::string *str_val;
  int int_val;
  BaseAST *ast_val;
}

// lexer 返回的所有 token 种类的声明
// 注意 IDENT 和 INT_CONST 会返回 token 的值, 分别对应 str_val 和 int_val
%token INT BOOL VOID IF ELSE WHILE BREAK MAIN CONTINUE RETURN
%token <str_val> IDENT
%token <int_val> INT_CONST

// 非终结符的类型定义, 
// the type definition here means the type of the value returned 
// when parsing of this non-terminal is over.
%type <ast_val> CompUnit Decl ConstDecl BType ConstDef ConstInitVal VarDecl VarDef InitVal
FuncType FuncFParams FuncFParam Block BlockItem Stmt Exp Cond LVal PrimaryExp UnaryExp UnaryOp 
FuncRParams MulExp AddExp RelExp EqExp LAndExp LOrExp ConstExp 
%type <int_val> Number
%start CompUnit
%%
    CompUnit: CompUnit Decl {
        $1->
    }
            | CompUnit FuncDef
            | Decl
            | FuncDef
            ;
        Decl: ConstDecl
            | VarDecl
            ;
   ConstDecl: Constdecl _semicolon
            ;
    Constdecl: _const BType ConstDef
            | Constdecl _comma ConstDef
            ;
       BType: _int
            | _bool
            ;
    ConstDef: Constdef '=' ConstInitVal
            ;
    Constdef: _identifier 
            | Constdef _left_square_bracket ConstExp _right_square_bracket
            ;
ConstInitVal: ConstExp
            | _left_curly_bracket _right_curly_bracket
            | _left_curly_bracket Constinitval _right_curly_bracket
            ;
Constinitval: ConstInitVal
            | Constinitval _comma ConstInitVal
            ;
     VarDecl: Vardecl _semicolon
            ;
     Vardecl: BType VarDef
            | Vardecl _comma VarDef
            ;
      VarDef: Vardef
            | Vardef '=' InitVal
            ;
      Vardef: _identifier 
            | Vardef _left_square_bracket Exp _right_square_bracket
            ;
     InitVal: Exp
            | _left_curly_bracket _right_curly_bracket
            | _left_curly_bracket Initval _right_curly_bracket
            ;
     Initval: InitVal
            | Initval _comma InitVal
            ;   
     FuncDef: FuncType _identifier '(' ')' Block
            | FuncType _identifier '(' FuncFParams ')' Block
            ;
    FuncType: _int | _void | _bool
            ;
 FuncFParams: FuncFParam
            | FuncFParams _comma FuncFParam
            ;
  FuncFParam: BType _identifier
            | FuncFparam
            ;
  Funcfparam: BType _identifier _left_square_bracket _right_square_bracket
            | Funcfparam _left_square_bracket Exp _right_square_bracket        
            ;
       Block: _left_curly_bracket block _right_curly_bracket
            ;
       block: BlockItem
            | block BlockItem
            ;
   BlockItem: Decl
            | Stmt
            ;
        Stmt: LVal '=' Exp _semicolon
            | Exp _semicolon
            | _semicolon
            | Block
            | _if '(' Cond ')' Stmt
            | _if '(' Cond ')' Stmt _else Stmt
            | _while '(' Cond ')' Stmt
            | _break _semicolon
            | _continue _semicolon
            | _return _semicolon
            | _return Exp _semicolon
            ;
         Exp: AddExp
            ;
        Cond: LOrExp
            ;
        LVal: _identifier
            | LVal _left_square_bracket Exp _right_square_bracket
            ;
  PrimaryExp: '(' Exp ')'
            | LVal
            | Number
            ;
      Number: _const_val
            ;
    UnaryExp: PrimaryExp
            | _identifier '(' ')'
            | _identifier '(' FuncRParams ')'
            | UnaryOp UnaryExp
            ;
     UnaryOp: '+'
            | '-'
            | _logical_not
            ;
 FuncRParams: Exp
            | FuncRParams _comma Exp
            ;
      MulExp: UnaryExp
            | MulExp _mul UnaryExp
            | MulExp _div UnaryExp
            | MulExp _mod UnaryExp
            ;
      AddExp: MulExp
            | AddExp '+' MulExp
            | AddExp '-' MulExp
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
