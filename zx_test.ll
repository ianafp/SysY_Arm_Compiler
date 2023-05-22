
v = addrspace(4) global i32 0, align 4

g = addrspace(32) global [ 8 x i32 ][[i32 1, i32 2, , i32 7, , i32 8, , ], [ 8 x i32 ] zeroinitializer, [ 8 x i32 ] zeroinitializer, [ 8 x i32 ] zeroinitializer, [ 8 x i32 ] zeroinitializer, [ 8 x i32 ] zeroinitializer, [ 8 x i32 ] zeroinitializer, [ 8 x i32 ] zeroinitializer], align 4
define i32 @main(){
%1 = bitcast i32 to i32*
%2 = mul i32*  %1, 5
%3 = bitcast i32 to i32*
store i32 %2, i32*  %3
%4 = bitcast i32 to i32*
%5 = mul i32 9, 8
%6 = sdiv i32 %5, 7
%7 = add i32*  %4, %6
%8 = icmp eq i32 8, 0
%9 = zext i1 %8 to i32
%10 = add i32 %7, %9
%11 = bitcast i32 to i32*
store i32 %10, i32*  %11
%12 = bitcast i32 to i32*
ret i32*  %12
}
