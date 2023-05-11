#ifndef _IR_TREE_H_
#define _IR_TREE_H_
#include <string>
#include <vector>
#include <iostream>
#include <ctype.h>
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
    static int GetId() { return counter++; }
    static void Rewind(){ counter=0;}
};
int TempIdAllocater::counter = 0;
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

bool isDigit(const std::string &str){
    for(int i =0;i<str.length();++i){
        if(str[i]>'9' || str[i]<0){
            return false;
        }
    }
    return true;
}
void CheckAndConvertExpToTemp(std::string &str)
{
    if (str[0] != '%' && str[0] != '@' && !isDigit(str))
    {
        int TempId = TempIdAllocater::GetId();
        std::cout << "%" << TempId << " = " << str << "\n";
        str = "%" + std::to_string(TempId);
    }
}

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
    std::string ExpDump() const override{return "";}

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
    std::string ExpDump() const override {return "";}
    
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
    std::string ExpDump() const override {return "";}
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
    std::string ExpDump() const override {return "";}
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
    std::string ExpDump() const override {return "";}
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
    std::string ExpDump() const override { return "";}
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
class AllocateIRT: public BaseAST{
public:
    int NumOfInt;
    int AlignSize;
    AllocateIRT(){}
    AllocateIRT(int num=1,int align=1):NumOfInt(num),AlignSize(align){}
    void Dump() const override{}
    std::string ExpDump() const ;
};
class CallIRT : public BaseIRT
{
public:
    ValueType RetValType;
    LableIRT *FuncLable, *RetLable, *ExceptionLable;
    std::vector<ExpIRT *> ArgsExpList;
    CallIRT(){}
    CallIRT(ValueType type, LableIRT *call, LableIRT *ret, LableIRT *exclable, std::vector<ExpIRT *> args) : RetValType(type), FuncLable(call), RetLable(ret), ExceptionLable(exclable), ArgsExpList(args) {}
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
    std::string ExpDump() const override {return "";};
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
    std::string ExpDump() const override {return "";};
};
void CjumpIRT::Dump() const
{
    BinOpIRT CondExp(RelationOp, LeftExp, RightExp);
    std::string ConString = CondExp.ExpDump();
    CheckAndConvertExpToTemp(ConString);
    std::cout << "\n";
    std::cout << "br i1 " << ConString << ", lable %" << LabelTrue->LableName << ", lable %" << LableFalse->LableName << "\n";
    
}
void MoveIRT::Dump() const
{
    std::string SrcString = SrcExp->ExpDump();
    if (MoveKind == ToTemp)
    {
        std::cout << "%" << DstTemp->TempVarId << " = " << SrcString;
        std::cout << "\n";
    }
    else
    {
        std::string DstAddrString = DstMem->ExpDump();
        CheckAndConvertExpToTemp(SrcString);
        CheckAndConvertExpToTemp(DstAddrString);
        std::cout << "store i32 " << SrcString << ", ptr " << DstAddrString << "\n";
    }
}
std::string ExpIRT::ExpDump() const 
{
    BinOpIRT *BinOpContent = reinterpret_cast<BinOpIRT *>(ExpContent);
    MemIRT *MemContent = reinterpret_cast<MemIRT *>(ExpContent);
    TempIRT *TempContent = reinterpret_cast<TempIRT *>(ExpContent);
    ESeqIRT *EseqContent = reinterpret_cast<ESeqIRT *>(ExpContent);
    NameIRT *NameContent = reinterpret_cast<NameIRT *>(ExpContent);
    ConstIRT *ConstContent = reinterpret_cast<ConstIRT *>(ExpContent);
    CallIRT *CallContent = reinterpret_cast<CallIRT *>(ExpContent);
    AllocateIRT* AllocateContent = reinterpret_cast<AllocateIRT *>(ExpContent);
    switch (ContentKind)
    {
    case ExpKind::BinOp:
        
        return BinOpContent->ExpDump();
    case ExpKind::Mem:
        
        return MemContent->ExpDump();
    case ExpKind::Temp:
        
        return TempContent->ExpDump();
    case ExpKind::ESeq:
        
        return EseqContent->ExpDump();
    case ExpKind::Name:
        
        return NameContent->ExpDump();
    case ExpKind::Const:
        
        return ConstContent->ExpDump();
    case ExpKind::Call:
        
        return CallContent->ExpDump();
    case ExpKind::Allocate:
        return AllocateContent->ExpDump();
    }
}
std::string BinOpIRT::ExpDump() const
{
    int temp1,temp2;
    std::string ResString("");
    std::string LeftTempString = LeftExp->ExpDump(), RightTempString = RightExp->ExpDump();
    CheckAndConvertExpToTemp(LeftTempString);
    CheckAndConvertExpToTemp(RightTempString);
    switch (OpKind)
    {
    case BinOpKind::plus:
        ResString += "add i32 " + LeftTempString + ", " + RightTempString ;
        break;
    case BinOpKind::minus:
        ResString += "sub i32 " + LeftTempString + ", " + RightTempString ;
        break;
    case BinOpKind::mul:
        ResString += "mul i32 " + LeftTempString + ", " + RightTempString ;
        break;
    case BinOpKind::_div:
        ResString += "sdiv i32 " + LeftTempString + ", " + RightTempString ;
        break;
    case BinOpKind::IsEqual:
        ResString += "icmp eq i32 " + LeftTempString + ", " + RightTempString ;
        break;
    case BinOpKind::IsNe:
        ResString += "icmp ne i32 " + LeftTempString + ", " + RightTempString ;
        break;
    case BinOpKind::IsLt:
        ResString += "icmp slt i32 " + LeftTempString + ", " + RightTempString ;
        break;
    case BinOpKind::IsLe:
        ResString += "icmp sle i32 " + LeftTempString + ", " + RightTempString ;
        break;
    case BinOpKind::IsGt:
        ResString += "icmp sgt i32 " + LeftTempString + ", " + RightTempString ;
        break;
    case BinOpKind::IsGe:
        ResString += "icmp sge i32 " + LeftTempString + ", " + RightTempString ;
        break;
    case BinOpKind::rem:
        ResString += "srem i32 " + LeftTempString + ", " + RightTempString ;
        break;
    case BinOpKind::LogicAnd:
        temp1 = TempIdAllocater::GetId();
        temp2 = TempIdAllocater::GetId();
        
        std::cout<<"%"<<temp1<<" = "<<"icmp ne i32 0, "<<LeftTempString<<"\n";
        std::cout<<"%"<<temp2<<" = "<<"icmp ne i32 0, "<<RightTempString<<"\n";
        ResString += "and i32 %"+std::to_string(temp1)+", %"+std::to_string(temp2);
        break;
    case BinOpKind::LogicOr:
        temp1 = TempIdAllocater::GetId();
        temp2 = TempIdAllocater::GetId();
        std::cout<<"%"<<temp1<<" = "<<"icmp ne i32 0, "<<LeftTempString<<"\n";
        std::cout<<"%"<<temp2<<" = "<<"icmp ne i32 0, "<<RightTempString<<"\n";
        ResString += "or i32 %"+std::to_string(temp1)+", %"+std::to_string(temp2);
        break;
    case BinOpKind::LogicNot:
        ResString += "icmp eq i32 0, " + LeftTempString;
        break;
    case BinOpKind::Neg:
        ResString += "sub i32, 0, "+LeftTempString;
        break;
    default:
        break;
    }
    return ResString;
}

std::string MemIRT::ExpDump() const
{
    return AddressExp->ExpDump();
}
std::string TempIRT::ExpDump() const
{
    return std::to_string(TempVarId);
}
std::string ESeqIRT::ExpDump() const
{
    SideEffectStm->Dump();
    return EstimatedExp->ExpDump();
}
std::string NameIRT::ExpDump() const
{
    return AsmLableName;
}
std::string ConstIRT::ExpDump() const
{
    return std::to_string(ConstVal);
}
std::string CallIRT::ExpDump() const
{
    std::string ResString("");
    std::string RetTypeString;
    if (RetValType == ValueType::INT32)
        RetTypeString = "i32";
    else
        RetTypeString = "void";
    ResString += "invoke signext " + RetTypeString + " @" + FuncLable->LableName + "(";
    for (int i = 0; i < ArgsExpList.size(); ++i)
    {
        ResString += "i32 %" + ArgsExpList[i]->ExpDump();
        if (i != ArgsExpList.size() - 1)
        {
            ResString += ", ";
        }
    }
    ResString += ") to lable %" + RetLable->LableName + " unwind lable " + ExceptionLable->LableName + "\n";
    return ResString;
}
std::string AllocateIRT::ExpDump() const{
    std::string ResString("");
    ResString += "alloca i32 ";
    if(NumOfInt>1){
        ResString += ", i32 " + std::to_string(NumOfInt);
    }
    if(AlignSize>1){
        ResString += ", align " + std::to_string(AlignSize);
    }
    ResString += "\n";
    return ResString;
}
void FuncIRT::Dump() const{
    std::string FuncTypeStr("");
    if(RetValType==ValueType::INT32){ FuncTypeStr = "i32";}
    else if(RetValType==ValueType::VOID){ FuncTypeStr = "void";}
    std::cout <<"define "<<FuncTypeStr<<" @"<<this->FuncLable->LableName<<"(";
    TempIdAllocater::Rewind();
    int TempId;
    for(int i=0;i<this->ArgsCount;++i){
        std::cout<<"i32 ";
        TempId = TempIdAllocater::GetId();
        std::cout<<"%"<<TempId;
        if(i<this->ArgsCount-1){
            std::cout<<", ";
        }
    }
    std::cout<<")";
    std::cout << "{\n";
    this->FuncStm->Dump();

    std::cout<<"}\n";
}
void RetIRT::Dump() const{
    std::string ValueStr("");
    if(this->RetExp!=NULL){
        ValueStr = this->RetExp->ExpDump();
        CheckAndConvertExpToTemp(ValueStr);
    }
    std::cout<<"ret ";
    if(this->RetValType==ValueType::VOID){
        std::cout<<"";
    }else{
        std::cout<<" i32 "<<ValueStr;
    }
    std::cout<<"\n";
}
#endif