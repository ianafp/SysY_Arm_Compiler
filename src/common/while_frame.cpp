#include "common/while_frame.h"
std::vector<LabelIRT*> WhileFrame:: begin, WhileFrame::end;
//init frame of while iter
void WhileFrame::init_frame()
{
    if(begin.size()==0){
        begin.push_back(new LabelIRT());
    }
    if(end.size()==0){
        end.push_back(new LabelIRT());
    }
}
//push begin and end label
void WhileFrame::push_back(LabelIRT* b, LabelIRT* e)
{
    begin.push_back(b);
    end.push_back(e);
}
//pop out begin and end label
void WhileFrame::pop_back()
{
    begin.pop_back();
    end.pop_back();
}
//get the last label
LabelIRT* WhileFrame::back(bool is_begin)
{
    if(is_begin)
        return begin.back();
    else
        return end.back();
}

bool WhileFrame::check_empty()
{
    if(begin.size() == 1 && end.size() == 1)
        return true;
    else
        return false;
}