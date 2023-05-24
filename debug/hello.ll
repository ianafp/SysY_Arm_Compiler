declare void @putint(i32)
declare void @putch(i32)
declare void @putarray(i32, i32*)
declare i32 @getint()
declare i32 @getch()
declare i32 @getarray(i32*)
declare void @starttime()
declare void @stoptime()
declare void @putf(i8*, i32, ...)


@test = global [ 8 x i32 ][i32 1, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0], align 4

@another = global [ 8 x i32 ] zeroinitializer, align 4
define void @HELLO(){
call void @putch(i32 72)
ret void
}
define i32 @main(){
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
%9 = sext i32 0 to i64
%10 = add i64 %8, %9
%11 = inttoptr i64 %10 to i32*
%12 = load i32,i32* %11
call void @putint(i32 %12)
%13 = ptrtoint [8x i32 ]* @test to i64
%14 = sext i32 1 to i64
%15 = add i64 %13, %14
%16 = inttoptr i64 %15 to i32*
%17 = load i32,i32* %16
call void @putint(i32 %17)
%18 = ptrtoint [8x i32 ]* @test to i64
%19 = sext i32 2 to i64
%20 = add i64 %18, %19
%21 = inttoptr i64 %20 to i32*
%22 = load i32,i32* %21
call void @putint(i32 %22)
%23 = ptrtoint [8x i32 ]* @test to i64
%24 = sext i32 3 to i64
%25 = add i64 %23, %24
%26 = inttoptr i64 %25 to i32*
%27 = load i32,i32* %26
call void @putint(i32 %27)
call void @putch(i32 10)
%28 = ptrtoint [4x i32 ]* %local to i64
%29 = sext i32 0 to i64
%30 = add i64 %28, %29
%31 = inttoptr i64 %30 to i32*
%32 = load i32,i32* %31
call void @putint(i32 %32)
%33 = ptrtoint [4x i32 ]* %local to i64
%34 = sext i32 1 to i64
%35 = add i64 %33, %34
%36 = inttoptr i64 %35 to i32*
%37 = load i32,i32* %36
call void @putint(i32 %37)
%38 = ptrtoint [4x i32 ]* %local to i64
%39 = sext i32 2 to i64
%40 = add i64 %38, %39
%41 = inttoptr i64 %40 to i32*
%42 = load i32,i32* %41
call void @putint(i32 %42)
%43 = ptrtoint [4x i32 ]* %local to i64
%44 = sext i32 3 to i64
%45 = add i64 %43, %44
%46 = inttoptr i64 %45 to i32*
%47 = load i32,i32* %46
call void @putint(i32 %47)
call void @putch(i32 10)
ret i32 0
}
