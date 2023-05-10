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
#include <assert.h>

#include "ast.h"

class Program {
 private:
  // the global variable hasn't been implemented.
  // here we can only parse one function, so the function list is not implemented as well.
 public:
  int temp_cnt = 0;
  std::string logic_exp_dealer(std::string* rst_ptr, BaseAST* exp)
  {
    std::string return_str1("");
    std::string return_str2("");
    
    if(exp->type() == "LOrExpAST")
    {
      LOrExpAST* lor_exp = dynamic_cast<LOrExpAST*>(exp);
      if(lor_exp->land_exp.size() == 0)
      {
        return "";
      }
      return_str1 = logic_exp_dealer(rst_ptr, lor_exp->land_exp[0]);
      for(int i=0; i<lor_exp->op.size(); i++)
      {
        assert(i+1 < lor_exp->land_exp.size());
        return_str2 = logic_exp_dealer(rst_ptr, lor_exp->land_exp[i+1]);
        assert(lor_exp->op[i] == "||");
        // *rst_ptr += "%" + std::to_string(temp_cnt) + " = or " + return_str1 + ", " + return_str2 + "\n  ";
        *rst_ptr += "%" + std::to_string(temp_cnt++) + " = eq " + return_str1 + ", 0\n  ";
        *rst_ptr += "%" + std::to_string(temp_cnt++) + " = eq " + return_str2 + ", 0\n  ";
        *rst_ptr += "%" + std::to_string(temp_cnt) + " = and %" + std::to_string(temp_cnt-1) + ", %" + std::to_string(temp_cnt-2) + "\n  ";
        temp_cnt++;
        *rst_ptr += "%" + std::to_string(temp_cnt) + " = eq %" + std::to_string(temp_cnt-1) + ", 0\n  ";
        return_str1 = "%" + std::to_string(temp_cnt++);
      }
    }
    else if(exp->type() == "LAndExpAST")
    {
      LAndExpAST* land_exp = dynamic_cast<LAndExpAST*>(exp);
      if(land_exp->eq_exp.size() == 0)
      {
        return "";
      }
      return_str1 = logic_exp_dealer(rst_ptr, land_exp->eq_exp[0]);
      for(int i=0; i<land_exp->op.size(); i++)
      {
        assert(i+1 < land_exp->eq_exp.size());
        return_str2 =logic_exp_dealer(rst_ptr, land_exp->eq_exp[i+1]);
        assert(land_exp->op[i] == "&&");
        // *rst_ptr += "%" + std::to_string(temp_cnt) + " = and " + return_str1 + ", " + return_str2 + "\n  ";
        *rst_ptr += "%" + std::to_string(temp_cnt++) + " = eq " + return_str1 + ", 0\n  ";
        *rst_ptr += "%" + std::to_string(temp_cnt++) + " = eq " + return_str2 + ", 0\n  ";
        *rst_ptr += "%" + std::to_string(temp_cnt) + " = or %" + std::to_string(temp_cnt-1) + ", %" + std::to_string(temp_cnt-2) + "\n  ";
        temp_cnt++;
        *rst_ptr += "%" + std::to_string(temp_cnt) + " = eq %" + std::to_string(temp_cnt-1) + ", 0\n  ";
        return_str1 = "%" + std::to_string(temp_cnt++);
      }
    }
    else if(exp->type() == "EqExpAST")
    {
      EqExpAST* eq_exp = dynamic_cast<EqExpAST*>(exp);
      if(eq_exp->rel_exp.size() == 0)
      {
        return "";
      }
      return_str1 = logic_exp_dealer(rst_ptr, eq_exp->rel_exp[0]);
      for(int i=0; i<eq_exp->op.size(); i++)
      {
        assert(i+1 < eq_exp->rel_exp.size());
        return_str2 =logic_exp_dealer(rst_ptr, eq_exp->rel_exp[i+1]);
        if(eq_exp->op[i] == "==")
          *rst_ptr += "%" + std::to_string(temp_cnt) + " = eq " + return_str1 + ", " + return_str2 + "\n  ";
        else if(eq_exp->op[i] == "!=")
          *rst_ptr += "%" + std::to_string(temp_cnt) + " = ne " + return_str1 + ", " + return_str2 + "\n  ";
        // else if(mul_exp->op[i] == "%")
        //   *rst_ptr += "%" + std::to_string(temp_cnt) + " = mod " + return_str1 + ", " + return_str2 + "\n  ";
        return_str1 = "%" + std::to_string(temp_cnt++);
      }
    }
    else if(exp->type() == "RelExpAST")
    {
      RelExpAST* rel_exp = dynamic_cast<RelExpAST*>(exp);
      if(rel_exp->add_exp.size() == 0)
      {
        return "";
      }
      return_str1 = add_exp_dealer(rst_ptr, rel_exp->add_exp[0]);
      for(int i=0; i<rel_exp->op.size(); i++)
      {
        assert(i+1 < rel_exp->add_exp.size());
        return_str2 =add_exp_dealer(rst_ptr, rel_exp->add_exp[i+1]);
        if(rel_exp->op[i] == "<")
          *rst_ptr += "%" + std::to_string(temp_cnt) + " = lt " + return_str1 + ", " + return_str2 + "\n  ";
        else if(rel_exp->op[i] == ">")
          *rst_ptr += "%" + std::to_string(temp_cnt) + " = gt " + return_str1 + ", " + return_str2 + "\n  ";
        else if(rel_exp->op[i] == "<=")
          *rst_ptr += "%" + std::to_string(temp_cnt) + " = le " + return_str1 + ", " + return_str2 + "\n  ";
        else if(rel_exp->op[i] == ">=")
          *rst_ptr += "%" + std::to_string(temp_cnt) + " = ge " + return_str1 + ", " + return_str2 + "\n  ";
        return_str1 = "%" + std::to_string(temp_cnt++);
      }
    }
    return return_str1;
  }

  std::string add_exp_dealer(std::string* rst_ptr, BaseAST* exp)
  {
    std::string return_str1("");
    std::string return_str2("");
    if(exp->type() == "AddExpAST")
    {
      // ExpAST* exp_available = dynamic_cast<ExpAST*>(exp);
      // if(exp_available->add_exp != nullptr)
      // {
      AddExpAST* add_exp = dynamic_cast<AddExpAST*>(exp);
      if(add_exp->mul_exp.size() == 0)
      {
        return "";
      }
      return_str1 = add_exp_dealer(rst_ptr, add_exp->mul_exp[0]);
      for(int i=0; i<add_exp->op.size(); i++)
      {
        assert(i+1 < add_exp->mul_exp.size());
        return_str2 = add_exp_dealer(rst_ptr, add_exp->mul_exp[i+1]);
        if(add_exp->op[i] == "+")
          *rst_ptr += "%" + std::to_string(temp_cnt) + " = add " + return_str1 + ", " + return_str2 + "\n  ";
        else if(add_exp->op[i] == "-")
          *rst_ptr += "%" + std::to_string(temp_cnt) + " = sub " + return_str1 + ", " + return_str2 + "\n  ";
        return_str1 = "%" + std::to_string(temp_cnt++);
      }
      // }
    }
    else if(exp->type() == "MulExpAST")
    {
      MulExpAST* mul_exp = dynamic_cast<MulExpAST*>(exp);
      if(mul_exp->unary_exp.size() == 0)
      {
        return "";
      }
      return_str1 = unary_exp_dealer(rst_ptr, mul_exp->unary_exp[0]);
      for(int i=0; i<mul_exp->op.size(); i++)
      {
        assert(i+1 < mul_exp->unary_exp.size());
        return_str2 =unary_exp_dealer(rst_ptr, mul_exp->unary_exp[i+1]);
        if(mul_exp->op[i] == "*")
          *rst_ptr += "%" + std::to_string(temp_cnt) + " = mul " + return_str1 + ", " + return_str2 + "\n  ";
        else if(mul_exp->op[i] == "/")
          *rst_ptr += "%" + std::to_string(temp_cnt) + " = div " + return_str1 + ", " + return_str2 + "\n  ";
        else if(mul_exp->op[i] == "%")
          *rst_ptr += "%" + std::to_string(temp_cnt) + " = mod " + return_str1 + ", " + return_str2 + "\n  ";
        return_str1 = "%" + std::to_string(temp_cnt++);
      }
    }
    return return_str1;
  }

  std::string unary_exp_dealer(std::string* rst_ptr, BaseAST* exp)
  {
    //scan all of the exp
    std::string return_num("");
    UnaryExpAST* unary_exp = nullptr;
    //identify the type
    // if(exp->type() == "MulExpAST")
    // {
    //   MulExpAST* exp_available = dynamic_cast<MulExpAST*>(exp);
    //   if(exp_available->unary_exp != nullptr)
    //   {
    //     unary_exp = dynamic_cast<UnaryExpAST*>(exp_available->unary_exp);
    //   }
    // }
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
            return_num = std::to_string(number->num);
          }
          return return_num;
        }
        else if(primary_exp->tp == "exp")
        {
          if(primary_exp->exp != nullptr)
          {
            ExpAST* exp = dynamic_cast<ExpAST*>(primary_exp->exp);
            if(exp->lor_exp != nullptr)
              return_num = logic_exp_dealer(rst_ptr, exp->lor_exp);
            return return_num;
          }
          
        }
      }
    }
    else if(unary_exp->tp == "op+exp")
    {
      if(unary_exp->unary_exp != nullptr && unary_exp->unary_op != nullptr)
      {
        return_num = unary_exp_dealer(rst_ptr, unary_exp->unary_exp);
        if(unary_exp->unary_op != nullptr)
        {
          UnaryOpAST* op = dynamic_cast<UnaryOpAST*>(unary_exp->unary_op);
          if(op->op == "!")
            *rst_ptr += "%" + std::to_string(temp_cnt) + " = eq " + return_num + ", 0\n  ";
          else if(op->op == "-")
            *rst_ptr += "%" + std::to_string(temp_cnt) + " = sub 0, " + return_num + "\n  ";
          else if(op->op == "+")
            return return_num;
        }
        return "%" + std::to_string(temp_cnt++); 
      }
    }
    return "";
  }

  void block_dealer(std::string* rst_ptr, BlockItemAST* block_item)
  {
    std::string ret_string("");
    std::string ret_number("");

    if(block_item->decl_or_stmt != nullptr && block_item->decl_or_stmt->type() == "StmtAST")
    {
      StmtAST *stmt_available = dynamic_cast<StmtAST*>(block_item->decl_or_stmt);
      //Deal with Stmt
      if (stmt_available != nullptr && stmt_available->ret_exp != nullptr) {
        ret_number = logic_exp_dealer(rst_ptr, dynamic_cast<ExpAST*>(stmt_available->ret_exp)->lor_exp);
        ret_string += stmt_available->ret_string;
      }
      *rst_ptr += "" + ret_string + " " + ret_number + "\n";
    }
  }

  void func_dealer(std::string * rst_ptr, FuncDefAST* func_def)
  {
    std::string result(""), ident("");
    BaseAST* func_type;
    BaseAST* func_fparams;
    BaseAST* block;

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

    std::string func_header("fun "); *rst_ptr += func_header;
    std::string func_name("@" + ident + "(): "); *rst_ptr += func_name;
    std::string INT_type("int");
    std::string VOID_type("void");
    std::string func_type_append("");
    if (type_analysis == INT_type) {
      func_type_append += "i32";
    }
    *rst_ptr += func_type_append;
    *rst_ptr += " {\n";
    std::string block_name("\%entry:\n  "); *rst_ptr += block_name;

    blockAST* block_true_available = nullptr;
    std::list<std::string> ret_stmt;
    if (block != nullptr) {
      block_true_available = dynamic_cast<blockAST*>(block_true);
      if (block_true_available != nullptr) {
        for(auto &it:block_true_available->block_item)
        {
          if(it != nullptr && it->type() == "BlockItemAST")
          {
            block_dealer(rst_ptr, dynamic_cast<BlockItemAST*>(it));
          }
        }
      }
    }
    
    //done with the AST analysis
    
    // for now, we only have one basic block, just add the basic block
    *rst_ptr += "}\n";
  }

  std::string* Scan(BaseAST* root) {
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
          func_dealer(rst_ptr, dynamic_cast<FuncDefAST*>(it));
        }
      }
    }

    return rst_ptr;
  }
};

#endif