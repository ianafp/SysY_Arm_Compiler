declare void @putint(i32)
declare void @putch(i32)
declare void @putarray(i32, i32*)
declare i32 @getint()
declare i32 @getch()
declare i32 @getarray(i32*)
declare void @starttime()
declare void @stoptime()
declare void @putf(i8*, ...)
declare i32 @printf(i8*, ...)


@MAX_SIZE = constant i32  10000, align 4

@nums = global [ 10000 x i32 ] zeroinitializer, align 4
define void @swap(i32* %0, i32 %1, i32 %2){
%4 = alloca i32 , align 4
%5 = ptrtoint i32* %0 to i64
%6 = mul i32 %1, 4
%7 = sext i32 %6 to i64
%8 = add i64 %5, %7
%9 = inttoptr i64 %8 to i32*
%10 = load i32,i32* %9
store i32 %10, i32*  %4
%11 = ptrtoint i32* %0 to i64
%12 = mul i32 %2, 4
%13 = sext i32 %12 to i64
%14 = add i64 %11, %13
%15 = inttoptr i64 %14 to i32*
%16 = ptrtoint i32* %0 to i64
%17 = mul i32 %1, 4
%18 = sext i32 %17 to i64
%19 = add i64 %16, %18
%20 = inttoptr i64 %19 to i32*
%21 = load i32,i32* %15
store i32 %21, i32*  %20
%22 = ptrtoint i32* %0 to i64
%23 = mul i32 %2, 4
%24 = sext i32 %23 to i64
%25 = add i64 %22, %24
%26 = inttoptr i64 %25 to i32*
%27 = load i32,i32* %4
store i32 %27, i32*  %26
ret void
}
define i32 @partition(i32* %0, i32 %1, i32 %2){
%4 = alloca i32 , align 4
%5 = ptrtoint i32* %0 to i64
%6 = mul i32 %2, 4
%7 = sext i32 %6 to i64
%8 = add i64 %5, %7
%9 = inttoptr i64 %8 to i32*
%10 = load i32,i32* %9
store i32 %10, i32*  %4
%11 = alloca i32 , align 4
%12 = sub i32 %1, 1
store i32 %12, i32*  %11
%13 = alloca i32 , align 4
store i32 %1, i32*  %13
br label %LOOP_ENTRY_5
LOOP_ENTRY_5:
%14 = load i32,i32* %13
%15 = icmp slt i32 %14, %2
%16 = zext i1 %15 to i32

%17 = icmp ne i32 %16, 0
br i1 %17, label %LOOP_BODY_6, label %LOOP_END_7
LOOP_BODY_6:
%18 = ptrtoint i32* %0 to i64
%19 = load i32,i32* %13
%20 = mul i32 %19, 4
%21 = sext i32 %20 to i64
%22 = add i64 %18, %21
%23 = inttoptr i64 %22 to i32*
%24 = load i32,i32* %23
%25 = load i32,i32* %4
%26 = icmp sle i32 %24, %25
%27 = zext i1 %26 to i32

%28 = icmp ne i32 %27, 0
br i1 %28, label %IF_LABEL_18, label %END_LABEL_19
IF_LABEL_18:
%29 = load i32,i32* %11
%30 = add i32 %29, 1
store i32 %30, i32*  %11
%31 = load i32,i32* %11
%32 = load i32,i32* %13
call void @swap(i32* %0, i32 %31, i32 %32)
br label %END_LABEL_19
END_LABEL_19:
%33 = load i32,i32* %13
%34 = add i32 %33, 1
store i32 %34, i32*  %13
br label %LOOP_ENTRY_5
LOOP_END_7:
%35 = load i32,i32* %11
%36 = add i32 %35, 1
call void @swap(i32* %0, i32 %36, i32 %2)
%37 = load i32,i32* %11
%38 = add i32 %37, 1
ret i32 %38
}
define void @quick_sort(i32* %0, i32 %1, i32 %2){
%4 = icmp slt i32 %1, %2
%5 = zext i1 %4 to i32

%6 = icmp ne i32 %5, 0
br i1 %6, label %IF_LABEL_22, label %END_LABEL_23
IF_LABEL_22:
%7 = alloca i32 , align 4
%8 = call i32 @partition(i32* %0, i32 %1, i32 %2)
store i32 %8, i32*  %7
%9 = load i32,i32* %7
%10 = sub i32 %9, 1
call void @quick_sort(i32* %0, i32 %1, i32 %10)
%11 = load i32,i32* %7
%12 = add i32 %11, 1
call void @quick_sort(i32* %0, i32 %12, i32 %2)
br label %END_LABEL_23
END_LABEL_23:
ret void
}
define i32 @main(){
%1 = alloca i32 , align 4
%2 = call i32 @getint()
store i32 %2, i32*  %1
%3 = alloca i32 , align 4
store i32 0, i32*  %3
br label %LOOP_ENTRY_28
LOOP_ENTRY_28:
%4 = load i32,i32* %3
%5 = load i32,i32* %1
%6 = icmp slt i32 %4, %5
%7 = zext i1 %6 to i32

%8 = icmp ne i32 %7, 0
br i1 %8, label %LOOP_BODY_29, label %LOOP_END_30
LOOP_BODY_29:
%9 = call i32 @getint()
%10 = ptrtoint [ 10000 x i32 ]* @nums to i64
%11 = load i32,i32* %3
%12 = mul i32 %11, 4
%13 = sext i32 %12 to i64
%14 = add i64 %10, %13
%15 = inttoptr i64 %14 to i32*
store i32 %9, i32*  %15
%16 = load i32,i32* %3
%17 = add i32 %16, 1
store i32 %17, i32*  %3
br label %LOOP_ENTRY_28
LOOP_END_30:
%18 = bitcast [ 10000 x i32 ]* @nums to i32*
%19 = load i32,i32* %1
%20 = sub i32 %19, 1
call void @quick_sort(i32*  %18, i32 0, i32 %20)
store i32 0, i32*  %3
br label %LOOP_ENTRY_35
LOOP_ENTRY_35:
%21 = load i32,i32* %3
%22 = load i32,i32* %1
%23 = icmp slt i32 %21, %22
%24 = zext i1 %23 to i32

%25 = icmp ne i32 %24, 0
br i1 %25, label %LOOP_BODY_36, label %LOOP_END_37
LOOP_BODY_36:
%26 = ptrtoint [ 10000 x i32 ]* @nums to i64
%27 = load i32,i32* %3
%28 = mul i32 %27, 4
%29 = sext i32 %28 to i64
%30 = add i64 %26, %29
%31 = inttoptr i64 %30 to i32*
%32 = load i32,i32* %31
call void @putint(i32 %32)
call void @putch(i32 10)
%33 = load i32,i32* %3
%34 = add i32 %33, 1
store i32 %34, i32*  %3
br label %LOOP_ENTRY_35
LOOP_END_37:
ret i32 0
}
