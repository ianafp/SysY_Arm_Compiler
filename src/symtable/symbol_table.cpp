#include"symtable/symbol_table.h"
std::vector<std::map<std::string,Symbol*>> SymbolTable::TableVec;
std::string SymbolTable::AddSymbol(SymType type,std::string name){
    std::string SymName("");
    int LastTableIndex = TableVec.size()-1;
    if(LastTableIndex!=1){
        SymName = "%" + name;
    }else{
        SymName = "@" + name;
    }
    
    TableVec[LastTableIndex].insert(std::pair<std::string,Symbol*>(name,new Symbol(type,SymName)));
    return SymName;
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