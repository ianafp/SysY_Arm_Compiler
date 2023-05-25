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


@MAX_SIZE = constant i32  25, align 4

@A = global [ 25 x [ 25 x i32 ]] zeroinitializer, align 4

@B = global [ 25 x [ 25 x i32 ]] zeroinitializer, align 4

@C = global [ 25 x [ 25 x i32 ]] zeroinitializer, align 4
define void @matrix_multiply(i32 %0, i32 %1, i32 %2){
%4 = alloca i32 , align 4
store i32 0, i32*  %4
br label %LOOP_ENTRY_5
LOOP_ENTRY_5:
%5 = load i32,i32* %4
%6 = icmp slt i32 %5, %0
%7 = zext i1 %6 to i32

%8 = icmp ne i32 %7, 0
br i1 %8, label %LOOP_BODY_6, label %LOOP_END_7
LOOP_BODY_6:
%9 = alloca i32 , align 4
store i32 0, i32*  %9
br label %LOOP_ENTRY_11
LOOP_ENTRY_11:
%10 = load i32,i32* %9
%11 = icmp slt i32 %10, %1
%12 = zext i1 %11 to i32

%13 = icmp ne i32 %12, 0
br i1 %13, label %LOOP_BODY_12, label %LOOP_END_13
LOOP_BODY_12:
%14 = ptrtoint [ 25 x[ 25 x i32 ]]* @C to i64
%15 = load i32,i32* %4
%16 = mul i32 100, %15
%17 = load i32,i32* %9
%18 = mul i32 %17, 4
%19 = add i32 %16, %18
%20 = sext i32 %19 to i64
%21 = add i64 %14, %20
%22 = inttoptr i64 %21 to i32*
store i32 0, i32*  %22
%23 = alloca i32 , align 4
store i32 0, i32*  %23
br label %LOOP_ENTRY_17
LOOP_ENTRY_17:
%24 = load i32,i32* %23
%25 = icmp slt i32 %24, %2
%26 = zext i1 %25 to i32

%27 = icmp ne i32 %26, 0
br i1 %27, label %LOOP_BODY_18, label %LOOP_END_19
LOOP_BODY_18:
%28 = ptrtoint [ 25 x[ 25 x i32 ]]* @C to i64
%29 = load i32,i32* %4
%30 = mul i32 100, %29
%31 = load i32,i32* %9
%32 = mul i32 %31, 4
%33 = add i32 %30, %32
%34 = sext i32 %33 to i64
%35 = add i64 %28, %34
%36 = inttoptr i64 %35 to i32*
%37 = load i32,i32* %36
%38 = ptrtoint [ 25 x[ 25 x i32 ]]* @A to i64
%39 = load i32,i32* %4
%40 = mul i32 100, %39
%41 = load i32,i32* %23
%42 = mul i32 %41, 4
%43 = add i32 %40, %42
%44 = sext i32 %43 to i64
%45 = add i64 %38, %44
%46 = inttoptr i64 %45 to i32*
%47 = load i32,i32* %46
%48 = ptrtoint [ 25 x[ 25 x i32 ]]* @B to i64
%49 = load i32,i32* %23
%50 = mul i32 100, %49
%51 = load i32,i32* %9
%52 = mul i32 %51, 4
%53 = add i32 %50, %52
%54 = sext i32 %53 to i64
%55 = add i64 %48, %54
%56 = inttoptr i64 %55 to i32*
%57 = load i32,i32* %56
%58 = mul i32 %47, %57
%59 = add i32 %37, %58
%60 = ptrtoint [ 25 x[ 25 x i32 ]]* @C to i64
%61 = load i32,i32* %4
%62 = mul i32 100, %61
%63 = load i32,i32* %9
%64 = mul i32 %63, 4
%65 = add i32 %62, %64
%66 = sext i32 %65 to i64
%67 = add i64 %60, %66
%68 = inttoptr i64 %67 to i32*
store i32 %59, i32*  %68
%69 = load i32,i32* %23
%70 = add i32 %69, 1
store i32 %70, i32*  %23
br label %LOOP_ENTRY_17
LOOP_END_19:
%71 = load i32,i32* %9
%72 = add i32 %71, 1
store i32 %72, i32*  %9
br label %LOOP_ENTRY_11
LOOP_END_13:
%73 = load i32,i32* %4
%74 = add i32 %73, 1
store i32 %74, i32*  %4
br label %LOOP_ENTRY_5
LOOP_END_7:
ret void
}
define i32 @main(){
%1 = alloca i32 , align 4
%2 = alloca i32 , align 4
%3 = alloca i32 , align 4
%4 = alloca i32 , align 4
%5 = call i32 @getint()
store i32 %5, i32*  %1
%6 = call i32 @getint()
store i32 %6, i32*  %2
%7 = alloca i32 , align 4
store i32 0, i32*  %7
br label %LOOP_ENTRY_24
LOOP_ENTRY_24:
%8 = load i32,i32* %7
%9 = load i32,i32* %1
%10 = icmp slt i32 %8, %9
%11 = zext i1 %10 to i32

%12 = icmp ne i32 %11, 0
br i1 %12, label %LOOP_BODY_25, label %LOOP_END_26
LOOP_BODY_25:
%13 = alloca i32 , align 4
store i32 0, i32*  %13
br label %LOOP_ENTRY_31
LOOP_ENTRY_31:
%14 = load i32,i32* %13
%15 = load i32,i32* %2
%16 = icmp slt i32 %14, %15
%17 = zext i1 %16 to i32

%18 = icmp ne i32 %17, 0
br i1 %18, label %LOOP_BODY_32, label %LOOP_END_33
LOOP_BODY_32:
%19 = call i32 @getint()
%20 = ptrtoint [ 25 x[ 25 x i32 ]]* @A to i64
%21 = load i32,i32* %7
%22 = mul i32 100, %21
%23 = load i32,i32* %13
%24 = mul i32 %23, 4
%25 = add i32 %22, %24
%26 = sext i32 %25 to i64
%27 = add i64 %20, %26
%28 = inttoptr i64 %27 to i32*
store i32 %19, i32*  %28
%29 = load i32,i32* %13
%30 = add i32 %29, 1
store i32 %30, i32*  %13
br label %LOOP_ENTRY_31
LOOP_END_33:
%31 = load i32,i32* %7
%32 = add i32 %31, 1
store i32 %32, i32*  %7
br label %LOOP_ENTRY_24
LOOP_END_26:
%33 = call i32 @getint()
store i32 %33, i32*  %3
%34 = call i32 @getint()
store i32 %34, i32*  %4
store i32 0, i32*  %7
br label %LOOP_ENTRY_38
LOOP_ENTRY_38:
%35 = load i32,i32* %7
%36 = load i32,i32* %3
%37 = icmp slt i32 %35, %36
%38 = zext i1 %37 to i32

%39 = icmp ne i32 %38, 0
br i1 %39, label %LOOP_BODY_39, label %LOOP_END_40
LOOP_BODY_39:
%40 = alloca i32 , align 4
store i32 0, i32*  %40
br label %LOOP_ENTRY_45
LOOP_ENTRY_45:
%41 = load i32,i32* %40
%42 = load i32,i32* %4
%43 = icmp slt i32 %41, %42
%44 = zext i1 %43 to i32

%45 = icmp ne i32 %44, 0
br i1 %45, label %LOOP_BODY_46, label %LOOP_END_47
LOOP_BODY_46:
%46 = call i32 @getint()
%47 = ptrtoint [ 25 x[ 25 x i32 ]]* @B to i64
%48 = load i32,i32* %7
%49 = mul i32 100, %48
%50 = load i32,i32* %40
%51 = mul i32 %50, 4
%52 = add i32 %49, %51
%53 = sext i32 %52 to i64
%54 = add i64 %47, %53
%55 = inttoptr i64 %54 to i32*
store i32 %46, i32*  %55
%56 = load i32,i32* %40
%57 = add i32 %56, 1
store i32 %57, i32*  %40
br label %LOOP_ENTRY_45
LOOP_END_47:
%58 = load i32,i32* %7
%59 = add i32 %58, 1
store i32 %59, i32*  %7
br label %LOOP_ENTRY_38
LOOP_END_40:
%60 = load i32,i32* %2
%61 = load i32,i32* %3
%62 = icmp ne i32 %60, %61
%63 = zext i1 %62 to i32

%64 = icmp ne i32 %63, 0
br i1 %64, label %IF_LABEL_52, label %END_LABEL_53
IF_LABEL_52:
call void @putch(i32 73)
call void @putch(i32 110)
call void @putch(i32 99)
call void @putch(i32 111)
call void @putch(i32 109)
call void @putch(i32 112)
call void @putch(i32 97)
call void @putch(i32 116)
call void @putch(i32 105)
call void @putch(i32 98)
call void @putch(i32 108)
call void @putch(i32 101)
call void @putch(i32 32)
call void @putch(i32 68)
call void @putch(i32 105)
call void @putch(i32 109)
call void @putch(i32 101)
call void @putch(i32 110)
call void @putch(i32 115)
call void @putch(i32 10)
ret i32 0
br label %END_LABEL_53
END_LABEL_53:
%66 = load i32,i32* %1
%67 = load i32,i32* %4
%68 = load i32,i32* %2
call void @matrix_multiply(i32 %66, i32 %67, i32 %68)
store i32 0, i32*  %7
br label %LOOP_ENTRY_58
LOOP_ENTRY_58:
%69 = load i32,i32* %7
%70 = load i32,i32* %1
%71 = icmp slt i32 %69, %70
%72 = zext i1 %71 to i32

%73 = icmp ne i32 %72, 0
br i1 %73, label %LOOP_BODY_59, label %LOOP_END_60
LOOP_BODY_59:
%13 = alloca i32 , align 4
store i32 0, i32*  %13
br label %LOOP_ENTRY_65
LOOP_ENTRY_65:
%74 = load i32,i32* %13
%75 = load i32,i32* %4
%76 = icmp slt i32 %74, %75
%77 = zext i1 %76 to i32

%78 = icmp ne i32 %77, 0
br i1 %78, label %LOOP_BODY_66, label %LOOP_END_67
LOOP_BODY_66:
%79 = ptrtoint [ 25 x[ 25 x i32 ]]* @C to i64
%80 = load i32,i32* %7
%81 = mul i32 100, %80
%82 = load i32,i32* %13
%83 = mul i32 %82, 4
%84 = add i32 %81, %83
%85 = sext i32 %84 to i64
%86 = add i64 %79, %85
%87 = inttoptr i64 %86 to i32*
%88 = load i32,i32* %87
call void @putint(i32 %88)
%89 = load i32,i32* %13
%90 = add i32 %89, 1
store i32 %90, i32*  %13
br label %LOOP_ENTRY_65
LOOP_END_67:
call void @putch(i32 10)
%91 = load i32,i32* %7
%92 = add i32 %91, 1
store i32 %92, i32*  %7
br label %LOOP_ENTRY_58
LOOP_END_60:
ret i32 0
}
