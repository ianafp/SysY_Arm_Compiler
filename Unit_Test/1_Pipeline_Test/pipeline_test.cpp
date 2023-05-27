#include <gtest/gtest.h>
#include "glog/logging.h"
#include <cstdlib>
#include <string>
#include <stdio.h>

#define MAX_OUTPUT_SIZE 128

// 基类
class ExecutableTest : public ::testing::Test {
protected:
    std::string name;
    std::string executablePath;

    void set_name(std::string n)
    {
        name = n;
    }

    // 生成可执行文件的过程（由派生类实现）
    virtual void compileExecutable() = 0;

    // 测试的过程（由派生类实现）
    virtual void testExecutable(std::string input) = 0;

    void SetUp() override {
        
    }
};

// 派生类
class MyExecutableTest : public ExecutableTest {
protected:
    void compileExecutable() override {
        std::string src = "../";
        std::string build = "build";
        std::string test = src + "test";
        std::string debug = src + "debug";

        std::string exe_path = build + "/pipeline_test";

        // 准备编译命令
        std::string cd = "cd .. && cd "+ build;
        DLOG(WARNING) << "cd command: " + cd + "\n";

        // std::string mkdir = "mkdir "+ exe_path;
        std::string gdb_direct = "clang "+ test + "/" + name + "_direct.c  -o " + debug + "/" + name + "_direct  > /dev/null 2>&1";
        DLOG(WARNING) << "clang command: " + gdb_direct + "\n";
        std::string make = "make " + name + " > /dev/null 2>&1";
        // std::string llc_cmd = "llc -march=x86-64" + debug + "/" + name + ".ll -o " + debug + "/" + name + ".s";
        // std::string as_cmd = "as " +  debug+ "/" + name + ".s -o" + debug + "/" + name + ".o";
        std::string make_build = "make build_" + name + " > /dev/null 2>&1";
        std::string command = make + " && " + make_build + " && exit";

        // 执行编译命令
        int result = system(cd.c_str());
        if (result != 0) {
            FAIL() << "Failed to compile executable.";
        }
        //gdb直接生成
        result = system(gdb_direct.c_str());
        if (result != 0) {
            FAIL() << "Failed to compile executable.";
        }
        //我们的方法生成
        result = system(command.c_str());
        if (result != 0) {
            FAIL() << "Failed to compile executable.";
        }
        DLOG(WARNING) << "make finish\n";
        // 将生成的可执行文件路径保存到executablePath变量中
        this->executablePath = debug;
    }


    void testExecutable(std::string input) override {
        std::string gdbpath = executablePath + "/" + name + "_direct";
        std::string ourpath = executablePath + "/" + name;
        
        // 调用通过gdb的可执行文件并获取输出结果
        std::string gdbexe = gdbpath;
        std::stringstream gdb_output;
        char buffer_gdb[MAX_OUTPUT_SIZE];
        FILE* gdb_code = popen(gdbexe.c_str(), "w");

        if (gdb_code == NULL) {
            printf("Failed to execute gdb code\n");
            return;
        }

        DLOG(WARNING) << "clang start exe!\n";
        // fprintf(gdb_code, "%s", input.c_str());
        fwrite(input.c_str(), sizeof(char), input.length(), gdb_code);
        fflush(gdb_code);

        // 读取输出并追加到结果字符串中
        while (fgets(buffer_gdb, sizeof(buffer_gdb), gdb_code) != nullptr) {
            gdb_output << buffer_gdb;
        }

        pclose(gdb_code);
        DLOG(WARNING) << "clang finish exe!\n";
        DLOG(WARNING) << "our code start exe!\n";
        // 调用通过我们的可执行文件并获取输出结果
        std::string ourexe = ourpath;
        std::stringstream our_output;
        char buffer_output[MAX_OUTPUT_SIZE];
        FILE* our_code = popen(ourexe.c_str(), "w");

        if (our_code == NULL) {
            printf("Failed to execute our code\n");
            return;
        }

        // fprintf(our_code, "%s", input.c_str());
        fwrite(input.c_str(), sizeof(char), input.length(), our_code);
        fflush(our_code);

        // 读取输出并追加到结果字符串中
        while (fgets(buffer_output, sizeof(buffer_output), our_code) != nullptr) {
            our_output << buffer_output;
        }
        pclose(our_code);
        DLOG(WARNING) << "our code finish exe!\n";
        // 比较两种编译方式得到的输出结果
        // DLOG(WARNING) << "gdb: " + gdb_output.str() + "\n";
        // DLOG(WARNING) << "ours: " + our_output.str() + "\n";
        EXPECT_EQ(gdb_output.str(), our_output.str());
    }
};

// 创建测试用例
TEST_F(MyExecutableTest, Quicksort) {
    set_name("quicksort");
    compileExecutable();
    testExecutable("4\n3\n2\n1\n1\n");
    testExecutable("3\n1\n0\n-1\n");
    testExecutable("10\n1\n0\n3\n6\n8\n33\n2\n44\n6\n2\n");
}

TEST_F(MyExecutableTest, Matrix_Mul) {
    set_name("matrix_mul");
    compileExecutable();
    testExecutable("2 3\n     1      2      3\n     4      5      6\n3 2\n     7      8\n     9     10\n    11     12\n");
    testExecutable("1 1\n    -2\n1 1\n     3\n");
    testExecutable("2 2\n     1      2\n    -3      4\n2 2\n     5      6\n     7     -8\n");
    testExecutable("2 1\n     1      2\n2 2\n     5      6\n     7     -8\n");
}

TEST_F(MyExecutableTest, Advisor) {
    set_name("advisor");
    compileExecutable();
    testExecutable("c0|3||\nc1|4|c0|\nc2|3|c0|\nc3|4|c1|\nc4|4|c2|\nc5|3|c3|\nc6|3|c2|\n\n");
    testExecutable("c0|3|c2|\n\n");
    testExecutable("c0|3||A\nc1|4|c0|A\nc2|3|c0|A\nc3|4|c1|A\nc4|4|c2|A\nc5|3|c3|B\nc6|3|c2|B\n\n");
    testExecutable("c0|3||A\nc1|4|c0|A\nc2|3|c0|A\nc3|4|c1|A\nc4|4|c2|A\nc5|3|c3|\nc6|3|c5|\n\n");
}