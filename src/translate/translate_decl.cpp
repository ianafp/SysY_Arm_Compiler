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

    }
    else{
        // to be implemented
    }
    return;
}
void Program::VarDefTranslater(VarDefAST* decl,BaseIRT* &ir){
    // to be implemented
    return;
}
void Program::ConstDeclTranslater(ConstDeclAST* decl,BaseIRT* &ir){
    // to be implemented
    return;
}