#include"symtable/symbol_table.h"
std::string SymbolTable::AddSymbol(SymType type,std::string name){
    std::string SymName("");
    int LastTableIndex = this->TableVec.size()-1;
    if(LastTableIndex!=1){
        SymName = "%" + name;
    }else{
        SymName = "@" + name;
    }
    
    this->TableVec[LastTableIndex].insert(std::pair<std::string,Symbol*>(name,new Symbol(type,SymName)));
    return SymName;
}
Symbol* SymbolTable::FindSymbol(std::string name){
    for(auto it = this->TableVec.rbegin();it!=this->TableVec.rend();it++){
        auto FindIt = it->find(name);
        if(FindIt!=it->end()){
            return FindIt->second;
        }
    }
    return NULL;
}
void SymbolTable::EnterScope(){
    this->TableVec.push_back(std::map<std::string,Symbol*>());
}
void SymbolTable::ExitScope(){
    for(auto &it:this->TableVec[this->TableVec.size()-1]){
        delete it.second;
    }
    this->TableVec.pop_back();
}