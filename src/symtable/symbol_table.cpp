#include"symtable/symbol_table.h"
std::vector<std::map<std::string,Symbol*>> SymbolTable::TableVec;
bool SymbolTable::AddSymbol(std::string name,Symbol* sym){
    std::string SymName("");
    int LastTableIndex = TableVec.size()-1;
    if(LastTableIndex!=1){
        sym->GlobalFlag = false;
    }else{
        sym->GlobalFlag = true;
    }
    if(TableVec[LastTableIndex].find(name)!=TableVec[LastTableIndex].end()) {
        delete sym;
        return true;
    }
    TableVec[LastTableIndex].insert(std::pair<std::string,Symbol*>(name,sym));
    return false;
}
Symbol* SymbolTable::FindSymbol(std::string name){
    for(auto it = TableVec.rbegin();it!=TableVec.rend();it++){
        auto FindIt = it->find(name);
        if(FindIt!=it->end()){
            return FindIt->second;
        }
    }
    return NULL;
}
void SymbolTable::EnterScope(){
    TableVec.push_back(std::map<std::string,Symbol*>());
}
void SymbolTable::ExitScope(){
    for(auto &it:TableVec[TableVec.size()-1]){
        delete it.second;
    }
    TableVec.pop_back();
}
void SymbolTable::InitTable(){
    if(TableVec.size()==0){
        TableVec.push_back(std::map<std::string,Symbol*>());
        // add function
        std::vector<ArgsType> args;
        // get int
        Symbol* sym = new Symbol(ValueType::INT32,args);
        TableVec[0].insert(std::pair<std::string,Symbol*>("getint",sym));
        // getch
        sym = new Symbol(ValueType::INT32,args);
        TableVec[0].insert(std::pair<std::string,Symbol*>("getch",sym));
        // get array
        args.push_back(ArgsType::Int32Array);
        sym = new Symbol(ValueType::INT32,args);
        TableVec[0].insert(std::pair<std::string,Symbol*>("getarray",sym));
        // putint
        args[0] = ArgsType::Int32;
        sym = new Symbol(ValueType::VOID,args);
        TableVec[0].insert(std::pair<std::string,Symbol*>("putint",sym));
        // putch
        sym = new Symbol(ValueType::VOID,args);
        TableVec[0].insert(std::pair<std::string,Symbol*>("putch",sym));
        // putarray
        args[0] = ArgsType::Int32;
        args.push_back(ArgsType::Int32Array);
        sym = new Symbol(ValueType::VOID,args);
        TableVec[0].insert(std::pair<std::string,Symbol*>("putarray",sym));
        // putf
        args[0] = ArgsType::String;
        args.push_back(ArgsType::VarsPacket);
        sym = new Symbol(ValueType::VOID,args);
        TableVec[0].insert(std::pair<std::string,Symbol*>("putf",sym));

    }
}
bool Symbol::GetGlobalFlag() const{
    return this->GlobalFlag;
}
std::string Symbol:: GetLabelStr(std::string SymName) const{
    if(this->GlobalFlag){
        return "@" + SymName;
    }else{
        return "%" + SymName;
    }
}