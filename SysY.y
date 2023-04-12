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

%union
{
    std::string *strval;
    int intval;
}

%parse-param { std::unique_ptr<std::string> &ast }

%token _int _bool _void _const
%token _if _else _while _break _continue _return _main
%token _comma _semicolon _add _sub _mul _div _mod
%token _bool _equal _nequal _greater _less _greater_equal _less_equal _logical_and _logical_not _logical_or
%token _left_curly_bracket  _left_parenthesis _left_square_bracket _right_curly_bracket _right_parenthesis _right_square_bracket
%token <strval> _identifier _string
%token <intval> _const_val

%start CompUnit
%%
    CompUnit: CompUnit Decl
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
     FuncDef: FuncType _identifier _left_parenthesis _right_parenthesis Block
            | FuncType _identifier _left_parenthesis FuncFParams _right_parenthesis Block
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
            | _if _left_parenthesis Cond _right_parenthesis Stmt
            | _if _left_parenthesis Cond _right_parenthesis Stmt _else Stmt
            | _while _left_parenthesis Cond _right_parenthesis Stmt
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
  PrimaryExp: _left_parenthesis Exp _right_parenthesis
            | LVal
            | Number
            ;
      Number: _const_val
            ;
    UnaryExp: PrimaryExp
            | _identifier _left_parenthesis _right_parenthesis
            | _identifier _left_parenthesis FuncRParams _right_parenthesis
            | UnaryOp UnaryExp
            ;
     UnaryOp: _add
            | _sub
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
            | AddExp _add MulExp
            | AddExp _sub MulExp
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
