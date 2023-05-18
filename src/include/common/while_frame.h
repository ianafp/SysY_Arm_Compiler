#ifndef _WHILE_FRAME_
#define _WHILE_FRAME_
#include <vector>
#include "ir/ir_tree.h"

class WhileFrame
{
private:
    static std::vector<LabelIRT*> begin;
    static std::vector<LabelIRT*> end;

public:
    static void init_frame();
    static void push_back(LabelIRT* b, LabelIRT* e);
    static void pop_back();
    static LabelIRT* back(bool is_begin);
    static bool check_empty();
};

#endif