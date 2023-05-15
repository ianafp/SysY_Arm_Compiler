#include "translate/ir_generator.h"

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
            else if (stmt_available->tp == StmtType::Exp)
            {
                assert(stmt_available->ret_exp != nullptr);
                BaseIRT *ir_exp = nullptr;
                logic_exp_dealer(stmt_available->ret_exp, ir_exp);
                ir = new StatementIRT(StmKind::Exp, ir_exp);
            }
            // to be implemented
            else if(stmt_available->tp == StmtType::Assign){

            }
            else if(stmt_available->tp == StmtType::Block){

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
    FuncFParamsAST *func_fparams;
    BaseAST *block;
    int para_cnt = 0;

    // Start with FuncDefAST, we translate it to IR
    func_type = func_def->func_type;
    ident += *func_def->ident;
    func_fparams = dynamic_cast<FuncFParamsAST*>(func_def->func_fparams);
    block = func_def->block;
    // get the count of parameters
    if (func_fparams != nullptr)
        para_cnt = func_fparams->func_fparam.size();

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

    //construct func_ir tree
    ValueType ret;
    if (type_analysis == INT_type)
    {
        ir = new StatementIRT(StmKind::Func, new FuncIRT(ValueType::INT32, new LabelIRT(ident), para_cnt, reinterpret_cast<StatementIRT *>(ir)));
        ret = ValueType::INT32;
        
    }
    if (type_analysis == VOID_type)
    {
        ir = new StatementIRT(StmKind::Func, new FuncIRT(ValueType::VOID, new LabelIRT(ident), para_cnt, reinterpret_cast<StatementIRT *>(ir)));
        ret = ValueType::VOID;
    }
        
    //add symbol table of this function
    std::vector<ArgsType> args;
    if(func_fparams != nullptr)
    {
        for(int i=0; i<para_cnt; i++)
        {
            if(dynamic_cast<FuncFParamAST *>(func_fparams->func_fparam[i])->tp == ArgsType::Int32)
                args.push_back(ArgsType::Int32);
            else if(dynamic_cast<FuncFParamAST *>(func_fparams->func_fparam[i])->tp == ArgsType::Int32Array)
                args.push_back(ArgsType::Int32Array);
        }
    }
    
    SymbolTable::AddSymbol(ident, new Symbol( ret, args));
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
