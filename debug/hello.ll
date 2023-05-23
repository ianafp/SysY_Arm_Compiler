
@v = addrspace(4) global i32 0, align 4

@g = addrspace(32) global [ 8 x i32 ][i32 1, i32 2, i32 7, i32 8, i32 0, i32 0, i32 0, i32 0], align 4
define i32 @main(){
%1 = add i32 3, 2
%w = alloca i32 , align 4
%2 = ptrtoint i32*  %w to i64
%3 = sext i32 0 to i64
%4 = add i64 %2, %3
%5 = inttoptr i64 %4 to i32*
store i32 %1, i32*  %5
%6 = load i32,i32* %w
%7 = icmp ne i32 %6, 0
%8 = zext i1 %7 to i32

%9 = icmp ne i32 %8, 0
br i1 %9, label %IF_LABEL_3, label %END_LABEL_4
IF_LABEL_3:
br label %END_LABEL_4
END_LABEL_4:
%10 = icmp ne i32 1, 0
%11 = zext i1 %10 to i32

%12 = icmp ne i32 %11, 0
br i1 %12, label %IF_LABEL_5, label %END_LABEL_6
IF_LABEL_5:
%13 = icmp ne i32 1, 0
%14 = zext i1 %13 to i32

%15 = icmp ne i32 %14, 0
br i1 %15, label %IF_LABEL_7, label %END_LABEL_8
IF_LABEL_7:
%16 = icmp ne i32 1, 0
%17 = zext i1 %16 to i32

%18 = icmp ne i32 %17, 0
br i1 %18, label %IF_LABEL_9, label %ELSE_LABEL_10
IF_LABEL_9:
ret void
br label %END_LABEL_11
ELSE_LABEL_10:
ret void
br label %END_LABEL_11
END_LABEL_11:
br label %END_LABEL_8
END_LABEL_8:
br label %END_LABEL_6
END_LABEL_6:
%19 = icmp ne i32 3, 0
%20 = zext i1 %19 to i32

%21 = icmp ne i32 %20, 0
br i1 %21, label %IF_LABEL_12, label %END_LABEL_13
IF_LABEL_12:
br label %END_LABEL_13
END_LABEL_13:
%22 = icmp ne i32 2, 0
%23 = zext i1 %22 to i32

%24 = icmp ne i32 %23, 0
br i1 %24, label %IF_LABEL_14, label %ELSE_LABEL_15
IF_LABEL_14:
br label %END_LABEL_16
ELSE_LABEL_15:
br label %END_LABEL_16
END_LABEL_16:
%25 = icmp ne i32 0, 5
%26 = icmp ne i32 0, 2
%27 = and i32 %25, %26%28 = icmp ne i32 0, 10
%29 = icmp ne i32 0, %27
%30 = or i32 %28, %29
%31 = icmp ne i32 %30, 0
br i1 %31, label %IF_LABEL_23, label %END_LABEL_24
IF_LABEL_23:
br label %END_LABEL_24
END_LABEL_24:
%ss = alloca [ 8 x i32 ], align 4
%32 = ptrtoint [8x i32 ]* %ss to i64
%33 = sext i32 0 to i64
%34 = add i64 %32, %33
%35 = inttoptr i64 %34 to i32*
store i32 1, i32*  %35
%a = alloca i32 , align 4
%36 = ptrtoint i32*  %a to i64
%37 = sext i32 0 to i64
%38 = add i64 %36, %37
%39 = inttoptr i64 %38 to i32*
%40 = load i32,i32* @v
store i32 %40, i32*  %39
%41 = load i32,i32* %a
%42 = mul i32 %41, 5
store i32 %42, i32*  %a
%43 = mul i32 9, 8
%44 = sdiv i32 %43, 7
%45 = load i32,i32* %a
%46 = add i32 %45, %44
%47 = icmp eq i32 8, 0
%48 = zext i1 %47 to i32
%49 = add i32 %46, %48
store i32 %49, i32*  %a
%50 = load i32,i32* %a
ret i32 %50
}
