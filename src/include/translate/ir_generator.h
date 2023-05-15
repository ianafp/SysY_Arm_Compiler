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
#include "ast/ast.h"
#include "ir/ir_tree.h"
#include "symtable/symbol_table.h"
class Program {
 private:
  // the global variable hasn't been implemented.
  // here we can only parse one function, so the function list is not implemented as well.
 public:

 /***************************************************************************************
  *  @author    Zhoujun Ying
  *  @brief     Deal with logic expression recursively
  *  @param     exp:the ast node of logic exp; ir:the IR tree we wanna construct   
  *  @note      ir is a reference
  *  @Sample usage:     called in block_exp_dealer() only recursively, no need for outer call
 *****************************************************************************************/
  void logic_exp_dealer(BaseAST* exp, BaseIRT* &ir);
/***************************************************************************************
  *  @author    Zhoujun Ying
  *  @brief     Deal with add expression recursively
  *  @param     exp:the ast node of add exp; ir:the IR tree we wanna construct   
  *  @note      ir is a reference
  *  @Sample usage:     called in logic_exp_dealer() only recursively, no need for outer call
 *****************************************************************************************/
  void add_exp_dealer(BaseAST* exp, BaseIRT* &ir);
 /***************************************************************************************
  *  @brief     Deal with unary expression recursively
  *  @param     exp:the ast node of unary exp; ir:the IR tree we wanna construct   
  *  @note      ir is a reference
  *  @Sample usage:     called in add_exp_dealer() only recursively, no need for outer call
 *****************************************************************************************/
  void unary_exp_dealer(BaseAST* exp, BaseIRT* &ir);
/***************************************************************************************
  *  @brief     Deal with blocks of a function recursively
  *  @param     block_item:the ast node of block of func; ir:the IR tree we wanna construct   
  *  @note      ir is a reference
  *  @Sample usage:     called in func_dealer() only recursively, no need for outer call
 *****************************************************************************************/
  void block_dealer(BlockItemAST* block_item, BaseIRT* &ir);

/***************************************************************************************
  *  @brief     Deal with the function definition of the IR construct process recursively
  *  @param     func_def:the ast node of func_def type; ir:the IR tree template we wanna construct   
  *  @note      ir is a reference
  *  @Sample usage:     called in Scan() recursively, no need for outer call
 *****************************************************************************************/
  void func_dealer(FuncDefAST* func_def, BaseIRT* &ir);

 /***************************************************************************************
  *  @brief     From root ast, we analysis AST in this fuction, and construct the IR in mem
  *  @param     root:the ast root; ir:the IR tree we wanna construct   
  *  @note      IR is a reference
  *  @Sample usage:     for each program class p, call p.scan(ast, ir)
 *****************************************************************************************/
  void Scan(BaseAST* root, BaseIRT* &ir) ;
  /**
   * @brief this method handle the decl ast translationg to ir
   * @author: zhang
   * @param decl: porinter to DeclAST to be handled
   * @param ir: referrence of ir porinters which will point to the result ir tree  
  */
  void DeclTranslater(DeclAST* decl,BaseIRT* &ir);
  /**
   * @brief this method handle the vardecl ast translationg to ir
   * @author: zhang
   * @param decl: porinter to VarDeclAST to be handled
   * @param ir: referrence of ir porinters which will point to the result ir tree  
  */
  void VarDeclTranslater(VarDeclAST* decl,BaseIRT* &ir);
  /**
   * @brief this method handle the var declarition ast translationg to ir
   * @author: zhang
   * @param type : the symbol type, define in symbol_table.h
   * @param decl: porinter to VarDefAST to be handled
   * @param ir: referrence of ir porinters which will point to the result ir tree  
  */
  void VarDefTranslater(SymType type,VarDefAST* decl,BaseIRT* &ir);
  /**
   * @brief this method handle the const var declarition ast translationg to ir
   * @author: zhang
   * @param type : the symbol type, define in symbol_table.h
   * @param decl: porinter to VarDefAST to be handled
   * @param ir: referrence of ir porinters which will point to the result ir tree  
  */
  void ConstDefTranslater(SymType type,VarDefAST* decl,BaseIRT* &ir);
  /**
   * @brief this method handle the constdecl ast translationg to ir
   * @author: zhang
   * @param decl: porinter to ConstDeclAST to be handled
   * @param ir: referrence of ir porinters which will point to the result ir tree  
  */
  void ConstDeclTranslater(ConstDeclAST* decl,BaseIRT* &ir);
  /**
   * @brief this method handle the assign ast translating LVal = Exp to MOVE ir
   * @param assign AssignAST ptr
   * @param ir result ir ptr referrence
   * 
  */
  void AssignTranslater(AssignAST* assign,BaseIRT* &ir);
  /**
   * @brief this method handle the lval ast translating LVal to MEM ir
   * @param assign LValAST ptr
   * @param ir result ir ptr referrence
   * 
  */
  void LValTranslater(LValAST* lval,BaseIRT* &ir);
};

#endif