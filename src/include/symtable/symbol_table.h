#ifndef _SYMBOL_TABLE_
#define _SYMBOL_TABLE_
#include<map>
#include<vector>
#include"common/enum.h"
class FunctionInfo{
public:
    ValueType RetValType;
    std::vector<ArgsType> ArgsTypeVec;
    FunctionInfo(){}
    FunctionInfo(ValueType ret,std::vector<ArgsType> args):RetValType(ret),ArgsTypeVec(args){}
};
class ArrayInfo{
public:
    std::vector<int> ArrayDimVec;
    ArrayInfo(){}
    ArrayInfo(std::vector<int> vec):ArrayDimVec(vec){}
};
// Note: the SymbolName is not equal to the key of table, SymbolName contains "%" or "@"
class Symbol{
public:
    SymType SymbolType;
    std::string SymbolName;
    bool ConstFlag;
    ArrayInfo ArrAttributes;
    FunctionInfo FunctionAttributes;
    Symbol(std::string name):SymbolType(SymType::Label),SymbolName(name){}
    Symbol(std::string name,std::vector<int> vec,bool IsConst = false):SymbolType(SymType::Int32Array),SymbolName(name),ArrAttributes(vec){}
    Symbol(std::string name,ValueType ret,std::vector<ArgsType> args):SymbolType(SymType::FuncName),FunctionAttributes(ret,args){}
};
class SymbolTable{
public:
    /**
     * @brief default ctor
    */
    // SymbolTable(){
    //     // init the basic table which contains global symbol
    //     TableVec.push_back(std::map<std::string,Symbol*>());
    // }
    /**
     * @brief add a new symbol
     * @author zhang xin
     * @param sym a symbol ptr
     * @return return  symbol name string, which contains "%" or "@" to imply global or local
     * @example: AddSymbol(new Symbol(SymType::INT32,"result"))
    */
    static std::string AddSymbol(std::string name,Symbol* sym);
    /**
     * @brief get a symbol by name
     * @param name: symbol name string
     * @return return a symbol ptr, if not find , return NULL
     * @example Symbol* sym = FindSymbol("name");
    */
    static Symbol* FindSymbol(std::string name);
    /**
     * @brief call when you enter a new scope
    */
    static void EnterScope();
    /**
     * @brief call when you exit a  scope
    */
    static void ExitScope();

private:
    static std::vector<std::map<std::string,Symbol*>> TableVec;
};
#endif