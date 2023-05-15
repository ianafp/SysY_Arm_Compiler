#include"translate/ir_generator.h"
void  Program::LValAST(LValAST* lval,BaseIRT* &ir){
    std::string LvalName = *lval->VarIdent;
    // check if valid symbol
    Symbol* sym = SymbolTable::FindSymbol(LvalName);
    if(sym==NULL){
        DLOG(ERROR)<<"Undefiled Left Value "<<LvalName<<"\n";
        exit(-1);
    }
}
void Program::AssignTranslater(AssignAST* assign,BaseIRT* &ir){

}