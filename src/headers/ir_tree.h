#include<string>
#include<vector>
#include<iostream>
typedef enum{Sequence,Lable,Jump,Cjump,Move,Exp} StmKind;
typedef enum{plus,minus,mul,div,rem,LeftShift,RightShift,
    LogicAnd,LogicOr,IsEqual,IsNe,IsLt,IsGt,IsLe,IsGe} BinOpKind;
typedef enum{INT32,VOID} ValueType;
class TempIdAllocater{
private:
    static int counter;
public:
    static int GetId(){return counter++;}
};
int TempIdAllocater::counter = 0;

class BaseIRT{
public:
    virtual ~BaseIRT() = default;
    virtual void Dump() const = 0;
};

class StatementIRT: public BaseIRT{
public:
    StmKind ContentKind;
    BaseIRT* StmContent;
    StatementIRT(StmKind kind,BaseIRT* content):ContentKind(kind),StmContent(content){}
};
class SequenceIRT:public BaseIRT{
public:
    BaseIRT* LeftChild,*RightChild;
    SequenceIRT(StatementIRT* LeftStm,StatementIRT* RightStm)
    :LeftChild(LeftStm),RightChild(RightStm){
    }
    void Dump() const override{
        LeftChild->Dump();
        RightChild->Dump();
    }
};
class LableIRT:public BaseIRT{
public:
    std::string LableName;
    LableIRT(std::string LableNameStr){ LableName = LableNameStr;}
    void Dump() const override{
        std::cout<<LableName<<":\n";
    }
};
class JumpIRT:public BaseIRT{
public:
    LableIRT* JumpLable;
    // BaseIRT* lable;
    // BaseIRT* AddressExp;
    // std::vector<BaseIRT*> LableList;
    JumpIRT(LableIRT* ArgLableIRT):JumpLable(ArgLableIRT){}
    void Dump() const override{
        std::cout<<"br lable %"<<JumpLable->LableName<<"\n"; 
    }
};
class CjumpIRT:public BaseIRT{
public:
    BinOpKind RelationOp;
    ExpIRT* LeftExp,* RightExp;
    LableIRT* LabelTrue,*LableFalse;
    CjumpIRT(BinOpKind kind,ExpIRT* left,ExpIRT* right,LableIRT* TrueLable,LableIRT* FalseLable)
    :RelationOp(kind),LeftExp(left),RightExp(right),LabelTrue(TrueLable),LableFalse(FalseLable)
    {}
    void Dump() const override{
        BinOpIRT CondExp(RelationOp,LeftExp,RightExp);
        int TempId = CondExp.ExpDump();
        std::cout<<"\n";
        std::cout<<"br i1 %" << TempId<<", lable %"<< LabelTrue->LableName<<", lable %"<<LableFalse->LableName<<"\n";
    }
};
class MoveIRT:public BaseIRT{
public:
    enum {ToTemp,ToMem} MoveKind;
    BaseIRT* DstExp;
    ExpIRT* SrcExp;
    MoveIRT(TempIRT* temp,ExpIRT* exp):SrcExp(exp),DstExp(temp),MoveKind(ToTemp){}
    MoveIRT(MemIRT* mem,ExpIRT* exp):SrcExp(exp),DstExp(mem),MoveKind(ToMem){}
    void Dump() const override{
        if(MoveKind==ToTemp){
            TempIRT* TempDst = reinterpret_cast<TempIRT*>(DstExp);
            int TempId = SrcExp->ExpDump();
            std::cout << "%" << TempDst->TempVarId << " = " << "%" << TempId;
            std::cout<<"\n";
        }
        else{
            MemIRT* MemDst = reinterpret_cast<MemIRT*>(DstExp);
            int SrcTempId = SrcExp->ExpDump();
            int DstAddrId = MemDst->ExpDump();
            std::cout<<"store i32 %"<<SrcTempId<<", ptr %"<<DstAddrId<<"\n";
        }
    }
};
class ExpIRT:public BaseIRT{
public:
    enum{BinOp,Mem,Temp,ESeq,Name,Const,Call} ExpKind;
    BaseIRT* ExpContent;
    void Dump() const override{    
    }
    int ExpDump() const{
        int TempId;
        switch(ExpKind){
            
        }
    }
};
class BinOpIRT: public BaseIRT{
public:
    BinOpKind OpKind;
    ExpIRT* LeftExp,*RightExp;
    BinOpIRT(BinOpKind kind,ExpIRT* left,ExpIRT* right):OpKind(kind),LeftExp(left),RightExp(right){}
    void Dump() const override{

    }
    int ExpDump() const{
        int ResTempId = TempIdAllocater::GetId();
        int LeftTempId = LeftExp->ExpDump(),RightTempId = RightExp->ExpDump();
        switch(OpKind){
            case BinOpKind::plus : 
                std::cout<<"%"<<ResTempId<<" = "<<"add i32 %"<<LeftTempId<<", %"<<RightTempId<<"\n";
                break;
            case BinOpKind::minus:
                std::cout<<"%"<<ResTempId<<" = "<<"sub i32 %"<<LeftTempId<<", %"<<RightTempId<<"\n";
                break;  
            case BinOpKind::mul:
                std::cout<<"%"<<ResTempId<<" = "<<"mul i32 %"<<LeftTempId<<", %"<<RightTempId<<"\n";
                break;               
            case BinOpKind::div:
                std::cout<<"%"<<ResTempId<<" = "<<"sdiv i32 %"<<LeftTempId<<", %"<<RightTempId<<"\n";
                break;      
            case BinOpKind::IsEqual:
                std::cout<<"%"<<ResTempId<<" = "<<"icmp eq i32 %"<<LeftTempId<<", %"<<RightTempId<<"\n";
                break;
            case BinOpKind::IsNe:
                std::cout<<"%"<<ResTempId<<" = "<<"icmp ne i32 %"<<LeftTempId<<", %"<<RightTempId<<"\n";
                break;   
            case BinOpKind::IsLt:
                std::cout<<"%"<<ResTempId<<" = "<<"icmp slt i32 %"<<LeftTempId<<", %"<<RightTempId<<"\n";
                break;    
            case BinOpKind::IsLe:
                std::cout<<"%"<<ResTempId<<" = "<<"icmp sle i32 %"<<LeftTempId<<", %"<<RightTempId<<"\n";
                break; 
            case BinOpKind::IsGt:
                std::cout<<"%"<<ResTempId<<" = "<<"icmp sgt i32 %"<<LeftTempId<<", %"<<RightTempId<<"\n";
                break; 
            case BinOpKind::IsGe:
                std::cout<<"%"<<ResTempId<<" = "<<"icmp sge i32 %"<<LeftTempId<<", %"<<RightTempId<<"\n";
                break; 
            case BinOpKind::rem:
                std::cout<<"%"<<ResTempId<<" = "<<"srem i32 %"<<LeftTempId<<", %"<<RightTempId<<"\n";
                break; 
            default:break;
        }
        return ResTempId;
    }
};
class MemIRT: public BaseIRT{
public:
    ExpIRT* AddressExp;
    MemIRT(ExpIRT* addr):AddressExp(addr){}
    void Dump() const override{
        
    }
    int ExpDump() const{
        return AddressExp->ExpDump();
    }
};
class TempIRT: public BaseIRT{
public:
    int TempVarId;
    TempIRT(){
        TempVarId = TempIdAllocater::GetId();
    }
    void Dump() const override{
        
    }
    int ExpDump() const{
        return TempVarId;
    }
};
class ESeqIRT: public BaseIRT{
public:
    StatementIRT* SideEffectStm;
    ExpIRT* EstimatedExp;
    ESeqIRT(StatementIRT* stm,ExpIRT* exp):SideEffectStm(stm),EstimatedExp(exp){}
    void Dump() const override{
        
    }
    int ExpDump() const{
        SideEffectStm->Dump();
        return EstimatedExp->ExpDump();
    }
};
class NameIRT: public BaseIRT{
public:
    std::string AsmLableName;
    NameIRT(std::string name):AsmLableName(name){}
    void Dump() const override{
        
    }
    std::string ExpDump() const{
        return AsmLableName;
    }
};
class ConstIRT:public BaseIRT{
public:
    int ConstVal;
    void Dump() const override{
        
    }
    int ExpDump() const{
        
    }
};
class CallIRT:public BaseIRT{
public:
    ValueType RetValType;
    LableIRT* FuncLable,*RetLable,*ExceptionLable;
    std::vector<ExpIRT*> ArgsExpList;
    CallIRT(ValueType type,LableIRT* call,LableIRT* ret,LableIRT* exclable,std::vector<ExpIRT*> args):RetValType(type),FuncLable(call),RetLable(ret),ExceptionLable(exclable),ArgsExpList(args){}
    void Dump() const override{
        
    }
    int ExpDump() const{
        int ResTempId = TempIdAllocater::GetId();
        std::vector<int> ArgsTemp;
        for(auto& it:ArgsExpList){
            ArgsTemp.push_back(it->ExpDump());
        }
        std::string RetTypeString;
        if(RetValType==ValueType::INT32) RetTypeString = "i32";
        else RetTypeString = "void";
        int TempId = TempIdAllocater::GetId();
        std::cout<<"%"<<ResTempId<<" = " << "invoke signext "<<RetTypeString<<" "<<"@"<<FuncLable->LableName<<"(";
        for(int i=0;i<ArgsTemp.size();++i){
            std::cout<<"i32 %"<<ArgsTemp[i];
            if(i!=ArgsTemp.size()-1){
                std::cout<<", ";
            }
        }
        std::cout<<") to lable %"<<RetLable<<" unwind lable "<<ExceptionLable<<"\n";
        return ResTempId;
    }
};

