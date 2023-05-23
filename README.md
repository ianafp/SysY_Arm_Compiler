# DEVELOPMENT USING CPP
This repo.'s resource comes from PKU, URL: https://pku-minic.github.io/online-doc/#/
And Our development environment is Docker in Windows. If you want to test the program, please follow instructions in the URL mentioned above.
The docker image can also be found in the document of PKU.
# build
```sh
    mkdir build
    cd build
    cmake ..
    make
```
# run
```sh
    cd build
    make run
```

# transfer C language source file into LLVM

```shell
cd build
clang -S -emit-llvm ../debug/hello.c -o ../debug/hello_template.ll
```

# transfer IR file to riscv-assembly code.

```sh
    cd build
    llc -march=riscv32 ../debug/hello.ll -o ../debug/hello_riscv.s
```
And then you can see the RISCV assembly code in `debug/hello_riscv.s`

# assemble riscv-assembly code to riscv-machine code.
```sh
    cd build
    clang ../debug/hello_riscv.s -c -o ../debug/hello.o -target riscv32-unknown-linux-elf -march=rv32im -mabi=ilp32
    ld.lld ../debug/hello.o -L$CDE_LIBRARY_PATH/riscv32 -lsysy -o ../debug/hello
```
Now you should be able to see `hello` ELF file in `debug` directory.

# Run ELF file
```sh
    cd build
    qemu-riscv32-static ../debug/hello
```
Now you will be capable to see the program running on your system.

# llvm referrence document

<a href="https://llvm.org/docs/LangRef.html#call-instruction">llvm ir</a>
