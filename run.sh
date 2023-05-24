cd build
make run
clang ../debug/hello_riscv.s -c -o ../debug/hello.o -target riscv32-unknown-linux-elf -march=rv32im -mabi=ilp32
ld.lld ../debug/hello.o -L$CDE_LIBRARY_PATH/riscv32 -lsysy -o ../debug/hello
qemu-riscv32-static ../debug/hello
