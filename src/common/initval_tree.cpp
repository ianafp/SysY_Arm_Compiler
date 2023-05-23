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
void PrintInitialStruct(const std::vector<int> &dim,int level)
{
    if(level==dim.size()){
        std::cout<<"i32 ";
        return;
    }
    std::cout<<"[ "<<dim[level]<<" x ";
    PrintInitialStruct(dim,level+1);
    std::cout<<"]";
}
void ConvertIntTreeToInitializer(InitValTree<int>* IntTree,const std::vector<int> &dim,int level)
{
    // std::cout<<"[";
    int len = dim.size()==level? 1 : dim[level];
    if(IntTree->keys.size()!=1)
    {
        std::cout<<"[";
    }
    if(IntTree->childs.size()){
        int i;
        for(i=0;i<IntTree->childs.size();++i){
            ConvertIntTreeToInitializer(IntTree->childs[i],dim,level+1);

            if(i!=len-1){
                std::cout<<", ";
            }
        }
        for(;i<len;++i){
            PrintInitialStruct(dim,level);
            std::cout<<" zeroinitializer";
            if(i!=len-1){
                std::cout<<", ";
            }
        }
    }
    else{
        int i;
        for(i=0;i<IntTree->keys.size();++i){
            std::cout<<"i32 "<<IntTree->keys[i];
            if(i!=len-1){
                std::cout<<", ";
            }
            else{
                std::cout<<" ";
            }
        }
        for(;i<len;++i){
            std::cout<<"i32 "<<0;
            if(i!=len-1){
                std::cout<<", ";
            }
            else{
                std::cout<<" ";
            }
        }
    }
    if(IntTree->keys.size()!=1)
    {
        std::cout<<"]";
    }

}

void AdjustTree(InitValTree<BaseAST*>* &tree)
{
    for(auto &it:tree->childs)
    {
        AdjustTree(it);
    }
    if(tree->childs.size()==1){
        InitValTree<BaseAST*>* temp = tree->childs[0];
        free(tree);
        tree = temp;
    }

}