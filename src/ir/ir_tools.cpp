#include"ir/ir_tree.h"
bool isDigit(const std::string &str){
    for(int i =0;i<str.length();++i){
        if(str[i]>'9' || str[i]<'0'){
            return false;
        }
    }
    return true;
}
void CheckAndConvertExpToTemp(std::string &str)
{
    if (str[0] != '%' && str[0] != '@' && !isDigit(str))
    {
        int TempId = TempIdAllocater::GetId();
        std::cout << "%" << TempId << " = " << str << "\n";
        str = "%" + std::to_string(TempId);
    }
}
void AddStmToTree(StatementIRT* &root,StatementIRT* stm){
    if(root==NULL) root = stm;
    else root = new StatementIRT(new SequenceIRT(root,stm));
}