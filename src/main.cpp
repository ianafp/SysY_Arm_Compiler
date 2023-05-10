#include <cassert>
#include <cstdio>
#include <iostream>
#include <memory>
#include <string>
#include "headers/ast.h"
#include "headers/ir_generator.h"
// #include "koopa.h"
// #include "headers/ir_tree.h"
// the header file can be found at https://github.com/pku-minic/koopa/blob/master/crates/libkoopa/include/koopa.h
// a implementation of the KOOPA definition.

using namespace std;

extern FILE *yyin;
extern int yyparse(BaseAST* &ast);

int main(int argc, const char *argv[]) {
  // 解析命令行参数. 测试脚本/评测平台要求你的编译器能接收如下参数:
  // compiler 模式 输入文件 -o 输出文件
  assert(argc == 5);
  auto mode = argv[1];
  auto input = argv[2];
  auto output = argv[4];

  cout << "mode: " << mode << endl;
  cout << "output file: " << output << endl;

  // 打开输入文件, 并且指定 lexer 在解析的时候读取这个文件
  yyin = fopen(input, "r");
  assert(yyin);

  // 调用 parser 函数, parser 函数会进一步调用 lexer 解析输入文件的
  BaseAST* ast;
  auto ret = yyparse(ast);
  assert(!ret);

  // 输出解析得到的 AST, 其实就是个字符串
  ast->Dump();
  cout << endl;

  // generate koopa IR
  Program p;
  BaseIRT *ir;
  p.Scan(ast, ir);
  FILE *IRout;
  IRout = fopen(output, "w");
  // fputs((*ir_str).c_str(), IRout);
  // cout << *ir_str;
<<<<<<< HEAD
  // ExpIRT* e = new ExpIRT();
  if(ir == nullptr) cout << "error";
  ir->Dump();
  cout << endl;
  // ConstIRT c1(11),c2(1100), c3(1000);
  // ExpIRT c1Exp(ExpKind::Const,&c1),c2Exp(ExpKind::Const,&c2),c3Exp(ExpKind::Const,&c3);
  // BinOpIRT StoreAddr(BinOpKind::plus,&c1Exp,&c2Exp);
  // ExpIRT s(ExpKind::BinOp, &StoreAddr);
  // BinOpIRT Storeaddr(BinOpKind::minus,&c1Exp,&c3Exp);
  // ExpIRT StoreAddrExp(ExpKind::BinOp,&StoreAddr);
  // MemIRT StoreAddrMem(&StoreAddrExp);
  // MoveIRT TestMove(&StoreAddrMem,new ExpIRT(new ConstIRT(3333)));
=======
  // cout << endl;
  // ConstIRT c1(11),c2(1100);
  // ExpIRT c1Exp(ExpKind::Const,&c1),c2Exp(ExpKind::Const,&c2);
  // BinOpIRT StoreAddr(BinOpKind::plus,&c1Exp,&c2Exp);
  // ExpIRT StoreAddrExp(ExpKind::BinOp,&StoreAddr);
  // MemIRT StoreAddrMem(&StoreAddrExp);
  // MoveIRT TestMove(&StoreAddrMem,new ExpIRT(new ConstIRT(3333)));
  // // ExpIRT *empty = new ExpIRT() ;
>>>>>>> 6b3ba4f738da4c4f78c98db4497fee9ae8e9417c
  // TestMove.Dump();
  return 0;
}