#include "ast/ast.h"
const char *AstKindStr[] = {"ConstDecl", "VarDecl"};
const char *VarTypeStr[] = {"INT"};
const char *StmtTypeStr[] = {"Assign", "Exp", "Block", "If", "IfElse", "While", "Break", "Continue",
                             "ReturnExp", "ReturnVoid"};
std::string EnumToString(AstType type)
{
    return AstKindStr[int(type)];
}
std::string EnumToString(VarType type)
{
    return VarTypeStr[int(type)];
}
std::string EnumToString(StmtType type)
{
    return StmtTypeStr[int(type)];
}
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
                int initval;
                if (reinterpret_cast<ExpAST *>((*(DefAstPtr->InitValueVec))[0])->GetConstVal(initval))
                {
                    LOG(ERROR) << "The Int32 " << *DefAstPtr->VarIdent << "'s init value is not const\n";
                    return true;
                }
                SymbolTable::AddSymbol(*DefAstPtr->VarIdent, new Symbol(SymType::INT32, initval, true));
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
                    std::vector<int> initval;
                    for (auto &it_init : *ConstDefPtr->InitValueVec)
                    {
                        int temp;
                        if (reinterpret_cast<ExpAST *>(it_init)->GetConstVal(temp))
                        {
                            LOG(ERROR) << "The Array " << *DefAstPtr->VarIdent << "'s init value is not const\n";
                            return true;
                        }
                        initval.push_back(temp);
                    }
                    Symbol *sym = new Symbol(ConstDefPtr->DimSizeVec, initval, true);
                    SymbolTable::AddSymbol(*DefAstPtr->VarIdent, sym);
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
                SymbolTable::AddSymbol(*DefAstPtr->VarIdent, new Symbol(SymType::INT32, false));
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
                    Symbol *sym = new Symbol(ConstDefPtr->DimSizeVec, false);
                    SymbolTable::AddSymbol(*DefAstPtr->VarIdent, sym);
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
        LOG(ERROR) << "Undifind Left Value " << *this->VarIdent << "\n";
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
        val = sym->InitValVec[0];
        return false;
    }
    if (sym->SymbolType == SymType::INT32)
    {
        int offset = 0;
        if (sym->ConstFlag == false)
        {
            LOG(ERROR) << "Int32 Array " << *this->VarIdent << " is not const!\n";
            return true;
        }
        // check index
        if (this->IndexVec.size() != sym->ArrAttributes.ArrayDimVec.size())
        {
            LOG(ERROR) << "Int32 Array " << *this->VarIdent << " 's shape mismatch this index\n";
            return true;
        }
        for (int i = 0; i < this->IndexVec.size(); ++i)
        {
            auto const_exp = reinterpret_cast<ExpAST *>(this->IndexVec[i]);
            int index_val;
            if (const_exp->GetConstVal(index_val))
            {
                LOG(ERROR) << "Int32 Array " << *this->VarIdent << "'s " << i << " th index is not const\n";
                return true;
            }
            if (index_val < 0 || index_val > sym->ArrAttributes.ArrayDimVec[i])
            {
                LOG(ERROR) << "Int32 Array " << *this->VarIdent << "'s " << i << " th index out of range\n";
                return true;
            }
            offset += sym->ArrAttributes.ArrayDimVec[i] * index_val;
            
        }
        val = sym->InitValVec[offset];
        return false;
    }
    return true;
}
std::vector<BaseAST *> *InitValTree::ConvertToInitValVec(std::vector<int> DimVec)
{
    auto res = new std::vector<BaseAST *>();
    if (this->childs.size())
    {
        std::vector<int> TempDim;
        for (int i = 0; i < TempDim.size() - 1; ++i)
        {
            TempDim[i] = TempDim[i + 1];
        }
        TempDim.pop_back();

        for (auto &it_child : this->childs)
        {
            std::vector<BaseAST *> *temp = it_child->ConvertToInitValVec(TempDim);
            for (auto &it : *temp)
            {
                res->push_back(it);
            }
            delete temp;
        }
        return res;
    }
    else
    {
        for(auto &it:this->keys){
            res->push_back(it);
        }
        int size = 1;
        for(auto &it:DimVec){
            size *= it;
        }
        for(int i = res->size();i<size;++i){
            auto num = new NumberAST();
            num->num = 0;
            auto primary = new PrimaryExpAST();
            primary->number = num;
            primary->tp = PrimaryType::Num;
            auto unary = new UnaryExpAST();
            unary->primary_exp = primary;
            auto mul = new MulExpAST();
            mul->unary_exp.push_back(unary);
            auto add = new AddExpAST();
            add->mul_exp.push_back(mul);
            auto rel = new RelExpAST();
            rel->add_exp.push_back(add);
            auto eq = new EqExpAST();
            eq->rel_exp.push_back(rel);
            auto land = new LAndExpAST();
            land->eq_exp .push_back(eq);
            auto lor = new LOrExpAST();
            lor->land_exp.push_back(land);
            auto exp = new ExpAST();
            exp->lor_exp = lor;
            res->push_back(exp);
        }
        return res;
    }
}