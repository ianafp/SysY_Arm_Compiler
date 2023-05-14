#include "translate/ir_generator.h"

void Program::logic_exp_dealer(BaseAST *exp, BaseIRT *&ir)
{
    // std::string return_str1("");
    // std::string return_str2("");
    BaseIRT *ir1 = new ExpIRT(), *ir2 = new ExpIRT();
    if (exp->type() == "ExpAST")
    {
        ExpAST* Exp = dynamic_cast<ExpAST*>(exp);
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
    if (unary_exp->tp == "primary")
    {
        if (unary_exp->primary_exp != nullptr)
        {
            PrimaryExpAST *primary_exp = dynamic_cast<PrimaryExpAST *>(unary_exp->primary_exp);
            if (primary_exp->tp == "number")
            {
                NumberAST *number = nullptr;
                if (primary_exp->number != nullptr)
                {
                    number = dynamic_cast<NumberAST *>(primary_exp->number);
                    ir = new ExpIRT(ExpKind::Const, new ConstIRT(number->num));
                }
            }
            else if (primary_exp->tp == "exp")
            {
                if (primary_exp->exp != nullptr)
                {
                    ExpAST *exp = dynamic_cast<ExpAST *>(primary_exp->exp);
                    if (exp->lor_exp != nullptr)
                        logic_exp_dealer(exp->lor_exp, ir);
                }
            }
        }
    }
    else if (unary_exp->tp == "op+exp")
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
    else if (unary_exp->tp == "call")
    {
        // !!!***need symbol table!
        std::vector<ExpIRT*> args;
        if(unary_exp->func_rparam == nullptr)
        {
            //need look up symbol table
            ir = new ExpIRT(ExpKind::Call, new CallIRT(ValueType::INT32, new LableIRT(*(unary_exp->ident)), args));
        }
        else
        {   
            BaseIRT* args_exp = nullptr;
            FuncRParamsAST* func_r = dynamic_cast<FuncRParamsAST*>(unary_exp->func_rparam);
            for(auto &it:func_r->exp)
            {
                logic_exp_dealer(it, args_exp);
                args.push_back(reinterpret_cast<ExpIRT*>(args_exp));
            }
            ir = new ExpIRT(ExpKind::Call, new CallIRT(ValueType::INT32, new LableIRT(*unary_exp->ident), args));
        }
    }
}

void Program::block_dealer(BlockItemAST *block_item, BaseIRT *&ir)
{
    // std::cout << "in block" << std::endl;/
    if (block_item->decl_or_stmt != nullptr && block_item->decl_or_stmt->type() == "StmtAST")
    {
        StmtAST *stmt_available = dynamic_cast<StmtAST *>(block_item->decl_or_stmt);
        // Deal with Stmt
        if (stmt_available != nullptr)
        {
            // return Exp ;
            if (stmt_available->tp == "retexp")
            {
                assert(stmt_available->ret_exp != nullptr);
                logic_exp_dealer(dynamic_cast<ExpAST *>(stmt_available->ret_exp)->lor_exp, ir);
                ir = new StatementIRT(StmKind::Ret, new RetIRT(ValueType::INT32, reinterpret_cast<ExpIRT *>(ir)));
            }
            // return ;
            else if (stmt_available->tp == "retnull")
            {
                assert(stmt_available->ret_exp == nullptr);
                ir = new StatementIRT(StmKind::Ret, new RetIRT(ValueType::VOID, NULL));
            }
            else if (stmt_available->tp == "exp")
            {
                assert(stmt_available->ret_exp != nullptr);
                BaseIRT *ir_exp = nullptr;
                logic_exp_dealer(stmt_available->ret_exp, ir_exp);
                ir = new StatementIRT(StmKind::Exp, ir_exp);
            }
            // more to continue...
        }
    }
    // deal with decl
    else if (block_item->decl_or_stmt != nullptr && block_item->decl_or_stmt->type() == "DeclAST")
    {
        // for zx to finish
    }
}

void Program::func_dealer(FuncDefAST *func_def, BaseIRT *&ir)
{
    std::string result(""), ident("");
    BaseAST *func_type;
    BaseAST *func_fparams;
    BaseAST *block;
    int para_cnt = 0;

    // Start with FuncDefAST, we translate it to IR
    func_type = func_def->func_type;
    ident += *func_def->ident;
    func_fparams = func_def->func_fparams;
    block = func_def->block;
    // get the count of parameters
    if (func_fparams != nullptr)
        para_cnt = dynamic_cast<FuncFParamsAST *>(func_fparams)->func_fparam.size();

    // Deal with FuncType
    FuncTypeAST *func_type_available = nullptr;
    std::string type_analysis("");
    if (func_type != nullptr)
    {
        func_type_available = dynamic_cast<FuncTypeAST *>(func_type);
        if (func_type_available != nullptr)
        {
            type_analysis += func_type_available->type_ret;
        }
    }

    // Deal with Block
    BlockAST *block_available = nullptr;
    BaseAST *block_true = nullptr;
    if (block != nullptr)
    {
        block_available = dynamic_cast<BlockAST *>(block);
        if (block_available != nullptr)
        {
            block_true = block_available->block;
        }
    }

    std::string INT_type("int");
    std::string VOID_type("void");

    BaseIRT* ir1 = nullptr, *ir2 = nullptr;
    blockAST *block_true_available = nullptr;
    std::list<std::string> ret_stmt;
    if (block_true != nullptr)
    {
        block_true_available = dynamic_cast<blockAST *>(block_true);
        //in function, there would be :blockitem -- blockitem -- ..
        if (block_true_available != nullptr)
        {
            assert(block_true_available->block_item[0] != nullptr && block_true_available->block_item[0]->type() == "BlockItemAST");
            block_dealer(dynamic_cast<BlockItemAST *>(block_true_available->block_item[0]), ir1);
            for (int i=1; i<block_true_available->block_item.size(); i++)
            {
                block_dealer(dynamic_cast<BlockItemAST *>(block_true_available->block_item[i]), ir2);
                ir1 = new StatementIRT(StmKind::Sequence, new SequenceIRT(reinterpret_cast<StatementIRT*>(ir1), reinterpret_cast<StatementIRT*>(ir2)));
            }
            ir = ir1;
        }
    }
    else
    {
        ir = new StatementIRT(StmKind::Ret, new RetIRT(ValueType::VOID, NULL));
    }

    if (type_analysis == INT_type)
        ir = new StatementIRT(StmKind::Func, new FuncIRT(ValueType::INT32, new LableIRT(ident), para_cnt, reinterpret_cast<StatementIRT *>(ir)));
    if (type_analysis == VOID_type)
        ir = new StatementIRT(StmKind::Func, new FuncIRT(ValueType::VOID, new LableIRT(ident), para_cnt, reinterpret_cast<StatementIRT *>(ir)));
}

void Program::Scan(BaseAST *root, BaseIRT *&ir)
{
    std::string comp_const("CompUnitAST");
    CompUnitAST *comp_unit = nullptr;
    BaseAST *root_raw_ptr = root;
    BaseAST *comp_unit_true = nullptr;
    if (root->type() == comp_const)
    {
        comp_unit = dynamic_cast<CompUnitAST *>(root_raw_ptr);
        if (comp_unit != nullptr)
        {
            comp_unit_true = comp_unit->comp_unit;
        }
    } // the error handling? Haven't implemented.

    BaseIRT *ir1 = nullptr, *ir2 = nullptr;
    CompunitAST *Compunit = dynamic_cast<CompunitAST *>(comp_unit_true);
    if (Compunit != nullptr)
    {
        if (Compunit->decl_list[0] != nullptr && Compunit->decl_list[0]->type() == "FuncDefAST")
        {
            func_dealer(dynamic_cast<FuncDefAST *>(Compunit->decl_list[0]), ir1);
        }
        else if (Compunit->decl_list[0] != nullptr && Compunit->decl_list[0]->type() == "DeclAST")
        {
            // for lv4
        }
        for (int i = 1; i < Compunit->decl_list.size(); i++)
        {
            // By order, we deal with different functions and declarations
            if (Compunit->decl_list[i] != nullptr && Compunit->decl_list[i]->type() == "FuncDefAST")
            {
                func_dealer(dynamic_cast<FuncDefAST *>(Compunit->decl_list[i]), ir2);
                ir1 = new StatementIRT(StmKind::Sequence, new SequenceIRT(reinterpret_cast<StatementIRT *>(ir1), reinterpret_cast<StatementIRT *>(ir2)));
            }
        }
        ir = ir1;
    }
}
