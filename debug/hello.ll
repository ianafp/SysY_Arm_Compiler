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
%2 = add i32 %1, 0
%3 = inttoptr i32 %2 to i32*
store i32 1, i32*  %3
%4 = add i32 %1, 4
%5 = inttoptr i32 %4 to i32*
store i32 2, i32*  %5
%6 = add i32 %1, 8
%7 = inttoptr i32 %6 to i32*
store i32 6, i32*  %7
%8 = ptrtoint [8x i32 ]* @test to i64
%9 = sext i32 1 to i64
%10 = add i64 %8, %9
%11 = inttoptr i64 %10 to i32*
%12 = load i32,i32* %11
call void @putch(i32 %12)
ret i32 0
}
