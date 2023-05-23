define i32 @main(){
%a = alloca i32 , align 4
%1 = ptrtoint i32*  %a to i64
%2 = sext i32 0 to i64
%3 = add i64 %1, %2
%4 = inttoptr i64 %3 to i32*
store i32 1000000, i32*  %4
br label %LOOP_ENTRY_6
LOOP_ENTRY_6:
%5 = load i32,i32* %a
%6 = icmp sgt i32 %5, 0
%7 = zext i1 %6 to i32

%8 = icmp ne i32 %7, 0
br i1 %8, label %LOOP_BODY_7, label %LOOP_END_8
LOOP_BODY_7:
%9 = load i32,i32* %a
%10 = call  @putint(i32 %9)
%11 = call  @putch(i32 10)
%12 = load i32,i32* %a
%13 = sub i32 %12, 1
store i32 %13, i32*  %a
br label %LOOP_ENTRY_6
LOOP_END_8:
ret i32 0
}
