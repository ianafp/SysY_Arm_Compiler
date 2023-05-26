#include"ir/temp_type.h"
void ConvertMemToTemp(ExpValue& val)
{
    if(val.IsPtr==false)
    {
        return;
    }
    BitCast(val,IrValType::i32,true);
    int TempId = TempIdAllocater::GetId();
    
    std::cout<<"%"<<std::to_string(TempId)<<" = "<<"load i32,i32* "<<val.LabelToString()<<"\n";
    val.IsPtr = false;
    val.TempId = TempId;
    val.VarName = "";
}
std::ostream & operator<<(std::ostream &o,const ExpValue& val)
{
    o<< val.TypeToString()<<" "<<val.LabelToString()<<" ";
    return o;
}
void ConvertPtrToInt(ExpValue& val)
{
    if(val.IsPtr==false)
    {
        return;
    }
    int TempId = TempIdAllocater::GetId();
    std::cout<<"%"<<std::to_string(TempId)<<" = "<<"ptrtoint "<<val.TypeToString()<<" "<<val.LabelToString()<<" to i64\n";
    val.IsPtr = false;
    val.TempId = TempId;
    val.ExpType = IrValType::i64;
    val.VarName = "";
    
}
void ConvertIntToPtr(ExpValue& val)
{
    if(val.IsPtr == true)
    {
        return;
    }
    int TempId = TempIdAllocater::GetId();
    std::cout<<"%"<<std::to_string(TempId)<<" = "<<"inttoptr "<<val.TypeToString()<<" "<<val.LabelToString()<<" to i32*\n";
    val.IsPtr = true;
    val.TempId = TempId;
    val.ExpType = IrValType::i32;
}
void BitCast(ExpValue& val,IrValType type,bool IsPtr)
{
    if(val.ExpType==type && val.IsPtr == IsPtr && val.ExpDim.size()==0)
    {
        return;
    }
    if(val.ExpDim.size()&& val.ExpDim[0] == 0) return;
    int TempId = TempIdAllocater::GetId();
    std::cout<<"%"<<std::to_string(TempId)<<" = "<< "bitcast " << val.TypeToString()<<" "<<val.LabelToString() << " to "<<EnumToString(type)<< (IsPtr? "*":"")<<"\n";
    val.IsPtr = IsPtr;
    val.TempId = TempId;
    val.ExpType = type;
    val.VarName = "";
    val.ExpDim = std::vector<int>();
}
IrValType OpBitSignedExtension(ExpValue &val1,ExpValue &val2)
{
    int BitWidth1 = int(val1.ExpType),BitWidth2 = int(val2.ExpType);
    if(val1.ExpType==val2.ExpType)
    {
        return val1.ExpType;
    }
    if(BitWidth1<BitWidth2)
    {
        int TempId = TempIdAllocater::GetId();
        std::cout<< "%" << std::to_string(TempId) << " = "<< "sext "<<val1.TypeToString()<<" "<<val1.LabelToString()<< " "<<"to "<<val2.TypeToString()<<"\n";
        val1.ExpType = val2.ExpType;
        val1.TempId = TempId;
        val1.VarName = "";
    }
    else
    {
        int TempId = TempIdAllocater::GetId();
        std::cout<< "%" << std::to_string(TempId) << " = "<< "sext "<<val2.TypeToString()<< " "<<val2.LabelToString()<<" to "<<val1.TypeToString()<<"\n";
        val2.ExpType = val1.ExpType;
        val2.TempId = TempId;
        val2.VarName = "";
    }
    return val1.ExpType;
}
std::string GetArrayStruct(IrValType type,const std::vector<int> &dim)
{
    std::string res("");
    if(dim[0] == 0)
    {
        return EnumToString(type);
    }
    for(int i=0;i<dim.size();++i)
    {
        res += "[ ";
        res += std::to_string(dim[i]);
        res += " x";
    }
    res += " "+ EnumToString(type) + " ";
    for(int i=0;i<dim.size();++i)
    {
        res += "]";
    }
    return res;
}
std::string ExpValue::LabelToString() const
{
    // if(this->TempId)
    // {
    //     return "%" + std::to_string(this->TempId);
    // }
    if(this->IsConst)
    {
        return std::to_string(this->ConstValue);
    }
    else if(this->VarName[0] == '@' )
    {
        return this->VarName;
    }
    else{
        return "%" + std::to_string(this->TempId);
    }
}
std::string ExpValue::TypeToString() const
{
    if(this->IsPtr)
    {
        if(this->ExpDim.size())
        {
            return GetArrayStruct(this->ExpType,this->ExpDim) + "*";
        }
        else return EnumToString(this->ExpType) + "* ";
    }
    else
    {
        return EnumToString(this->ExpType);
    }
}