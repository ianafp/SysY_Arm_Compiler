
#ifndef _IR_TREE_H_
#define _IR_TREE_H_
#include <string>
#include <vector>
#include <iostream>
#include <ctype.h>
#include <assert.h>
typedef enum
{
    Func,
    Sequence,
    Lable,
    Jump,
    Cjump,
    Ret,
    Move,
    Exp
} StmKind;
typedef enum
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
} BinOpKind;
typedef enum
{
    INT32,
    VOID
} ValueType;
typedef enum
{
    BinOp,
    Mem,
    Temp,
    ESeq,
    Name,
    Const,
    Call,
    Allocate 
} ExpKind;
class TempIdAllocater
{
private:
    static int counter;

public:
    static int GetId();
    static void Rewind();
};

class ExpIRT;
class BinOpIRT;
class TempIRT;
class MemIRT;
class ConstIRT;
class CallIRT;
class NameIRT;
class ESeqIRT;
class AllocateIRT;
class SequenceIRT;
class JumpIRT;
class CjumpIRT;
class MoveIRT;
class LableIRT;
class FuncIRT;
class RetIRT;
class BaseIRT
{
public:
    virtual ~BaseIRT() = default;
    virtual void Dump() const = 0;
    virtual std::string  ExpDump() const = 0;
};


class StatementIRT : public BaseIRT
{
public:
    StmKind ContentKind;
    BaseIRT *StmContent;
    StatementIRT(){}
    StatementIRT(StmKind kind, BaseIRT *content) : ContentKind(kind), StmContent(content) {}
    StatementIRT(SequenceIRT* seq):ContentKind(StmKind::Sequence),StmContent(reinterpret_cast<BaseIRT*>(seq)) {}
    StatementIRT(LableIRT* lable):ContentKind(StmKind::Lable),StmContent(reinterpret_cast<BaseIRT*>(lable)) {}
    StatementIRT(JumpIRT* jump):ContentKind(StmKind::Jump),StmContent(reinterpret_cast<BaseIRT*>(jump)) {}
    StatementIRT(CjumpIRT* cjump):ContentKind(StmKind::Cjump),StmContent(reinterpret_cast<BaseIRT*>(cjump)) {}
    StatementIRT(MoveIRT* move):ContentKind(StmKind::Move),StmContent(reinterpret_cast<BaseIRT*>(move)) {}
    StatementIRT(ExpIRT* exp):ContentKind(StmKind::Exp),StmContent(reinterpret_cast<BaseIRT*>(exp)) {}
    void Dump() const override{
        StmContent->Dump();
    }
    std::string ExpDump() const override;

};
class SequenceIRT : public BaseIRT
{
public:
    BaseIRT *LeftChild, *RightChild;
    SequenceIRT(){}
    SequenceIRT(StatementIRT *LeftStm, StatementIRT *RightStm)
        : LeftChild(LeftStm), RightChild(RightStm)
    {
    }
    void Dump() const override
    {
        LeftChild->Dump();
        RightChild->Dump();
    }
    std::string ExpDump() const override ;
    
};
class LableIRT : public BaseIRT
{
public:
    std::string LableName;
    
    LableIRT(std::string LableNameStr) { LableName = LableNameStr; }
    LableIRT():LableName(std::string("temp_lable_"+std::to_string(TempIdAllocater::GetId()))){}
    void Dump() const override
    {
        std::cout << LableName << ":\n";
    }
    std::string ExpDump() const override ;
};
class JumpIRT : public BaseIRT
{
public:
    LableIRT *JumpLable;
    // BaseIRT* lable;
    // BaseIRT* AddressExp;
    // std::vector<BaseIRT*> LableList;
    JumpIRT(){}
    JumpIRT(LableIRT *ArgLableIRT) : JumpLable(ArgLableIRT) {}
    void Dump() const override
    {
        std::cout << "br lable %" << JumpLable->LableName << "\n";
    }
    std::string ExpDump() const override ;
};
class CjumpIRT : public BaseIRT
{
public:
    BinOpKind RelationOp;
    ExpIRT *LeftExp, *RightExp;
    LableIRT *LabelTrue, *LableFalse;
    CjumpIRT(){}
    CjumpIRT(BinOpKind kind, ExpIRT *left, ExpIRT *right, LableIRT *TrueLable, LableIRT *FalseLable)
        : RelationOp(kind), LeftExp(left), RightExp(right), LabelTrue(TrueLable), LableFalse(FalseLable)
    {
    }
    void Dump() const override;
    std::string ExpDump() const override;
};

class MoveIRT : public BaseIRT
{
public:
    enum
    {
        ToTemp,
        ToMem
    } MoveKind;
    TempIRT* DstTemp;
    MemIRT* DstMem;
    ExpIRT* SrcExp;
    MoveIRT(){}
    MoveIRT(TempIRT *temp, ExpIRT *exp) : MoveKind(ToTemp),DstTemp(temp),DstMem(nullptr),SrcExp(exp) {}
    MoveIRT(MemIRT *mem, ExpIRT *exp) : MoveKind(ToMem), DstTemp(nullptr),DstMem(mem),SrcExp(exp) {}
    void Dump() const override;
    std::string ExpDump() const override;
};
class ExpIRT : public BaseIRT
{
public:

    ExpKind ContentKind;
    BaseIRT *ExpContent;
    ExpIRT(){}
    ExpIRT(ExpKind kind, BaseIRT *content) : ContentKind(kind), ExpContent(reinterpret_cast<BaseIRT*>(content)) {}
    ExpIRT(ConstIRT* constant):ContentKind(ExpKind::Const),ExpContent(reinterpret_cast<BaseIRT*>(constant)){}
    ExpIRT(CallIRT* call):ContentKind(ExpKind::Call),ExpContent(reinterpret_cast<BaseIRT*>(call)){}
    ExpIRT(NameIRT* name):ContentKind(ExpKind::Name),ExpContent(reinterpret_cast<BaseIRT*>(name)){}
    ExpIRT(ESeqIRT* eseq):ContentKind(ExpKind::ESeq),ExpContent(reinterpret_cast<BaseIRT*>(eseq)){}
    ExpIRT(TempIRT* temp):ContentKind(ExpKind::Temp),ExpContent(reinterpret_cast<BaseIRT*>(temp)){}
    ExpIRT(MemIRT* mem):ContentKind(ExpKind::Mem),ExpContent(reinterpret_cast<BaseIRT*>(mem)){}
    ExpIRT(BinOpIRT* binop ):ContentKind(ExpKind::BinOp),ExpContent(reinterpret_cast<BaseIRT*>(binop)){} 
    ExpIRT(AllocateIRT* alloc):ContentKind(ExpKind::Allocate),ExpContent(reinterpret_cast<BaseIRT*>(alloc)) {}
    void Dump() const override
    {
    }
    std::string ExpDump() const override ;
};
class BinOpIRT : public BaseIRT
{
public:
    BinOpKind OpKind;
    ExpIRT *LeftExp, *RightExp;
    BinOpIRT(BinOpKind kind, ExpIRT *left, ExpIRT *right = NULL) : OpKind(kind), LeftExp(left), RightExp(right) {}
    
    void Dump() const override
    {
    }
    std::string ExpDump() const override;
};
class MemIRT : public BaseIRT
{
public:
    ExpIRT *AddressExp;
    MemIRT(){}
    MemIRT(ExpIRT *addr) : AddressExp(addr) {}
    void Dump() const override
    {
    }
    std::string ExpDump() const override;
};
class TempIRT : public BaseIRT
{
public:
    int TempVarId;
    TempIRT()
    {
        TempVarId = TempIdAllocater::GetId();
    }
    void Dump() const override
    {
    }
    std::string ExpDump() const override;
};
class ESeqIRT : public BaseIRT
{
public:
    StatementIRT *SideEffectStm;
    ExpIRT *EstimatedExp;
    ESeqIRT(){}
    ESeqIRT(StatementIRT *stm, ExpIRT *exp) : SideEffectStm(stm), EstimatedExp(exp) {}
    void Dump() const override
    {
    }
    std::string ExpDump() const override;
};
class NameIRT : public BaseIRT
{
public:
    std::string AsmLableName;
    NameIRT(){}
    NameIRT(std::string name) : AsmLableName(name) {}
    void Dump() const override
    {
    }
    std::string ExpDump() const override;
};
class ConstIRT : public BaseIRT
{
public:
    int ConstVal;
    ConstIRT(){}
    ConstIRT(int val):ConstVal(val){}
    void Dump() const override
    {
    }
    std::string ExpDump() const override;
};
class AllocateIRT: public BaseIRT{
public:
    int NumOfInt;
    int AlignSize;
    AllocateIRT(){}
    AllocateIRT(int num=1,int align=1):NumOfInt(num),AlignSize(align){}
    void Dump() const override{}
    std::string ExpDump() const override ;
};
class CallIRT : public BaseIRT
{
public:
    ValueType RetValType;
    LableIRT *FuncLable, *RetLable, *ExceptionLable;
    std::vector<ExpIRT *> ArgsExpList;
    CallIRT(){}
    CallIRT(ValueType type, LableIRT *call, LableIRT *ret, LableIRT *exclable, std::vector<ExpIRT *> args) : RetValType(type), FuncLable(call), RetLable(ret), ExceptionLable(exclable), ArgsExpList(args) {}
    CallIRT(ValueType type, LableIRT *call, LableIRT *ret, LableIRT *exclable = NULL) : RetValType(type), FuncLable(call), RetLable(ret), ExceptionLable(exclable) {}
    CallIRT(ValueType type, LableIRT *call, LableIRT *ret, std::vector<ExpIRT *> args) : RetValType(type), FuncLable(call), RetLable(ret), ArgsExpList(args) {}
    void Dump() const override
    {
    }
    std::string ExpDump() const override;


};
class FuncIRT:public BaseIRT{
public:
    ValueType RetValType;
    LableIRT *FuncLable;
    int ArgsCount;
    StatementIRT* FuncStm;
    FuncIRT(){}
    FuncIRT(ValueType type, LableIRT *call, int count,StatementIRT* stm,ExpIRT* RetExp=NULL) : RetValType(type), FuncLable(call), ArgsCount(count),FuncStm(stm) {}
    void Dump() const override;
    std::string ExpDump() const override;
};
class RetIRT:public BaseIRT{
public:
    ValueType RetValType;
    ExpIRT* RetExp;
    RetIRT(){}
    RetIRT(ValueType type):RetValType(type){
        if(type==ValueType::VOID){
            RetExp = NULL;
        }else{
            RetExp = new ExpIRT(new ConstIRT(0));
        }
    }
    RetIRT(ValueType value,ExpIRT* exp):RetValType(value),RetExp(exp){
        if(exp==NULL){
            assert(value == ValueType::VOID);
        }
    }
    void Dump() const override;
    std::string ExpDump() const override;
};

#endif