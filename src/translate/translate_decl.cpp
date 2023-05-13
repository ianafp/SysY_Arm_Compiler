#include"translate/ir_generator.h"

void Program::DeclTranslater(DeclAST* decl,BaseIRT* &ir){

    if(decl->tp==AstKind::ConstDecl){
        ConstDeclTranslater(reinterpret_cast<ConstDeclAST*>(decl->const_or_var_decl),ir);
    }else{
        VarDeclTranslater(reinterpret_cast<VarDeclAST*>(decl->const_or_var_decl),ir);
    }
    return;
}
void Program::VarDeclTranslater(VarDeclAST* decl,BaseIRT* &ir){
    // to be implemented
    
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
void Program::VarDefTranslater(SymType type,VarDefAST* decl,BaseIRT* &ir){
    DLOG(ERROR)<<"NOT IMPLEMENTED YET\n";
    ValueType ValTy;
    int DefCount = 1;
    if(decl->DimSizeVec.size()>0){
        
    }
    if(type==SymType::INT32){
        ValTy = ValueType::INT32;

    }
    else{
        DLOG(ERROR)<<"NOT IMPLEMENTED YET\n";
    }
    return;
}
void Program::ConstDeclTranslater(ConstDeclAST* decl,BaseIRT* &ir){
    // to be implemented
    DLOG(ERROR)<<"NOT IMPLEMENTED YET\n";
    return;
}