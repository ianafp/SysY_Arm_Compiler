# DEVELOPMENT USING CPP
This repo.'s resource comes from PKU, URL: https://pku-minic.github.io/online-doc/#/
And Our development environment is Docker in Windows. If you want to test the program, please follow instructions in the URL mentioned above.
The docker image can also be found in the document of PKU.

Our project report in Feishu: https://sqchh8cke3.feishu.cn/docx/P2NKdjo3doivDoxuYuGcS3pqnty

# build
```sh
mkdir build
cd build
cmake ..
make

make quicksort # use our program to convert quick_sort.c to quick_sort.ll
make build_quicksort # use LLVM backend to build quick_sort.ll into assembly and link the IO lib.
make test_quicksort # test checkpoint.
```

# llvm referrence document

<a href="https://llvm.org/docs/LangRef.html#call-instruction">llvm ir</a>
