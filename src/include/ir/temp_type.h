#ifndef _TEMP_TYPE_H_
#define _TEMP_TYPE_H_
#include"common/enum.h"
#include<vector>
#include<string>
#include<iostream>
#include"common/temp_allocate.h"
class ExpValue;
std::ostream& operator<<(std::ostream& o,const ExpValue& val);
void ConvertPtrToInt(ExpValue& val);
void ConvertIntToPtr(ExpValue& val);
void ConvertMemToTemp(ExpValue& val);
void BitCast(ExpValue& val,IrValType type,bool IsPtr);
IrValType OpBitSignedExtension(ExpValue &val1,ExpValue &val2);
std::string GetArrayStruct(IrValType type,const std::vector<int> &dim);
class ExpValue
{
public:
    bool IsConst;
    int ConstValue;
    bool IsPtr;
    int TempId;
    std::string VarName;
    IrValType ExpType;
    std::vector<int> ExpDim;
    ExpValue():IsConst(false),ConstValue(0),IsPtr(false),TempId(0),VarName(""),ExpType(IrValType::i32){}
    ExpValue(std::vector<int> dim):IsConst(false),ConstValue(0),IsPtr(true),TempId(0),VarName(""),ExpType(IrValType::i32),ExpDim(dim){}

    std::string LabelToString() const;
    std::string TypeToString() const;
};

#endif