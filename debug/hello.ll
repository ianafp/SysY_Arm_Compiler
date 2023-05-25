declare void @putint(i32)
declare void @putch(i32)
declare void @putarray(i32, i32*)
declare i32 @getint()
declare i32 @getch()
declare i32 @getarray(i32*)
declare void @starttime()
declare void @stoptime()
declare void @putf(i8*, i32, ...)

define void @Swap(i32* arr, i32 i, i32 j){
%temp = alloca i32 , align 4
%1 = ptrtoint i32* %arr to i64
%2 = mul i32 %i, 4
%3 = sext i32 %2 to i64
%4 = add i64 %1, %3
%5 = inttoptr i64 %4 to i32*
%6 = ptrtoint i32*  %temp to i64
%7 = sext i32 0 to i64
%8 = add i64 %6, %7
%9 = inttoptr i64 %8 to i32*
%10 = load i32,i32* %5
store i32 %10, i32*  %9
%11 = ptrtoint i32* %arr to i64
%12 = mul i32 %j, 4
%13 = sext i32 %12 to i64
%14 = add i64 %11, %13
%15 = inttoptr i64 %14 to i32*
%16 = ptrtoint i32* %arr to i64
%17 = mul i32 %i, 4
%18 = sext i32 %17 to i64
%19 = add i64 %16, %18
%20 = inttoptr i64 %19 to i32*
%21 = load i32,i32* %15
store i32 %21, i32*  %20
%22 = ptrtoint i32* %arr to i64
%23 = mul i32 %j, 4
%24 = sext i32 %23 to i64
%25 = add i64 %22, %24
%26 = inttoptr i64 %25 to i32*
%27 = load i32,i32* %temp
store i32 %27, i32*  %26
%28 = mul i32 %j, 4
store i32 %28, i32 %i
}
define i32 @main(){
%local = alloca [ 4 x [ 4 x i32 ]], align 4
%1 = ptrtoint [4x[4x i32 ]]* %local to i64
%2 = sext i32 0 to i64
%3 = add i64 %1, %2
%4 = inttoptr i64 %3 to i32*
store i32 1, i32*  %4
%5 = ptrtoint [4x[4x i32 ]]* %local to i64
%6 = sext i32 0 to i64
%7 = add i64 %5, %6
%8 = inttoptr i64 %7 to i32*
store i32 2, i32*  %8
%9 = ptrtoint [4x[4x i32 ]]* %local to i64
%10 = sext i32 4 to i64
%11 = add i64 %9, %10
%12 = inttoptr i64 %11 to i32*
store i32 3, i32*  %12
%13 = ptrtoint [4x[4x i32 ]]* %local to i64
%14 = mul i32 16, 0
%15 = mul i32 0, 4
%16 = add i32 %14, %15
%17 = sext i32 %16 to i64
%18 = add i64 %13, %17
%19 = inttoptr i64 %18 to i32*
store i32 1, i32*  %19
%20 = ptrtoint [4x[4x i32 ]]* %local to i64
%21 = mul i32 16, 1
%22 = mul i32 0, 4
%23 = add i32 %21, %22
%24 = sext i32 %23 to i64
%25 = add i64 %20, %24
%26 = inttoptr i64 %25 to i32*
store i32 2, i32*  %26
%27 = ptrtoint [4x[4x i32 ]]* %local to i64
%28 = mul i32 16, 1
%29 = mul i32 2, 4
%30 = add i32 %28, %29
%31 = sext i32 %30 to i64
%32 = add i64 %27, %31
%33 = inttoptr i64 %32 to i32*
store i32 3, i32*  %33
%34 = ptrtoint [4x[4x i32 ]]* %local to i64
%35 = mul i32 16, 2
%36 = mul i32 3, 4
%37 = add i32 %35, %36
%38 = sext i32 %37 to i64
%39 = add i64 %34, %38
%40 = inttoptr i64 %39 to i32*
%41 = load i32,i32* %40
call void @putch(i32 %41)
ret i32 0
}
