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
br i1 %9, label %IF_LABEL_3, label %ELSE_LABEL_4
IF_LABEL_3:
br label %END_LABEL_5
ELSE_LABEL_4:
br label %END_LABEL_5
END_LABEL_5:
ret i32 0
}
