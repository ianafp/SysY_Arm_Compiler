#include"translate/ir_generator.h"
void  Program::LValTranslater(LValAST* lval,BaseIRT* &ir){
    std::string LvalName = *lval->VarIdent;
    // check if valid symbol
    Symbol* sym = SymbolTable::FindSymbol(LvalName);
    if(sym==NULL){
        DLOG(ERROR)<<"Undefiled Left Value "<<LvalName<<"\n";
        exit(-1);
    }
    // get var ir label name
    LvalName = sym->SymbolName;
    if(sym->SymbolType == SymType::INT32){
        ir = new MemIRT(new ExpIRT(new NameIRT(LvalName)));
    }
    else if(sym->SymbolType == SymType::Int32Array){
        // get offset
        // depends on const exp implement
    }
    // may add more lval type
    else{
        DLOG(ERROR)<<"Illegal Left Value \n";
        exit(-1);
    }

}
void Program::AssignTranslater(AssignAST* assign,BaseIRT* &ir){
    BaseIRT* ExpIr,*LvalIr;
    Program::LValTranslater(reinterpret_cast<LValAST*>(assign->LVal),LvalIr);
    Program::add_exp_dealer(assign->ValueExp,ExpIr);
    ir = new MoveIRT(reinterpret_cast<MemIRT*>(LvalIr),reinterpret_cast<ExpIRT*>(ExpIr));
}