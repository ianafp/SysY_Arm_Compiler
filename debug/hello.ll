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

@another = addrspace(32) global [ 8 x i32 ] zeroinitializer, align 4
define void @HELLO(){
call void @putch(i32 72)
ret void
}
define i32 @main(){
%local = alloca [ 4 x i32 ], align 4
%1 = ptrtoint [4x i32 ]* %local to i64
%2 = sext i32 0 to i64
%3 = add i64 %1, %2
%4 = inttoptr i64 %3 to i32*
store i32 1, i32*  %4
%5 = sext i32 4 to i64
%6 = add i64 %1, %5
%7 = inttoptr i64 %6 to i32*
store i32 2, i32*  %7
%8 = sext i32 8 to i64
%9 = add i64 %1, %8
%10 = inttoptr i64 %9 to i32*
store i32 6, i32*  %10
%11 = ptrtoint [8x i32 ]* @test to i64
%12 = sext i32 1 to i64
%13 = add i64 %11, %12
%14 = inttoptr i64 %13 to i32*
%15 = load i32,i32* %14
call void @putch(i32 %15)
ret i32 0
}
