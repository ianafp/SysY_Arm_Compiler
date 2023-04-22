#include <cassert>
#include <cstdio>
#include <iostream>
#include <memory>
#include <string>

#include "headers/ast.h"
#include "headers/ir_generator.h"
#include "koopa.h"
// the header file can be found at https://github.com/pku-minic/koopa/blob/master/crates/libkoopa/include/koopa.h
// a implementation of the KOOPA definition.

using namespace std;

extern FILE *yyin;
extern int yyparse(unique_ptr<BaseAST> &ast);

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
  unique_ptr<BaseAST> ast;
  auto ret = yyparse(ast);
  assert(!ret);

  // 输出解析得到的 AST, 其实就是个字符串
  ast->Dump();
  cout << endl;

  // generate koopa IR
  Program p;
  unique_ptr<std::string> ir_str = p.Scan(ast.get());
  FILE *IRout;
  IRout = fopen(output, "w");
  fputs((*ir_str).c_str(), IRout);
  cout << *ir_str;
  cout << endl;

  return 0;
}
