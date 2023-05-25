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
%1 = ptrtoint [ 0 x i32 ]* %a to i64
%2 = load i32,i32* %i
%3 = mul i32 %2, 4
%4 = sext i32 %3 to i64
%5 = add i64 %1, %4
%6 = inttoptr i64 %5 to i32*
%7 = ptrtoint i32*  %temp to i64
%8 = sext i32 0 to i64
%9 = add i64 %7, %8
%10 = inttoptr i64 %9 to i32*
%11 = load i32,i32* %6
store i32 %11, i32*  %10
%12 = ptrtoint [ 0 x i32 ]* %a to i64
%13 = load i32,i32* %j
%14 = mul i32 %13, 4
%15 = sext i32 %14 to i64
%16 = add i64 %12, %15
%17 = inttoptr i64 %16 to i32*
%18 = ptrtoint [ 0 x i32 ]* %a to i64
%19 = load i32,i32* %i
%20 = mul i32 %19, 4
%21 = sext i32 %20 to i64
%22 = add i64 %18, %21
%23 = inttoptr i64 %22 to i32*
%24 = load i32,i32* %17
store i32 %24, i32*  %23
%25 = ptrtoint [ 0 x i32 ]* %a to i64
%26 = load i32,i32* %j
%27 = mul i32 %26, 4
%28 = sext i32 %27 to i64
%29 = add i64 %25, %28
%30 = inttoptr i64 %29 to i32*
%31 = load i32,i32* %temp
store i32 %31, i32*  %30
}
define i32 @main(){
%local = alloca [ 4 x [ 4 x i32 ]], align 4
%1 = ptrtoint [ 4 x[ 4 x i32 ]]* %local to i64
%2 = mul i32 16, 2
%3 = mul i32 1, 4
%4 = add i32 %2, %3
%5 = sext i32 %4 to i64
%6 = add i64 %1, %5
%7 = inttoptr i64 %6 to i32*
store i32 7, i32*  %7
%8 = ptrtoint [ 4 x[ 4 x i32 ]]* %local to i64
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
