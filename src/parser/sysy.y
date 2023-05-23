%define parse.error verbose
%code requires {
  #include <memory>
  #include <string>
  #include "ast/ast.h"
  #include "common/position.h"
  #include "common/initval_tree.h"
}

%{
#include "common/initval_tree.h"
#include <iostream>
#include <memory>
#include <string>
#include "ast/ast.h"
#include "common/position.h"
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
    VarType type_val;
    int int_val;
    BaseAST *ast_val;
    std::vector<int> *int_vec_val;
    std::vector<BaseAST*> *ast_vec_val;
    InitValTree<BaseAST*>* init_val;
    InitValTree<int>* const_init_val;
}

%parse-param { BaseAST* &ast }

%token _int _void _const
%token _if _else _while _break _continue _return
%token _equal _nequal _greater _less _greater_equal _less_equal _logical_and _logical_or
%token <str_val> _identifier _string 
%token <int_val> _const_val
%type<type_val> BType
%type <ast_val> CompUnit Compunit FuncDef  Block block BlockItem Stmt FuncFParam Decl ConstDecl VarDecl Vardecl Vardef VarDef LVal Exp UnaryExp PrimaryExp Number UnaryOp AddExp MulExp RelExp EqExp LAndExp LOrExp FuncFParams  Funcfparam FuncRParams FuncDeclare Cond String
Constdecl Constdef ConstDef ConstExp
%type <init_val>  InitVal Initval ConstInitVal Constinitval

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
    Compunit: Compunit Decl
            {
                auto ast = reinterpret_cast<CompunitAST*>($1);
                ast->decl_list.push_back($2);
                root = ast;
                $$ = ast;
                $$->position.line = cur_pos.line; $$->position.column = cur_pos.column;
            }
            | Compunit FuncDef
            {
                auto ast = reinterpret_cast<CompunitAST*>($1);
                ast->decl_list.push_back($2);
                root = ast;
                $$ = ast;
                $$->position.line = cur_pos.line; $$->position.column = cur_pos.column;
            }
            | Decl
            {
                auto ast = new CompunitAST();
                ast->decl_list.push_back($1);
                root = ast;
                $$ = ast;
                $$->position.line = cur_pos.line; $$->position.column = cur_pos.column;
            }
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
                auto ast = new DeclAST();
                ast->tp = AstType::ConstDecl;
                ast->const_or_var_decl = $1;
                // ast->HandleSymbol();
                $$ = ast;
                $$->position.line = cur_pos.line; $$->position.column = cur_pos.column;
            }
            | VarDecl
            {
                auto ast = new DeclAST();
                ast->tp = AstType::VarDecl;
                ast->const_or_var_decl = $1;
                $$ = ast;
                $$->position.line = cur_pos.line; $$->position.column = cur_pos.column;
            }
            ;
   ConstDecl: Constdecl ';'{
                $$ = $1;
                $$->position.line = cur_pos.line; $$->position.column = cur_pos.column;
            }
            ;
    Constdecl: _const BType ConstDef{
                auto ast = new ConstDeclAST();
                ast->BType = $2;
                ast->ConstDefVec.push_back($3);
                $$ = ast;
                $$->position.line = cur_pos.line; $$->position.column = cur_pos.column;
            }
            | Constdecl ',' ConstDef{
                reinterpret_cast<ConstDeclAST*>($1)->ConstDefVec.push_back($3);
                $$ = $1;
                $$->position.line = cur_pos.line; $$->position.column = cur_pos.column;
            }
            ;
       BType: _int 
            {
                $$ = VarType::INT;
            }
            | _void
            {
                $$ = VarType::VOID;
            }
    ConstDef: Constdef '=' ConstInitVal
            {
                auto ast = reinterpret_cast<VarDefAST*>($1);
                // AdjustTree($3);
                ast->InitValue = $3;
                $$ = ast;
                $$->position.line = cur_pos.line; $$->position.column = cur_pos.column;
            }
            ;
    Constdef: _identifier 
            {
                auto ast = new VarDefAST();
                ast->VarIdent = $1;
                // ast->DimSizeVec = new std::vector<BaseAST*>();
                ast->InitValue = NULL;
                $$ = ast;
                $$->position.line = cur_pos.line; $$->position.column = cur_pos.column;
            }
            | Constdef '[' ConstExp ']'
            {
                auto ast = reinterpret_cast<VarDefAST*>($1);
                ast->DimSizeVec.push_back($3);
                $$ = ast;
                $$->position.line = cur_pos.line; $$->position.column = cur_pos.column;
            }
            ;
ConstInitVal: ConstExp
            {
                $$ = new InitValTree<BaseAST*>();
                $$->keys.push_back($1); 
            }
            | '{' '}'
            {
                $$ = new InitValTree<BaseAST*>(); 
            }
            | '{' Constinitval '}'{
                $$ = new InitValTree<BaseAST*>();
                $$->childs.push_back($2);
            }
            ;
Constinitval: ConstInitVal 
            {
                $$ = $1;
            }
            | Constinitval ',' ConstInitVal 
            {
                $1->childs.push_back($3);
                $$ = $1;
            }
            ;
     VarDecl: Vardecl ';' 
            {
                $$ = $1;
                $$->position.line = cur_pos.line; $$->position.column = cur_pos.column;
            }
            ;
     Vardecl: BType VarDef 
            {
                auto ast = new VarDeclAST();
                ast->BType = $1;
                ast->VarDefVec.push_back($2);
                $$ = ast;
                $$->position.line = cur_pos.line; $$->position.column = cur_pos.column;
            }
            | Vardecl ',' VarDef
            {
                auto ast = reinterpret_cast<VarDeclAST*>($1);
                ast->VarDefVec.push_back($3);
                $$ = ast;
                $$->position.line = cur_pos.line; $$->position.column = cur_pos.column;
            }
            ;
      VarDef: Vardef
            {
                $$ = $1;

                $$->position.line = cur_pos.line; $$->position.column = cur_pos.column;
            }
            | Vardef '=' InitVal
            {
                auto ast = reinterpret_cast<VarDefAST*>($1);
                // AdjustTree($3);
                 ast->InitValue = $3;
                ast->IsInited = true;
                $$ = $1;
                $$->position.line = cur_pos.line; $$->position.column = cur_pos.column;
            }
            ;
      Vardef: _identifier
            {
                auto ast = new VarDefAST();
                ast->VarIdent = $1;
                ast->InitValue = NULL;
                ast->IsInited = false;
                $$ = ast;
                
                $$->position.line = cur_pos.line; $$->position.column = cur_pos.column;
            }
            | Vardef '[' ConstExp ']'
            {

                reinterpret_cast<VarDefAST*>($1)->DimSizeVec.push_back($3);
                $$ = $1;
                $$->position.line = cur_pos.line; $$->position.column = cur_pos.column;
            }
            ;
     InitVal: Exp 
            {
                $$ = new InitValTree<BaseAST*>();
                $$->keys.push_back($1);
                
            }
            | '{' '}'
            {
                $$ = new InitValTree<BaseAST*>();
                
            }
            | '{' Initval '}'
            {
                $$ = new InitValTree<BaseAST*>();
                $$->childs.push_back($2);

            }
            ;
     Initval: InitVal
            {
                $$ = new InitValTree<BaseAST*>();
                $$->childs.push_back($1);
            }
            | Initval ',' InitVal
            {
                $1->childs.push_back($3);
                $$ = $1;
            }
            ;   
     FuncDef: BType _identifier '(' ')' Block
            {
                /*if(SymbolTable::FindSymbol(*$2)){
                    LOG(ERROR) <<"Multidefinition of function "<<*$2<<"\n";
                    exit(-1);
                }*/
                SymbolTable::EnterScope();
                auto ast = new FuncDefAST();
                ast->func_type = $1;
                ast->ident = $2;
                ast->func_fparams = nullptr;
                ast->block = $5;
                /* SymbolTable::AddSymbol(*$2,new Symbol(ValueType::INT32,std::vector<ArgsType>())); */
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            | BType _identifier '(' FuncFParams ')' Block
            {
                /*
                LOG(WARNING)<<"Function Def "<<*$2<<"\n";
                if(SymbolTable::FindSymbol(*$2)){
                    LOG(ERROR) <<"Multidefinition of function "<<*$2<<"\n";
                    exit(-1);
                }
                SymbolTable::EnterScope();
                */
                auto ast = new FuncDefAST();
                ast->func_type = $1;
                ast->ident = $2;
                ast->func_fparams = $4;
                ast->block = $6;
                /*
                std::vector<ArgsType> args;
                for(auto &it:reinterpret_cast<FuncFParamsAST*>($4)->func_fparam){
                    auto param = reinterpret_cast<FuncFParamAST*>(it);
                    args.push_back(param->tp);
                    Symbol* sym = SymbolTable::FindSymbol(*param->ident);
                    if(sym!=NULL){
                        LOG(ERROR)<<"Multidefinition of function"<<*$2<<" parameter"<<*param->ident<<"\n";
                        exit(-1);
                    }
                    if(param->tp == ArgsType::Int32){
                        sym = new Symbol(false);
                    }
                    else if(param->tp == ArgsType::Int32Array){
                        sym = new Symbol(false,param->dimension);
                    }
                    SymbolTable::AddSymbol(*param->ident,sym);
                }
                SymbolTable::AddSymbol(*$2,new Symbol(ValueType::INT32,args));
                */
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            ;

    /*FuncType: _int
            {
                auto ast = new FuncTypeAST();
                ast->type_ret = "int";
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }| _void
            {
                auto ast = new FuncTypeAST();
                ast->type_ret = "void";
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            ;*/
 FuncFParams: FuncFParam
            {
                auto ast = new FuncFParamsAST();
                ast->func_fparam.push_back($1);
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            | FuncFParams ',' FuncFParam
            {
                auto ast = reinterpret_cast<FuncFParamsAST*>($1);
                ast->func_fparam.push_back($3);
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            ;
  FuncFParam: BType _identifier
            {
                auto ast = new FuncFParamAST();
                ast->tp = ArgsType::Int32;
                ast->Btype = $1;
                ast->ident = $2;
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            | Funcfparam
            {
                auto ast = $1;
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            ;
  Funcfparam: BType _identifier '[' ']'
            {
                auto ast = new FuncFParamAST();
                ast->tp = ArgsType::Int32Array;
                ast->Btype = $1;
                ast->ident = $2;
                if(ast->EmitHighestDimFlag==true){
                    LOG(ERROR)<<"Array Parameter "<<*$2<<"Emit Too Many Dimensions\n";
                    exit(-1);
                }
                ast->EmitHighestDimFlag = true;
                ast->dimension.push_back(0);
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            | Funcfparam '[' Exp ']'
            {
                auto ast = reinterpret_cast<FuncFParamAST*>($1);
                int temp;
                if($3->GetConstVal(temp)){
                    LOG(ERROR)<<"Array Parameter "<<*reinterpret_cast<FuncFParamAST*>($1)->ident<<" Has Varieble Dimension\n";
                    exit(-1);
                }
                ast->dimension.push_back(temp);
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            ;

       Block: '{' block '}'
            {
                auto ast = new BlockAST();
                ast->block = $2;
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            | '{' '}'
            {
                auto ast = new BlockAST();
                ast->block = nullptr;
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
            {
                auto ast = new BlockItemAST();
                ast->tp="Decl";
                ast->decl_or_stmt = $1;
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            | Stmt
            {
                auto ast = new BlockItemAST();
                ast->tp = "Stmt";
                ast->decl_or_stmt = $1;
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            ;
        Stmt: LVal '=' Exp ';'
            {
                auto ast = new StmtAST();
                ast->tp = StmtType::Assign;
                auto assign = new AssignAST();
                assign->LVal = $1;
                assign->ValueExp = $3;
                ast->ret_exp = assign;
                $$ = ast;
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
            }
            | Exp ';'
            {
                auto ast = new StmtAST();
                ast->tp = StmtType::Exp;
                ast->ret_exp = $1;
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            | ';'
            {
                auto ast = new StmtAST();
                ast->tp = StmtType::Empty;
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            | Block
            {
                auto ast = new StmtAST();
                ast->tp = StmtType::Block;
                ast->ret_exp = $1;
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            |  _if '(' Cond ')'  Stmt
            {
                auto ast = new StmtAST();
                ast->tp = StmtType::If;
                ast->cond_exp = $3;
                ast->stmt_if = $5;
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            | _if '(' Cond ')' Stmt _else Stmt
            {
                auto ast = new StmtAST();
                ast->tp = StmtType::IfElse;
                ast->cond_exp = $3;
                ast->stmt_if = $5;
                ast->stmt_else = $7;
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            | _while '(' Cond ')'  Stmt
            {
                auto ast = new StmtAST();
                ast->tp = StmtType::While;
                ast->cond_exp = $3;
                ast->stmt_while = $5;
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            | _break ';'
            {
                auto ast = new StmtAST();
                ast->tp = StmtType::Break;
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            | _continue ';'
            {
                auto ast = new StmtAST();
                ast->tp = StmtType::Continue;
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            | _return ';'
            {
                auto ast = new StmtAST();
                ast->tp = StmtType::ReturnVoid;
                // ast->ret_string = "ret";
                ast->ret_exp = nullptr;
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            | _return Exp ';'
            {
                auto ast = new StmtAST();
                ast->tp = StmtType::ReturnExp;
                // ast->ret_string = "ret";
                ast->ret_exp = $2;
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            ;
         Exp: LOrExp
            {
                auto ast = new ExpAST();
                ast->lor_exp = $1;
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }           
            ;
        Cond: LOrExp
            ;
        LVal: _identifier
            {
                /*
                Symbol* sym = SymbolTable::FindSymbol(*$1);
                if(sym==NULL){
                    LOG(ERROR)<<"Undefined Varieble"<<*$1<<"\n";
                    exit(-1);
                }
                */
                auto ast = new LValAST();
                ast->VarIdent = $1;
                // ast->LValSym = sym;
                $$ = ast;
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
            }
            | LVal '[' Exp ']'
            {
                auto ast = reinterpret_cast<LValAST*>($1);
                /*
                if(ast->LValSym->SymbolType!=SymType::Int32Array){
                    LOG(ERROR)<<"Varieble "<<*(ast->VarIdent)<<" is not array\n";
                    exit(-1);
                }
                ast->IndexVec.push_back($3);
                if(ast->IndexVec.size()>ast->LValSym->ArrAttributes->ArrayDimVec.size()){
                    LOG(ERROR)<<"Array "<<*(ast->VarIdent)<<" index dimension mismatch\n";
                    exit(-1);
                }
                */
                $$ = $1;
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
            }
            ;
  PrimaryExp: '(' Exp ')'
            {
                auto ast = new PrimaryExpAST();
                ast->tp = PrimaryType::Exp;
                ast->exp = $2;
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            | LVal
            {
                auto ast = new PrimaryExpAST();
                ast->tp = PrimaryType::LVal;
                ast->lval = $1;
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            | Number
            {
                auto ast = new PrimaryExpAST();
                ast->tp = PrimaryType::Num;
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
                ast->tp = ExpType::Primary;
                ast->primary_exp = $1;
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            | _identifier '(' ')'
            {
                auto ast = new UnaryExpAST();
                ast->tp = ExpType::Call;
                ast->ident = $1;
                ast->func_rparam = nullptr;
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            | _identifier '(' FuncRParams ')'
            {
                /*
                Symbol* sym = SymbolTable::FindSymbol(*$1);
                if(sym==NULL){
                    LOG(ERROR)<<"Undefined identifier "<<*$1<<"\n";
                    exit(-1);
                }
                if(sym->SymbolType!=SymType::FuncName){
                    LOG(ERROR)<<"identifier "<<*$1<<" is not a function\n";
                    exit(-1);
                }
                if(sym->FunctionAttributes->ArgsTypeVec.size()!=reinterpret_cast<FuncRParamsAST*>($3)->exp.size()){
                    LOG(ERROR)<<"function "<<*$1<<" call args mismatch\n";
                    exit(-1);
                }
                ast -> FuncSym = sym;
                */
                auto ast = new UnaryExpAST();
                ast->tp = ExpType::Call;
                ast->ident = $1;
                ast->func_rparam = $3;
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            | UnaryOp UnaryExp
            {
                auto ast = new UnaryExpAST();
                ast->tp = ExpType::OpExp;
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
 String: _string
        {
            auto ast = new StringAST();
            ast->StringLabel = SymbolTable::AddConstString(*$1);
            delete $1;
            ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
            $$ = ast;
        }
 FuncRParams: Exp
            {
                auto ast = new FuncRParamsAST();
                ast->exp.push_back($1);
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            |
            String
            {
                auto ast = new FuncRParamsAST();
                ast->exp.push_back($1);
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            | FuncRParams ',' Exp
            {
                auto ast = reinterpret_cast<FuncRParamsAST*>($1);
                ast->exp.push_back($3);
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
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
            {
                auto ast = new RelExpAST();
                ast->add_exp.push_back($1);
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            | RelExp _less AddExp
            {
                auto ast = reinterpret_cast<RelExpAST*>($1);
                ast->add_exp.push_back($3);
                ast->op.push_back("<");
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            | RelExp _greater AddExp
            {
                auto ast = reinterpret_cast<RelExpAST*>($1);
                ast->add_exp.push_back($3);
                ast->op.push_back(">");
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            | RelExp _less_equal AddExp
            {
                auto ast = reinterpret_cast<RelExpAST*>($1);
                ast->add_exp.push_back($3);
                ast->op.push_back("<=");
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            | RelExp _greater_equal AddExp
            {
                auto ast = reinterpret_cast<RelExpAST*>($1);
                ast->add_exp.push_back($3);
                ast->op.push_back(">=");
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            ;
       EqExp: RelExp
            {
                auto ast = new EqExpAST();
                ast->rel_exp.push_back($1);
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            | EqExp _equal RelExp
            {
                auto ast = reinterpret_cast<EqExpAST*>($1);
                ast->rel_exp.push_back($3);
                ast->op.push_back("==");
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            | EqExp _nequal RelExp
            {
                auto ast = reinterpret_cast<EqExpAST*>($1);
                ast->rel_exp.push_back($3);
                ast->op.push_back("!=");
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            ;
     LAndExp: EqExp
            {
                auto ast = new LAndExpAST();
                ast->eq_exp.push_back($1);
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            | LAndExp _logical_and EqExp
            {
                auto ast = reinterpret_cast<LAndExpAST*>($1);
                ast->eq_exp.push_back($3);
                ast->op.push_back("&&");
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            ;
      LOrExp: LAndExp
            {
                auto ast = new LOrExpAST();
                ast->land_exp.push_back($1);
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            | LOrExp _logical_or LAndExp
            {
                auto ast = reinterpret_cast<LOrExpAST*>($1);
                ast->land_exp.push_back($3);
                ast->op.push_back("||");
                ast->position.line = cur_pos.line; ast->position.column = cur_pos.column;
                $$ = ast;
            }
            ;
    ConstExp: AddExp
            ;
      
    

%%
// 定义错误处理函数, 其中第二个参数是错误信息
// parser 如果发生错误 (例如输入的程序出现了语法错误), 就会调用这个函数
void yyerror(BaseAST* &ast, const char *s) {
  cerr << "error: " << s << endl;
}
