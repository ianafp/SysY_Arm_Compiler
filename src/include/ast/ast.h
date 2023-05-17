#ifndef __AST_H__
#define __AST_H__
#include"common/enum.h"
#include <iostream>
#include <memory>
#include <string>
#include <list>
#include <vector>
#include "glog/logging.h"
#include "symtable/symbol_table.h"
#include"common/initval_tree.h"
#include"common/base_ast.h"
/*
 * This file contains AST classes' declarations
 *
 */

std::string EnumToString(AstType type);
std::string EnumToString(VarType type);
std::string EnumToString(StmtType type);

// CompUnit 是 BaseAST
class CompUnitAST : public BaseAST
{
public:
  // 用智能指针管理对象
  BaseAST *comp_unit;
  void Dump() const override
  {

    std::cout << "CompUnitAST { \n\t";
    comp_unit->Dump();
    std::cout << "\n\t }";
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
  // 用智能指针管理对象
  std::vector<BaseAST *> decl_list;
  void Dump() const override
  {

    // std::cout << "CompUnitAST { ";
    for (auto &it : decl_list)
    {
      it->Dump();
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
    std::cout << "DeclAST { ";
    const_or_var_decl->Dump();
    std::cout << " }";
  }
  std::string type(void) const override
  {
    std::unique_ptr<std::string> rst_ptr(new std::string("DeclAST"));
    return *rst_ptr;
  }

  /**
   * @brief chech the symbol decl, if right, add to symbol and return false, else return true
  */
  bool HandleSymbol() const;
};
class VarDeclAST : public BaseAST
{
public:
  VarType BType;
  std::vector<BaseAST *> VarDefVec;
  void Dump() const override
  {
    std::cout << "VarDeclAst{ ";
    std::cout << "vartype:" << EnumToString(BType);
    for (auto &it : VarDefVec)
    {
      it->Dump();
    }
    std::cout << " }";
  }
  /**
   * @brief chech the symbol decl, if right, add to symbol and return false, else return true
  */
  bool HandleSymbol() const;
};

class VarDefAST : public BaseAST
{
public:
  std::string *VarIdent;
  std::vector<int> DimSizeVec;
  bool IsInited;
  InitValTree<BaseAST*>* InitValue;
  InitValTree<int>* IntInitValue;
  Symbol* VarSym;
  // std::vector<BaseAST *> *InitValueVec;
  void Dump() const override
  {
    std::cout << *VarIdent;
    for (auto &it : DimSizeVec)
    {
      std::cout << "[" << it << "]";
    }
    std::cout << " = "
              << "{ ";
    InitValue->Dump();
    // for (auto &it : *InitValueVec)
    // {
    //   it->Dump();
    //   std::cout << " ";
    // }
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
    std::cout << "DeclAST { "
              << "vartype:" << EnumToString(BType);
    for (auto &it : ConstDefVec)
    {
      it->Dump();
    }
    std::cout << " }";
  }
  std::string type(void) const override
  {
    std::unique_ptr<std::string> rst_ptr(new std::string("ConstDeclAST"));
    return *rst_ptr;
  }
  /**
   * @brief chech the symbol decl, if right, add to symbol and return false, else return true
  */
  bool HandleSymbol() const;
};

// Function Definition Part
//  FuncDef 也是 BaseAST
class FuncDefAST : public BaseAST
{
public:
  BaseAST *func_type;
  std::string *ident;
  BaseAST *func_fparams;
  BaseAST *block;
  void Dump() const override
  {
    std::cout << "FuncDefAST { ";
    func_type->Dump();
    std::cout << ", " << *ident << ", ";
    if (func_fparams != nullptr)
      func_fparams->Dump();
    block->Dump();
    std::cout << " }";
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
    std::cout << "FuncTypeAST { ";
    std::cout << type_ret;
    std::cout << " }";
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
    std::cout << "FuncFParamsAST { ";
    for (auto &it : func_fparam)
    {
      it->Dump();
    }
    std::cout << " }";
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
    std::cout << "FuncFParamAST { ";
    if (tp == ArgsType::Int32)
    {
      std::cout << "Btype:" << EnumToString(Btype) << ", " << *ident;
    }
    else if (tp == ArgsType::Int32Array)
    {
      func_fparam->Dump();
    }
    std::cout << " }";
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
    std::cout << "FuncRParamsAST { ";
    for (auto &it : exp)
    {
      it->Dump();
    }
    std::cout << " }";
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
    std::cout << "BlockAST { ";
    if (block != nullptr)
      block->Dump();
    std::cout << " }";
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
    std::cout << "BlockItemAST { ";
    decl_or_stmt->Dump();
    std::cout << " }";
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
    std::cout << "Assign {";
    LVal->Dump();
    std::cout << ", ";
    ValueExp->Dump();
    std::cout << "}";
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
  Symbol* LValSym;
  void Dump() const override
  {
    std::cout << "LValAST{ ";
    std::cout << *VarIdent;
    for (auto &it : IndexVec)
    {
      std::cout << "[";
      it->Dump();
      std::cout << "]";
    }
    std::cout << "}";
  }
  std::string type(void) const override
  {
    std::unique_ptr<std::string> rst_ptr(new std::string("LValAST"));
    return *rst_ptr;
  }
  /**
   * @brief get value of const exp, return true if this exp is not const exp, otherwise return true
  */
  bool GetConstVal(int &val) const override;
};
// tp = "block" indicate a block ast member ptr
class StmtAST : public BaseAST
{
public:
  StmtType tp;
  // std::string ret_string;
  // int ret_number;
  BaseAST *ret_exp;
  void Dump() const override
  {
    std::cout << "StmtAST { ";
    // if(tp == "retexp")
    // {
    //   std::cout << "ret , ";
    //   ret_exp->Dump();

    // }
    if (tp == StmtType::ReturnExp)
    {
      std::cout << EnumToString(tp);
      ret_exp->Dump();
    }
    std::cout << " }";
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
    std::cout << "ExpAST { ";
    lor_exp->Dump();
    std::cout << " }";
  }
  std::string type(void) const override
  {
    std::unique_ptr<std::string> rst_ptr(new std::string("ExpAST"));
    return *rst_ptr;
  }
  /**
   * @brief get value of const exp, return true if this exp is not const exp, otherwise return true
  */
  bool GetConstVal(int &val) const override;
};

class LOrExpAST : public BaseAST
{
public:
  std::vector<BaseAST *> land_exp;
  std::vector<std::string> op;
  void Dump() const override
  {
    std::cout << "LOrExpAST { ";
    for (int i = 0; i < land_exp.size(); i++)
    {
      if (i != 0)
      {
        std::cout << " " << op[i - 1] << " ";
      }
      land_exp[i]->Dump();
    }

    std::cout << " }";
  }
  std::string type(void) const override
  {
    std::unique_ptr<std::string> rst_ptr(new std::string("LOrExpAST"));
    return *rst_ptr;
  }
  /**
   * @brief get value of const exp, return true if this exp is not const exp, otherwise return true
  */
  bool GetConstVal(int &val) const override;
};

class LAndExpAST : public BaseAST
{
public:
  std::vector<BaseAST *> eq_exp;
  std::vector<std::string> op;
  void Dump() const override
  {
    std::cout << "LAndExpAST { ";
    for (int i = 0; i < eq_exp.size(); i++)
    {
      if (i != 0)
      {
        std::cout << " " << op[i - 1] << " ";
      }
      eq_exp[i]->Dump();
    }

    std::cout << " }";
  }
  std::string type(void) const override
  {
    std::unique_ptr<std::string> rst_ptr(new std::string("LAndExpAST"));
    return *rst_ptr;
  }
  /**
   * @brief get value of const exp, return true if this exp is not const exp, otherwise return true
  */
  bool GetConstVal(int &val) const override;
};

class EqExpAST : public BaseAST
{
public:
  std::vector<BaseAST *> rel_exp;
  std::vector<std::string> op;
  void Dump() const override
  {
    std::cout << "EqExpAST { ";
    for (int i = 0; i < rel_exp.size(); i++)
    {
      if (i != 0)
      {
        std::cout << " " << op[i - 1] << " ";
      }
      rel_exp[i]->Dump();
    }

    std::cout << " }";
  }
  std::string type(void) const override
  {
    std::unique_ptr<std::string> rst_ptr(new std::string("EqExpAST"));
    return *rst_ptr;
  }
  /**
   * @brief get value of const exp, return true if this exp is not const exp, otherwise return true
  */
  bool GetConstVal(int &val) const override;
};

class RelExpAST : public BaseAST
{
public:
  std::vector<BaseAST *> add_exp;
  std::vector<std::string> op;
  void Dump() const override
  {
    std::cout << "RelExpAST { ";
    for (int i = 0; i < add_exp.size(); i++)
    {
      if (i != 0)
      {
        std::cout << " " << op[i - 1] << " ";
      }
      add_exp[i]->Dump();
    }

    std::cout << " }";
  }
  std::string type(void) const override
  {
    std::unique_ptr<std::string> rst_ptr(new std::string("RelExpAST"));
    return *rst_ptr;
  }
  /**
   * @brief get value of const exp, return true if this exp is not const exp, otherwise return true
  */
  bool GetConstVal(int &val) const override;
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
    std::cout << "AddExpAST { ";
    for (int i = 0; i < mul_exp.size(); i++)
    {
      if (i != 0)
      {
        std::cout << " " << op[i - 1] << " ";
      }
      mul_exp[i]->Dump();
    }

    std::cout << " }";
  }
  std::string type(void) const override
  {
    std::unique_ptr<std::string> rst_ptr(new std::string("AddExpAST"));
    return *rst_ptr;
  }
  /**
   * @brief get value of const exp, return true if this exp is not const exp, otherwise return true
  */
  bool GetConstVal(int &val) const override;
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
    std::cout << "MulExpAST { ";
    for (int i = 0; i < unary_exp.size(); i++)
    {
      if (i != 0)
      {
        std::cout << " " << op[i - 1] << " ";
      }
      unary_exp[i]->Dump();
    }

    std::cout << " }";
  }
  std::string type(void) const override
  {
    std::unique_ptr<std::string> rst_ptr(new std::string("MulExpAST"));
    return *rst_ptr;
  }
  /**
   * @brief get value of const exp, return true if this exp is not const exp, otherwise return true
  */
  bool GetConstVal(int &val) const override;
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
  Symbol* FuncSym;
  void Dump() const override
  {
    std::cout << "UnaryExpAST { ";
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
    std::cout << " }";
  }
  std::string type(void) const override
  {
    std::unique_ptr<std::string> rst_ptr(new std::string("UnaryExpAST"));
    return *rst_ptr;
  }
  /**
   * @brief get value of const exp, return true if this exp is not const exp, otherwise return true
  */
  bool GetConstVal(int &val) const override;
};

class PrimaryExpAST : public BaseAST
{
public:
  PrimaryType tp;
  BaseAST *exp;
  BaseAST *number;
  BaseAST* lval;
  void Dump() const override
  {
    std::cout << "PrimaryExpAST { ";
    if (tp == PrimaryType::Exp)
      exp->Dump();
    else if (tp == PrimaryType::Num)
      number->Dump();
    else{
      lval->Dump();
    }
    std::cout << " }";
  }
  std::string type(void) const override
  {
    std::unique_ptr<std::string> rst_ptr(new std::string("PrimaryExpAST"));
    return *rst_ptr;
  }
  /**
   * @brief get value of const exp, return true if this exp is not const exp, otherwise return true
  */
  bool GetConstVal(int &val) const override;
};

class NumberAST : public BaseAST
{
public:
  int num;
  void Dump() const override
  {
    std::cout << "NumberAST { ";
    std::cout << num;
    std::cout << " }";
  }
  std::string type(void) const override
  {
    std::unique_ptr<std::string> rst_ptr(new std::string("NumberAST"));
    return *rst_ptr;
  }
  /**
   * @brief get value of const exp, return true if this exp is not const exp, otherwise return true
  */
  bool GetConstVal(int &val) const override;
};

class UnaryOpAST : public BaseAST
{
public:
  std::string op;
  void Dump() const override
  {
    std::cout << "UnaryOpAST { ";
    std::cout << op;
    std::cout << " }";
  }
  std::string type(void) const override
  {
    std::unique_ptr<std::string> rst_ptr(new std::string("UnaryOpAST"));
    return *rst_ptr;
  }

};

#endif