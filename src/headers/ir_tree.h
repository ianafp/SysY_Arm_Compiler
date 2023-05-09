#include<string>
#include<vector>
class BaseIRT{
public:
    virtual ~BaseIRT() = default;
    virtual void Dump() const = 0;
};
class StatementIRT: public BaseIRT{
public:
    enum {Sequence,Lable,Jump,Cjump,Move,Exp} StmKind;
    BaseIRT* StmContent;
};
class SequenceIRT:public BaseIRT{
public:
    BaseIRT* LeftChild,*RightChild;
};
class LableIRT:public BaseIRT{
public:
    std::string lable;
};
class JumpIRT:public BaseIRT{
public:
    BaseIRT* AddressExp;
    std::vector<BaseIRT*> LableList;
};
class CjumpIRT:public BaseIRT{
public:
    BaseIRT* operation;
    BaseIRT* LeftExp,* RightExp;
    BaseIRT* LabelTrue,*LableFalse;
};
class MoveIRT:public BaseIRT{
public:
    BaseIRT* SrceExp,* DstExp;
};
class ExpIRT:public BaseIRT{
public:
    enum{BinOp,Mem,Temp,ESeq,Name,Const,Call} ExpKind;
    BaseIRT* ExpContent;
};
class BinOpIRT: public BaseIRT{
public:
    enum{plus,minus,mul,div,BitAnd,pr,LeftShift,RightShift,BitXor} BinOpKind;
    BaseIRT* LeftExp,*RightExp;
};
class MemIRT: public BaseIRT{
public:
    BaseIRT* AddressExp;
};
class TempIRT: public BaseIRT{
public:
    int TempVarId;
};
class ESeqIRT: public BaseIRT{
public:
    BaseIRT* SideEffectStm,*EstimatedExp;
};
class NameIRT: public BaseIRT{
public:
    BaseIRT* lable;
};
class ConstIRT:public BaseIRT{
public:
    int ConstVal;
};
class CallIRT:public BaseIRT{
public:
    BaseIRT* FuncNameExp;
    std::vector<BaseIRT*> ArgsExpList;
};

