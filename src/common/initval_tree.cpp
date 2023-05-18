#include"common/initval_tree.h"

bool ConvertTreeToInt(InitValTree<BaseAST*> *AstTree,InitValTree<int>* &IntTree){
    IntTree = new InitValTree<int>();
    for(auto &it:AstTree->childs){
        InitValTree<int>* TempPtr;
        if(ConvertTreeToInt(it,TempPtr)){
            // if not const
            delete IntTree;
            IntTree = NULL;
            return true;
        }
        IntTree->childs.push_back(TempPtr);
    }
    for(auto &it:AstTree->keys){
        int temp;
        if(it->GetConstVal(temp)){
            delete IntTree;
            IntTree = NULL;
            return true;
        }
        IntTree->keys.push_back(temp);
    }
    return false;
}
void ConvertIntTreeToInitializer(InitValTree<int>* IntTree)
{
    if(IntTree->childs.size()>1)
    {
        std::cout<<"[";
    }
    if(IntTree->childs.size()){
        for(auto &it:IntTree->childs){
            ConvertIntTreeToInitializer(it);
        }
    }
    else{
        for(int i=0;i<IntTree->keys.size();++i){
            std::cout<<"i32 "<<IntTree->keys[i];
            if(i!=IntTree->keys.size()-1){
                std::cout<<", ";
            }
            else{
                std::cout<<" ";
            }
        }
    }
    if(IntTree->childs.size()>1)
    {
        std::cout<<"]";
    }
}