declare void @putint(i32)
declare void @putch(i32)
declare void @putarray(i32, i32*)
declare i32 @getint()
declare i32 @getch()
declare i32 @getarray(i32*)
declare void @starttime()
declare void @stoptime()
declare void @putf(i8*, i32, ...)


@test = addrspace(32) global [ 8 x i32 ][i32 1, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0], align 4
@test2 = addrspace(32) global [ 8 x i32 ][i32 1, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0], align 4
@another = addrspace(32) global [ 8 x i32 ] zeroinitializer, align 4
define void @HELLO(){
call void @putch(i32 72)
ret void
}
define i32 @main(){
<<<<<<< HEAD
%local = alloca [ 4 x i32 ], align 4
%1 = ptrtoint [4x i32 ]* %local to i64
%2 = add i32 %1, 0
%3 = inttoptr i32 %2 to i32*
store i32 1, i32*  %3
%4 = add i32 %1, 4
%5 = inttoptr i32 %4 to i32*
store i32 2, i32*  %5
%6 = add i32 %1, 8
%7 = inttoptr i32 %6 to i32*
store i32 6, i32*  %7
%8 = ptrtoint [8x i32 ]* @test to i64
%9 = sext i32 1 to i64
%10 = add i64 %8, %9
%11 = inttoptr i64 %10 to i32*
%12 = load i32,i32* %11
call void @putch(i32 %12)
=======
%a = alloca i32 , align 4
%1 = ptrtoint i32*  %a to i64
%2 = sext i32 0 to i64
%3 = add i64 %1, %2
%4 = inttoptr i64 %3 to i32*
store i32 1000000, i32*  %4
%t = alloca [ 4 x i32 ], align 4
%5 = ptrtoint [4x i32 ]* %t to i64
%6 = sext i32 0 to i64
%7 = add i64 %5, %6
%8 = inttoptr i64 %7 to i32*
store i32 1, i32*  %8
;%t = alloca [ 4 x i32 ], align 4
%9 = ptrtoint [4x i32 ]* %t to i64
%10 = sext i32 4 to i64
%11 = add i64 %9, %10
%12 = inttoptr i64 %11 to i32*
store i32 2, i32*  %12
br label %LOOP_ENTRY_6
LOOP_ENTRY_6:
%13 = load i32,i32* %a
%14 = icmp sgt i32 %13, 0
%15 = zext i1 %14 to i32

%16 = icmp ne i32 %15, 0
br i1 %16, label %LOOP_BODY_7, label %LOOP_END_8
LOOP_BODY_7:
%17 = load i32,i32* %a
call void @putint(i32 %17)
call void @putch(i32 10)
call void @HELLO()
%18 = load i32,i32* %a
%19 = sub i32 %18, 1
store i32 %19, i32*  %a
br label %LOOP_ENTRY_6
LOOP_END_8:
%20 = call i32 @getch()
%k = alloca i32 , align 4
%21 = ptrtoint i32*  %k to i64
%22 = sext i32 0 to i64
%23 = add i64 %21, %22
%24 = inttoptr i64 %23 to i32*
store i32 %20, i32*  %24
%25 = load i32,i32* %k
call void @putint(i32 %25)
call void @putch(i32 10)
>>>>>>> 50ad145483dc84b7af898f49b836b7c77b313d0d
ret i32 0
}
