
v = addrspace(4) global i32 0, align 4

g = addrspace(32) global [ 8 x i32 ][i32 1, i32 2, i32 7, i32 8, i32 0, i32 0, i32 0, i32 0], align 4
define i32 @main(){
%ss = alloca [ 8 x i32 ], align 4
%1 = ptrtoint [8x i32 ]* %ss to i64
%2 = sext i32 0 to i64
%3 = add i64 %1, %2
%4 = inttoptr i64 %3 to i32*
store i32 1, i32*  %4
%a = alloca i32 , align 4
%5 = ptrtoint i32*  %a to i64
%6 = sext i32 0 to i64
%7 = add i64 %5, %6
%8 = inttoptr i64 %7 to i32*
%9 = load i32,i32* @v
store i32 %9, i32*  %8
%10 = load i32,i32* %a
%11 = mul i32 %10, 5
store i32 %11, i32*  %a
%12 = mul i32 9, 8
%13 = sdiv i32 %12, 7
%14 = load i32,i32* %a
%15 = add i32 %14, %13
%16 = icmp eq i32 8, 0
%17 = zext i1 %16 to i32
%18 = add i32 %15, %17
store i32 %18, i32*  %a
%19 = load i32,i32* %a
ret i32 %19
}
