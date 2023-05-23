define i32 @main(){
%1 = add i32 3, 2
%w = alloca i32 , align 4
%2 = ptrtoint i32*  %w to i64
%3 = sext i32 0 to i64
%4 = add i64 %2, %3
%5 = inttoptr i64 %4 to i32*
store i32 %1, i32*  %5
%6 = load i32,i32* %w
%7 = sub i32 %6, 5

%8 = icmp ne i32 %7, 0
br i1 %8, label %IF_LABEL_5, label %END_LABEL_6
IF_LABEL_5:
br label %END_LABEL_6
END_LABEL_6:
%9 = load i32,i32* %w
%10 = icmp ne i32 %9, 0
%11 = zext i1 %10 to i32

%12 = icmp ne i32 %11, 0
br i1 %12, label %IF_LABEL_7, label %ELSE_LABEL_8
IF_LABEL_7:
br label %END_LABEL_9
ELSE_LABEL_8:
br label %END_LABEL_9
END_LABEL_9:
br label %LOOP_ENTRY_10
LOOP_ENTRY_10:
%13 = load i32,i32* %w
%14 = icmp ne i32 %13, 0
%15 = zext i1 %14 to i32

%16 = icmp ne i32 %15, 0
br i1 %16, label %LOOP_BODY_11, label %LOOP_END_12
LOOP_BODY_11:
%17 = load i32,i32* %w
%18 = sub i32 %17, 1
store i32 %18, i32*  %w
br label %LOOP_ENTRY_10
LOOP_END_12:
ret i32 0
}
