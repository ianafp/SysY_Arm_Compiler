#include "ast/ast.h"
bool DeclAST::HandleSymbol() const
{
    if (this->tp == AstType::ConstDecl)
    {
        return reinterpret_cast<ConstDeclAST *>(this->const_or_var_decl)->HandleSymbol();
    }
    else
    {
        return reinterpret_cast<VarDeclAST *>(this->const_or_var_decl)->HandleSymbol();
    }
}
bool ConstDeclAST::HandleSymbol() const
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
                    return true;
                }
                int initval = DefAstPtr->IntInitValue->keys[0];
                Symbol* sym = new Symbol(true, initval);
                SymbolTable::AddSymbol(*DefAstPtr->VarIdent, sym);
                DefAstPtr->VarSym = sym;
                return false;
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
                        return true;
                    }
                    // create symbol info
                    Symbol *sym = new Symbol(true,ConstDefPtr->DimSizeVec,ConstDefPtr->IntInitValue);
                    SymbolTable::AddSymbol(*DefAstPtr->VarIdent, sym);
                    ConstDefPtr->VarSym = sym;
                }
                return false;
                // if(SymbolTable::AddSymbol(*DefAstPtr->VarIdent,new Symbol()))
            }

        }
        return false;
    }
    else
    {
        DLOG(ERROR) << "NOT IMPLEMENTED YET\n";
        return true;
    }
}
bool VarDeclAST::HandleSymbol() const
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
                    return true;
                }
                Symbol* sym = new Symbol(false);
                SymbolTable::AddSymbol(*DefAstPtr->VarIdent,sym);
                DefAstPtr->VarSym = sym;
                if(sym->GetGlobalFlag()){
                    InitValTree<int>* IntTree;
                    if(ConvertTreeToInt(DefAstPtr->InitValue,IntTree)){
                        LOG(ERROR) << "global symbol " << *DefAstPtr->VarIdent << " initialized by varieble!\n";
                        exit(-1);
                        return true;  
                    }
                    DefAstPtr->IntInitValue = IntTree;
                }
                return false;
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
                        return true;
                    }
                    // create symbol info
                    Symbol *sym = new Symbol(false,ConstDefPtr->DimSizeVec);
                    SymbolTable::AddSymbol(*DefAstPtr->VarIdent, sym);
                    ConstDefPtr->VarSym = sym;
                    if(sym->GetGlobalFlag()){
                    InitValTree<int>* IntTree;
                    if(ConvertTreeToInt(DefAstPtr->InitValue,IntTree)){
                        LOG(ERROR) << "global varieble " << *DefAstPtr->VarIdent << " initialized by varieble!\n";
                        exit(-1);
                        // return true;  
                    }
                    DefAstPtr->IntInitValue = IntTree;
                }
                }
                // if(SymbolTable::AddSymbol(*DefAstPtr->VarIdent,new Symbol()))
            }
        }
        return false;
    }
    else
    {
        DLOG(ERROR) << "NOT IMPLEMENTED YET\n";
        return true;
    }
}

bool NumberAST::GetConstVal(int &val) const
{
    val = this->num;
    return true;
}
bool PrimaryExpAST::GetConstVal(int &val) const
{
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
        return reinterpret_cast<LValAST *>(this->exp)->GetConstVal(val);
    }
}
bool UnaryExpAST::GetConstVal(int &val) const
{
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
    return reinterpret_cast<LOrExpAST *>(this->lor_exp)->GetConstVal(val);
}
bool LValAST::GetConstVal(int &val) const
{
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
        for(auto &it:this->IndexVec){
            int temp;
            if(it->GetConstVal(temp)){
                LOG(ERROR) << "the index is not const\n";
                return true;
            }
            index.push_back(temp);
        }
        sym->ArrAttributes->ConstInitVal->find(index,val);
        // val = sym->InitValVec[offset];

        return false;
    }
    return true;
}

