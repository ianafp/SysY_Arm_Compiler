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
%1 = ptrtoint i32* %a to i64
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
%11 = ptrtoint i32* %a to i64
%12 = mul i32 %j, 4
%13 = sext i32 %12 to i64
%14 = add i64 %11, %13
%15 = inttoptr i64 %14 to i32*
%16 = ptrtoint i32* %a to i64
%17 = mul i32 %i, 4
%18 = sext i32 %17 to i64
%19 = add i64 %16, %18
%20 = inttoptr i64 %19 to i32*
%21 = load i32,i32* %15
store i32 %21, i32*  %20
%22 = ptrtoint i32* %a to i64
%23 = mul i32 %j, 4
%24 = sext i32 %23 to i64
%25 = add i64 %22, %24
%26 = inttoptr i64 %25 to i32*
%27 = load i32,i32* %temp
store i32 %27, i32*  %26
ret void
}
define i32 @partition(i32* %arr, i32 %low, i32 %high){
%pivot = alloca i32 , align 4
%1 = ptrtoint i32* %arr to i64
%2 = mul i32 %high, 4
%3 = sext i32 %2 to i64
%4 = add i64 %1, %3
%5 = inttoptr i64 %4 to i32*
%6 = ptrtoint i32*  %pivot to i64
%7 = sext i32 0 to i64
%8 = add i64 %6, %7
%9 = inttoptr i64 %8 to i32*
%10 = load i32,i32* %5
store i32 %10, i32*  %9
%i = alloca i32 , align 4
%11 = sub i32 %low, 1
%12 = ptrtoint i32*  %i to i64
%13 = sext i32 0 to i64
%14 = add i64 %12, %13
%15 = inttoptr i64 %14 to i32*
store i32 %11, i32*  %15
%j = alloca i32 , align 4
%16 = ptrtoint i32*  %j to i64
%17 = sext i32 0 to i64
%18 = add i64 %16, %17
%19 = inttoptr i64 %18 to i32*
store i32 %low, i32*  %19
br label %LOOP_ENTRY_6
LOOP_ENTRY_6:
%20 = load i32,i32* %j
%21 = icmp slt i32 %20, %high
%22 = zext i1 %21 to i32

%23 = icmp ne i32 %22, 0
br i1 %23, label %LOOP_BODY_7, label %LOOP_END_8
LOOP_BODY_7:
%24 = ptrtoint i32* %arr to i64
%25 = load i32,i32* %j
%26 = mul i32 %25, 4
%27 = sext i32 %26 to i64
%28 = add i64 %24, %27
%29 = inttoptr i64 %28 to i32*
%30 = load i32,i32* %29
%31 = load i32,i32* %pivot
%32 = icmp sle i32 %30, %31
%33 = zext i1 %32 to i32

%34 = icmp ne i32 %33, 0
br i1 %34, label %IF_LABEL_19, label %END_LABEL_20
IF_LABEL_19:
%35 = load i32,i32* %i
%36 = add i32 %35, 1
store i32 %36, i32*  %i
br label %END_LABEL_20
END_LABEL_20:
%37 = load i32,i32* %j
%38 = add i32 %37, 1
store i32 %38, i32*  %j
br label %LOOP_ENTRY_6
LOOP_END_8:
%39 = sub i32 %low, 1
ret i32 %39
}

@local = global [ 4 x [ 4 x i32 ]] zeroinitializer, align 4
define i32 @main(){
%i = alloca i32 , align 4
%j = alloca i32 , align 4
store i32 0, i32*  %i
br label %LOOP_ENTRY_24
LOOP_ENTRY_24:
%1 = load i32,i32* %i
%2 = icmp slt i32 %1, 4
%3 = zext i1 %2 to i32

%4 = icmp ne i32 %3, 0
br i1 %4, label %LOOP_BODY_25, label %LOOP_END_26
LOOP_BODY_25:
store i32 0, i32*  %j
br label %LOOP_ENTRY_30
LOOP_ENTRY_30:
%5 = load i32,i32* %j
%6 = icmp slt i32 %5, 4
%7 = zext i1 %6 to i32

%8 = icmp ne i32 %7, 0
br i1 %8, label %LOOP_BODY_31, label %LOOP_END_32
LOOP_BODY_31:
%9 = ptrtoint [ 4 x[ 4 x i32 ]]* @local to i64
%10 = load i32,i32* %i
%11 = mul i32 16, %10
%12 = load i32,i32* %j
%13 = mul i32 %12, 4
%14 = add i32 %11, %13
%15 = sext i32 %14 to i64
%16 = add i64 %9, %15
%17 = inttoptr i64 %16 to i32*
%18 = load i32,i32* %17
call void @putint(i32 %18)
call void @putch(i32 32)
%19 = load i32,i32* %j
%20 = add i32 %19, 1
store i32 %20, i32*  %j
br label %LOOP_ENTRY_30
LOOP_END_32:
call void @putch(i32 10)
%21 = load i32,i32* %i
%22 = add i32 %21, 1
store i32 %22, i32*  %i
br label %LOOP_ENTRY_24
LOOP_END_26:
ret i32 0
}
