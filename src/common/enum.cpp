#include"common/enum.h"
const char *AstKindStr[] = {"ConstDecl", "VarDecl"};
const char *VarTypeStr[] = {"INT"};
const char *StmtTypeStr[] = {"Assign", "Exp", "Block", "If", "IfElse", "While", "Break", "Continue", "ReturnExp", "ReturnVoid"};
const char *ArgTypeStr[] = {"i32","i32*","i8*","undefied"};  
const char *IrValTypeStr[] = {"i1","i8","i16","i32","i64","void"}; 
const char* ValueTypeStr[] = {"i32","void"};
std::string EnumToString(ValueType type)
{
    return ValueTypeStr[int(type)];
}              
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
std::string EnumToString(ArgsType type){
    return ArgTypeStr[int(type)];
}
std::string EnumToString(IrValType type)
{
    return IrValTypeStr[int(type)];
}