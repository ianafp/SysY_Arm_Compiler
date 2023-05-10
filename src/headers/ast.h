#ifndef __AST_H__
#define __AST_H__

#include <iostream>
#include <memory>
#include <string>
#include <list>
#include <vector>

#include "position.h"
/*
 * This file contains AST classes' declarations
 *
*/

// 所有 AST 的基类
class BaseAST {
 public:
  virtual ~BaseAST() = default;
  virtual void Dump() const = 0;
  virtual std::string type(void) const {
    std::unique_ptr<std::string> rst_ptr(new std::string("BaseAST"));
    return *rst_ptr;
  }
  pos_t position;
};

// CompUnit 是 BaseAST
class CompUnitAST : public BaseAST {
 public:
  // 用智能指针管理对象
  BaseAST* comp_unit;
  void Dump() const override {
    
    std::cout << "CompUnitAST { \n\t";
    comp_unit->Dump();
    std::cout << "\n\t }";
  }
  std::string type(void) const override {
    std::unique_ptr<std::string> rst_ptr(new std::string("CompUnitAST"));
    return *rst_ptr;
  }
};

// Compunit --temporary
class CompunitAST : public BaseAST {
 public:
  // 用智能指针管理对象
  std::list<BaseAST*> decl_list;
  void Dump() const override {
    
    // std::cout << "CompUnitAST { ";
    for(auto &it:decl_list){
      it->Dump();
    }
    // std::cout << " }";
  }
  std::string type(void) const override {
    std::unique_ptr<std::string> rst_ptr(new std::string("CompunitAST"));
    return *rst_ptr;
  }
};

//Declare Part
// Decl 也是 BaseAST
class DeclAST : public BaseAST {
 public:
  BaseAST* const_or_var_decl;
  void Dump() const override{
    std::cout << "DeclAST { ";
    const_or_var_decl->Dump();
    std::cout << " }";
  }
  std::string type(void) const override {
    std::unique_ptr<std::string> rst_ptr(new std::string("DeclAST"));
    return *rst_ptr;
  }
};

class ConstDeclAST : public BaseAST {
 public:
  BaseAST* BType;
  std::list<BaseAST*> constdef_list;
  void Dump() const override{
    std::cout << "DeclAST { ";
    BType->Dump();
    for(auto &it:constdef_list){
      it->Dump();
    }
    std::cout << " }";
  }
  std::string type(void) const override {
    std::unique_ptr<std::string> rst_ptr(new std::string("ConstDeclAST"));
    return *rst_ptr;
  }
};

//Function Definition Part
// FuncDef 也是 BaseAST
class FuncDefAST : public BaseAST {
 public:
  BaseAST* func_type;
  std::string* ident;
  BaseAST* func_fparams;
  BaseAST* block;
  void Dump() const override {
    std::cout << "FuncDefAST { ";
    func_type->Dump();
    std::cout << ", " << *ident << ", ";
    if(func_fparams)
      func_fparams->Dump();
    block->Dump();
    std::cout << " }";
  }
  std::string type(void) const override {
    std::unique_ptr<std::string> rst_ptr(new std::string("FuncDefAST"));
    return *rst_ptr;
  }
};

class FuncTypeAST : public BaseAST {
 public:
  std::string type_ret;
  void Dump() const override {
    std::cout << "FuncTypeAST { ";
    std::cout << type_ret;
    std::cout << " }";
  }
  std::string type(void) const override {
    std::unique_ptr<std::string> rst_ptr(new std::string("FuncTypeAST"));
    return *rst_ptr;
  }
};

class BlockAST : public BaseAST {
 public:
  BaseAST* block;
  void Dump() const override {
    std::cout << "BlockAST { ";
    block->Dump();
    std::cout << " }";
  }
  std::string type(void) const override {
    std::unique_ptr<std::string> rst_ptr(new std::string("BlockAST"));
    return *rst_ptr;
  }
};

class blockAST : public BaseAST {
 public:
  std::list<BaseAST*> block_item;
  void Dump() const override {
    // std::cout << "blockAST { ";
    for(auto &it:block_item)
    {
      it->Dump();
    }
    // std::cout << " }";
  }
  std::string type(void) const override {
    std::unique_ptr<std::string> rst_ptr(new std::string("blockAST"));
    return *rst_ptr;
  }
};

class BlockItemAST : public BaseAST {
 public:
  BaseAST* decl_or_stmt;
  void Dump() const override {
    std::cout << "BlockItemAST { ";
    decl_or_stmt->Dump();
    std::cout << " }";
  }
  std::string type(void) const override {
    std::unique_ptr<std::string> rst_ptr(new std::string("BlockItemAST"));
    return *rst_ptr;
  }
};

class StmtAST : public BaseAST {
 public:
  std::string tp;
  std::string ret_string;
  // int ret_number;
  BaseAST* ret_exp;
  void Dump() const override {
    std::cout << "StmtAST { ";
    if(tp == "retexp")
    {
      std::cout << ret_string << ", ";
      ret_exp->Dump();
    }
    std::cout << " }";
  }
  std::string type(void) const override {
    std::unique_ptr<std::string> rst_ptr(new std::string("StmtAST"));
    return *rst_ptr;
  }
};

class ExpAST : public BaseAST {
 public:
  // std::string type;
  // std::string ret_string;
  BaseAST* lor_exp;
  void Dump() const override {
    std::cout << "ExpAST { ";
    lor_exp->Dump();
    std::cout << " }";
  }
  std::string type(void) const override {
    std::unique_ptr<std::string> rst_ptr(new std::string("ExpAST"));
    return *rst_ptr;
  }
};

class LOrExpAST : public BaseAST {
 public:
  std::vector<BaseAST*> land_exp;
  std::vector<std::string> op;
  void Dump() const override {
    std::cout << "LOrExpAST { ";
    for(int i = 0; i < land_exp.size(); i++)
    {
      if(i != 0)
      {
        std::cout << " " << op[i-1] << " ";
      }
      land_exp[i]->Dump();
    }
    
    std::cout << " }";
  }
  std::string type(void) const override {
    std::unique_ptr<std::string> rst_ptr(new std::string("LOrExpAST"));
    return *rst_ptr;
  }
};

class LAndExpAST : public BaseAST {
 public:
  std::vector<BaseAST*> eq_exp;
  std::vector<std::string> op;
  void Dump() const override {
    std::cout << "LAndExpAST { ";
    for(int i = 0; i < eq_exp.size(); i++)
    {
      if(i != 0)
      {
        std::cout << " " << op[i-1] << " ";
      }
      eq_exp[i]->Dump();
    }
    
    std::cout << " }";
  }
  std::string type(void) const override {
    std::unique_ptr<std::string> rst_ptr(new std::string("LAndExpAST"));
    return *rst_ptr;
  }
};

class EqExpAST : public BaseAST {
 public:
  std::vector<BaseAST*> rel_exp;
  std::vector<std::string> op;
  void Dump() const override {
    std::cout << "EqExpAST { ";
    for(int i = 0; i < rel_exp.size(); i++)
    {
      if(i != 0)
      {
        std::cout << " " << op[i-1] << " ";
      }
      rel_exp[i]->Dump();
    }
    
    std::cout << " }";
  }
  std::string type(void) const override {
    std::unique_ptr<std::string> rst_ptr(new std::string("EqExpAST"));
    return *rst_ptr;
  }
};

class RelExpAST : public BaseAST {
 public:
  std::vector<BaseAST*> add_exp;
  std::vector<std::string> op;
  void Dump() const override {
    std::cout << "RelExpAST { ";
    for(int i = 0; i < add_exp.size(); i++)
    {
      if(i != 0)
      {
        std::cout << " " << op[i-1] << " ";
      }
      add_exp[i]->Dump();
    }
    
    std::cout << " }";
  }
  std::string type(void) const override {
    std::unique_ptr<std::string> rst_ptr(new std::string("RelExpAST"));
    return *rst_ptr;
  }
};
class AddExpAST : public BaseAST {
 public:
  //for instance: exp1 + exp2 - exp3
  std::vector<BaseAST*> mul_exp;
  //mul_exp: exp1 exp2 exp3
  std::vector<std::string> op;
  //op: + -
  void Dump() const override {
    std::cout << "AddExpAST { ";
    for(int i = 0; i < mul_exp.size(); i++)
    {
      if(i != 0)
      {
        std::cout << " " << op[i-1] << " ";
      }
      mul_exp[i]->Dump();
    }
    
    std::cout << " }";
  }
  std::string type(void) const override {
    std::unique_ptr<std::string> rst_ptr(new std::string("AddExpAST"));
    return *rst_ptr;
  }
};

class MulExpAST : public BaseAST {
 public:
  //for instance: exp1 + exp2 - exp3
  std::vector<BaseAST*> unary_exp;
  //mul_exp: exp1 exp2 exp3
  std::vector<std::string> op;
  //op: + -
  void Dump() const override {
    std::cout << "MulExpAST { ";
    for(int i = 0; i < unary_exp.size(); i++)
    {
      if(i != 0)
      {
        std::cout << " " << op[i-1] << " ";
      }
      unary_exp[i]->Dump();
    }
    
    std::cout << " }";
  }
  std::string type(void) const override {
    std::unique_ptr<std::string> rst_ptr(new std::string("MulExpAST"));
    return *rst_ptr;
  }
};

class UnaryExpAST : public BaseAST {
 public:
  std::string tp;
  BaseAST* primary_exp;
  BaseAST* unary_op;
  BaseAST* unary_exp;
  void Dump() const override {
    std::cout << "UnaryExpAST { ";
    if(tp == "primary")
      primary_exp->Dump();
    else if(tp == "op+exp")
    {
      unary_op->Dump();
      std::cout << ", ";
      unary_exp->Dump();
    }
    std::cout << " }";
  }
  std::string type(void) const override {
    std::unique_ptr<std::string> rst_ptr(new std::string("UnaryExpAST"));
    return *rst_ptr;
  }
};

class PrimaryExpAST : public BaseAST {
 public:
  std::string tp;
  BaseAST* exp;
  BaseAST* number;
  void Dump() const override {
    std::cout << "PrimaryExpAST { ";
    if(tp == "exp")
      exp->Dump();
    else if(tp == "number")
      number->Dump();
    std::cout << " }";
  }
  std::string type(void) const override {
    std::unique_ptr<std::string> rst_ptr(new std::string("PrimaryExpAST"));
    return *rst_ptr;
  }
};

class NumberAST : public BaseAST {
 public:
  int num;
  void Dump() const override {
    std::cout << "NumberAST { ";
    std::cout << num;
    std::cout << " }";
  }
  std::string type(void) const override {
    std::unique_ptr<std::string> rst_ptr(new std::string("NumberAST"));
    return *rst_ptr;
  }
};

class UnaryOpAST : public BaseAST {
 public:
  std::string op;
  void Dump() const override {
    std::cout << "UnaryOpAST { ";
    std::cout << op;
    std::cout << " }";
  }
  std::string type(void) const override {
    std::unique_ptr<std::string> rst_ptr(new std::string("UnaryOpAST"));
    return *rst_ptr;
  }
};

#endif