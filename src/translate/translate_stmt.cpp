#include"translate/ir_generator.h"
void  Program::LValTranslater(LValAST* lval,BaseIRT* &ir){
    std::string LvalName = *lval->VarIdent;
    // get var ir label name
    Symbol* sym = lval->LValSym;
    LvalName = sym->GetLabelStr(LvalName);
    if(sym->SymbolType == SymType::INT32){
        ir = new MemIRT(new ExpIRT(new NameIRT(LvalName)));
    }
    else if(sym->SymbolType == SymType::Int32Array){
        // get offset
        std::vector<int> &dim = sym->ArrAttributes->ArrayDimVec;
        if(lval->IndexVec.size()!=sym->ArrAttributes->ArrayDimVec.size()){
            LOG(ERROR)<<"Array Index of "<<*lval->VarIdent <<" mismatch dimension\n";
            exit(-1);
        }
        int base = 1;
        BaseIRT* LastIndex;
        this->logic_exp_dealer(lval->IndexVec[lval->IndexVec.size()-1],LastIndex);
        ExpIRT* offset = reinterpret_cast<ExpIRT*>(LastIndex);
        for(int i = lval->IndexVec.size()-2;i>-1;i--){
            base *= dim[i];
            BaseIRT* indexExp;
            this->logic_exp_dealer(lval->IndexVec[i],indexExp);
            ExpIRT* additem = new ExpIRT(new ConstIRT(base<<2));
            additem = new ExpIRT(new BinOpIRT(BinOpKind::mul,additem,reinterpret_cast<ExpIRT*>(indexExp)));
            offset = new ExpIRT(new BinOpIRT(BinOpKind::plus,additem,offset));
        }
        NameIRT* ident = new NameIRT(sym->GetLabelStr(*lval->VarIdent));
        ir = new MemIRT(new ExpIRT(new BinOpIRT(BinOpKind::plus,new ExpIRT(ident),offset)));
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
    Program::logic_exp_dealer(assign->ValueExp,ExpIr);
    ir =  new StatementIRT(new MoveIRT(reinterpret_cast<MemIRT*>(LvalIr),reinterpret_cast<ExpIRT*>(ExpIr)));
}