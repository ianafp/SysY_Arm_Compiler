#ifndef _SYMBOL_TABLE_
#define _SYMBOL_TABLE_
#include<map>
#include<vector>
enum class SymType
{
    Label,
    FuncName,
    INT32,
    IntArray
};
// Note: the SymbolName is not equal to the key of table, SymbolName contains "%" or "@"
class Symbol{
public:
    SymType SymbolType;
    std::string SymbolName;
    std::vector<int> ArrayDimVec;
    Symbol(SymType type,std::string name):SymbolType(type),SymbolName(name){}
    Symbol(std::string name,std::vector<int> vec):SymbolType(SymType::IntArray),SymbolName(name),ArrayDimVec(vec){}
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
    static std::string AddSymbol(SymType type,std::string name);
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