#include"ir/ir_tree.h"

void CjumpIRT::Dump() const
{
    BinOpIRT CondExp(RelationOp, LeftExp, RightExp);
    auto ConValue = CondExp.ExpDump();
    std::cout << "\n";
    std::string condition_type = ConValue.TypeToString();
    std::string condition_label = ConValue.LabelToString();
    if (ConValue.TypeToString() == std::string("i32")) {
        // add a statement to convert.
        condition_type = std::string("i1");
        condition_label = "%" + std::to_string(TempIdAllocater::GetId());
        std::cout << condition_label << " = " << "icmp ne i32 " << ConValue.LabelToString() << ", 0" << std::endl;
    }
    std::cout << "br "<< condition_type <<" "<< condition_label << ", label %" << LabelTrue->LableName << ", label %" << LableFalse->LableName << "\n";
    
}
void MoveIRT::Dump() const
{
    auto SrcExpVal = SrcExp->ExpDump();
    if (MoveKind == ToTemp)
    {
        std::cout << "%" << DstTemp->TempVarId << " = " << SrcExpVal.LabelToString();
        std::cout << "\n";
    }
    else
    {
        auto DstAddrVal = DstMem->ExpDump();
        BitCast(DstAddrVal,SrcExpVal.ExpType,true);
        std::cout << "store "<< SrcExpVal.TypeToString() <<" "<< SrcExpVal.LabelToString() << ", "<<DstAddrVal.TypeToString()<<" "<< DstAddrVal.LabelToString() << "\n";
    }
}
ExpValue ExpIRT::ExpDump() const 
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
ExpValue BinOpIRT::ExpDump() const
{
    int temp1,temp2,res,temp ;
    std::string ResString(""),TempString;
    // ExpValue ResVal;
    ExpValue ResVal;
    auto LeftValue = LeftExp->ExpDump(), RightValue = RightExp->ExpDump();
    // OpBitSignedExtension(LeftValue,RightValue);
    switch (OpKind)
    {
    case BinOpKind::plus:
        res = TempIdAllocater::GetId();
        ResString += "%" + std::to_string(res);
        
        std::cout<<ResString<<" = "<<"add "<<LeftValue.TypeToString()<<" "<<LeftValue.LabelToString()<<", "<<RightValue.LabelToString()<<"\n";  
        break;
    case BinOpKind::minus:
        res = TempIdAllocater::GetId();
        ResString += "%" + std::to_string(res);

        std::cout<<ResString<<" = "<<"sub "<<LeftValue.TypeToString()<<" "<<LeftValue.LabelToString()<<", "<<RightValue.LabelToString()<<"\n";  
        break;
    case BinOpKind::mul:
        res = TempIdAllocater::GetId();
        ResString += "%" + std::to_string(res);

        std::cout<<ResString<<" = "<<"mul "<<LeftValue.TypeToString()<<" "<<LeftValue.LabelToString()<<", "<<RightValue.LabelToString()<<"\n";  
        break;
    case BinOpKind::_div:
        res = TempIdAllocater::GetId();
        ResString += "%" + std::to_string(res);
        std::cout<<ResString<<" = "<<"sdiv "<<LeftValue.TypeToString()<<" "<<LeftValue.LabelToString()<<", "<<RightValue.LabelToString()<<"\n";  
        break;
    case BinOpKind::IsEqual:
        temp = TempIdAllocater::GetId();
        TempString = "%" + std::to_string(temp);
        res = TempIdAllocater::GetId();
        ResString += "%" + std::to_string(res);
        std::cout<<TempString<<" = "<<"icmp eq "<<LeftValue.TypeToString() <<" " <<LeftValue.LabelToString()<<", "<<RightValue.LabelToString()<<"\n";  
        std::cout<<ResString<<" = "<<"zext i1 "<<TempString<<" to i32\n";
        break;
    case BinOpKind::IsNe:
        temp = TempIdAllocater::GetId();
        TempString = "%" + std::to_string(temp);
        res = TempIdAllocater::GetId();
        ResString += "%" + std::to_string(res);
        std::cout<<TempString<<" = "<<"icmp ne "<<LeftValue.TypeToString() <<" " <<LeftValue.LabelToString()<<", "<<RightValue.LabelToString()<<"\n";  
        std::cout<<ResString<<" = "<<"zext i1 "<<TempString<<" to i32\n";
        break;
    case BinOpKind::IsLt:
        temp = TempIdAllocater::GetId();
        TempString = "%" + std::to_string(temp);
        res = TempIdAllocater::GetId();
        ResString += "%" + std::to_string(res);
        std::cout<<TempString<<" = "<<"icmp slt "<<LeftValue.TypeToString() <<" " <<LeftValue.LabelToString()<<", "<<RightValue.LabelToString()<<"\n";  
        std::cout<<ResString<<" = "<<"zext i1 "<<TempString<<" to i32\n";
        break;
    case BinOpKind::IsLe:
         temp = TempIdAllocater::GetId();
        TempString = "%" + std::to_string(temp);
        res = TempIdAllocater::GetId();
        ResString += "%" + std::to_string(res);
        std::cout<<TempString<<" = "<<"icmp sle "<<LeftValue.TypeToString() <<" " <<LeftValue.LabelToString()<<", "<<RightValue.LabelToString()<<"\n";  
        std::cout<<ResString<<" = "<<"zext i1 "<<TempString<<" to i32\n";
        break;
    case BinOpKind::IsGt:
        temp = TempIdAllocater::GetId();
        TempString = "%" + std::to_string(temp);
        res = TempIdAllocater::GetId();
        ResString += "%" + std::to_string(res);
        std::cout<<TempString<<" = "<<"icmp sgt "<<LeftValue.TypeToString() <<" " <<LeftValue.LabelToString()<<", "<<RightValue.LabelToString()<<"\n";  
        std::cout<<ResString<<" = "<<"zext i1 "<<TempString<<" to i32\n";
        break;
    case BinOpKind::IsGe:
        temp = TempIdAllocater::GetId();
        TempString = "%" + std::to_string(temp);
        res = TempIdAllocater::GetId();
        ResString += "%" + std::to_string(res);
        std::cout<<TempString<<" = "<<"icmp sge "<<LeftValue.TypeToString() <<" " <<LeftValue.LabelToString()<<", "<<RightValue.LabelToString()<<"\n";  
        std::cout<<ResString<<" = "<<"zext i1 "<<TempString<<" to i32\n";
        break;
    case BinOpKind::rem:
        res = TempIdAllocater::GetId();
        ResString += "%" + std::to_string(res);
        std::cout<<ResString<<" = "<<"srem "<<LeftValue.TypeToString()<<" "<<LeftValue.LabelToString()<<", "<<RightValue.LabelToString()<<"\n";  
        break;
    case BinOpKind::LogicAnd:
        temp1 = TempIdAllocater::GetId();
        temp2 = TempIdAllocater::GetId();
        res = TempIdAllocater::GetId();
        std::cout<<"%"<<temp1<<" = "<<"icmp ne i32 0, "<<LeftValue.LabelToString()<<"\n";
        std::cout<<"%"<<temp2<<" = "<<"icmp ne i32 0, "<<RightValue.LabelToString()<<"\n";
        std::cout<<"%"<<std::to_string(res)<<" = "<<"and i32 %"<<std::to_string(temp1)<<", %"<<std::to_string(temp2);
        ResString = "%" + std::to_string(res);
        break;
    case BinOpKind::LogicOr:
        temp1 = TempIdAllocater::GetId();
        temp2 = TempIdAllocater::GetId();
        res = TempIdAllocater::GetId();
        std::cout<<"%"<<temp1<<" = "<<"icmp ne i32 0, "<<LeftValue.LabelToString()<<"\n";
        std::cout<<"%"<<temp2<<" = "<<"icmp ne i32 0, "<<RightValue.LabelToString()<<"\n";
        std::cout<<"%"<<std::to_string(res)<<" = "<<"or i32 %"<<std::to_string(temp1)<<", %"<<std::to_string(temp2);
        ResString = "%" + std::to_string(res);
        break;
    case BinOpKind::LogicNot:
        res = TempIdAllocater::GetId();
        ResString = "%" + std::to_string(res);
        std::cout<<ResString<<" = "<<"icmp eq i32 0, "<<LeftValue.LabelToString();
        break;
    case BinOpKind::Neg:
        res = TempIdAllocater::GetId();
        ResString = "%" + std::to_string(res);
        std::cout<<ResString<<" = "<<"sub i32 0, "<<LeftValue.LabelToString();
        break;
    default:
        res = 0;
        break;
    }
    ResVal.TempId = res;
    return ResVal;
}

ExpValue MemIRT::ExpDump() const
{
    auto res =  AddressExp->ExpDump();
    BitCast(res,IrValType::i32,true);
    return res;
}
ExpValue TempIRT::ExpDump() const
{
    ExpValue res;
    res.TempId = this->TempVarId;
    return res;
}
ExpValue ESeqIRT::ExpDump() const
{
    SideEffectStm->Dump();
    return EstimatedExp->ExpDump();
}
ExpValue NameIRT::ExpDump() const
{
    ExpValue res;
    res.VarName = this->AsmLableName;
    if(this->ArrayDim.size())
    {
        res.IsPtr = true;
        res.ExpDim = this->ArrayDim;
    }
    return res;
}
ExpValue ConstIRT::ExpDump() const
{
    ExpValue res;
    res.IsConst = true;
    res.ConstValue = this->ConstVal;
    return res;
 
}
ExpValue CallIRT::ExpDump() const
{
    ExpValue res;
    std::string ResString("");
    std::string RetTypeString;
    std::vector<ExpValue> ArgsVal;
    for(auto &it:this->ArgsExpList){
        auto TempVal = it->ExpDump();
        ArgsVal.push_back(TempVal);
    }
    int TempId = TempIdAllocater::GetId();
    if (RetValType == ValueType::INT32)
        res.ExpType = IrValType::i32;
    else
        res.ExpType = IrValType::_void_;
    std::cout<<"%"<<TempId<<" = "<<"call " << RetTypeString << " @" << FuncLable->LableName + "(";
    res.TempId = TempId;
    for (int i = 0; i < ArgsVal.size(); ++i)
    {
        std::cout <<ArgsVal[i].TypeToString()<<" "<<ArgsVal[i].LabelToString();
        if (i != ArgsVal.size() - 1)
        {
            std::cout<<", ";
        }
    }
    std::cout<<")\n";
    return res;
}
ExpValue AllocateIRT::ExpDump() const{
    ExpValue res;
    std::cout<<"%"<<this->ident<<" = " <<"alloca i32 ";
    PrintInitialStruct(this->ArrDim,0);
    if(AlignSize>1){
        std::cout<<", align " <<std::to_string(AlignSize);
    }
    std::cout<<"\n";
    res.IsPtr = true;
    res.ExpDim = this->ArrDim;
    res.VarName = "%" + this->ident;
    BitCast(res,IrValType::i64,false);
    return res;
}
void FuncIRT::Dump() const{
    std::string FuncTypeStr("");
    if(RetValType==ValueType::INT32){FuncTypeStr="i32";}
    else if(RetValType==ValueType::VOID){FuncTypeStr="void";}
    std::cout <<"define "<<FuncTypeStr<<" @"<<this->FuncLable->LableName<<"(";
    TempIdAllocater::Rewind();
    // int TempId;
    // for(int i=0;i<this->ArgsCount;++i){
    //     std::cout<<"i32 ";
    //     TempId = TempIdAllocater::GetId();
    //     std::cout<<"%"<<TempId;
    //     if(i<this->ArgsCount-1){
    //         std::cout<<", ";
    //     }
    // }
    for(int i=0;i<this->ArgsVec.size();++i){
        std::cout << EnumToString(ArgsVec[i]);
        std::cout<<" ";
        std::cout<< this->ParameterNameVec[i];
        if(i!=this->ArgsVec.size()-1){
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
    ExpValue Value;
    if(this->RetExp!=NULL){
        Value = this->RetExp->ExpDump();
        // CheckAndConvertExpToTemp(ValueStr);
    }
    std::cout<<"ret "<<Value.TypeToString()<<" "<<Value.LabelToString();
    std::cout<<"\n";
}
void GlobalVarIRT::Dump() const{
    if(this->GlobalVarType == ValueType::INT32){
        int size = 1;
        if(this->IsArray){
            for(auto &it:this->DimVec){
                size *= it;
            }
        }
        int AddressSpace = size << 2;
        std::cout<<"\n"<<"@"<<this->GlobalVarName<<" = "<<"addrspace("<<AddressSpace<<") ";
        if(this->IsConstant){
            std::cout<<"constant ";
        }else{
            std::cout<<"global ";
        }
        // std::cout<<"i32 ";
        PrintInitialStruct(this->DimVec,0);
        if(this->InitVal!=NULL){
            ConvertIntTreeToInitializer(this->InitVal,this->DimVec,0);
        }
        else{
            std::cout<<this->Int32Val;
        }
        std::cout<<", align 4\n";
    }
    else{
        // to be implemented
        DLOG(ERROR)<<"NOT IMPLEMENTED YET!\n";
    }
}
void ExpIRT::Dump() const{
    
}
