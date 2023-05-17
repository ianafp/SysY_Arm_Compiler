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
void Program::AssignTranslater(AssignAST* assign, BaseIRT* &ir){
    BaseIRT* ExpIr,*LvalIr;
    Program::LValTranslater(reinterpret_cast<LValAST*>(assign->LVal),LvalIr);
    Program::logic_exp_dealer(assign->ValueExp,ExpIr);
    ir =  new StatementIRT(new MoveIRT(reinterpret_cast<MemIRT*>(LvalIr),reinterpret_cast<ExpIRT*>(ExpIr)));
}
void Program::BranchConditionJudge(ExpIRT* ir_condition_exp, ExpIRT* &leftExp, ExpIRT* &rightExp, BinOpKind &opkind){
    if (ir_condition_exp->ContentKind == ExpKind::BinOp) {
        // condition expression with two sides
        BinOpIRT* ir_condition_binop = reinterpret_cast<BinOpIRT* >(ir_condition_exp->ExpContent);
        if (ir_condition_binop != nullptr) {
            opkind = ir_condition_binop->OpKind;
            leftExp = ir_condition_binop->LeftExp;
            rightExp = ir_condition_binop->RightExp;
        } else {
            DLOG(ERROR) << "Haven't implement error handling.";
        }
    } else {
        // condition expresssion with only one side, now we need to add one side
        assert(ir_condition_exp->ContentKind == ExpKind::Const);
        ExpIRT* zero_irt = new ExpIRT(new ConstIRT(0));
        opkind = BinOpKind::IsNe;
        leftExp = reinterpret_cast<ExpIRT *>(ir_condition_exp->ExpContent);
        rightExp = zero_irt;
    }
}
void Program::BranchTranslater(StmtAST* stmt_available, BaseIRT* &ir){
    assert(stmt_available->ret_exp == nullptr); // not used in If statement
    assert(stmt_available->stmt_else == nullptr); // here the else statement block should not be used.
    assert(stmt_available->cond_exp != nullptr && stmt_available->stmt_if != nullptr);
    DLOG(WARNING) << "If statement";
    DLOG(WARNING) << stmt_available->cond_exp->type();
    // the type is LOrExpAST
    LOrExpAST* conditional_exp = reinterpret_cast<LOrExpAST *>(stmt_available->cond_exp);
    BaseIRT* ir_condition;
    // note that the ExpIRT is the type of ir_condition
    logic_exp_dealer(conditional_exp, ir_condition);
    // short circuit? haven't implemented yet. Please do not use this trait in your program.
    ExpIRT * ir_condition_exp = dynamic_cast<ExpIRT*>(ir_condition);
    DLOG(WARNING) << "Condition of IF statement is: " << ir_condition_exp->ExpDump();
    BinOpKind opkind;
    ExpIRT *leftExp = nullptr, *rightExp = nullptr;
    // use BranchConditionJudge to extract the condition of if-statement    
    BranchConditionJudge(ir_condition_exp, leftExp, rightExp, opkind);
    LabelIRT* if_block = new LabelIRT(std::string("if"));
    LabelIRT* end_label = new LabelIRT(std::string("end"));
    ir = new StatementIRT(StmKind::Cjump, new CjumpIRT(opkind, leftExp, rightExp, if_block, end_label));
}
// void Program::BranchConditionJudge(ExpIRT* ir_condition_exp, ExpIRT* &leftExp, ExpIRT* &rightExp, BinOpKind &opkind){
//     if (ir_condition_exp->ContentKind == ExpKind::BinOp) {
//         // condition expression with two sides
//         BinOpIRT* ir_condition_binop = reinterpret_cast<BinOpIRT* >(ir_condition_exp->ExpContent);
//         if (ir_condition_binop != nullptr) {
//             opkind = ir_condition_binop->OpKind;
//             leftExp = ir_condition_binop->LeftExp;
//             rightExp = ir_condition_binop->RightExp;
//         } else {
//             DLOG(ERROR) << "Haven't implement error handling.";
//         }
//     } else {
//         // condition expresssion with only one side, now we need to add one side
//         assert(ir_condition_exp->ContentKind == ExpKind::Const);
//         ExpIRT* zero_irt = new ExpIRT(new ConstIRT(0));
//         opkind = BinOpKind::IsNe;
//         leftExp = reinterpret_cast<ExpIRT *>(ir_condition_exp->ExpContent);
//         rightExp = zero_irt;
//     }
// }
// void Program::BranchTranslater(StmtAST* stmt_available, BaseIRT* &ir){
//     assert(stmt_available->ret_exp == nullptr); // not used in If statement
//     assert(stmt_available->stmt_else == nullptr); // here the else statement block should not be used.
//     assert(stmt_available->cond_exp != nullptr && stmt_available->stmt_if != nullptr);
//     DLOG(WARNING) << "If statement";
//     DLOG(WARNING) << stmt_available->cond_exp->type();
//     // the type is LOrExpAST
//     LOrExpAST* conditional_exp = reinterpret_cast<LOrExpAST *>(stmt_available->cond_exp);
//     BaseIRT* ir_condition;
//     // note that the ExpIRT is the type of ir_condition
//     logic_exp_dealer(conditional_exp, ir_condition);
//     // short circuit? haven't implemented yet. Please do not use this trait in your program.
//     ExpIRT * ir_condition_exp = dynamic_cast<ExpIRT*>(ir_condition);
//     DLOG(WARNING) << "Condition of IF statement is: " << ir_condition_exp->ExpDump();
//     BinOpKind opkind;
//     ExpIRT *leftExp = nullptr, *rightExp = nullptr;
//     // use BranchConditionJudge to extract the condition of if-statement    
//     BranchConditionJudge(ir_condition_exp, leftExp, rightExp, opkind);
//     LabelIRT* if_block = new LabelIRT(std::string("if"));
//     LabelIRT* end_label = new LabelIRT(std::string("end"));
//     ir = new StatementIRT(StmKind::Cjump, new CjumpIRT(opkind, leftExp, rightExp, if_block, end_label));
// }