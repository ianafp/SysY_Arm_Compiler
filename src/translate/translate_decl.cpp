#include"translate/ir_generator.h"
#include"common/initval_tree.h"
void Program::DeclTranslater(DeclAST* decl,BaseIRT* &ir){

    if(decl->tp==AstType::ConstDecl){
        ConstDeclTranslater(reinterpret_cast<ConstDeclAST*>(decl->const_or_var_decl),ir);
    }else{
        VarDeclTranslater(reinterpret_cast<VarDeclAST*>(decl->const_or_var_decl),ir);
    }
    return;
}
void Program::VarDeclTranslater(VarDeclAST* decl,BaseIRT* &ir){
    if(decl->BType==VarType::INT){
        for(auto &it:decl->VarDefVec){
            this->VarDefTranslater(SymType::INT32,reinterpret_cast<VarDefAST*>(it),ir);
        }
    }
    else{
        // to be implemented
    }
    return;
}
void Program::ConvertExpInitTreeToIR(InitValTree<BaseAST*> *AstTree,const std::vector<int> &dim,std::vector<int> &trait,ExpIRT* addr,StatementIRT* &ir){
    if(AstTree->childs.size()){
        for(int i=0;i<AstTree->childs.size();++i){
            trait.push_back(i);
            ConvertExpInitTreeToIR(AstTree->childs[i],dim,trait,addr,ir);
            trait.pop_back();
        }
    }
    else{
        int Base = 1,Offset = 0;
        for(int i=trait.size()-1;i>-1;--i){
            Base *= dim[i];
            Offset += Base*trait[i];
        }
        for(int i=0;i<AstTree->keys.size();++i){
            BaseIRT* initexp;
            this->add_exp_dealer(AstTree->keys[i],initexp);
            AddStmToTree(ir,
            new StatementIRT(
                new MoveIRT(
                    new MemIRT(
                        new ExpIRT(
                            new BinOpIRT(
                                BinOpKind::plus,addr,new ExpIRT(new ConstIRT((Offset++)<<2))
                                )
                            )
                        )
                        ,reinterpret_cast<ExpIRT*>(initexp)
                    )
                )
            )
            ;
        }
    }
}
void Program::VarDefTranslater(SymType type,VarDefAST* decl,BaseIRT* &ir){
    if(type==SymType::INT32){
        // if global
        if(decl->VarSym->GetGlobalFlag()){
            // if array
            if(decl->DimSizeVec.size()){
                ir = new GlobalVarIRT(ValueType::INT32,*decl->VarIdent,false,decl->DimSizeVec,decl->IntInitValue);
            }
            // var
            {
                ir = new GlobalVarIRT(ValueType::INT32,*decl->VarIdent,false,decl->IntInitValue);
            }
        }
        // local
        else{
            // get stack space
            int size = 1;
            for(auto &it:decl->DimSizeVec){
                size *= it;
            }
            auto addr = new ExpIRT(new AllocateIRT(size<<2,4));
            StatementIRT* init = NULL;
            std::vector<int> trait;
            this->ConvertExpInitTreeToIR(decl->InitValue,decl->DimSizeVec,trait,addr,init);
            ir = new StatementIRT(addr);
            ir = new StatementIRT(new SequenceIRT(reinterpret_cast<StatementIRT*>(ir),init));
        }
    }   
    else{
        LOG(ERROR)<<"NOT IMPELENTED YET!\n";
    }
    return;
}
void Program:: ConstDefTranslater(SymType type,VarDefAST* decl,BaseIRT* &ir){
    if(type==SymType::INT32){
        // if global
        if(decl->VarSym->GetGlobalFlag()){
            // if array
            if(decl->DimSizeVec.size()){
                ir = new GlobalVarIRT(ValueType::INT32,*decl->VarIdent,true,decl->DimSizeVec,decl->IntInitValue);
            }
            // var
            {
                ir = new GlobalVarIRT(ValueType::INT32,*decl->VarIdent,true,decl->IntInitValue);
            }
        }
        // local
        else{
            // get stack space
            // int size = 1;
            // for(auto &it:decl->DimSizeVec){
            //     size *= it;
            // }
            // auto addr = new ExpIRT(new AllocateIRT(size<<2,4));
            // StatementIRT* init = NULL;
            // std::vector<int> trait;
            // this->ConvertExpInitTreeToIR(decl->InitValue,decl->DimSizeVec,trait,addr,init);
            // ir = new StatementIRT(addr);
            // ir = new StatementIRT(new SequenceIRT(reinterpret_cast<StatementIRT*>(ir),init));
            // no ir 
            ir = NULL;
        }
    }   
    else{
        LOG(ERROR)<<"NOT IMPELENTED YET!\n";
    }
    return;
}
void Program::ConstDeclTranslater(ConstDeclAST* decl,BaseIRT* &ir){
    if(decl->BType==VarType::INT){
        for(auto &it:decl->ConstDefVec){
            this->ConstDefTranslater(SymType::INT32,reinterpret_cast<VarDefAST*>(it),ir);
        }
    }
    else{
        // to be implemented
    }
    return;
}