#ifndef _ENUM_H_
#define _ENUM_H_
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
  ReturnVoid
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
    Int32Array
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
#endif