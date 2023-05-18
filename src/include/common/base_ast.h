#ifndef _BASE_AST_
#define _BASE_AST_
#include "common/position.h"
#include<iostream>
#include <memory>
#include <string>
#include "glog/logging.h"
// 所有 AST 的基类
class BaseAST
{
public:
  virtual ~BaseAST() = default;
  virtual void Dump() const = 0;
  virtual bool GetConstVal(int &val)const { 
    DLOG(INFO)<<"Base\n";
    return true;
  }
  virtual std::string type(void) const
  {
    std::unique_ptr<std::string> rst_ptr(new std::string("BaseAST"));
    return *rst_ptr;
  }
  pos_t position;
};

#endif 