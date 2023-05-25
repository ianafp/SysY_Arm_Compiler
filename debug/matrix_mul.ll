declare void @putint(i32)
declare void @putch(i32)
declare void @putarray(i32, i32*)
declare i32 @getint()
declare i32 @getch()
declare i32 @getarray(i32*)
declare void @starttime()
declare void @stoptime()
declare void @putf(i8*, i32, ...)


@MAX_SIZE = constant i32  25, align 4

@A = global [ 25 x [ 25 x i32 ]] zeroinitializer, align 4

@B = global [ 25 x [ 25 x i32 ]] zeroinitializer, align 4

@C = global [ 25 x [ 25 x i32 ]] zeroinitializer, align 4
define void @matrix_multiply(i32 %0, i32 %1, i32 %2){
%4 = alloca i32 , align 4
%5 = ptrtoint i32*  %4 to i64
%6 = sext i32 0 to i64
%7 = add i64 %5, 0
%8 = inttoptr i64 %7 to i32*
store i32 0, i32*  %8
br label %LOOP_ENTRY_5
LOOP_ENTRY_5:
%9 = load i32,i32* %4
%10 = icmp slt i32 %9, %0
%11 = zext i1 %10 to i32

%12 = icmp ne i32 %11, 0
br i1 %12, label %LOOP_BODY_6, label %LOOP_END_7
LOOP_BODY_6:
%13 = alloca i32 , align 4
%14 = ptrtoint i32*  %13 to i64
%15 = sext i32 0 to i64
%16 = add i64 %14, 0
%17 = inttoptr i64 %16 to i32*
store i32 0, i32*  %17
br label %LOOP_ENTRY_11
LOOP_ENTRY_11:
%18 = load i32,i32* %13
%19 = icmp slt i32 %18, %1
%20 = zext i1 %19 to i32

%21 = icmp ne i32 %20, 0
br i1 %21, label %LOOP_BODY_12, label %LOOP_END_13
LOOP_BODY_12:
%22 = ptrtoint [ 25 x[ 25 x i32 ]]* @C to i64
%23 = load i32,i32* %4
%24 = mul i32 100, %23
%25 = load i32,i32* %13
%26 = mul i32 %25, 4
%27 = add i32 %24, %26
%28 = sext i32 %27 to i64
%29 = add i64 %22, %28
%30 = inttoptr i64 %29 to i32*
store i32 0, i32*  %30
%31 = alloca i32 , align 4
%32 = ptrtoint i32*  %31 to i64
%33 = sext i32 0 to i64
%34 = add i64 %32, 0
%35 = inttoptr i64 %34 to i32*
store i32 0, i32*  %35
br label %LOOP_ENTRY_17
LOOP_ENTRY_17:
%36 = load i32,i32* %31
%37 = icmp slt i32 %36, %2
%38 = zext i1 %37 to i32

%39 = icmp ne i32 %38, 0
br i1 %39, label %LOOP_BODY_18, label %LOOP_END_19
LOOP_BODY_18:
%40 = ptrtoint [ 25 x[ 25 x i32 ]]* @C to i64
%41 = load i32,i32* %4
%42 = mul i32 100, %41
%43 = load i32,i32* %13
%44 = mul i32 %43, 4
%45 = add i32 %42, %44
%46 = sext i32 %45 to i64
%47 = add i64 %40, %46
%48 = inttoptr i64 %47 to i32*
%49 = load i32,i32* %48
%50 = ptrtoint [ 25 x[ 25 x i32 ]]* @A to i64
%51 = load i32,i32* %4
%52 = mul i32 100, %51
%53 = load i32,i32* %31
%54 = mul i32 %53, 4
%55 = add i32 %52, %54
%56 = sext i32 %55 to i64
%57 = add i64 %50, %56
%58 = inttoptr i64 %57 to i32*
%59 = load i32,i32* %58
%60 = ptrtoint [ 25 x[ 25 x i32 ]]* @B to i64
%61 = load i32,i32* %31
%62 = mul i32 100, %61
%63 = load i32,i32* %13
%64 = mul i32 %63, 4
%65 = add i32 %62, %64
%66 = sext i32 %65 to i64
%67 = add i64 %60, %66
%68 = inttoptr i64 %67 to i32*
%69 = load i32,i32* %68
%70 = mul i32 %59, %69
%71 = add i32 %49, %70
%72 = ptrtoint [ 25 x[ 25 x i32 ]]* @C to i64
%73 = load i32,i32* %4
%74 = mul i32 100, %73
%75 = load i32,i32* %13
%76 = mul i32 %75, 4
%77 = add i32 %74, %76
%78 = sext i32 %77 to i64
%79 = add i64 %72, %78
%80 = inttoptr i64 %79 to i32*
store i32 %71, i32*  %80
%81 = load i32,i32* %31
%82 = add i32 %81, 1
store i32 %82, i32*  %31
br label %LOOP_ENTRY_17
LOOP_END_19:
%83 = load i32,i32* %13
%84 = add i32 %83, 1
store i32 %84, i32*  %13
br label %LOOP_ENTRY_11
LOOP_END_13:
%85 = load i32,i32* %4
%86 = add i32 %85, 1
store i32 %86, i32*  %4
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
%8 = ptrtoint i32*  %7 to i64
%9 = sext i32 0 to i64
%10 = add i64 %8, 0
%11 = inttoptr i64 %10 to i32*
store i32 0, i32*  %11
br label %LOOP_ENTRY_24
LOOP_ENTRY_24:
%12 = load i32,i32* %7
%13 = load i32,i32* %1
%14 = icmp slt i32 %12, %13
%15 = zext i1 %14 to i32

%16 = icmp ne i32 %15, 0
br i1 %16, label %LOOP_BODY_25, label %LOOP_END_26
LOOP_BODY_25:
%17 = alloca i32 , align 4
%18 = ptrtoint i32*  %17 to i64
%19 = sext i32 0 to i64
%20 = add i64 %18, 0
%21 = inttoptr i64 %20 to i32*
store i32 0, i32*  %21
br label %LOOP_ENTRY_31
LOOP_ENTRY_31:
%22 = load i32,i32* %17
%23 = load i32,i32* %2
%24 = icmp slt i32 %22, %23
%25 = zext i1 %24 to i32

%26 = icmp ne i32 %25, 0
br i1 %26, label %LOOP_BODY_32, label %LOOP_END_33
LOOP_BODY_32:
%27 = call i32 @getint()
%28 = ptrtoint [ 25 x[ 25 x i32 ]]* @A to i64
%29 = load i32,i32* %7
%30 = mul i32 100, %29
%31 = load i32,i32* %17
%32 = mul i32 %31, 4
%33 = add i32 %30, %32
%34 = sext i32 %33 to i64
%35 = add i64 %28, %34
%36 = inttoptr i64 %35 to i32*
store i32 %27, i32*  %36
%37 = load i32,i32* %17
%38 = add i32 %37, 1
store i32 %38, i32*  %17
br label %LOOP_ENTRY_31
LOOP_END_33:
%39 = load i32,i32* %7
%40 = add i32 %39, 1
store i32 %40, i32*  %7
br label %LOOP_ENTRY_24
LOOP_END_26:
%41 = call i32 @getint()
store i32 %41, i32*  %3
%42 = call i32 @getint()
store i32 %42, i32*  %4
store i32 0, i32*  %7
br label %LOOP_ENTRY_38
LOOP_ENTRY_38:
%43 = load i32,i32* %7
%44 = load i32,i32* %3
%45 = icmp slt i32 %43, %44
%46 = zext i1 %45 to i32

%47 = icmp ne i32 %46, 0
br i1 %47, label %LOOP_BODY_39, label %LOOP_END_40
LOOP_BODY_39:
%48 = alloca i32 , align 4
%49 = ptrtoint i32*  %48 to i64
%50 = sext i32 0 to i64
%51 = add i64 %49, 0
%52 = inttoptr i64 %51 to i32*
store i32 0, i32*  %52
br label %LOOP_ENTRY_45
LOOP_ENTRY_45:
%53 = load i32,i32* %48
%54 = load i32,i32* %4
%55 = icmp slt i32 %53, %54
%56 = zext i1 %55 to i32

%57 = icmp ne i32 %56, 0
br i1 %57, label %LOOP_BODY_46, label %LOOP_END_47
LOOP_BODY_46:
%58 = call i32 @getint()
%59 = ptrtoint [ 25 x[ 25 x i32 ]]* @B to i64
%60 = load i32,i32* %7
%61 = mul i32 100, %60
%62 = load i32,i32* %48
%63 = mul i32 %62, 4
%64 = add i32 %61, %63
%65 = sext i32 %64 to i64
%66 = add i64 %59, %65
%67 = inttoptr i64 %66 to i32*
store i32 %58, i32*  %67
%68 = load i32,i32* %48
%69 = add i32 %68, 1
store i32 %69, i32*  %48
br label %LOOP_ENTRY_45
LOOP_END_47:
%70 = load i32,i32* %7
%71 = add i32 %70, 1
store i32 %71, i32*  %7
br label %LOOP_ENTRY_38
LOOP_END_40:
%72 = load i32,i32* %2
%73 = load i32,i32* %3
%74 = icmp ne i32 %72, %73
%75 = zext i1 %74 to i32

%76 = icmp ne i32 %75, 0
br i1 %76, label %IF_LABEL_52, label %END_LABEL_53
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
%77 = load i32,i32* %1
%78 = load i32,i32* %4
%79 = load i32,i32* %2
call void @matrix_multiply(i32 %77, i32 %78, i32 %79)
store i32 0, i32*  %7
br label %LOOP_ENTRY_58
LOOP_ENTRY_58:
%80 = load i32,i32* %7
%81 = load i32,i32* %1
%82 = icmp slt i32 %80, %81
%83 = zext i1 %82 to i32

%84 = icmp ne i32 %83, 0
br i1 %84, label %LOOP_BODY_59, label %LOOP_END_60
LOOP_BODY_59:
%17 = alloca i32 , align 4
%85 = ptrtoint i32*  %17 to i64
%86 = sext i32 0 to i64
%87 = add i64 %85, 0
%88 = inttoptr i64 %87 to i32*
store i32 0, i32*  %88
br label %LOOP_ENTRY_65
LOOP_ENTRY_65:
%89 = load i32,i32* %17
%90 = load i32,i32* %4
%91 = icmp slt i32 %89, %90
%92 = zext i1 %91 to i32

%93 = icmp ne i32 %92, 0
br i1 %93, label %LOOP_BODY_66, label %LOOP_END_67
LOOP_BODY_66:
%94 = ptrtoint [ 25 x[ 25 x i32 ]]* @C to i64
%95 = load i32,i32* %7
%96 = mul i32 100, %95
%97 = load i32,i32* %17
%98 = mul i32 %97, 4
%99 = add i32 %96, %98
%100 = sext i32 %99 to i64
%101 = add i64 %94, %100
%102 = inttoptr i64 %101 to i32*
%103 = load i32,i32* %102
call void @putint(i32 %103)
%104 = load i32,i32* %17
%105 = add i32 %104, 1
store i32 %105, i32*  %17
br label %LOOP_ENTRY_65
LOOP_END_67:
call void @putch(i32 10)
%106 = load i32,i32* %7
%107 = add i32 %106, 1
store i32 %107, i32*  %7
br label %LOOP_ENTRY_58
LOOP_END_60:
ret i32 0
}
