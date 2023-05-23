declare void @putint(i32)
declare void @putch(i32)
declare void @putarray(i32, i32*)
declare i32 @getint()
declare i32 @getch()
declare i32 @getarray(i32*)
declare void @starttime()
declare void @stoptime()

define void @HELLO(){
call void @putch(i32 72)
call void @putch(i32 101)
call void @putch(i32 108)
call void @putch(i32 108)
call void @putch(i32 111)
call void @putch(i32 44)
call void @putch(i32 32)
call void @putch(i32 87)
call void @putch(i32 111)
call void @putch(i32 114)
call void @putch(i32 108)
call void @putch(i32 100)
call void @putch(i32 33)
call void @putch(i32 10)
ret void
}
define i32 @main(){
%a = alloca i32 , align 4
%1 = ptrtoint i32*  %a to i64
%2 = sext i32 0 to i64
%3 = add i64 %1, %2
%4 = inttoptr i64 %3 to i32*
store i32 5, i32*  %4
br label %LOOP_ENTRY_6
LOOP_ENTRY_6:
%5 = load i32,i32* %a
%6 = icmp sgt i32 %5, 0
%7 = zext i1 %6 to i32

%8 = icmp ne i32 %7, 0
br i1 %8, label %LOOP_BODY_7, label %LOOP_END_8
LOOP_BODY_7:
%9 = load i32,i32* %a
call void @putint(i32 %9)
call void @putch(i32 10)
call void @HELLO()
%10 = load i32,i32* %a
%11 = sub i32 %10, 1
store i32 %11, i32*  %a
br label %LOOP_ENTRY_6
LOOP_END_8:
%12 = call i32 @getch()
%t = alloca i32 , align 4
%13 = ptrtoint i32*  %t to i64
%14 = sext i32 0 to i64
%15 = add i64 %13, %14
%16 = inttoptr i64 %15 to i32*
store i32 %12, i32*  %16
%17 = load i32,i32* %t
call void @putint(i32 %17)
call void @putch(i32 10)
ret i32 0
}
