#include "translate/ir_generator.h"

void Program::block_dealer(BlockItemAST *block_item, BaseIRT *&ir)
{
    // std::cout << "in block" << std::endl;/
    if (block_item->decl_or_stmt != nullptr && block_item->decl_or_stmt->type() == "StmtAST")
    {
        StmtAST *stmt_available = dynamic_cast<StmtAST *>(block_item->decl_or_stmt);
        // Deal with Stmt
        stmt_dealer(stmt_available, ir);
        //Further: need to consider: what if no return here in a void function while there are exp or other stmt??
    }
    // deal with decl
    else if (block_item->decl_or_stmt != nullptr && block_item->decl_or_stmt->type() == "DeclAST")
    {
        DeclTranslater(reinterpret_cast<DeclAST*>(block_item->decl_or_stmt), ir);
    }
}

void Program::func_dealer(FuncDefAST *func_def, BaseIRT *&ir)
{
    std::string result(""), ident("");
    VarType func_type;
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

    //deal with blocks
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
    //notice that para_cnt may not work

    auto parameters = reinterpret_cast<FuncFParamsAST*>(func_def->func_fparams);
    std::vector<std::string> names;
    std::vector<ArgsType> types;
    for(auto &it:parameters->func_fparam){
        auto param = reinterpret_cast<FuncFParamAST*>(it);
        names.push_back(*param->ident);
        types.push_back(param->tp);
    }
    if (func_type == VarType::INT)
    {

        ir = new StatementIRT(StmKind::Func, new FuncIRT(ValueType::INT32, new LabelIRT(ident),names,types, reinterpret_cast<StatementIRT *>(ir)));        
    }
    if (func_type == VarType::VOID)
    {
        ir = new StatementIRT(StmKind::Func, new FuncIRT(ValueType::VOID, new LabelIRT(ident), names,types, reinterpret_cast<StatementIRT *>(ir)));
    }
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
