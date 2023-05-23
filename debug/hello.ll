
@v = addrspace(4) global i32 0, align 4

;@g = addrspace(32) global [ 8 x i32 ][[i32 1, i32 2, , i32 7, , i32 8, , ], [ 8 x i32 ] zeroinitializer, [ 8 x i32 ] zeroinitializer, [ 8 x i32 ] zeroinitializer, [ 8 x i32 ] zeroinitializer, [ 8 x i32 ] zeroinitializer, [ 8 x i32 ] zeroinitializer, [ 8 x i32 ] zeroinitializer], align 4
define i32 @main(){
%1 = add i32 3, 2
%w = alloca i32 i32 , align 4
%2 = bitcast i32*  to i64
%3 = add i64 %2, 0
%4 = bitcast i32 to i32*
store i32 %1, i32*  %4
%5 = bitcast i32 to i32*
%6 = add i32*  %5, 1
%7 = bitcast i32 to i32*
store i32 %6, i32*  %7
%8 = icmp ne i32 1, 0
%9 = zext i1 %8 to i32

%10 = icmp ne i32 %9, 0
br i1 %10, label %IF_LABEL_3, label %END_LABEL_4
IF_LABEL_3:
br label %END_LABEL_4
END_LABEL_4:
%11 = icmp ne i32 1, 0
%12 = zext i1 %11 to i32

%13 = icmp ne i32 %12, 0
br i1 %13, label %IF_LABEL_5, label %END_LABEL_6
IF_LABEL_5:
%14 = icmp ne i32 1, 0
%15 = zext i1 %14 to i32

%16 = icmp ne i32 %15, 0
br i1 %16, label %IF_LABEL_7, label %END_LABEL_8
IF_LABEL_7:
%17 = icmp ne i32 1, 0
%18 = zext i1 %17 to i32

%19 = icmp ne i32 %18, 0
br i1 %19, label %IF_LABEL_9, label %ELSE_LABEL_10
IF_LABEL_9:
ret i32 
br label %END_LABEL_11
ELSE_LABEL_10:
ret i32 
br label %END_LABEL_11
END_LABEL_11:
br label %END_LABEL_8
END_LABEL_8:
br label %END_LABEL_6
END_LABEL_6:
%20 = icmp ne i32 3, 0
%21 = zext i1 %20 to i32

%22 = icmp ne i32 %21, 0
br i1 %22, label %IF_LABEL_12, label %END_LABEL_13
IF_LABEL_12:
br label %END_LABEL_13
END_LABEL_13:
%23 = icmp ne i32 2, 0
%24 = zext i1 %23 to i32

%25 = icmp ne i32 %24, 0
br i1 %25, label %IF_LABEL_14, label %ELSE_LABEL_15
IF_LABEL_14:
br label %END_LABEL_16
ELSE_LABEL_15:
br label %END_LABEL_16
END_LABEL_16:
%26 = icmp ne i32 0, 5
%27 = icmp ne i32 0, 2
%28 = and i32 %26, %27%29 = icmp ne i32 0, 10
%30 = icmp ne i32 0, %28
%31 = or i32 %29, %30
%32 = icmp ne i32 %31, 0
br i1 %32, label %IF_LABEL_23, label %END_LABEL_24
IF_LABEL_23:
br label %END_LABEL_24
END_LABEL_24:
%ss = alloca i32 [ 8 x i32 ], align 4
%33 = bitcast [8x i32 ] to i64
%34 = add [8x i64 ] %33, 0
%35 = bitcast i32 to i32*
store i32 1, i32*  %35
%36 = bitcast i32 to i32*
%a = alloca i32 i32 , align 4
%37 = bitcast i32*  to i64
%38 = add i64 %37, 0
%39 = bitcast i32 to i32*
store i32*  %36, i32*  %39
%40 = bitcast i32 to i32*
%41 = mul i32*  %40, 5
%42 = bitcast i32 to i32*
store i32 %41, i32*  %42
%43 = bitcast i32 to i32*
%44 = mul i32 9, 8
%45 = sdiv i32 %44, 7
%46 = add i32*  %43, %45
%47 = icmp eq i32 8, 0
%48 = zext i1 %47 to i32
%49 = add i32 %46, %48
%50 = bitcast i32 to i32*
store i32 %49, i32*  %50
%51 = bitcast i32 to i32*
ret i32*  %51
}
