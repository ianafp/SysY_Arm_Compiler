#include"ir/ir_tree.h"

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
    std::vector<std::string> ArgsStr;
    for(auto &it:this->ArgsExpList){
        std::string TempStr = it->ExpDump();
        CheckAndConvertExpToTemp(TempStr);
        ArgsStr.push_back(TempStr);
    }
    int TempId = TempIdAllocater::GetId();
    if (RetValType == ValueType::INT32)
        RetTypeString = "i32";
    else
        RetTypeString = "void";
    std::cout<<"%"<<TempId<<" = "<<"invoke signext " << RetTypeString << " @" << FuncLable->LableName + "(";
    ResString += "invoke signext " + RetTypeString + " @" + FuncLable->LableName + "(";
    for (int i = 0; i < ArgsStr.size(); ++i)
    {
        std::cout << "i32 %" << ArgsStr[i];
        if (i != ArgsStr.size() - 1)
        {
            std::cout<<", ";
        }
    }
    std::string RetLable = "%func_ret_"+std::to_string(TempIdAllocater::GetId());
    std::cout<<") to lable %"<<RetLable<<" unwind lable "<<RetLable<<"\n";
    ResString = "%" + std::to_string(TempId);
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
    if(RetValType==ValueType::INT32){FuncTypeStr="i32";}
    else if(RetValType==ValueType::VOID){FuncTypeStr="void";}
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
    if(this->FuncStm!=NULL)
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

std::string RetIRT:: ExpDump() const  {return "";};
std::string FuncIRT:: ExpDump() const  {return "";};
std::string MoveIRT:: ExpDump() const  { return "";}
std::string CjumpIRT:: ExpDump() const  {return "";}
std::string JumpIRT:: ExpDump() const  {return "";}
std::string LableIRT:: ExpDump() const  {return "";}
std::string SequenceIRT:: ExpDump() const  {return "";}
std::string StatementIRT:: ExpDump() const {return "";}
