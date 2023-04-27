#ifndef __AST_H__
#define __AST_H__

#include <iostream>
#include <memory>
#include <string>
#include <list>
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
  virtual std::string type(void) const =0;
  pos_t position;
};

// CompUnit 是 BaseAST
class CompUnitAST : public BaseAST {
 public:
  // 用智能指针管理对象
  std::list<BaseAST*> decl_list;
  void Dump() const override {
    
    std::cout << "CompUnitAST { ";
    for(auto &it:decl_list){
      it->Dump();
    }
    std::cout << " }";
  }
  std::string type(void) const override {
    std::unique_ptr<std::string> rst_ptr(new std::string("CompUnitAST"));
    return *rst_ptr;
  }
};
// 声明 Decl -> ConstDecl | VarDecl
class DeclAST: public BaseAST{
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
// 常量声明 ConstDecl -> 'const' BType ConstDef {',' ConstDef}';'
class ConstDeclAST: public BaseAST{
  public:
  std::unique_ptr<BaseAST> BType;
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
// FuncDef 也是 BaseAST
class FuncDefAST : public BaseAST {
 public:
  std::unique_ptr<BaseAST> func_type;
  std::string ident;
  std::unique_ptr<BaseAST> block;
  void Dump() const override {
    std::cout << "FuncDefAST { ";
    func_type->Dump();
    std::cout << ", " << ident << ", ";
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
  std::unique_ptr<BaseAST> stmt;
  void Dump() const override {
    std::cout << "BlockAST { ";
    stmt->Dump();
    std::cout << " }";
  }
  std::string type(void) const override {
    std::unique_ptr<std::string> rst_ptr(new std::string("BlockAST"));
    return *rst_ptr;
  }
};

class StmtAST : public BaseAST {
 public:
  std::string ret_string;
  int ret_number;
  void Dump() const override {
    std::cout << "StmtAST { ";
    std::cout << ret_string << ", " << ret_number;
    std::cout << " }";
  }
  std::string type(void) const override {
    std::unique_ptr<std::string> rst_ptr(new std::string("StmtAST"));
    return *rst_ptr;
  }
};

#endif