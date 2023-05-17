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
    LvalName = sym->GetLabelStr(LvalName);
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
void Program::AssignTranslater(AssignAST* assign, BaseIRT* &ir){
    BaseIRT* ExpIr,*LvalIr;
    Program::LValTranslater(reinterpret_cast<LValAST*>(assign->LVal),LvalIr);
    Program::add_exp_dealer(assign->ValueExp,ExpIr);
    ir = new MoveIRT(reinterpret_cast<MemIRT*>(LvalIr),reinterpret_cast<ExpIRT*>(ExpIr));
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
void Program::BranchTranslater(StmtAST* stmt_available, BaseIRT* &ir, bool has_else){
    if (!has_else){
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
    } else {
        assert(stmt_available->ret_exp == nullptr); // not used in If statement
        assert(stmt_available->cond_exp != nullptr && stmt_available->stmt_if != nullptr && stmt_available->stmt_else != nullptr);
        DLOG(WARNING) << "If else statement";
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
        LabelIRT* else_label = new LabelIRT(std::string("else"));
        ir = new StatementIRT(StmKind::Cjump, new CjumpIRT(opkind, leftExp, rightExp, if_block, else_label));
    }
}