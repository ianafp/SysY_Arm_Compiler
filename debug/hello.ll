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
define void @swap(i32* %0, i32 %1, i32 %2){
%4 = alloca i32 , align 4
%5 = ptrtoint i32* %0 to i64
%6 = mul i32 %1, 4
%7 = sext i32 %6 to i64
%8 = add i64 %5, %7
%9 = inttoptr i64 %8 to i32*
%10 = ptrtoint i32*  %4 to i64
%11 = sext i32 0 to i64
%12 = add i64 %10, 0
%13 = inttoptr i64 %12 to i32*
%14 = load i32,i32* %9
store i32 %14, i32*  %13
%15 = ptrtoint i32* %0 to i64
%16 = mul i32 %2, 4
%17 = sext i32 %16 to i64
%18 = add i64 %15, %17
%19 = inttoptr i64 %18 to i32*
%20 = ptrtoint i32* %0 to i64
%21 = mul i32 %1, 4
%22 = sext i32 %21 to i64
%23 = add i64 %20, %22
%24 = inttoptr i64 %23 to i32*
%25 = load i32,i32* %19
store i32 %25, i32*  %24
%26 = ptrtoint i32* %0 to i64
%27 = mul i32 %2, 4
%28 = sext i32 %27 to i64
%29 = add i64 %26, %28
%30 = inttoptr i64 %29 to i32*
%31 = load i32,i32* %4
store i32 %31, i32*  %30
}
define i32 @main(){
%1 = alloca [ 4 x [ 4 x i32 ]], align 4
%2 = ptrtoint [ 4 x[ 4 x i32 ]]* %1 to i64
%3 = sext i32 0 to i64
%4 = add i64 %2, 0
%5 = inttoptr i64 %4 to i32*
store i32 1, i32*  %5
%6 = ptrtoint [ 4 x[ 4 x i32 ]]* %1 to i64
%7 = sext i32 0 to i64
%8 = add i64 %6, 0
%9 = inttoptr i64 %8 to i32*
store i32 2, i32*  %9
%10 = ptrtoint [ 4 x[ 4 x i32 ]]* %1 to i64
%11 = sext i32 4 to i64
%12 = add i64 %10, 4
%13 = inttoptr i64 %12 to i32*
store i32 3, i32*  %13
%14 = ptrtoint [ 4 x[ 4 x i32 ]]* %1 to i64
%15 = mul i32 16, 0
%16 = mul i32 0, 4
%17 = add i32 %15, %16
%18 = sext i32 %17 to i64
%19 = add i64 %14, %18
%20 = inttoptr i64 %19 to i32*
store i32 1, i32*  %20
%21 = ptrtoint [ 4 x[ 4 x i32 ]]* %1 to i64
%22 = mul i32 16, 1
%23 = mul i32 0, 4
%24 = add i32 %22, %23
%25 = sext i32 %24 to i64
%26 = add i64 %21, %25
%27 = inttoptr i64 %26 to i32*
store i32 2, i32*  %27
%28 = ptrtoint [ 4 x[ 4 x i32 ]]* %1 to i64
%29 = mul i32 16, 1
%30 = mul i32 2, 4
%31 = add i32 %29, %30
%32 = sext i32 %31 to i64
%33 = add i64 %28, %32
%34 = inttoptr i64 %33 to i32*
store i32 3, i32*  %34
%35 = ptrtoint [ 4 x[ 4 x i32 ]]* %1 to i64
%36 = mul i32 16, 2
%37 = mul i32 3, 4
%38 = add i32 %36, %37
%39 = sext i32 %38 to i64
%40 = add i64 %35, %39
%41 = inttoptr i64 %40 to i32*
%42 = load i32,i32* %41
call void @putch(i32 %42)
ret i32 0
}
