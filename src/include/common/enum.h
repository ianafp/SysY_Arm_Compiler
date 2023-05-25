#ifndef _ENUM_H_
#define _ENUM_H_
#include<string>
enum class AstType
{
  ConstDecl,
  VarDecl,
};
enum class VarType
{
  INT,
  //potentially not used
  VOID
};
enum class StmtType
{
  Assign,
  Exp,
  Block,
  If,
  IfElse,
  While,
  Break,
  Continue,
  ReturnExp,
  ReturnVoid,
  Empty
};
enum class StmKind
{  
    GlobalVar,
    Func,
    Sequence,
    Lable,
    Jump,
    Cjump,
    Ret,
    Move,
    Exp
};
enum class BinOpKind
{
    plus,
    minus,
    mul,
    _div,
    rem,
    LeftShift,
    RightShift,
    Neg,
    LogicNot,
    LogicAnd,
    LogicOr,
    IsEqual,
    IsNe,
    IsLt,
    IsGt,
    IsLe,
    IsGe
} ;
enum class ValueType
{
    INT32,
    VOID
} ;
enum  class ExpKind
{
    BinOp,
    Mem,
    Temp,
    ESeq,
    Name,
    Const,
    Call,
    Allocate 
} ;
enum class ArgsType{
    Int32,
    Int32Array,
    String,
    VarsPacket 
};
enum class SymType
{
    Label,
    FuncName,
    INT32,
    Int32Array
};
enum class ExpType{
    Primary,
    OpExp,
    Call
};
enum class PrimaryType{
    Exp,
    Num,
    LVal
};
enum class IrValType
{
    i1,
    i8,
    i16,
    i32,
    i64,
    _void_
};
std::string EnumToString(AstType type);
std::string EnumToString(VarType type);
std::string EnumToString(StmtType type);
std::string EnumToString(ArgsType type);
std::string EnumToString(IrValType type);
std::string EnumToString(ValueType type);
#endif