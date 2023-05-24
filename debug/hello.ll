declare void @putint(i32)
declare void @putch(i32)
declare void @putarray(i32, i32*)
declare i32 @getint()
declare i32 @getch()
declare i32 @getarray(i32*)
declare void @starttime()
declare void @stoptime()
declare void @putf(i8*, i32, ...)


@MAX_SIZE = constant i32  10000, align 4

@nums = global [ 10000 x i32 ] zeroinitializer, align 4
define void @swap(i32* %a, i32 %i, i32 %j){
%temp = alloca i32 , align 4
%1 = ptrtoint i32*  %temp to i64
%2 = ptrtoint [ 0 x i32 ]* %a to i64
%3 = load i32,i32* %i
%4 = sext i32 %3 to i64
%5 = add i64 %2, %4
%6 = inttoptr i64 %5 to i32*
%7 = sext i32 0 to i64
%8 = add i64 %1, %7
%9 = inttoptr i64 %8 to i32*
%10 = load i32,i32* %6
store i32 %10, i32*  %9
%11 = ptrtoint [ 0 x i32 ]* %a to i64
%12 = load i32,i32* %j
%13 = sext i32 %12 to i64
%14 = add i64 %11, %13
%15 = inttoptr i64 %14 to i32*
%16 = ptrtoint [ 0 x i32 ]* %a to i64
%17 = load i32,i32* %i
%18 = sext i32 %17 to i64
%19 = add i64 %16, %18
%20 = inttoptr i64 %19 to i32*
%21 = load i32,i32* %15
store i32 %21, i32*  %20
%22 = ptrtoint [ 0 x i32 ]* %a to i64
%23 = load i32,i32* %j
%24 = sext i32 %23 to i64
%25 = add i64 %22, %24
%26 = inttoptr i64 %25 to i32*
%27 = load i32,i32* %temp
store i32 %27, i32*  %26
}
define i32 @main(){
ret i32 0
}
