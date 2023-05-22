
v = addrspace(4) global i32 0, align 4

g = addrspace(32) global [ 8 x i32 ][[i32 1, i32 2, , i32 7, , i32 8, , ], [ 8 x i32 ] zeroinitializer, [ 8 x i32 ] zeroinitializer, [ 8 x i32 ] zeroinitializer, [ 8 x i32 ] zeroinitializer, [ 8 x i32 ] zeroinitializer, [ 8 x i32 ] zeroinitializer, [ 8 x i32 ] zeroinitializer], align 4
define i32 @main(){
%ss = alloca i32 [ 8 x i32 ], align 4
%1 = bitcast [8x i32 ] to i64
%2 = add [8x i64 ] %1, 0
%3 = bitcast i32 to i32*
store i32 1, i32*  %3
%4 = bitcast i32 to i32*
%a = alloca i32 i32 , align 4
%5 = bitcast i32*  to i64
%6 = add i64 %5, 0
%7 = bitcast i32 to i32*
store i32*  %4, i32*  %7
%8 = bitcast i32 to i32*
%9 = mul i32*  %8, 5
%10 = bitcast i32 to i32*
store i32 %9, i32*  %10
%11 = bitcast i32 to i32*
%12 = mul i32 9, 8
%13 = sdiv i32 %12, 7
%14 = add i32*  %11, %13
%15 = icmp eq i32 8, 0
%16 = zext i1 %15 to i32
%17 = add i32 %14, %16
%18 = bitcast i32 to i32*
store i32 %17, i32*  %18
%19 = bitcast i32 to i32*
ret i32*  %19
}
