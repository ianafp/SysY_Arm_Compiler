#include "translate/ir_generator.h"

void Program::logic_exp_dealer(BaseAST *exp, BaseIRT *&ir)
{
    // std::string return_str1("");
    // std::string return_str2("");
    BaseIRT *ir1 = new ExpIRT(), *ir2 = new ExpIRT();
    if (exp->type() == "ExpAST")
    {
        ExpAST *Exp = dynamic_cast<ExpAST *>(exp);
        assert(Exp->lor_exp != nullptr);
        logic_exp_dealer(Exp->lor_exp, ir);
    }
    if (exp->type() == "LOrExpAST")
    {
        // std::cout << "in logic" << std::endl;
        LOrExpAST *lor_exp = dynamic_cast<LOrExpAST *>(exp);
        if (lor_exp->land_exp.size() == 0)
            return;
        logic_exp_dealer(lor_exp->land_exp[0], ir1);
        for (int i = 0; i < lor_exp->op.size(); i++)
        {
            assert(i + 1 < lor_exp->land_exp.size());
            logic_exp_dealer(lor_exp->land_exp[i + 1], ir2);
            assert(lor_exp->op[i] == "||");
            BinOpIRT *or_exp = new BinOpIRT(BinOpKind::LogicOr, reinterpret_cast<ExpIRT *>(ir1), reinterpret_cast<ExpIRT *>(ir2));
            ir1 = new ExpIRT(ExpKind::BinOp, or_exp);
        }
        ir = ir1;
    }
    else if (exp->type() == "LAndExpAST")
    {
        // std::cout << "in logic and" << std::endl;
        LAndExpAST *land_exp = dynamic_cast<LAndExpAST *>(exp);
        if (land_exp->eq_exp.size() == 0)
            return;
        logic_exp_dealer(land_exp->eq_exp[0], ir1);
        for (int i = 0; i < land_exp->op.size(); i++)
        {
            assert(i + 1 < land_exp->eq_exp.size());
            logic_exp_dealer(land_exp->eq_exp[i + 1], ir2);
            assert(land_exp->op[i] == "&&");
            BinOpIRT *and_exp = new BinOpIRT(BinOpKind::LogicAnd, reinterpret_cast<ExpIRT *>(ir1), reinterpret_cast<ExpIRT *>(ir2));
            ir1 = new ExpIRT(ExpKind::BinOp, and_exp);
        }
        ir = ir1;
    }
    else if (exp->type() == "EqExpAST")
    {
        // std::cout << "in eq" << std::endl;
        EqExpAST *eq_exp = dynamic_cast<EqExpAST *>(exp);
        if (eq_exp->rel_exp.size() == 0)
            return;
        logic_exp_dealer(eq_exp->rel_exp[0], ir1);
        for (int i = 0; i < eq_exp->op.size(); i++)
        {
            assert(i + 1 < eq_exp->rel_exp.size());
            logic_exp_dealer(eq_exp->rel_exp[i + 1], ir2);
            BinOpIRT *eq = nullptr;
            if (eq_exp->op[i] == "==")
                eq = new BinOpIRT(BinOpKind::IsEqual, reinterpret_cast<ExpIRT *>(ir1), reinterpret_cast<ExpIRT *>(ir2));
            else if (eq_exp->op[i] == "!=")
                eq = new BinOpIRT(BinOpKind::IsNe, reinterpret_cast<ExpIRT *>(ir1), reinterpret_cast<ExpIRT *>(ir2));
            ir1 = new ExpIRT(ExpKind::BinOp, eq);
        }
        ir = ir1;
    }
    else if (exp->type() == "RelExpAST")
    {
        // std::cout << "in rel" << std::endl;
        RelExpAST *rel_exp = dynamic_cast<RelExpAST *>(exp);
        if (rel_exp->add_exp.size() == 0)
            return;
        add_exp_dealer(rel_exp->add_exp[0], ir1);
        for (int i = 0; i < rel_exp->op.size(); i++)
        {
            assert(i + 1 < rel_exp->add_exp.size());
            add_exp_dealer(rel_exp->add_exp[i + 1], ir2);
            BinOpIRT *add = nullptr;
            if (rel_exp->op[i] == "<")
                add = new BinOpIRT(BinOpKind::IsLt, reinterpret_cast<ExpIRT *>(ir1), reinterpret_cast<ExpIRT *>(ir2));
            else if (rel_exp->op[i] == ">")
                add = new BinOpIRT(BinOpKind::IsGt, reinterpret_cast<ExpIRT *>(ir1), reinterpret_cast<ExpIRT *>(ir2));
            else if (rel_exp->op[i] == "<=")
                add = new BinOpIRT(BinOpKind::IsLe, reinterpret_cast<ExpIRT *>(ir1), reinterpret_cast<ExpIRT *>(ir2));
            else if (rel_exp->op[i] == ">=")
                add = new BinOpIRT(BinOpKind::IsGe, reinterpret_cast<ExpIRT *>(ir1), reinterpret_cast<ExpIRT *>(ir2));
            ir1 = new ExpIRT(ExpKind::BinOp, add);
        }
        ir = ir1;
    }
}

void Program::add_exp_dealer(BaseAST *exp, BaseIRT *&ir)
{
    BaseIRT *ir1 = new ExpIRT(), *ir2 = new ExpIRT();
    if (exp->type() == "AddExpAST")
    {
        AddExpAST *add_exp = dynamic_cast<AddExpAST *>(exp);
        if (add_exp->mul_exp.size() == 0)
            return;
        BinOpIRT *add = nullptr;
        add_exp_dealer(add_exp->mul_exp[0], ir1);
        for (int i = 0; i < add_exp->op.size(); i++)
        {
            assert(i + 1 < add_exp->mul_exp.size());
            add_exp_dealer(add_exp->mul_exp[i + 1], ir2);
            if (add_exp->op[i] == "+")
                add = new BinOpIRT(BinOpKind::plus, reinterpret_cast<ExpIRT *>(ir1), reinterpret_cast<ExpIRT *>(ir2));
            else if (add_exp->op[i] == "-")
                add = new BinOpIRT(BinOpKind::minus, reinterpret_cast<ExpIRT *>(ir1), reinterpret_cast<ExpIRT *>(ir2));
            ir1 = new ExpIRT(ExpKind::BinOp, add);
        }

        ir = ir1;
    }
    else if (exp->type() == "MulExpAST")
    {
        MulExpAST *mul_exp = dynamic_cast<MulExpAST *>(exp);
        if (mul_exp->unary_exp.size() == 0)
            return;
        BinOpIRT *mul = nullptr;
        unary_exp_dealer(mul_exp->unary_exp[0], ir1);
        for (int i = 0; i < mul_exp->op.size(); i++)
        {
            assert(i + 1 < mul_exp->unary_exp.size());
            unary_exp_dealer(mul_exp->unary_exp[i + 1], ir2);
            if (mul_exp->op[i] == "*")
                mul = new BinOpIRT(BinOpKind::mul, reinterpret_cast<ExpIRT *>(ir1), reinterpret_cast<ExpIRT *>(ir2));
            else if (mul_exp->op[i] == "/")
                mul = new BinOpIRT(BinOpKind::_div, reinterpret_cast<ExpIRT *>(ir1), reinterpret_cast<ExpIRT *>(ir2));
            else if (mul_exp->op[i] == "%")
                mul = new BinOpIRT(BinOpKind::rem, reinterpret_cast<ExpIRT *>(ir1), reinterpret_cast<ExpIRT *>(ir2));
            ir1 = new ExpIRT(ExpKind::BinOp, mul);
        }
        ir = ir1;
    }
}

void Program::unary_exp_dealer(BaseAST *exp, BaseIRT *&ir)
{
    // scan all of the exp
    UnaryExpAST *unary_exp = nullptr;
    // identify the type
    if (exp->type() == "UnaryExpAST")
    {
        unary_exp = dynamic_cast<UnaryExpAST *>(exp);
    }
    // deal with the ast
    if (unary_exp->tp == ExpType::Primary)
    {
        if (unary_exp->primary_exp != nullptr)
        {
            PrimaryExpAST *primary_exp = dynamic_cast<PrimaryExpAST *>(unary_exp->primary_exp);
            if (primary_exp->tp == PrimaryType::Num)
            {
                NumberAST *number = nullptr;
                if (primary_exp->number != nullptr)
                {
                    number = dynamic_cast<NumberAST *>(primary_exp->number);
                    ir = new ExpIRT(ExpKind::Const, new ConstIRT(number->num));
                }
            }
            else if (primary_exp->tp == PrimaryType::Exp)
            {
                if (primary_exp->exp != nullptr)
                {
                    ExpAST *exp = dynamic_cast<ExpAST *>(primary_exp->exp);
                    if (exp->lor_exp != nullptr)
                        logic_exp_dealer(exp->lor_exp, ir);
                }
            }
            else
            {
                if (primary_exp->lval != nullptr)
                {
                    auto lval = dynamic_cast<LValAST *>(primary_exp->lval);
                    this->LValTranslater(lval, ir);
                    ir = new ExpIRT(reinterpret_cast<MemIRT *>(ir));
                }
            }
        }
    }
    else if (unary_exp->tp == ExpType::OpExp)
    {
        if (unary_exp->unary_exp != nullptr && unary_exp->unary_op != nullptr)
        {
            unary_exp_dealer(unary_exp->unary_exp, ir);
            if (unary_exp->unary_op != nullptr)
            {
                UnaryOpAST *op = dynamic_cast<UnaryOpAST *>(unary_exp->unary_op);
                if (op->op == "!")
                    ir = new ExpIRT(ExpKind::BinOp, new BinOpIRT(BinOpKind::IsEqual, dynamic_cast<ExpIRT *>(ir), new ExpIRT(new ConstIRT(0))));
                else if (op->op == "-")
                    ir = new ExpIRT(ExpKind::BinOp, new BinOpIRT(BinOpKind::minus, new ExpIRT(new ConstIRT(0)), dynamic_cast<ExpIRT *>(ir)));
            }
        }
    }
    else if (unary_exp->tp == ExpType::Call)
    {
        // !!!***need symbol table!
        std::vector<ExpIRT *> args;
        std::vector<ArgsType> types;
        Symbol *sym = SymbolTable::FindSymbol(*(unary_exp->ident));
        if (sym == NULL)
        {
            std::cout << "Error: function " + *(unary_exp->ident) + " haven't been declared." << std::endl;
            exit(-1);
        }
        // Further: haven't implement args checking
        if (unary_exp->func_rparam == nullptr)
        {
            // need look up symbol table
            if (sym->FunctionAttributes->ArgsTypeVec.size())
            {
                LOG(ERROR) << "Function Call " << *(unary_exp->ident) << " Parameters Do Not Match Declaration Parameters\n";
                exit(-1);
            }
            // Here we need to create the IR tree 
            // by looking up symbol table to check the type of the function
            if (sym->FunctionAttributes->RetValType == ValueType::INT32) {
                ir = new ExpIRT(ExpKind::Call, new CallIRT(ValueType::INT32, new LabelIRT(*(unary_exp->ident)), types, args));
            } else if (sym->FunctionAttributes->RetValType == ValueType::VOID) {
                ir = new ExpIRT(ExpKind::Call, new CallIRT(ValueType::VOID, new LabelIRT(*(unary_exp->ident)), types, args));
            }
            
        }
        else
        {
            DLOG(WARNING) << "FUNC ID: " << *(unary_exp->ident);
            BaseIRT *args_exp = nullptr;
            FuncRParamsAST *func_r = dynamic_cast<FuncRParamsAST *>(unary_exp->func_rparam);
            // auto &ArgsCall = func_r->exp;
            auto &ArgsFVec = sym->FunctionAttributes->ArgsTypeVec;
            if (sym->FunctionAttributes->ArgsTypeVec.size() != func_r->exp.size() && ArgsFVec[ArgsFVec.size()-1]!=ArgsType::VarsPacket)
            {

                LOG(ERROR) << "Function Call " << *(unary_exp->ident) << " Parameters Do Not Match Declaration Parameters\n";
                exit(-1);
            }
            int i = 0;
            for (auto &it : func_r->exp)
            {
                if(it->type()=="StringAST")
                {
                    args_exp = new ExpIRT(new MemIRT(new ExpIRT(new NameIRT(reinterpret_cast<StringAST*>(it)->StringLabel,true))));
                }
                else
                {
                    logic_exp_dealer(it, args_exp);
                }
                args.push_back(reinterpret_cast<ExpIRT *>(args_exp));
                if(i<ArgsFVec.size())
                {
                    types.push_back(ArgsFVec[i]);
                }
                else
                {
                    types.push_back(ArgsType::Int32);
                }
                i++;
            }
            // Here we need to create the IR tree 
            // by looking up symbol table to check the type of the function
            if (sym->FunctionAttributes->RetValType == ValueType::INT32) {
                DLOG(WARNING) << "RETURN TYPE: INT32; " << *(unary_exp->ident);
                ir = new ExpIRT(ExpKind::Call, new CallIRT(ValueType::INT32, new LabelIRT(*(unary_exp->ident)), types, args));
            } else if (sym->FunctionAttributes->RetValType == ValueType::VOID) {
                DLOG(WARNING) << "RETURN TYPE: VOID; " << *(unary_exp->ident);
                ir = new ExpIRT(ExpKind::Call, new CallIRT(ValueType::VOID, new LabelIRT(*(unary_exp->ident)), types, args));
            }
        }
    }
}