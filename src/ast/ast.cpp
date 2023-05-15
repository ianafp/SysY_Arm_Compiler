#include"ast/ast.h"
const char* AstKindStr[] = {"ConstDecl","VarDecl"};
const char* VarTypeStr[] = {"INT"};
const char* StmtTypeStr[] = {"Assign","Exp","Block","If","IfElse","While","Break","Continue",
"ReturnExp","ReturnVoid"};
std::string EnumToString(AstType type){
    return AstKindStr[int(type)];
}
std::string EnumToString(VarType type){
    return VarTypeStr[int(type)];
}
std::string EnumToString(StmtType type){
    return StmtTypeStr[int(type)];
}