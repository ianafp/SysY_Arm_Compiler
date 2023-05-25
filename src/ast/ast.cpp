#include "ast/ast.h"
// bool DeclAST::HandleSymbol() const
// {
//     if (this->tp == AstType::ConstDecl)
//     {
//         return reinterpret_cast<ConstDeclAST *>(this->const_or_var_decl)->HandleSymbol();
//     }
//     else
//     {
//         return reinterpret_cast<VarDeclAST *>(this->const_or_var_decl)->HandleSymbol();
//     }
// }
void ConstDeclAST::HandleSymbol() const
{
    if (this->BType == VarType::INT)
    {
        for (auto &it : this->ConstDefVec)
        {
            auto DefAstPtr = reinterpret_cast<VarDefAST *>(it);
            if (DefAstPtr->DimSizeVec.size() == 0)
            {
                // int type
                if (SymbolTable::FindSymbol(*DefAstPtr->VarIdent))
                {
                    LOG(ERROR) << "Multidefinition of symbol " << *DefAstPtr->VarIdent << "\n";
                    // return true;
                    exit(-1);
                }
                int initval;
                if (DefAstPtr->InitValue->keys[0]->GetConstVal(initval))
                {
                    LOG(ERROR) << "Initialization of const variable " << *DefAstPtr->VarIdent << "uses variable values\n";
                    // return true;
                    exit(-1);
                }
                Symbol *sym = new Symbol(true,false, initval);
                SymbolTable::AddSymbol(*DefAstPtr->VarIdent, sym);
                DefAstPtr->VarSym = sym;

                // return false;
            }
            else
            {
                // wait for implement of const exp
                // int array type
                std::vector<int> ArrayDimVec;
                for (auto &it : this->ConstDefVec)
                {
                    auto ConstDefPtr = reinterpret_cast<VarDefAST *>(it);
                    // check ident
                    if (SymbolTable::FindSymbol(*ConstDefPtr->VarIdent))
                    {
                        LOG(ERROR) << "Multidefinition of symbol " << *ConstDefPtr->VarIdent << "\n";
                        // return true;
                        exit(-1);
                    }
                    // create symbol info
                    InitValTree<int> *initval = NULL;
                    if (ConstDefPtr->InitValue && ConvertTreeToInt(ConstDefPtr->InitValue, initval))
                    {
                        LOG(ERROR) << "Initialization of const array variable " << *DefAstPtr->VarIdent << "uses variable values\n";
                        exit(-1);
                    }

                    std::vector<int> dim;
                    for (auto &it : ConstDefPtr->DimSizeVec)
                    {
                        int temp;
                        if (it->GetConstVal(temp))
                        {
                            LOG(ERROR) << "The Array " << *ConstDefPtr->VarIdent << " Dimension\n";
                            exit(-1);
                        }
                        dim.push_back(temp);
                    }
                    Symbol *sym = new Symbol(true, dim, initval);
                    SymbolTable::AddSymbol(*DefAstPtr->VarIdent, sym);
                    ConstDefPtr->VarSym = sym;
                }
                // return false;
                // if(SymbolTable::AddSymbol(*DefAstPtr->VarIdent,new Symbol()))
            }
        }
        // return false;
    }
    else
    {
        LOG(ERROR) << "NOT IMPLEMENTED YET\n";
        // return true;
        exit(-1);
    }
}
void VarDeclAST::HandleSymbol() const
{
    if (this->BType == VarType::INT)
    {
        for (auto &it : this->VarDefVec)
        {
            auto DefAstPtr = reinterpret_cast<VarDefAST *>(it);
            if (DefAstPtr->DimSizeVec.size() == 0)
            {
                // int type
                if (SymbolTable::FindSymbol(*DefAstPtr->VarIdent))
                {
                    LOG(ERROR) << "Multidefinition of symbol " << *DefAstPtr->VarIdent << "\n";
                    // return true;
                    exit(-1);
                }
                Symbol *sym = new Symbol(false,true,0);
                SymbolTable::AddSymbol(*DefAstPtr->VarIdent, sym);
                DefAstPtr->VarSym = sym;
                bool IsInit = !!DefAstPtr->InitValue;
                bool IsConstInit;
                bool IsGlobal = sym->GetGlobalFlag();
                if (IsInit)
                {
                    sym->VarArrtributes.IsInited = true;
                    InitValTree<int> *IntTree;
                    IsConstInit = !ConvertTreeToInt(DefAstPtr->InitValue, IntTree);
                    if (IsGlobal)
                    {
                        if (!IsConstInit)
                        {
                            LOG(ERROR) << "global symbol " << *DefAstPtr->VarIdent << " initialized by varieble!\n";
                            exit(-1);
                        }
                        sym->VarArrtributes.InitVal = IntTree->FindFirst();
                    }
                    else
                    {
                        sym->VarArrtributes.ExpVal = DefAstPtr->InitValue->FindFirst();
                    }
                }
                else
                {
                    sym->VarArrtributes.IsInited = false;
                }
            }
            else
            {
                // wait for implement of const exp
                // int array type
                std::vector<int> ArrayDimVec;
                for (auto &it : this->VarDefVec)
                {
                    auto ConstDefPtr = reinterpret_cast<VarDefAST *>(it);
                    // check ident
                    if (SymbolTable::FindSymbol(*ConstDefPtr->VarIdent))
                    {
                        LOG(ERROR) << "Multidefinition of symbol " << *ConstDefPtr->VarIdent << "\n";
                    }
                    // create symbol info
                    std::vector<int> dim;
                    for (auto &it : ConstDefPtr->DimSizeVec)
                    {
                        int temp;
                        if (it->GetConstVal(temp))
                        {
                            LOG(ERROR) << "The Array " << *ConstDefPtr->VarIdent << " Dimension\n";
                            exit(-1);
                        }
                        dim.push_back(temp);
                    }
                    Symbol *sym = new Symbol(false, dim);
                    SymbolTable::AddSymbol(*DefAstPtr->VarIdent, sym);
                    ConstDefPtr->VarSym = sym;
                    bool IsInit = !!ConstDefPtr->InitValue;
                    bool IsConstInit;
                    bool IsGlobal = sym->GetGlobalFlag();
                    if (IsInit)
                    {
                        sym->ArrAttributes->IsInited = true;
                        InitValTree<int> *IntTree;
                        IsConstInit = !ConvertTreeToInt(ConstDefPtr->InitValue, IntTree);
                        if (IsGlobal)
                        {
                            if (!IsConstInit)
                            {
                                LOG(ERROR) << "global symbol " << *ConstDefPtr->VarIdent << " initialized by varieble!\n";
                                exit(-1);
                            }
                            sym->ArrAttributes->ConstInitVal = IntTree;
                            sym->ArrAttributes->VarInitVal = NULL;
                        }
                        else
                        {
                            sym->ArrAttributes->ConstInitVal = NULL;
                            sym->ArrAttributes->VarInitVal = ConstDefPtr->InitValue;
                        }
                    }
                    else
                    {
                        sym->ArrAttributes->IsInited = false;
                    }
                }
            }
            // if(SymbolTable::AddSymbol(*DefAstPtr->VarIdent,new Symbol()))
        }
    }

    else
    {
        LOG(ERROR) << "NOT IMPLEMENTED YET\n";
        exit(-1);
    }
}

bool NumberAST::GetConstVal(int &val) const
{
    DLOG(INFO) << "num\n";
    val = this->num;
    return false;
}
bool PrimaryExpAST::GetConstVal(int &val) const
{
    DLOG(INFO) << "primary\n";
    if (this->tp == PrimaryType::Num)
    {
        return reinterpret_cast<NumberAST *>(this->number)->GetConstVal(val);
    }
    else if (this->tp == PrimaryType::Exp)
    {
        return reinterpret_cast<ExpAST *>(this->exp)->GetConstVal(val);
    }
    else
    {
        // lval
        return reinterpret_cast<LValAST *>(this->lval)->GetConstVal(val);
    }
}
bool UnaryExpAST::GetConstVal(int &val) const
{
    DLOG(INFO) << "unary\n";
    if (tp == ExpType::Primary)
    {
        return reinterpret_cast<PrimaryExpAST *>(this->primary_exp)->GetConstVal(val);
    }
    else if (tp == ExpType::OpExp)
    {
        return reinterpret_cast<UnaryExpAST *>(this->unary_exp)->GetConstVal(val);
    }
    else if (tp == ExpType::Call)
    {
        return true;
    }
    else
    {
        LOG(ERROR) << "NOT IMPLEMENTED YET\n";
        return true;
    }
}
bool MulExpAST::GetConstVal(int &val) const
{
    DLOG(INFO) << "mul\n";
    int temp, res;
    bool flag;
    // first unary exp
    flag = reinterpret_cast<UnaryExpAST *>(this->unary_exp[0])->GetConstVal(temp);
    if (flag)
        return true;
    res = temp;
    // iterate
    for (int i = 1; i < unary_exp.size(); ++i)
    {
        if (this->op[i - 1] == "*")
        {
            flag = reinterpret_cast<UnaryExpAST *>(this->unary_exp[i])->GetConstVal(temp);
            if (flag)
                return true;
            res *= temp;
        }
        else if (this->op[i - 1] == "/")
        {
            flag = reinterpret_cast<UnaryExpAST *>(this->unary_exp[i])->GetConstVal(temp);
            if (flag)
                return true;
            res /= temp;
        }
        else if (this->op[i - 1] == "%")
        {
            flag = reinterpret_cast<UnaryExpAST *>(this->unary_exp[i])->GetConstVal(temp);
            if (flag)
                return true;
            res %= temp;
        }
        else
        {
            LOG(ERROR) << "NOT IMPLEMENTED YET\n";
            return true;
        }
    }
    val = res;
    return false;
}

bool AddExpAST::GetConstVal(int &val) const
{
    DLOG(INFO) << "add\n";
    int temp, res;
    bool flag;
    // first unary exp
    flag = reinterpret_cast<MulExpAST *>(this->mul_exp[0])->GetConstVal(temp);
    if (flag)
        return true;
    res = temp;
    // iterate
    for (int i = 1; i < mul_exp.size(); ++i)
    {
        if (this->op[i - 1] == "+")
        {
            flag = reinterpret_cast<MulExpAST *>(this->mul_exp[i])->GetConstVal(temp);
            if (flag)
                return true;
            res += temp;
        }
        else if (this->op[i - 1] == "-")
        {
            flag = reinterpret_cast<MulExpAST *>(this->mul_exp[i])->GetConstVal(temp);
            if (flag)
                return true;
            res -= temp;
        }
        else
        {
            LOG(ERROR) << "NOT IMPLEMENTED YET\n";
            return true;
        }
    }
    val = res;
    return false;
}
bool RelExpAST::GetConstVal(int &val) const
{
    DLOG(INFO) << "rel\n";
    int temp, res;
    bool flag;
    // first unary exp
    flag = reinterpret_cast<AddExpAST *>(this->add_exp[0])->GetConstVal(temp);
    if (flag)
        return true;
    res = temp;
    // iterate
    for (int i = 1; i < add_exp.size(); ++i)
    {
        if (this->op[i - 1] == ">")
        {
            flag = reinterpret_cast<AddExpAST *>(this->add_exp[i])->GetConstVal(temp);
            if (flag)
                return true;
            res = res > temp;
        }
        else if (this->op[i - 1] == ">=")
        {
            flag = reinterpret_cast<AddExpAST *>(this->add_exp[i])->GetConstVal(temp);
            if (flag)
                return true;
            res = res >= temp;
        }
        else if (this->op[i - 1] == "<")
        {
            flag = reinterpret_cast<AddExpAST *>(this->add_exp[i])->GetConstVal(temp);
            if (flag)
                return true;
            res = res < temp;
        }
        else if (this->op[i - 1] == "<=")
        {
            flag = reinterpret_cast<AddExpAST *>(this->add_exp[i])->GetConstVal(temp);
            if (flag)
                return true;
            res = res <= temp;
        }
        else
        {
            LOG(ERROR) << "NOT IMPLEMENTED YET\n";
            return true;
        }
    }
    val = res;
    return false;
}
bool EqExpAST::GetConstVal(int &val) const
{
    DLOG(INFO) << "eq\n";
    int temp, res;
    bool flag;
    // first unary exp
    flag = reinterpret_cast<RelExpAST *>(this->rel_exp[0])->GetConstVal(temp);
    if (flag)
        return true;
    res = temp;
    // iterate
    for (int i = 1; i < rel_exp.size(); ++i)
    {
        if (this->op[i - 1] == "==")
        {
            flag = reinterpret_cast<RelExpAST *>(this->rel_exp[i])->GetConstVal(temp);
            if (flag)
                return true;
            res = res == temp;
        }
        else if (this->op[i - 1] == "!=")
        {
            flag = reinterpret_cast<RelExpAST *>(this->rel_exp[i])->GetConstVal(temp);
            if (flag)
                return true;
            res = res != temp;
        }
        else
        {
            LOG(ERROR) << "NOT IMPLEMENTED YET\n";
            return true;
        }
    }
    val = res;
    return false;
}
bool LAndExpAST::GetConstVal(int &val) const
{
    DLOG(INFO) << "LAnd\n";
    int temp, res;
    bool flag;
    // first unary exp
    flag = reinterpret_cast<EqExpAST *>(this->eq_exp[0])->GetConstVal(temp);
    if (flag)
        return true;
    res = temp;
    // iterate
    for (int i = 1; i < eq_exp.size(); ++i)
    {
        flag = reinterpret_cast<EqExpAST *>(eq_exp[i])->GetConstVal(temp);
        if (flag)
            return true;
        res = res && temp;
    }
    val = res;
    return false;
}
bool LOrExpAST::GetConstVal(int &val) const
{
    DLOG(INFO) << "Lor\n";
    int temp, res;
    bool flag;
    // first unary exp
    flag = reinterpret_cast<LAndExpAST *>(this->land_exp[0])->GetConstVal(temp);
    if (flag)
        return true;
    res = temp;
    // iterate
    for (int i = 1; i < land_exp.size(); ++i)
    {
        flag = reinterpret_cast<LAndExpAST *>(land_exp[i])->GetConstVal(temp);
        if (flag)
            return true;
        res = res || temp;
    }
    val = res;
    return false;
}
bool ExpAST::GetConstVal(int &val) const
{
    DLOG(INFO) << "EXP ";
    return reinterpret_cast<LOrExpAST *>(this->lor_exp)->GetConstVal(val);
}
bool LValAST::GetConstVal(int &val) const
{
    DLOG(INFO) << "LVal\n";
    // search symbol table
    Symbol *sym = SymbolTable::FindSymbol(*this->VarIdent);
    if (sym == NULL)
    {
        LOG(ERROR) << "Undefined Left Value " << *this->VarIdent << "\n";
        return true;
    }
    // check sym type
    if (sym->SymbolType == SymType::FuncName)
    {
        LOG(ERROR) << "Function Name " << *this->VarIdent << " can not be left value!\n";
        return true;
    }
    if (sym->SymbolType == SymType::Label)
    {
        LOG(ERROR) << "Label Name " << *this->VarIdent << " can not be left value!\n";
        return true;
    }
    if (sym->SymbolType == SymType::INT32)
    {
        if (this->IndexVec.size() != 0)
        {
            LOG(ERROR) << "Int32 " << *this->VarIdent << " can not be indexd!\n";
            return true;
        }
        if (sym->ConstFlag == false)
        {
            LOG(ERROR) << "Int32 " << *this->VarIdent << " is not const!\n";
            return true;
        }
        val = sym->VarArrtributes.InitVal;
        return false;
    }
    if (sym->SymbolType == SymType::INT32)
    {
        if (sym->ConstFlag == false)
        {
            LOG(ERROR) << "Int32 Array " << *this->VarIdent << " is not const!\n";
            return true;
        }
        // check index
        if (this->IndexVec.size() != sym->ArrAttributes->ArrayDimVec.size())
        {
            LOG(ERROR) << "Int32 Array " << *this->VarIdent << " 's shape mismatch this index\n";
            return true;
        }
        std::vector<int> index;
        for (auto &it : this->IndexVec)
        {
            int temp;
            if (it->GetConstVal(temp))
            {
                LOG(ERROR) << "the index is not const\n";
                return true;
            }
            index.push_back(temp);
        }
        sym->ArrAttributes->ConstInitVal->find(index, val);
        // val = sym->InitValVec[offset];

        return false;
    }
    return true;
}
