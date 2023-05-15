#include"symtable/symbol_table.h"
std::vector<std::map<std::string,Symbol*>> SymbolTable::TableVec;
void SymbolTable::AddSymbol(std::string name,Symbol* sym){
    std::string SymName("");
    int LastTableIndex = TableVec.size()-1;
    if(LastTableIndex!=1){
        sym->GlobalFlag = false;
    }else{
        sym->GlobalFlag = true;
    }
    TableVec[LastTableIndex].insert(std::pair<std::string,Symbol*>(name,sym));
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