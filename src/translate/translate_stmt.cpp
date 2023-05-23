#include"translate/ir_generator.h"
//deal with statement
void Program::stmt_dealer(StmtAST* stmt_available, BaseIRT* &ir)
{
    // Deal with Stmt
    if (stmt_available != nullptr)
    {
        // return Exp ;
        if (stmt_available->tp == StmtType::ReturnExp)
        {
            assert(stmt_available->ret_exp != nullptr);
            logic_exp_dealer(dynamic_cast<ExpAST *>(stmt_available->ret_exp)->lor_exp, ir);
            ir = new StatementIRT(StmKind::Ret, new RetIRT(ValueType::INT32, reinterpret_cast<ExpIRT *>(ir)));
        }
        // return ;
        else if (stmt_available->tp == StmtType::ReturnVoid)
        {
            assert(stmt_available->ret_exp == nullptr);
            ir = new StatementIRT(StmKind::Ret, new RetIRT(ValueType::VOID, NULL));
        }
        // if (cond) stmt_if, without else stmt_else
        else if (stmt_available->tp == StmtType::If)
        {
            BranchTranslater(stmt_available, ir, false);
        }
        // if (cond) stmt_if, else stmt_else
        else if (stmt_available->tp == StmtType::IfElse)
        {
            BranchTranslater(stmt_available, ir, true);
        }
        else if (stmt_available->tp == StmtType::While)
        {
            WhileTranslater(stmt_available, ir);
        }
        else if (stmt_available->tp == StmtType::Break)
        {
            ir = new StatementIRT(StmKind::Jump, new JumpIRT(WhileFrame::back(false)));
        }
        else if (stmt_available->tp == StmtType::Continue)
        {
            ir = new StatementIRT(StmKind::Jump, new JumpIRT(WhileFrame::back(true)));
        }
        else if (stmt_available->tp == StmtType::Exp)
        {
            assert(stmt_available->ret_exp != nullptr);
            BaseIRT *ir_exp = nullptr;
            logic_exp_dealer(stmt_available->ret_exp, ir_exp);
            ir = new StatementIRT(StmKind::Exp, ir_exp);
        }
        // to be implemented
        else if(stmt_available->tp == StmtType::Assign){
            AssignTranslater(reinterpret_cast<AssignAST*>(stmt_available->ret_exp), ir);
        }
        else if(stmt_available->tp == StmtType::Block){
            block_dealer(reinterpret_cast<BlockAST*>(stmt_available->ret_exp), ir);
        }
        // more to continue...
    }
    //Further: need to consider: what if no return here in a void function while there are exp or other stmt??
}

void  Program::LValTranslater(LValAST* lval,BaseIRT* &ir){
    std::string LvalName = *lval->VarIdent;
    // get var ir label name
    Symbol* sym = SymbolTable::FindSymbol(*lval->VarIdent);
    if(sym==NULL){
        LOG(ERROR)<<"Undefined Lval "<<*lval->VarIdent<<"\n";
        exit(-1);
    }
    LvalName = sym->GetLabelStr(LvalName);
    if(sym->SymbolType == SymType::INT32){
        ir = new MemIRT(new ExpIRT(new NameIRT(LvalName)));
    }
    else if(sym->SymbolType == SymType::Int32Array){
        // get offset
        // depends on const exp implement
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
        // assert(ir_condition_exp->ContentKind == ExpKind::Const);
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

        /* 1. first part: deal with the condition of the expression, construct the CJUMP IR tree. */
        BaseIRT* ir_cjump = nullptr; // this is used to receive the cjump ir tree.
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
        ir_cjump = new StatementIRT(StmKind::Cjump, new CjumpIRT(opkind, leftExp, rightExp, if_block, end_label));

        /* 2. deal with the label, attach the label to the IR tree */
        BaseIRT* ir_block = nullptr;
        BaseAST* stmt_if_ast = stmt_available->stmt_if;
        assert(stmt_if_ast->type() == std::string("StmtAST"));
        stmt_dealer(reinterpret_cast<StmtAST*>(stmt_if_ast), ir_block);
        if (ir_block == nullptr) {
            ir = ir_cjump;
        } else {
            // attach the if_label to the start of the block
            ir_block = new StatementIRT(StmKind::Sequence, new SequenceIRT(new StatementIRT(if_block), reinterpret_cast<StatementIRT *>(ir_block)));
            // attach the unconditional jump to the end of if block to construct a basic block
            ir_block = new StatementIRT(StmKind::Sequence, new SequenceIRT(reinterpret_cast<StatementIRT *>(ir_block), new StatementIRT(StmKind::Jump, new JumpIRT(end_label))));
            // attach the end_label to the end of the block
            ir_block = new StatementIRT(StmKind::Sequence, new SequenceIRT(reinterpret_cast<StatementIRT *>(ir_block), new StatementIRT(end_label)));
            // attach the cjump ir to the block ir
            ir = new StatementIRT(StmKind::Sequence, new SequenceIRT(reinterpret_cast<StatementIRT *>(ir_cjump), reinterpret_cast<StatementIRT*>(ir_block)));
        }
    } else {
        assert(stmt_available->ret_exp == nullptr); // not used in If statement
        assert(stmt_available->cond_exp != nullptr && stmt_available->stmt_if != nullptr && stmt_available->stmt_else != nullptr);
        DLOG(WARNING) << "If else statement";
        
        /* 1. first part: deal with the condition of the expression, construct the CJUMP IR tree. */
        BaseIRT* ir_cjump = nullptr; // this is used to receive the cjump ir tree.
        LOrExpAST* conditional_exp = reinterpret_cast<LOrExpAST *>(stmt_available->cond_exp);
        BaseIRT* ir_condition;
        // note that the ExpIRT is the type of ir_condition
        logic_exp_dealer(conditional_exp, ir_condition);
        // short circuit? haven't implemented yet. Please do not use this trait in your program.
        ExpIRT * ir_condition_exp = dynamic_cast<ExpIRT*>(ir_condition);
        DLOG(WARNING) << "Condition of IF-ELSE statement is: " << ir_condition_exp->ExpDump();
        BinOpKind opkind;
        ExpIRT *leftExp = nullptr, *rightExp = nullptr;
        // use BranchConditionJudge to extract the condition of if-statement    
        BranchConditionJudge(ir_condition_exp, leftExp, rightExp, opkind);
        LabelIRT* if_block = new LabelIRT(std::string("if"));
        LabelIRT* else_label = new LabelIRT(std::string("else"));
        LabelIRT* end_label = new LabelIRT(std::string("end"));
        ir_cjump = new StatementIRT(StmKind::Cjump, new CjumpIRT(opkind, leftExp, rightExp, if_block, else_label));
    
        /* 2. deal with the label, attach the label to the IR tree */
        BaseIRT *ir_block, *else_block;
        BaseAST *stmt_if_ast = stmt_available->stmt_if;
        BaseAST *stmt_else_ast = stmt_available->stmt_else;
        assert(stmt_if_ast->type() == std::string("StmtAST"));
        stmt_dealer(reinterpret_cast<StmtAST*>(stmt_if_ast), ir_block);
        stmt_dealer(reinterpret_cast<StmtAST*>(stmt_else_ast), else_block);
        // attach the if_label to the start of the block
        ir_block = new StatementIRT(StmKind::Sequence, new SequenceIRT(new StatementIRT(if_block), reinterpret_cast<StatementIRT *>(ir_block)));
        // attach the unconditional jump to the end of the block
        ir_block = new StatementIRT(StmKind::Sequence, new SequenceIRT(reinterpret_cast<StatementIRT *>(ir_block), new StatementIRT(StmKind::Jump, new JumpIRT(end_label))));
        // attach the else_label to the start of the else block
        else_block = new StatementIRT(StmKind::Sequence, new SequenceIRT(new StatementIRT(else_label), reinterpret_cast<StatementIRT *>(else_block)));
        // attach the unconditional jump to the end of the else block
        else_block = new StatementIRT(StmKind::Sequence, new SequenceIRT(reinterpret_cast<StatementIRT *>(else_block), new StatementIRT(StmKind::Jump, new JumpIRT(end_label))));
        // attach the end_label to the end of else block
        else_block = new StatementIRT(StmKind::Sequence, new SequenceIRT(reinterpret_cast<StatementIRT *>(else_block), new StatementIRT(end_label)));
        // attach the if block to the else block
        BaseIRT *ir_combine = new StatementIRT(StmKind::Sequence, new SequenceIRT(reinterpret_cast<StatementIRT*>(ir_block), reinterpret_cast<StatementIRT*>(else_block)));
        // attach the cjump ir to the block ir
        ir = new StatementIRT(StmKind::Sequence, new SequenceIRT(reinterpret_cast<StatementIRT *>(ir_cjump), reinterpret_cast<StatementIRT*>(ir_combine)));
    }
}

void Program::WhileTranslater(StmtAST* stmt_available, BaseIRT* &ir){
    assert(stmt_available->ret_exp == nullptr); // not used in If statement
    assert(stmt_available->cond_exp != nullptr && stmt_available->stmt_while != nullptr);
    DLOG(WARNING) << "While statement";
    LOrExpAST* conditional_exp = reinterpret_cast<LOrExpAST *>(stmt_available->cond_exp);
    BaseIRT* ir_condition;
    // note that the ExpIRT is the type of ir_condition
    logic_exp_dealer(conditional_exp, ir_condition);
    // short circuit? haven't implemented yet. Please do not use this trait in your program.
    ExpIRT * ir_condition_exp = dynamic_cast<ExpIRT*>(ir_condition);
    DLOG(WARNING) << "Condition of While statement is: " << ir_condition_exp->ExpDump();
    BinOpKind opkind;
    ExpIRT *leftExp = nullptr, *rightExp = nullptr;
    // use BranchConditionJudge to extract the condition of if-statement    
    BranchConditionJudge(ir_condition_exp, leftExp, rightExp, opkind);
    LabelIRT* entry_label = new LabelIRT(std::string("loop_entry"));
    LabelIRT* body_label = new LabelIRT(std::string("loop_body"));
    LabelIRT* end_label = new LabelIRT(std::string("loop_end"));
    ir = new StatementIRT(StmKind::Sequence, new SequenceIRT(new StatementIRT(StmKind::Lable, entry_label), new StatementIRT(StmKind::Cjump, new CjumpIRT(opkind, leftExp, rightExp, body_label, end_label))));
    ir = new StatementIRT(StmKind::Sequence, new SequenceIRT(reinterpret_cast<StatementIRT*>(ir), new StatementIRT(StmKind::Lable, body_label)));
    
    //add label in while frame
    WhileFrame::push_back(entry_label, end_label);

    BaseIRT* stmt_ir = nullptr;
    stmt_dealer(reinterpret_cast<StmtAST*>(stmt_available->stmt_while), stmt_ir);
    if(stmt_ir != nullptr)
        ir = new StatementIRT(StmKind::Sequence, new SequenceIRT(reinterpret_cast<StatementIRT*>(ir), reinterpret_cast<StatementIRT*>(stmt_ir)));
    ir = new StatementIRT(StmKind::Sequence, new SequenceIRT(reinterpret_cast<StatementIRT*>(ir), new StatementIRT(StmKind::Jump, new JumpIRT(entry_label))));
    ir = new StatementIRT(StmKind::Sequence, new SequenceIRT(reinterpret_cast<StatementIRT*>(ir), new StatementIRT(StmKind::Lable, end_label)));

    //pop label in while frame
    WhileFrame::pop_back();
}