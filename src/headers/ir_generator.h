#ifndef __IR_GENERATOR_H__
#define __IR_GENERATOR_H__

/*
 * This file is used for IR generation
 * As this is the first version, I just generate
 * the texture form of IR.
 * What's more, This module should call the 
 * symbol table interface to create 
 * the symbol table while do the generation of IR
 *
*/

#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <cstring>
#include <assert.h>
#include "ast.h"
#include "ir_tree.h"

class Program {
 private:
  // the global variable hasn't been implemented.
  // here we can only parse one function, so the function list is not implemented as well.
 public:
  int temp_cnt = 0;
  void logic_exp_dealer(std::string* rst_ptr, BaseAST* exp, BaseIRT* &ir)
  {
    // std::string return_str1("");
    // std::string return_str2("");
    BaseIRT *ir1 = new ExpIRT(), *ir2 = new ExpIRT();

    if(exp->type() == "LOrExpAST")
    {
      // std::cout << "in logic" << std::endl;
      LOrExpAST* lor_exp = dynamic_cast<LOrExpAST*>(exp);
      if(lor_exp->land_exp.size() == 0) return;
      logic_exp_dealer(rst_ptr, lor_exp->land_exp[0], ir1);
      for(int i=0; i<lor_exp->op.size(); i++)
      {
        assert(i+1 < lor_exp->land_exp.size());
        logic_exp_dealer(rst_ptr, lor_exp->land_exp[i+1], ir2);
        assert(lor_exp->op[i] == "||");
        BinOpIRT* or_exp = new BinOpIRT(BinOpKind::LogicOr, reinterpret_cast<ExpIRT*>(ir1), reinterpret_cast<ExpIRT*>(ir2));
        ir1 = new ExpIRT(ExpKind::BinOp, or_exp);
      }
      ir = ir1;
    }
    else if(exp->type() == "LAndExpAST")
    {
      // std::cout << "in logic and" << std::endl;
      LAndExpAST* land_exp = dynamic_cast<LAndExpAST*>(exp);
      if(land_exp->eq_exp.size() == 0) return;
      logic_exp_dealer(rst_ptr, land_exp->eq_exp[0], ir1);
      for(int i=0; i<land_exp->op.size(); i++)
      {
        assert(i+1 < land_exp->eq_exp.size());
        logic_exp_dealer(rst_ptr, land_exp->eq_exp[i+1], ir2);
        assert(land_exp->op[i] == "&&");
        BinOpIRT* and_exp = new BinOpIRT(BinOpKind::LogicAnd, reinterpret_cast<ExpIRT*>(ir1), reinterpret_cast<ExpIRT*>(ir2));
        ir1 = new ExpIRT(ExpKind::BinOp, and_exp);
      }
      ir = ir1;
    }
    else if(exp->type() == "EqExpAST")
    {
      // std::cout << "in eq" << std::endl;
      EqExpAST* eq_exp = dynamic_cast<EqExpAST*>(exp);
      if(eq_exp->rel_exp.size() == 0) return;
      logic_exp_dealer(rst_ptr, eq_exp->rel_exp[0], ir1);
      for(int i=0; i<eq_exp->op.size(); i++)
      {
        assert(i+1 < eq_exp->rel_exp.size());
        logic_exp_dealer(rst_ptr, eq_exp->rel_exp[i+1], ir2);
        BinOpIRT *eq = nullptr;
        if(eq_exp->op[i] == "==")
          eq = new BinOpIRT(BinOpKind::IsEqual, reinterpret_cast<ExpIRT*>(ir1), reinterpret_cast<ExpIRT*>(ir2));
        else if(eq_exp->op[i] == "!=")
          eq = new BinOpIRT(BinOpKind::IsNe, reinterpret_cast<ExpIRT*>(ir1), reinterpret_cast<ExpIRT*>(ir2));
        ir1 = new ExpIRT(ExpKind::BinOp, eq);
      }
      ir = ir1;
    }
    else if(exp->type() == "RelExpAST")
    {
      // std::cout << "in rel" << std::endl;
      RelExpAST* rel_exp = dynamic_cast<RelExpAST*>(exp);
      if(rel_exp->add_exp.size() == 0) return;
      add_exp_dealer(rst_ptr, rel_exp->add_exp[0], ir1);
      for(int i=0; i<rel_exp->op.size(); i++)
      {
        assert(i+1 < rel_exp->add_exp.size());
        add_exp_dealer(rst_ptr, rel_exp->add_exp[i+1], ir2);
        BinOpIRT *add = nullptr;
        if(rel_exp->op[i] == "<")
          add = new BinOpIRT(BinOpKind::IsLt, reinterpret_cast<ExpIRT*>(ir1), reinterpret_cast<ExpIRT*>(ir2));
        else if(rel_exp->op[i] == ">")
          add = new BinOpIRT(BinOpKind::IsGt, reinterpret_cast<ExpIRT*>(ir1), reinterpret_cast<ExpIRT*>(ir2));
        else if(rel_exp->op[i] == "<=")
          add = new BinOpIRT(BinOpKind::IsLe, reinterpret_cast<ExpIRT*>(ir1), reinterpret_cast<ExpIRT*>(ir2));
        else if(rel_exp->op[i] == ">=")
          add = new BinOpIRT(BinOpKind::IsGe, reinterpret_cast<ExpIRT*>(ir1), reinterpret_cast<ExpIRT*>(ir2));
        ir1 = new ExpIRT(ExpKind::BinOp, add);
      }
      ir = ir1;
    }
    // delete ir1, ir2;
  }

  void add_exp_dealer(std::string* rst_ptr, BaseAST* exp, BaseIRT* &ir)
  {
    // std::string return_str1("");
    // std::string return_str2("");
    BaseIRT *ir1 = new ExpIRT(), *ir2 = new ExpIRT();
    if(exp->type() == "AddExpAST")
    {
      AddExpAST* add_exp = dynamic_cast<AddExpAST*>(exp);
      if(add_exp->mul_exp.size() == 0) return;
      BinOpIRT *add = nullptr;
      add_exp_dealer(rst_ptr, add_exp->mul_exp[0], ir1);
      for(int i=0; i<add_exp->op.size(); i++)
      {
        assert(i+1 < add_exp->mul_exp.size());
        add_exp_dealer(rst_ptr, add_exp->mul_exp[i+1], ir2);
        // std::cout << "ir1: " << std::to_string(i) << ir1->ExpDump() << std::endl;
        // std::cout << "ir2: " << std::to_string(i) << ir2->ExpDump() << std::endl;
        if(add_exp->op[i] == "+")
          add = new BinOpIRT(BinOpKind::plus, reinterpret_cast<ExpIRT*>(ir1), reinterpret_cast<ExpIRT*>(ir2));
        else if(add_exp->op[i] == "-")
          add = new BinOpIRT(BinOpKind::minus, reinterpret_cast<ExpIRT*>(ir1), reinterpret_cast<ExpIRT*>(ir2));
        // std::cout << "1+" << add->ExpDump();
        ir1 = new ExpIRT(ExpKind::BinOp, add);
        // std::cout << std::to_string(i) << ir1->ExpDump();
      }
      
      ir = ir1;
    }
    else if(exp->type() == "MulExpAST")
    {
      MulExpAST* mul_exp = dynamic_cast<MulExpAST*>(exp);
      if(mul_exp->unary_exp.size() == 0) return;
      BinOpIRT *mul = nullptr;
      unary_exp_dealer(rst_ptr, mul_exp->unary_exp[0], ir1);
      for(int i=0; i<mul_exp->op.size(); i++)
      {
        assert(i+1 < mul_exp->unary_exp.size());
        unary_exp_dealer(rst_ptr, mul_exp->unary_exp[i+1], ir2);
        if(mul_exp->op[i] == "*")
          mul = new BinOpIRT(BinOpKind::mul, reinterpret_cast<ExpIRT*>(ir1), reinterpret_cast<ExpIRT*>(ir2));
          // *rst_ptr += "%" + std::to_string(temp_cnt) + " = mul " + return_str1 + ", " + return_str2 + "\n  ";
        else if(mul_exp->op[i] == "/")
          mul = new BinOpIRT(BinOpKind::_div, reinterpret_cast<ExpIRT*>(ir1), reinterpret_cast<ExpIRT*>(ir2));
          // *rst_ptr += "%" + std::to_string(temp_cnt) + " = div " + return_str1 + ", " + return_str2 + "\n  ";
        else if(mul_exp->op[i] == "%")
          mul = new BinOpIRT(BinOpKind::rem, reinterpret_cast<ExpIRT*>(ir1), reinterpret_cast<ExpIRT*>(ir2));
          // *rst_ptr += "%" + std::to_string(temp_cnt) + " = mod " + return_str1 + ", " + return_str2 + "\n  ";
        // return_str1 = "%" + std::to_string(temp_cnt++);
        ir1 = new ExpIRT(ExpKind::BinOp, mul);
      }
      ir = ir1;
    }
    // delete ir1, ir2;
    // return return_str1;
  }

  void unary_exp_dealer(std::string* rst_ptr, BaseAST* exp, BaseIRT* &ir)
  {
    //scan all of the exp
    // ExpIRT* return_num;
    UnaryExpAST* unary_exp = nullptr;
    //identify the type
    if(exp->type() == "UnaryExpAST")
    {
      unary_exp = dynamic_cast<UnaryExpAST*>(exp);
    }
    //deal with the ast
    if(unary_exp->tp == "primary")
    {
      if(unary_exp->primary_exp != nullptr)
      {
        PrimaryExpAST* primary_exp = dynamic_cast<PrimaryExpAST*>(unary_exp->primary_exp);
        if(primary_exp->tp == "number")
        {
          NumberAST* number = nullptr;
          if(primary_exp->number != nullptr)
          {
            number = dynamic_cast<NumberAST*>(primary_exp->number);
            ConstIRT*c = new ConstIRT(number->num);
            ExpIRT* exp_ir = new ExpIRT(ExpKind::Const, c);
            ir = exp_ir;
          }
        }
        else if(primary_exp->tp == "exp")
        {
          if(primary_exp->exp != nullptr)
          {
            ExpAST* exp = dynamic_cast<ExpAST*>(primary_exp->exp);
            if(exp->lor_exp != nullptr)
              logic_exp_dealer(rst_ptr, exp->lor_exp, ir);
          }
          
        }
      }
    }
    else if(unary_exp->tp == "op+exp")
    {
      if(unary_exp->unary_exp != nullptr && unary_exp->unary_op != nullptr)
      {
        unary_exp_dealer(rst_ptr, unary_exp->unary_exp, ir);
        if(unary_exp->unary_op != nullptr)
        {
          UnaryOpAST* op = dynamic_cast<UnaryOpAST*>(unary_exp->unary_op);
          if(op->op == "!")
            ir = new BinOpIRT(BinOpKind::IsEqual, dynamic_cast<ExpIRT*>(ir), new ExpIRT(new ConstIRT(0)));
          else if(op->op == "-")
            ir = new BinOpIRT(BinOpKind::minus, dynamic_cast<ExpIRT*>(ir), new ExpIRT(new ConstIRT(0)));
        }
      }
    }
  }

  void block_dealer(std::string* rst_ptr, BlockItemAST* block_item, BaseIRT* &ir)
  {
    std::string ret_string("");
    std::string ret_number("");
    // std::cout << "in block" << std::endl;/
    if(block_item->decl_or_stmt != nullptr && block_item->decl_or_stmt->type() == "StmtAST")
    {
      StmtAST *stmt_available = dynamic_cast<StmtAST*>(block_item->decl_or_stmt);
      //Deal with Stmt
      if (stmt_available != nullptr && stmt_available->ret_exp != nullptr) {
        logic_exp_dealer(rst_ptr, dynamic_cast<ExpAST*>(stmt_available->ret_exp)->lor_exp, ir);
        // ret_string += stmt_available->ret_string;
        ir = new RetIRT(ValueType::INT32, reinterpret_cast<ExpIRT*>(ir));
      }
      // *rst_ptr += "" + ret_string + " " + ret_number + "\n";
    }
  }

  void func_dealer(std::string * rst_ptr, FuncDefAST* func_def, BaseIRT* &ir)
  {
    std::string result(""), ident("");
    BaseAST* func_type;
    BaseAST* func_fparams;
    BaseAST* block;

    // std::cout << "in func" << std::endl;

    //Start with FuncDefAST, we translate it to IR
    func_type = func_def->func_type;
    ident += *func_def->ident;
    func_fparams = func_def;
    block = func_def->block;

    //Deal with FuncType
    FuncTypeAST* func_type_available = nullptr;
    std::string type_analysis("");
    if(func_type != nullptr)
    {
      func_type_available = dynamic_cast<FuncTypeAST*>(func_type);
      if (func_type_available != nullptr) {
        type_analysis += func_type_available->type_ret;
      }
    }

    //Deal with Block
    BlockAST* block_available = nullptr;
    BaseAST* block_true = nullptr;
    if (block != nullptr) {
      block_available = dynamic_cast<BlockAST*>(block);
      if (block_available != nullptr) {
        block_true = block_available->block;
      }
    }

    std::string INT_type("int");
    std::string VOID_type("void");

    blockAST* block_true_available = nullptr;
    std::list<std::string> ret_stmt;
    if (block != nullptr) {
      block_true_available = dynamic_cast<blockAST*>(block_true);
      if (block_true_available != nullptr) {
        for(auto &it:block_true_available->block_item)
        {
          if(it != nullptr && it->type() == "BlockItemAST")
          {
            block_dealer(rst_ptr, dynamic_cast<BlockItemAST*>(it), ir);
            if(type_analysis == INT_type)
              ir = new FuncIRT(ValueType::INT32, new LableIRT(ident), new LableIRT(), new LableIRT(), 0,  new StatementIRT());
          }
        }
      }
    }
  }

  void Scan(BaseAST* root, BaseIRT* &IR) {
    // if(root->type() == "CompUnitAST")
    //   root->Dump();
    std::string* rst_ptr = new std::string("");
    // as the consequence that we haven't implement global variable, 
    // so no variable need to be considered.
    std::string comp_const("CompUnitAST");
    CompUnitAST* comp_unit = nullptr;
    BaseAST* root_raw_ptr = root;
    BaseAST* comp_unit_true = nullptr;
    if (root->type() == comp_const) {
      comp_unit = dynamic_cast<CompUnitAST*>(root_raw_ptr);
      if (comp_unit != nullptr) {
        comp_unit_true = comp_unit->comp_unit;
      }
    } // the error handling? Haven't implemented.

    CompunitAST* Compunit = dynamic_cast<CompunitAST*>(comp_unit_true);
    if(Compunit != nullptr)
    {
      for(auto &it:Compunit->decl_list){
        if(it != nullptr && it->type() == "FuncDefAST")
        {
          func_dealer(rst_ptr, dynamic_cast<FuncDefAST*>(it), IR);
        }
      }
    }
  }
};

#endif