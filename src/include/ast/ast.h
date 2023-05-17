#ifndef __AST_H__
#define __AST_H__
#include "common/enum.h"
#include "common/visualize.h"
#include <iostream>
#include <memory>
#include <string>
#include <list>
#include <vector>
#include "position.h"
#include "glog/logging.h"
/*
 * This file contains AST classes' declarations
 *
 */

extern class Visualize visual;

std::string EnumToString(AstType type);
std::string EnumToString(VarType type);
std::string EnumToString(StmtType type);

// 所有 AST 的基类
class BaseAST
{
public:
  virtual ~BaseAST() = default;
  virtual void Dump() const = 0;
  virtual std::string type(void) const
  {
    std::unique_ptr<std::string> rst_ptr(new std::string("BaseAST"));
    return *rst_ptr;
  }
  pos_t position;
};

// CompUnit 是 BaseAST
class CompUnitAST : public BaseAST
{
public:
  BaseAST *comp_unit;
  void Dump() const override
  {

    std::cout << "CompUnitAST {\n";
    visual.add_pair(std::string("CompUnitAST"), std::string("CompunitAST"), false);
    comp_unit->Dump();
    std::cout << "\n}(CompUnitAST ends) ";
  }
  std::string type(void) const override
  {
    std::unique_ptr<std::string> rst_ptr(new std::string("CompUnitAST"));
    return *rst_ptr;
  }
};

// Compunit --temporary
class CompunitAST : public BaseAST
{
public:
  std::vector<BaseAST *> decl_list;
  void Dump() const override
  {

    int idx_visual = 0;
    // std::cout << "CompUnitAST { ";
    for (auto &it : decl_list)
    {
      visual.add_pair(std::string("CompunitAST"), std::string("FuncDefAST_instance_") + std::to_string(idx_visual), true);
      it->Dump();
      idx_visual++;
    }
    // std::cout << " }";
  }
  std::string type(void) const override
  {
    std::unique_ptr<std::string> rst_ptr(new std::string("CompunitAST"));
    return *rst_ptr;
  }
};

// member tp =  "ConstDecl" or "VarDecl"
class DeclAST : public BaseAST
{
public:
  AstType tp;
  BaseAST *const_or_var_decl;
  void Dump() const override
  {
    std::cout << "DeclAST {\n";
    const_or_var_decl->Dump();
    std::cout << "\n}(DeclAST ends) ";
  }
  std::string type(void) const override
  {
    std::unique_ptr<std::string> rst_ptr(new std::string("DeclAST"));
    return *rst_ptr;
  }
};
class VarDeclAST : public BaseAST
{
public:
  VarType BType;
  std::vector<BaseAST *> VarDefVec;
  void Dump() const override
  {
    std::cout << "VarDeclAst {\n";
    std::cout << "vartype:" << EnumToString(BType);
    for (auto &it : VarDefVec)
    {
      it->Dump();
    }
    std::cout << "\n}(VarDeclAST ends) ";
  }
};
class VarDefAST : public BaseAST
{
public:
  std::string *VarIdent;
  std::vector<BaseAST *> DimSizeVec;
  bool IsInited;
  std::vector<BaseAST *> *InitValueVec;
  void Dump() const override
  {
    std::cout << *VarIdent;
    for (auto &it : DimSizeVec)
    {
      std::cout << "[" << it << "]";
    }
    std::cout << " = "
              << "{ ";
    for (auto &it : *InitValueVec)
    {
      it->Dump();
      std::cout << " ";
    }
    std::cout << "}";
  }
};
class ConstDeclAST : public BaseAST
{
public:
  VarType BType;
  std::vector<BaseAST *> ConstDefVec;
  void Dump() const override
  {
    std::cout << "DeclAST {\n"
              << "vartype:" << EnumToString(BType);
    for (auto &it : ConstDefVec)
    {
      it->Dump();
    }
    std::cout << "\n}(DeclAST ends) ";
  }
  std::string type(void) const override
  {
    std::unique_ptr<std::string> rst_ptr(new std::string("ConstDeclAST"));
    return *rst_ptr;
  }
  ~ConstDeclAST()
  {
  }
};
class InitValTree
{
public:
  std::vector<InitValTree *> childs;
  std::vector<BaseAST *> keys;
  std::vector<BaseAST *> *ConvertToInitValVec(std::vector<BaseAST *> DimVec)
  {
    DLOG(ERROR) << "NOT IMPLEMENTED YET!\n";
    return new std::vector<BaseAST *>();
  }
};
// Function Definition Part
class FuncDefAST : public BaseAST
{
public:
  VarType func_type;
  std::string *ident;
  BaseAST *func_fparams;
  BaseAST *block;
  void Dump() const override
  {
    std::cout << "FuncDefAST {\n";
    std::string instance_name;
    if (int t = visual.find_map(std::string("CompunitAST"), instance_name)) {
      DLOG(WARNING) << "CompunitAST found " << t;
      std::string id = std::string("FunctionId_") + *ident;
      DLOG(WARNING) << "ID is " << id;
      visual.add_pair(std::string(instance_name), std::string("FuncTypeAST_") + std::string(*ident), false);
      DLOG(WARNING) << "first add pair success";
      visual.add_pair(std::string(instance_name), std::string(id), false);
      visual.add_pair(std::string(instance_name), std::string("FuncFParamsAST_") + std::string(*ident), false);
      visual.add_pair(std::string(instance_name), std::string("Block_") + std::string(*ident), false);
      DLOG(WARNING) << "add pair finished";
      visual.remove_map(std::string("CompunitAST"), instance_name);
      DLOG(WARNING) << "remove map";
    }
    // func_type->Dump();
    std::cout << ", " << *ident << ", ";
    if (func_fparams != nullptr)
      func_fparams->Dump();
    block->Dump();
    std::cout << "\n}(FuncDefAST ends) ";
  }
  std::string type(void) const override
  {
    std::unique_ptr<std::string> rst_ptr(new std::string("FuncDefAST"));
    return *rst_ptr;
  }
};

class FuncTypeAST : public BaseAST
{
public:
  std::string type_ret;
  void Dump() const override
  {
    std::cout << "FuncTypeAST {\n";
    std::cout << type_ret;
    std::cout << "\n}(FuncTypeAST ends) ";
  }
  std::string type(void) const override
  {
    std::unique_ptr<std::string> rst_ptr(new std::string("FuncTypeAST"));
    return *rst_ptr;
  }
};
// AST for Funcfparams list(i.e. in the fundef part)
class FuncFParamsAST : public BaseAST
{
public:
  std::vector<BaseAST *> func_fparam;
  void Dump() const override
  {
    std::cout << "FuncFParamsAST {\n";
    for (auto &it : func_fparam)
    {
      it->Dump();
    }
    std::cout << "\n}(FuncFParamsAST ends) ";
  }
  std::string type(void) const override
  {
    std::unique_ptr<std::string> rst_ptr(new std::string("FuncFParamsAST"));
    return *rst_ptr;
  }
};

// AST for Funcfparam (i.e. in the fundef part)
class FuncFParamAST : public BaseAST
{
public:
  ArgsType tp;
  VarType Btype;
  std::string *ident;
  BaseAST *func_fparam;
  void Dump() const override
  {
    std::cout << "FuncFParamAST {\n";
    if (tp == ArgsType::Int32)
    {
      std::cout << "Btype:" << EnumToString(Btype) << ", " << *ident;
    }
    else if (tp == ArgsType::Int32Array)
    {
      func_fparam->Dump();
    }
    std::cout << "\n}(FuncFParamAST ends) ";
  }
  std::string type(void) const override
  {
    std::unique_ptr<std::string> rst_ptr(new std::string("FuncFParamAST"));
    return *rst_ptr;
  }
};

// AST for Funcfparams list(i.e. in the fundef part)
class FuncRParamsAST : public BaseAST
{
public:
  std::vector<BaseAST *> exp;
  void Dump() const override
  {
    std::cout << "FuncRParamsAST {\n";
    for (auto &it : exp)
    {
      it->Dump();
    }
    std::cout << "\n}(FuncRParamsAST ends) ";
  }
  std::string type(void) const override
  {
    std::unique_ptr<std::string> rst_ptr(new std::string("FuncRParamsAST"));
    return *rst_ptr;
  }
};

class BlockAST : public BaseAST
{
public:
  BaseAST *block;
  void Dump() const override
  {
    std::cout << "BlockAST {\n";
    if (block != nullptr)
      block->Dump();
    std::cout << "\n}(BlockAST ends) ";
  }
  std::string type(void) const override
  {
    std::unique_ptr<std::string> rst_ptr(new std::string("BlockAST"));
    return *rst_ptr;
  }
};

class blockAST : public BaseAST
{
public:
  std::vector<BaseAST *> block_item;
  void Dump() const override
  {
    // std::cout << "blockAST { ";
    for (auto &it : block_item)
    {
      it->Dump();
    }
    // std::cout << " }";
  }
  std::string type(void) const override
  {
    std::unique_ptr<std::string> rst_ptr(new std::string("blockAST"));
    return *rst_ptr;
  }
};

class BlockItemAST : public BaseAST
{
public:
  std::string tp;
  BaseAST *decl_or_stmt;
  void Dump() const override
  {
    std::cout << "BlockItemAST {\n";
    decl_or_stmt->Dump();
    std::cout << "\n}(BlockItemAST ends) ";
  }
  std::string type(void) const override
  {
    std::unique_ptr<std::string> rst_ptr(new std::string("BlockItemAST"));
    return *rst_ptr;
  }
};
class AssignAST : public BaseAST
{
public:
  BaseAST *LVal;
  BaseAST *ValueExp;
  void Dump() const override
  {
    std::cout << "AssignAST {\n";
    LVal->Dump();
    std::cout << ", ";
    ValueExp->Dump();
    std::cout << "\n}(AssignAST ends) ";
  }
  std::string type(void) const override
  {
    std::unique_ptr<std::string> rst_ptr(new std::string("AssignAST"));
    return *rst_ptr;
  }
};
class LValAST : public BaseAST
{
public:
  std::string *VarIdent;
  std::vector<BaseAST *> IndexVec;
  void Dump() const override
  {
    std::cout << "LValAST {\n";
    std::cout << *VarIdent;
    for (auto &it : IndexVec)
    {
      std::cout << "[";
      it->Dump();
      std::cout << "]";
    }
    std::cout << "\n}(LValAST ends) ";
  }
  std::string type(void) const override
  {
    std::unique_ptr<std::string> rst_ptr(new std::string("LValAST"));
    return *rst_ptr;
  }
};
// tp = "block" indicate a block ast member ptr
class StmtAST : public BaseAST
{
public:
  StmtType tp;
  // std::string ret_string;
  // int ret_number;
  BaseAST *ret_exp;
  BaseAST *cond_exp;
  BaseAST *stmt_if;
  BaseAST *stmt_else;
  void Dump() const override
  {
    std::cout << "StmtAST {\n";
    // if(tp == "retexp")
    // {
    //   std::cout << "ret , ";
    //   ret_exp->Dump();

    // }
    if (tp == StmtType::ReturnExp)
    {
      std::cout << EnumToString(tp);
      ret_exp->Dump();
    } else if (tp == StmtType::If)
    {
      std::cout << EnumToString(tp);
      std::cout << EnumToString(tp);
      std::cout << std::endl << "if (" << std::endl;
      cond_exp->Dump();
      std::cout << std::endl << ") {" << std::endl;
      stmt_if->Dump();
      std::cout << std::endl << "}" << std::endl;
    } else if (tp == StmtType::IfElse)
    {
      std::cout << EnumToString(tp);
      std::cout << EnumToString(tp);
      std::cout << std::endl << "if (" << std::endl;
      cond_exp->Dump();
      std::cout << std::endl << ") {" << std::endl;
      stmt_if->Dump();
      std::cout << std::endl << "}" << std::endl;
      std::cout << std::endl << "else {" << std::endl;
      stmt_else->Dump();
      std::cout << std::endl << "}" << std::endl;
    }
    std::cout << "\n}(StmtAST ends) ";
  }
  std::string type(void) const override
  {
    std::unique_ptr<std::string> rst_ptr(new std::string("StmtAST"));
    return *rst_ptr;
  }
};

class ExpAST : public BaseAST
{
public:
  // std::string type;
  // std::string ret_string;
  BaseAST *lor_exp;
  void Dump() const override
  {
    std::cout << "ExpAST {\n";
    lor_exp->Dump();
    std::cout << "\n}(ExpAST ends) ";
  }
  std::string type(void) const override
  {
    std::unique_ptr<std::string> rst_ptr(new std::string("ExpAST"));
    return *rst_ptr;
  }
};

class LOrExpAST : public BaseAST
{
public:
  std::vector<BaseAST *> land_exp;
  std::vector<std::string> op;
  void Dump() const override
  {
    std::cout << "LOrExpAST {\n";
    for (int i = 0; i < land_exp.size(); i++)
    {
      if (i != 0)
      {
        std::cout << " " << op[i - 1] << " ";
      }
      land_exp[i]->Dump();
    }

    std::cout << "\n}(LOrExpAST ends) ";
  }
  std::string type(void) const override
  {
    std::unique_ptr<std::string> rst_ptr(new std::string("LOrExpAST"));
    return *rst_ptr;
  }
};

class LAndExpAST : public BaseAST
{
public:
  std::vector<BaseAST *> eq_exp;
  std::vector<std::string> op;
  void Dump() const override
  {
    std::cout << "LAndExpAST {\n";
    for (int i = 0; i < eq_exp.size(); i++)
    {
      if (i != 0)
      {
        std::cout << " " << op[i - 1] << " ";
      }
      eq_exp[i]->Dump();
    }

    std::cout << "\n}(LAndExpAST ends) ";
  }
  std::string type(void) const override
  {
    std::unique_ptr<std::string> rst_ptr(new std::string("LAndExpAST"));
    return *rst_ptr;
  }
};

class EqExpAST : public BaseAST
{
public:
  std::vector<BaseAST *> rel_exp;
  std::vector<std::string> op;
  void Dump() const override
  {
    std::cout << "EqExpAST {\n";
    for (int i = 0; i < rel_exp.size(); i++)
    {
      if (i != 0)
      {
        std::cout << " " << op[i - 1] << " ";
      }
      rel_exp[i]->Dump();
    }

    std::cout << "\n}(EqExpAST ends) ";
  }
  std::string type(void) const override
  {
    std::unique_ptr<std::string> rst_ptr(new std::string("EqExpAST"));
    return *rst_ptr;
  }
};

class RelExpAST : public BaseAST
{
public:
  std::vector<BaseAST *> add_exp;
  std::vector<std::string> op;
  void Dump() const override
  {
    std::cout << "RelExpAST {\n";
    for (int i = 0; i < add_exp.size(); i++)
    {
      if (i != 0)
      {
        std::cout << " " << op[i - 1] << " ";
      }
      add_exp[i]->Dump();
    }

    std::cout << "\n}(RelExpAST ends) ";
  }
  std::string type(void) const override
  {
    std::unique_ptr<std::string> rst_ptr(new std::string("RelExpAST"));
    return *rst_ptr;
  }
};
class AddExpAST : public BaseAST
{
public:
  // for instance: exp1 + exp2 - exp3
  std::vector<BaseAST *> mul_exp;
  // mul_exp: exp1 exp2 exp3
  std::vector<std::string> op;
  // op: + -
  void Dump() const override
  {
    std::cout << "AddExpAST {\n";
    for (int i = 0; i < mul_exp.size(); i++)
    {
      if (i != 0)
      {
        std::cout << " " << op[i - 1] << " ";
      }
      mul_exp[i]->Dump();
    }

    std::cout << "\n}(AddExpAST ends) ";
  }
  std::string type(void) const override
  {
    std::unique_ptr<std::string> rst_ptr(new std::string("AddExpAST"));
    return *rst_ptr;
  }
};

class MulExpAST : public BaseAST
{
public:
  // for instance: exp1 + exp2 - exp3
  std::vector<BaseAST *> unary_exp;
  // mul_exp: exp1 exp2 exp3
  std::vector<std::string> op;
  // op: + -
  void Dump() const override
  {
    std::cout << "MulExpAST {\n";
    for (int i = 0; i < unary_exp.size(); i++)
    {
      if (i != 0)
      {
        std::cout << " " << op[i - 1] << " ";
      }
      unary_exp[i]->Dump();
    }

    std::cout << "\n}(MulExpAST ends) ";
  }
  std::string type(void) const override
  {
    std::unique_ptr<std::string> rst_ptr(new std::string("MulExpAST"));
    return *rst_ptr;
  }
};

class UnaryExpAST : public BaseAST
{
public:
  ExpType tp;
  BaseAST *primary_exp;
  BaseAST *unary_op;
  BaseAST *unary_exp;
  std::string *ident;
  BaseAST *func_rparam;
  void Dump() const override
  {
    std::cout << "UnaryExpAST {\n";
    if (tp == ExpType::Primary)
      primary_exp->Dump();
    else if (tp == ExpType::OpExp)
    {
      unary_op->Dump();
      std::cout << ", ";
      unary_exp->Dump();
    }
    else if (tp == ExpType::Call)
    {
      std::cout << *ident << ", ";
      if (func_rparam != nullptr)
        func_rparam->Dump();
    }
    std::cout << "\n}(UnaryExpAST ends) ";
  }
  std::string type(void) const override
  {
    std::unique_ptr<std::string> rst_ptr(new std::string("UnaryExpAST"));
    return *rst_ptr;
  }
};

class PrimaryExpAST : public BaseAST
{
public:
  PrimaryType tp;
  BaseAST *exp;
  BaseAST *number;
  void Dump() const override
  {
    std::cout << "PrimaryExpAST {\n";
    if (tp == PrimaryType::Exp)
      exp->Dump();
    else if (tp == PrimaryType::Num)
      number->Dump();
    std::cout << "\n}(PrimaryExpAST ends) ";
  }
  std::string type(void) const override
  {
    std::unique_ptr<std::string> rst_ptr(new std::string("PrimaryExpAST"));
    return *rst_ptr;
  }
};

class NumberAST : public BaseAST
{
public:
  int num;
  void Dump() const override
  {
    std::cout << "NumberAST {\n";
    std::cout << num;
    std::cout << "\n}(NumberAST ends) ";
  }
  std::string type(void) const override
  {
    std::unique_ptr<std::string> rst_ptr(new std::string("NumberAST"));
    return *rst_ptr;
  }
};

class UnaryOpAST : public BaseAST
{
public:
  std::string op;
  void Dump() const override
  {
    std::cout << "UnaryOpAST {\n";
    std::cout << op;
    std::cout << "\n}(UnaryOpAST ends) ";
  }
  std::string type(void) const override
  {
    std::unique_ptr<std::string> rst_ptr(new std::string("UnaryOpAST"));
    return *rst_ptr;
  }
};

#endif