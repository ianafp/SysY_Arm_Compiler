declare void @putint(i32)
declare void @putch(i32)
declare void @putarray(i32, i32*)
declare i32 @getint()
declare i32 @getch()
declare i32 @getarray(i32*)
declare void @starttime()
declare void @stoptime()
declare void @putf(i8*, i32, ...)


@test = addrspace(32) global [ 8 x i32 ][i32 1, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0], align 4

@another = addrspace(32) global [ 8 x i32 ]0, align 4
define void @HELLO(){
call void @putch(i32 72)
ret void
}
define i32 @main(){
%local = alloca [ 4 x i32 ], align 4
%1 = ptrtoint [4x i32 ]* %local to i64
%local = alloca [ 4 x i32 ], align 4
%2 = ptrtoint [4x i32 ]* %local to i64
%3 = add i32 %2, 0
%4 = inttoptr i32 %3 to i32*
store i32 1, i32*  %4
%5 = add i32 %2, 4
%6 = inttoptr i32 %5 to i32*
store i32 2, i32*  %6
%7 = add i32 %2, 8
%8 = inttoptr i32 %7 to i32*
store i32 6, i32*  %8
%9 = load i32,i32* @test
%10 = add i32 %9, 1
%11 = inttoptr i32 %10 to i32*
%12 = load i32,i32* %11
call void @putch(i32 %12)
ret i32 0
}
