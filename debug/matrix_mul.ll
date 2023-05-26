@.str = private unnamed_addr constant [ 5 x i8 ]c"%10d\00", align 1
@.str.1 = private unnamed_addr constant [ 2 x i8 ]c"\0A\00", align 1
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
%5 = alloca i32 , align 4
%6 = alloca i32 , align 4
br label %LOOP_ENTRY_5
LOOP_ENTRY_5:
%7 = load i32,i32* %4
%8 = icmp slt i32 %7, %0
%9 = zext i1 %8 to i32

%10 = icmp ne i32 %9, 0
br i1 %10, label %LOOP_BODY_6, label %LOOP_END_7
LOOP_BODY_6:
store i32 0, i32*  %5
br label %LOOP_ENTRY_11
LOOP_ENTRY_11:
%11 = load i32,i32* %5
%12 = icmp slt i32 %11, %1
%13 = zext i1 %12 to i32

%14 = icmp ne i32 %13, 0
br i1 %14, label %LOOP_BODY_12, label %LOOP_END_13
LOOP_BODY_12:
%15 = ptrtoint [ 25 x[ 25 x i32 ]]* @C to i64
%16 = load i32,i32* %4
%17 = mul i32 100, %16
%18 = load i32,i32* %5
%19 = mul i32 %18, 4
%20 = add i32 %17, %19
%21 = sext i32 %20 to i64
%22 = add i64 %15, %21
%23 = inttoptr i64 %22 to i32*
store i32 0, i32*  %23
store i32 0, i32*  %6
br label %LOOP_ENTRY_17
LOOP_ENTRY_17:
%24 = load i32,i32* %6
%25 = icmp slt i32 %24, %2
%26 = zext i1 %25 to i32

%27 = icmp ne i32 %26, 0
br i1 %27, label %LOOP_BODY_18, label %LOOP_END_19
LOOP_BODY_18:
%28 = ptrtoint [ 25 x[ 25 x i32 ]]* @C to i64
%29 = load i32,i32* %4
%30 = mul i32 100, %29
%31 = load i32,i32* %5
%32 = mul i32 %31, 4
%33 = add i32 %30, %32
%34 = sext i32 %33 to i64
%35 = add i64 %28, %34
%36 = inttoptr i64 %35 to i32*
%37 = load i32,i32* %36
%38 = ptrtoint [ 25 x[ 25 x i32 ]]* @A to i64
%39 = load i32,i32* %4
%40 = mul i32 100, %39
%41 = load i32,i32* %6
%42 = mul i32 %41, 4
%43 = add i32 %40, %42
%44 = sext i32 %43 to i64
%45 = add i64 %38, %44
%46 = inttoptr i64 %45 to i32*
%47 = load i32,i32* %46
%48 = ptrtoint [ 25 x[ 25 x i32 ]]* @B to i64
%49 = load i32,i32* %6
%50 = mul i32 100, %49
%51 = load i32,i32* %5
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
%63 = load i32,i32* %5
%64 = mul i32 %63, 4
%65 = add i32 %62, %64
%66 = sext i32 %65 to i64
%67 = add i64 %60, %66
%68 = inttoptr i64 %67 to i32*
store i32 %59, i32*  %68
%69 = load i32,i32* %6
%70 = add i32 %69, 1
store i32 %70, i32*  %6
br label %LOOP_ENTRY_17
LOOP_END_19:
%71 = load i32,i32* %5
%72 = add i32 %71, 1
store i32 %72, i32*  %5
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
%8 = alloca i32 , align 4
br label %LOOP_ENTRY_24
LOOP_ENTRY_24:
%9 = load i32,i32* %7
%10 = load i32,i32* %1
%11 = icmp slt i32 %9, %10
%12 = zext i1 %11 to i32

%13 = icmp ne i32 %12, 0
br i1 %13, label %LOOP_BODY_25, label %LOOP_END_26
LOOP_BODY_25:
store i32 0, i32*  %8
br label %LOOP_ENTRY_31
LOOP_ENTRY_31:
%14 = load i32,i32* %8
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
%23 = load i32,i32* %8
%24 = mul i32 %23, 4
%25 = add i32 %22, %24
%26 = sext i32 %25 to i64
%27 = add i64 %20, %26
%28 = inttoptr i64 %27 to i32*
store i32 %19, i32*  %28
%29 = load i32,i32* %8
%30 = add i32 %29, 1
store i32 %30, i32*  %8
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
store i32 0, i32*  %8
br label %LOOP_ENTRY_45
LOOP_ENTRY_45:
%40 = load i32,i32* %8
%41 = load i32,i32* %4
%42 = icmp slt i32 %40, %41
%43 = zext i1 %42 to i32

%44 = icmp ne i32 %43, 0
br i1 %44, label %LOOP_BODY_46, label %LOOP_END_47
LOOP_BODY_46:
%45 = call i32 @getint()
%46 = ptrtoint [ 25 x[ 25 x i32 ]]* @B to i64
%47 = load i32,i32* %7
%48 = mul i32 100, %47
%49 = load i32,i32* %8
%50 = mul i32 %49, 4
%51 = add i32 %48, %50
%52 = sext i32 %51 to i64
%53 = add i64 %46, %52
%54 = inttoptr i64 %53 to i32*
store i32 %45, i32*  %54
%55 = load i32,i32* %8
%56 = add i32 %55, 1
store i32 %56, i32*  %8
br label %LOOP_ENTRY_45
LOOP_END_47:
%57 = load i32,i32* %7
%58 = add i32 %57, 1
store i32 %58, i32*  %7
br label %LOOP_ENTRY_38
LOOP_END_40:
%59 = load i32,i32* %2
%60 = load i32,i32* %3
%61 = icmp ne i32 %59, %60
%62 = zext i1 %61 to i32

%63 = icmp ne i32 %62, 0
br i1 %63, label %IF_LABEL_52, label %END_LABEL_53
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
call void @putch(i32 105)
call void @putch(i32 111)
call void @putch(i32 110)
call void @putch(i32 115)
call void @putch(i32 10)
ret i32 0
br label %END_LABEL_53
END_LABEL_53:
%65 = load i32,i32* %1
%66 = load i32,i32* %4
%67 = load i32,i32* %2
call void @matrix_multiply(i32 %65, i32 %66, i32 %67)
store i32 0, i32*  %7
br label %LOOP_ENTRY_58
LOOP_ENTRY_58:
%68 = load i32,i32* %7
%69 = load i32,i32* %1
%70 = icmp slt i32 %68, %69
%71 = zext i1 %70 to i32

%72 = icmp ne i32 %71, 0
br i1 %72, label %LOOP_BODY_59, label %LOOP_END_60
LOOP_BODY_59:
store i32 0, i32*  %8
br label %LOOP_ENTRY_65
LOOP_ENTRY_65:
%73 = load i32,i32* %8
%74 = load i32,i32* %4
%75 = icmp slt i32 %73, %74
%76 = zext i1 %75 to i32

%77 = icmp ne i32 %76, 0
br i1 %77, label %LOOP_BODY_66, label %LOOP_END_67
LOOP_BODY_66:
%78 = bitcast [ 5 x i8 ]* @.str to i8*
%79 = ptrtoint [ 25 x[ 25 x i32 ]]* @C to i64
%80 = load i32,i32* %7
%81 = mul i32 100, %80
%82 = load i32,i32* %8
%83 = mul i32 %82, 4
%84 = add i32 %81, %83
%85 = sext i32 %84 to i64
%86 = add i64 %79, %85
%87 = inttoptr i64 %86 to i32*
%88 = load i32,i32* %87
%89 = call i32(i8*,...)  @printf(i8*  %78, i32 %88)
%90 = load i32,i32* %8
%91 = add i32 %90, 1
store i32 %91, i32*  %8
br label %LOOP_ENTRY_65
LOOP_END_67:
%92 = bitcast [ 2 x i8 ]* @.str.1 to i8*
%93 = call i32(i8*,...)  @printf(i8*  %92)
%94 = load i32,i32* %7
%95 = add i32 %94, 1
store i32 %95, i32*  %7
br label %LOOP_ENTRY_58
LOOP_END_60:
ret i32 0
}
