#ifndef _SYMBOL_TABLE_
#define _SYMBOL_TABLE_
#include<map>
#include<vector>
#include"common/enum.h"
#include"common/initval_tree.h"
#include"common/base_ast.h"
class VarInfo{
public:
    bool IsInited;
    int InitVal;
    BaseAST* ExpVal;
    VarInfo(int val):IsInited(true),InitVal(val),ExpVal(NULL) {}
    VarInfo():IsInited(false),InitVal(0),ExpVal(NULL){}
};
class FunctionInfo{
public:
    ValueType RetValType;
    std::vector<ArgsType> ArgsTypeVec;
    FunctionInfo(){}
    FunctionInfo(ValueType ret,std::vector<ArgsType> args):RetValType(ret),ArgsTypeVec(args){}
};
class ArrayInfo{
public:
    bool IsInited;
    bool IsConstInit;
    std::vector<int> ArrayDimVec;
    InitValTree<BaseAST*> *VarInitVal;
    InitValTree<int> *ConstInitVal; 
    ArrayInfo():IsInited(false),IsConstInit(false),VarInitVal(NULL),ConstInitVal(NULL){}
    ArrayInfo(std::vector<int> vec):IsInited(false),IsConstInit(false),ArrayDimVec(vec),
    VarInitVal(NULL),ConstInitVal(NULL){}
    ArrayInfo(std::vector<int> vec,InitValTree<BaseAST*> * VarInit):IsInited(true),IsConstInit(false),ArrayDimVec(vec),VarInitVal(VarInit),ConstInitVal(NULL){}
    ArrayInfo(std::vector<int> vec,InitValTree<int> * ConstInit):IsInited(true),IsConstInit(false),ArrayDimVec(vec),VarInitVal(NULL),ConstInitVal(ConstInit){}  
    ~ArrayInfo(){
        delete VarInitVal;
        delete ConstInitVal;
    }
};
class Symbol{
    friend class SymbolTable;
private:
    bool GlobalFlag;
public:
    SymType SymbolType;
    bool ConstFlag;
    VarInfo VarArrtributes;
    ArrayInfo* ArrAttributes;
    FunctionInfo* FunctionAttributes;
    /**
     * @brief var ctor
    */
   Symbol(bool IsConst,int val = 0):SymbolType(SymType::INT32),ConstFlag(IsConst),VarArrtributes(val){
        ArrAttributes = NULL;
        FunctionAttributes = NULL;
   }
    /**
     * 
     * @brief var symbol ctor
    */
//    Symbol(bool IsConst,int initval = 0,BaseAST* initexp = NULL):SymbolType(SymType::INT32),ConstFlag(IsConst)
//    {
//         if(initexp != NULL){
//             VarArrtributes = new VarInfo(initexp);
//         }
//         else VarArrtributes = new VarInfo(initval);
//         ArrAttributes = NULL;
//         FunctionAttributes = NULL;
//    }
   /**
    * @brief arr symbol ctor
   */
   Symbol(bool IsConst,std::vector<int> dim,InitValTree<int>* initval = NULL,InitValTree<BaseAST*>* initexp = NULL):SymbolType(SymType::Int32Array),ConstFlag(IsConst)
   {
        if(initexp != NULL){
            ArrAttributes = new ArrayInfo(dim,initexp);
        }
        else ArrAttributes = new ArrayInfo(dim,initval);
        // VarAttributes = NULL;
        FunctionAttributes = NULL;
   }
   /**
    * @brief fun symbol ctor
   */
   Symbol(ValueType ret,std::vector<ArgsType> args):SymbolType(SymType::FuncName)
   {
        ArrAttributes = NULL;
        // VarAttributes = NULL;
        FunctionAttributes = new FunctionInfo(ret,args);
   }

    /**
     * @brief get a bool return val, true indacates this symbol is global
    */
    bool GetGlobalFlag() const;
    /**
     * @brief this function process the symbol name to label (add '%' or '@' depends on global flag)
    */
   std::string GetLabelStr(std::string SymName) const;
   ~Symbol()
   {
        // delete VarArrtributes;
        delete ArrAttributes;
        delete FunctionAttributes;
   }

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