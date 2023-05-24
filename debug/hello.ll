@.str = private unnamed_addr constant [ 8 x i8 ]c""sadas"\00", align 1

@test = addrspace(32) global [ 8 x i32 ][i32 1, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0], align 4

@another = addrspace(32) global [ 8 x i32 ]0, align 4
define void @HELLO(){
%1 = call  @putch(i32 72)
ret void
}
define i32 @main(){
%a = alloca i32 , align 4
%1 = ptrtoint i32*  %a to i64
%2 = sext i32 0 to i64
%3 = add i64 %1, %2
%4 = inttoptr i64 %3 to i32*
<<<<<<< HEAD
store i32 1000000, i32*  %4
%5 = call  @putf(i32*  @.str)
%t = alloca [ 4 x i32 ], align 4
%6 = ptrtoint [4x i32 ]* %t to i64
%7 = sext i32 0 to i64
%8 = add i64 %6, %7
%9 = inttoptr i64 %8 to i32*
store i32 1, i32*  %9
%t = alloca [ 4 x i32 ], align 4
%10 = ptrtoint [4x i32 ]* %t to i64
%11 = sext i32 4 to i64
%12 = add i64 %10, %11
%13 = inttoptr i64 %12 to i32*
store i32 2, i32*  %13
br label %LOOP_ENTRY_6
LOOP_ENTRY_6:
%14 = load i32,i32* %a
%15 = icmp sgt i32 %14, 0
%16 = zext i1 %15 to i32

%17 = icmp ne i32 %16, 0
br i1 %17, label %LOOP_BODY_7, label %LOOP_END_8
LOOP_BODY_7:
%18 = load i32,i32* %a
%19 = call  @putint(i32 %18)
%20 = call  @putch(i32 10)
%21 = load i32,i32* %a
%22 = sub i32 %21, 1
store i32 %22, i32*  %a
=======
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
>>>>>>> a304bf2d5a2dc0fbab5d328205a8e7723c50df6b
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
