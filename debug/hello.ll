declare void @putint(i32)
declare void @putch(i32)
declare void @putarray(i32, i32*)
declare i32 @getint()
declare i32 @getch()
declare i32 @getarray(i32*)
declare void @starttime()
declare void @stoptime()
declare void @putf(i8*, i32, ...)


@test = global [ 8 x i32 ][i32 1, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0], align 4

@another = global [ 8 x i32 ] zeroinitializer, align 4
define void @HELLO(){
call void @putch(i32 72)
ret void
}
define i32 @main(){
%local = alloca [ 4 x [ 4 x i32 ]], align 4
%1 = ptrtoint [4x[4x i32 ]]* %local to i64
%2 = mul i32 16, 2
%3 = mul i32 1, 4
%4 = add i32 %2, %3
%5 = sext i32 %4 to i64
%6 = add i64 %1, %5
%7 = inttoptr i64 %6 to i32*
store i32 7, i32*  %7
%8 = ptrtoint [4x[4x i32 ]]* %local to i64
%9 = mul i32 16, 2
%10 = mul i32 3, 4
%11 = add i32 %9, %10
%12 = sext i32 %11 to i64
%13 = add i64 %8, %12
%14 = inttoptr i64 %13 to i32*
%15 = load i32,i32* %14
call void @putch(i32 %15)
ret i32 0
}
