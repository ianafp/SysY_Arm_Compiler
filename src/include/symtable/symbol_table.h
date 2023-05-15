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
class Symbol{
    friend class SymbolTable;
private:
    bool GlobalFlag;
public:
    SymType SymbolType;
    bool ConstFlag;
    std::vector<int> InitValVec;
    ArrayInfo ArrAttributes;
    FunctionInfo FunctionAttributes;
    /**
     * @brief INT Symbol ctor
    */
    Symbol(SymType type,bool IsConst = false):SymbolType(type),ConstFlag(IsConst){}
    /**
     * @brief INT Symbol ctor with init
    */
    Symbol(SymType type,int initval,bool IsConst = false):SymbolType(type),ConstFlag(IsConst),InitValVec(initval){}
    /**
     * @brief lable symbol ctor
    */
    Symbol():SymbolType(SymType::Label){}
    /**
     * @brief array symbol ctor without init
    */
    Symbol(std::vector<int> vec,bool IsConst = false):SymbolType(SymType::Int32Array),ArrAttributes(vec){}
    /**
     * @brief array symbol ctor with init
    */
    Symbol(std::vector<int> vec,std::vector<int> initval,bool IsConst = false):SymbolType(SymType::Int32Array),InitValVec(initval),ArrAttributes(vec){}
    /**
     * @brief function symbol ctor
    */
    Symbol(ValueType ret,std::vector<ArgsType> args):SymbolType(SymType::FuncName),FunctionAttributes(ret,args){}

    /**
     * @brief get a bool return val, true indacates this symbol is global
    */
    bool GetGlobalFlag() const;
    /**
     * @brief this function process the symbol name to label (add '%' or '@' depends on global flag)
    */
   std::string GetLabelStr(std::string SymName) const;

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
     * @return return bool, true indicate duplicate symbol, false otherwise
     * @example: AddSymbol(new Symbol(SymType::INT32,"result"))
    */
    static bool AddSymbol(std::string name,Symbol* sym);
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
    /**
     * @brief Call only once in main, then you can use symbol table
    */
    static void InitTable();

private:
    static std::vector<std::map<std::string,Symbol*>> TableVec;
};
#endif