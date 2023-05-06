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

#include "ast.h"

class Program {
 private:
  // the global variable hasn't been implemented.
  // here we can only parse one function, so the function list is not implemented as well.
 public:
  void exp_dealer(std::string* rst_ptr, ExpAST* exp)
  {
    //scan all of the exp
  }

  void block_dealer(std::string* rst_ptr, BlockItemAST* block_item)
  {
    std::string ret_string("");
    int ret_number = 0;

    if(block_item->decl_or_stmt != nullptr && block_item->decl_or_stmt->type() == "StmtAST")
    {
      StmtAST *stmt_available = dynamic_cast<StmtAST*>(block_item->decl_or_stmt);
      //Deal with Stmt
      if (stmt_available != nullptr) {
        // ret_number = stmt_available->ret_number; for exp_dealer
        ret_string += stmt_available->ret_string;
      }
      *rst_ptr += "" + ret_string + " " + std::to_string(ret_number) + "\n";
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