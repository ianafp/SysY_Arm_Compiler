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
  std::unique_ptr<std::string> Scan(BaseAST* root) {
    std::unique_ptr<std::string> rst_ptr(new std::string());
    // as the consequence that we haven't implement global variable, 
    // so no variable need to be considered.
    std::string comp_const("CompUnitAST");
    CompUnitAST* comp_unit = nullptr;
    BaseAST* root_raw_ptr = root;
    BaseAST* func_def = nullptr;
    if (root->type() == comp_const) {
      comp_unit = dynamic_cast<CompUnitAST*>(root_raw_ptr);
      if (comp_unit != nullptr) {
        func_def = comp_unit->func_def.get();
      }
    } // the error handling? Haven't implemented.

    FuncDefAST* func_def_available = nullptr;
    BaseAST* func_type = nullptr;
    std::string ident("");
    BaseAST* block = nullptr;
    if (func_def != nullptr) {
      func_def_available = dynamic_cast<FuncDefAST*>(func_def);
      if (func_def_available != nullptr) {
        func_type = func_def_available->func_type.get();
        ident += func_def_available->ident;
        std::cout << ident << std::endl;
        block = func_def_available->block.get();
      }
    } // the error handling? Haven't implemented.  

    FuncTypeAST* func_type_available = nullptr;
    std::string type_analysis("");
    if (func_type != nullptr) {
      func_type_available = dynamic_cast<FuncTypeAST*>(func_type);
      if (func_type_available != nullptr) {
        type_analysis += func_type_available->type_ret;
      }
    } // the error handling? Haven't implemented.

    BlockAST* block_available = nullptr;
    BaseAST* stmt = nullptr;
    if (block != nullptr) {
      block_available = dynamic_cast<BlockAST*>(block);
      if (block_available != nullptr) {
        stmt = block_available->stmt.get();
      }
    } // the error handling? Haven't implemented.

    std::string ret_string("");
    int ret_number = 0;

    StmtAST* stmt_availabel = nullptr;
    if (stmt != nullptr) {
      stmt_availabel = dynamic_cast<StmtAST*>(stmt);
      if (stmt_availabel != nullptr) {
        ret_number = stmt_availabel->ret_number;
        ret_string += stmt_availabel->ret_string;
      }
    }
    // now the analyse of AST has been done.

    std::string func_header("fun "); *rst_ptr += func_header;
    std::string func_name("@" + ident + "(): "); *rst_ptr += func_name;
    std::string INT_type("int"); std::string func_type_append("");
    if (type_analysis == INT_type) {
      func_type_append += "i32";
      func_type_append += " {\n";
    }
    *rst_ptr += func_type_append;
    std::string block_name("\%entry:\n  "); *rst_ptr += block_name;
    // for now, we only have one basic block, just add the basic block
    
    std::string ret_stmt("" + ret_string + " " + std::to_string(ret_number) + "\n}");
    *rst_ptr += ret_stmt;

    return rst_ptr;
  }
};



#endif