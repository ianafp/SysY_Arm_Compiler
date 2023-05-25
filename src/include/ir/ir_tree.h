
#ifndef _IR_TREE_H_
#define _IR_TREE_H_
#include"common/temp_allocate.h"
#include"common/enum.h"
#include <string>
#include <vector>
#include <iostream>
#include <ctype.h>
#include <assert.h>
#include "glog/logging.h"
#include"common/initval_tree.h"
#include"ir/temp_type.h"
bool isDigit(const std::string &str);
void CheckAndConvertExpToTemp(std::string &str);

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
class LabelIRT;
class FuncIRT;
class RetIRT;
class GlobalVarIRT;
class BaseIRT
{
public:
    virtual ~BaseIRT() = default;
    virtual void Dump() const = 0;
    virtual ExpValue ExpDump() const {
        ExpValue val;
        return val;
    }
};


class StatementIRT : public BaseIRT
{
public:
    StmKind ContentKind;
    BaseIRT *StmContent;
    StatementIRT(){}
    StatementIRT(StmKind kind, BaseIRT *content) : ContentKind(kind), StmContent(content) {}
    StatementIRT(SequenceIRT* seq):ContentKind(StmKind::Sequence),StmContent(reinterpret_cast<BaseIRT*>(seq)) {}
    StatementIRT(LabelIRT* label):ContentKind(StmKind::Lable),StmContent(reinterpret_cast<BaseIRT*>(label)) {}
    StatementIRT(JumpIRT* jump):ContentKind(StmKind::Jump),StmContent(reinterpret_cast<BaseIRT*>(jump)) {}
    StatementIRT(CjumpIRT* cjump):ContentKind(StmKind::Cjump),StmContent(reinterpret_cast<BaseIRT*>(cjump)) {}
    StatementIRT(MoveIRT* move):ContentKind(StmKind::Move),StmContent(reinterpret_cast<BaseIRT*>(move)) {}
    StatementIRT(ExpIRT* exp):ContentKind(StmKind::Exp),StmContent(reinterpret_cast<BaseIRT*>(exp)) {}
    void Dump() const override{
        StmContent->Dump();
    }
    

};
class GlobalVarIRT :public BaseIRT
{
public:
    ValueType GlobalVarType;
    std::string GlobalVarName;
    bool IsConstant;
    // int GlobalVarCount;
    bool IsArray;
    std::vector<int> DimVec;
    InitValTree<int>* InitVal;
    int Int32Val;
    GlobalVarIRT(ValueType type,std::string name,bool ConstFlag,std::vector<int> dim,InitValTree<int>* init):GlobalVarType(type),GlobalVarName(name),IsConstant(ConstFlag),IsArray(true),DimVec(dim),InitVal(init){
    }
    GlobalVarIRT(ValueType type,std::string name,bool ConstFlag,int init):GlobalVarType(type),GlobalVarName(name),IsConstant(ConstFlag),IsArray(false),InitVal(NULL),Int32Val(init){
    }
    void Dump() const override;
    
};
class SequenceIRT : public BaseIRT
{
public:
    StatementIRT *LeftChild, *RightChild;
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
    
    
};
class LabelIRT : public BaseIRT
{
public:
    std::string LableName;
    
    LabelIRT(std::string LableNameStr) { 
        if (LableNameStr == std::string("if")) {
            LableName = std::string("IF_LABEL_" + std::to_string(TempIdAllocater::GetId()));
        } else if (LableNameStr == std::string("else")) {
            LableName = std::string("ELSE_LABEL_" + std::to_string(TempIdAllocater::GetId()));
        } else if (LableNameStr == std::string("end")) {
            LableName = std::string("END_LABEL_" + std::to_string(TempIdAllocater::GetId()));
        } else if (LableNameStr == std::string("loop_entry")) {
            LableName = std::string("LOOP_ENTRY_" + std::to_string(TempIdAllocater::GetId()));
        } else if (LableNameStr == std::string("loop_body")) {
            LableName = std::string("LOOP_BODY_" + std::to_string(TempIdAllocater::GetId()));
        } else if (LableNameStr == std::string("loop_end")) {
            LableName = std::string("LOOP_END_" + std::to_string(TempIdAllocater::GetId()));
        }
        else {
            LableName = LableNameStr;
        } 
    }
    LabelIRT():LableName(std::string("temp_lable_"+std::to_string(TempIdAllocater::GetId()))){}
    void Dump() const override
    {
        std::cout << LableName << ":\n";
    }
    
};
class JumpIRT : public BaseIRT
{
public:
    LabelIRT *JumpLable;
    // BaseIRT* label;
    // BaseIRT* AddressExp;
    // std::vector<BaseIRT*> LableList;
    JumpIRT(){}
    JumpIRT(LabelIRT *ArgLableIRT) : JumpLable(ArgLableIRT) {}
    void Dump() const override
    {
        std::cout << "br label %" << JumpLable->LableName << "\n";
    }
    
};
class CjumpIRT : public BaseIRT
{
public:
    BinOpKind RelationOp;
    ExpIRT *LeftExp, *RightExp;
    LabelIRT *LabelTrue, *LableFalse;
    CjumpIRT(){}
    CjumpIRT(BinOpKind kind, ExpIRT *left, ExpIRT *right, LabelIRT *TrueLable, LabelIRT *FalseLable)
        : RelationOp(kind), LeftExp(left), RightExp(right), LabelTrue(TrueLable), LableFalse(FalseLable)
    {
    }
    void Dump() const override;
    
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
    void Dump() const override;
    ExpValue ExpDump() const override ;
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
    ExpValue ExpDump() const override;
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
    ExpValue ExpDump() const override;
};
class TempIRT : public BaseIRT
{
public:
    ExpValue TempValue;
    TempIRT(){}
    void Dump() const override
    {
    }
    ExpValue ExpDump() const override;
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
    ExpValue ExpDump() const override;
};
class NameIRT : public BaseIRT
{
public:
    std::string AsmLableName;
    bool IsPtr;
    std::vector<int> ArrayDim;
    NameIRT(){}
    NameIRT(std::string name,bool flag) : AsmLableName(name),IsPtr(flag) {}
    NameIRT(std::string name,std::vector<int> dim) : AsmLableName(name),IsPtr(true),ArrayDim(dim) {}
    void Dump() const override
    {
    }
    ExpValue ExpDump() const override;
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
    ExpValue ExpDump() const override;
};
class AllocateIRT: public BaseIRT{
public:
    int AlignSize;
    std::string ident;
    std::vector<int> ArrDim;
    AllocateIRT(){}
    AllocateIRT(std::string name,int align=1):AlignSize(align),ident(name){}
    AllocateIRT(std::string name,std::vector<int> dim,int align=1):AlignSize(align),ident(name),ArrDim(dim){}
    void Dump() const override{}
    ExpValue ExpDump() const override ;
};
/**
 * @author: zhang xin
 * @brief: CallIRT class is an ir tree class with exp type
 * @param: constructing a call irt needs return value type, function label and args, with the ret label implemented implicitly in ExpDump
 * @usage: call ExpDump() to get a temp in which stores ret value of function  
*/
class CallIRT : public BaseIRT
{
public:
    ValueType RetValType;
    LabelIRT *FuncLable;
    std::vector<ArgsType> ArgsTypeList;
    std::vector<ExpIRT *> ArgsExpList;
    CallIRT(){}
    CallIRT(ValueType type, LabelIRT *call,std::vector<ArgsType> types,std::vector<ExpIRT *> args) : RetValType(type), FuncLable(call),ArgsTypeList(types), ArgsExpList(args) {}
    void Dump() const override
    {
    }
    ExpValue ExpDump() const override;


};
class FuncIRT:public BaseIRT{
public:
    ValueType RetValType;
    LabelIRT *FuncLable;
    std::vector<std::string> ParameterNameVec;
    std::vector<ArgsType> ArgsVec;
    StatementIRT* FuncStm;
    FuncIRT(){}
    FuncIRT(ValueType type, LabelIRT *call,std::vector<std::string> name,std::vector<ArgsType> vec,StatementIRT* stm,ExpIRT* RetExp=NULL) : RetValType(type), FuncLable(call),ParameterNameVec(name),ArgsVec(vec),FuncStm(stm) {}
    void Dump() const override;
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

};
/**
 * @auther: zhang xin
 * @brief this function will concentenate an existing ir tree and a new stm irt to a new ir tree
 * @param root: reference of the original ir stm tree
 * @param stm: new statementIRT pointer
*/
void AddStmToTree(StatementIRT* &root,StatementIRT* stm);
#endif