#include "common/initval_tree.h"

bool ConvertTreeToInt(InitValTree<BaseAST *> *AstTree, InitValTree<int> *&IntTree)
{
    IntTree = new InitValTree<int>();
    for (auto &it : AstTree->childs)
    {
        InitValTree<int> *TempPtr;
        if (ConvertTreeToInt(it, TempPtr))
        {
            // if not const
            delete IntTree;
            IntTree = NULL;
            return true;
        }
        IntTree->childs.push_back(TempPtr);
    }
    for (auto &it : AstTree->keys)
    {
        int temp;
        if (it->GetConstVal(temp))
        {
            delete IntTree;
            IntTree = NULL;
            return true;
        }
        IntTree->keys.push_back(temp);
    }
    return false;
}
void PrintInitialStruct(const std::vector<int> &dim, int level)
{
    if (level == dim.size() || dim[0] == 0)
    {
        std::cout << "i32 ";
        return;
    }
    std::cout << "[ " << dim[level] << " x ";
    PrintInitialStruct(dim, level + 1);
    std::cout << "]";
}
std::string GetInitialStruct(const std::vector<int> &dim, int level)
{
    std::string res("");
    for (int i = level; i < dim.size(); ++i)
    {
        res += "[ ";
        res += std::to_string(dim[i]);
        res += " x";
    }
    res += " i32 ";
    for (int i = level; i < dim.size(); ++i)
    {
        res += "] ";
    }
    return res;
}
std::string InternalInitializerConvert(InitValTree<int> *IntTree, const std::vector<int> &dim,int level)
{
    std::string res("");
    int len;

    if(level>=dim.size())
    {
        len = 1;
    }
    else
    {
        len = dim[level];
    }
    if(len!=1)
    {
        res += "[";
    }
    if(IntTree->childs.size())
    {
        int i;

        for(i = 0;i < IntTree->childs.size();++i)
        {
            res += InternalInitializerConvert(IntTree->childs[i],dim,level+1);
            if(i!=len-1)
            {
                res += ", ";
            }
        }
        if(level==dim.size()-1)
        {
            for( ; i < len; ++i)
            {
                res += "i32 0";
                if(i!=len-1)
                {
                    res += ", ";
                }
            }
        }
        else
        {
            for( ; i < len; ++i)
            {
                res += GetInitialStruct(dim,level);
                if(i!=len-1)
                {
                    res += ", ";
                }
            }
        }
    }
    else 
    {
        res += "i32 "+std::to_string(IntTree->keys[0]);
    }
    if(len!=1)
    {
        res += "]";
    }
    return res;
}
void ConvertIntTreeToInitializer(InitValTree<int> *IntTree, const std::vector<int> &dim)
{
    std::string res (""),head(""),tail(""),temp("");
    // get init value tree depth
    int depth = 0;
    auto p = IntTree->childs[0];
    while(1)
    {
        if(p->childs.size())
        {
            depth++;
            p = p->childs[0];
        }
        else
        {
            break;
        }
    }
    // if no array
    if(depth==0)
    {
        std::cout<<" i32 "<<IntTree->FindFirst();
        return;
    }
    // if array
    // handle the case init value dimension less than the array dimension
    if(depth<dim.size())
    {

        for(int i = 0;i<dim.size()-depth;++i)
        {
            head += "[ ";
            temp = "";
            for(int j=1;j<dim[i];++j)
            {
                temp +=  GetInitialStruct(dim,i+1) + "zeroinitializer" ;
                if(j!=dim[i]-1)
                {
                    temp += ", ";
                }
            }
            tail = temp + "]" + tail;
        }
        tail = ", " + tail;
    }
    // handle init value
    res = head + InternalInitializerConvert(IntTree->childs[0],dim,dim.size()-depth) + tail;
    // return res;
    std::cout<<res;
}

void AdjustTree(InitValTree<BaseAST *> *&tree)
{
    for (auto &it : tree->childs)
    {
        AdjustTree(it);
    }
    if (tree->childs.size() == 1)
    {
        InitValTree<BaseAST *> *temp = tree->childs[0];
        free(tree);
        tree = temp;
    }
}