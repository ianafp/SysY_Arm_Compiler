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
ret void
}
define i32 @partition(i32* %0, i32 %1, i32 %2){
%4 = alloca i32 , align 4
%5 = ptrtoint i32* %0 to i64
%6 = mul i32 %2, 4
%7 = sext i32 %6 to i64
%8 = add i64 %5, %7
%9 = inttoptr i64 %8 to i32*
%10 = ptrtoint i32*  %4 to i64
%11 = sext i32 0 to i64
%12 = add i64 %10, 0
%13 = inttoptr i64 %12 to i32*
%14 = load i32,i32* %9
store i32 %14, i32*  %13
%15 = alloca i32 , align 4
%16 = sub i32 %1, 1
%17 = ptrtoint i32*  %15 to i64
%18 = sext i32 0 to i64
%19 = add i64 %17, 0
%20 = inttoptr i64 %19 to i32*
store i32 %16, i32*  %20
%21 = alloca i32 , align 4
%22 = ptrtoint i32*  %21 to i64
%23 = sext i32 0 to i64
%24 = add i64 %22, 0
%25 = inttoptr i64 %24 to i32*
store i32 %1, i32*  %25
br label %LOOP_ENTRY_5
LOOP_ENTRY_5:
%26 = load i32,i32* %21
%27 = icmp slt i32 %26, %2
%28 = zext i1 %27 to i32

%29 = icmp ne i32 %28, 0
br i1 %29, label %LOOP_BODY_6, label %LOOP_END_7
LOOP_BODY_6:
%30 = ptrtoint i32* %0 to i64
%31 = load i32,i32* %21
%32 = mul i32 %31, 4
%33 = sext i32 %32 to i64
%34 = add i64 %30, %33
%35 = inttoptr i64 %34 to i32*
%36 = load i32,i32* %35
%37 = load i32,i32* %4
%38 = icmp sle i32 %36, %37
%39 = zext i1 %38 to i32

%40 = icmp ne i32 %39, 0
br i1 %40, label %IF_LABEL_18, label %END_LABEL_19
IF_LABEL_18:
%41 = load i32,i32* %15
%42 = add i32 %41, 1
store i32 %42, i32*  %15
%43 = bitcast i32* %0 to i32*
%44 = load i32,i32* %15
%45 = load i32,i32* %21
call void @swap(i32*  %43, i32 %44, i32 %45)
br label %END_LABEL_19
END_LABEL_19:
%46 = load i32,i32* %21
%47 = add i32 %46, 1
store i32 %47, i32*  %21
br label %LOOP_ENTRY_5
LOOP_END_7:
%48 = bitcast i32* %0 to i32*
%49 = load i32,i32* %15
%50 = add i32 %49, 1
call void @swap(i32*  %48, i32 %50, i32 %2)
%51 = load i32,i32* %15
%52 = add i32 %51, 1
ret i32 %52
}
define void @quick_sort(i32* %0, i32 %1, i32 %2){
%4 = icmp slt i32 %1, %2
%5 = zext i1 %4 to i32

%6 = icmp ne i32 %5, 0
br i1 %6, label %IF_LABEL_22, label %END_LABEL_23
IF_LABEL_22:
%7 = alloca i32 , align 4
%8 = bitcast i32* %0 to i32*
%9 = call i32 @partition(i32*  %8, i32 %1, i32 %2)
%10 = ptrtoint i32*  %7 to i64
%11 = sext i32 0 to i64
%12 = add i64 %10, 0
%13 = inttoptr i64 %12 to i32*
store i32 %9, i32*  %13
%14 = bitcast i32* %0 to i32*
%15 = load i32,i32* %7
%16 = sub i32 %15, 1
call void @quick_sort(i32*  %14, i32 %1, i32 %16)
%17 = bitcast i32* %0 to i32*
%18 = load i32,i32* %7
%19 = add i32 %18, 1
call void @quick_sort(i32*  %17, i32 %19, i32 %2)
br label %END_LABEL_23
END_LABEL_23:
ret void
}
define i32 @main(){
%1 = alloca i32 , align 4
%2 = call i32 @getint()
%3 = ptrtoint i32*  %1 to i64
%4 = sext i32 0 to i64
%5 = add i64 %3, 0
%6 = inttoptr i64 %5 to i32*
store i32 %2, i32*  %6
%7 = alloca i32 , align 4
%8 = ptrtoint i32*  %7 to i64
%9 = sext i32 0 to i64
%10 = add i64 %8, 0
%11 = inttoptr i64 %10 to i32*
store i32 0, i32*  %11
br label %LOOP_ENTRY_28
LOOP_ENTRY_28:
%12 = load i32,i32* %7
%13 = load i32,i32* %1
%14 = icmp slt i32 %12, %13
%15 = zext i1 %14 to i32

%16 = icmp ne i32 %15, 0
br i1 %16, label %LOOP_BODY_29, label %LOOP_END_30
LOOP_BODY_29:
%17 = call i32 @getint()
%18 = ptrtoint [ 10000 x i32 ]* @nums to i64
%19 = load i32,i32* %7
%20 = mul i32 %19, 4
%21 = sext i32 %20 to i64
%22 = add i64 %18, %21
%23 = inttoptr i64 %22 to i32*
store i32 %17, i32*  %23
%24 = load i32,i32* %7
%25 = add i32 %24, 1
store i32 %25, i32*  %7
br label %LOOP_ENTRY_28
LOOP_END_30:
%26 = bitcast [ 10000 x i32 ]* @nums to i32*
%27 = load i32,i32* %1
%28 = sub i32 %27, 1
call void @quick_sort(i32*  %26, i32 0, i32 %28)
store i32 0, i32*  %7
br label %LOOP_ENTRY_35
LOOP_ENTRY_35:
%29 = load i32,i32* %7
%30 = load i32,i32* %1
%31 = icmp slt i32 %29, %30
%32 = zext i1 %31 to i32

%33 = icmp ne i32 %32, 0
br i1 %33, label %LOOP_BODY_36, label %LOOP_END_37
LOOP_BODY_36:
%34 = ptrtoint [ 10000 x i32 ]* @nums to i64
%35 = load i32,i32* %7
%36 = mul i32 %35, 4
%37 = sext i32 %36 to i64
%38 = add i64 %34, %37
%39 = inttoptr i64 %38 to i32*
%40 = load i32,i32* %39
call void @putint(i32 %40)
call void @putch(i32 10)
%41 = load i32,i32* %7
%42 = add i32 %41, 1
store i32 %42, i32*  %7
br label %LOOP_ENTRY_35
LOOP_END_37:
ret i32 0
}
