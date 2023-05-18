define i32 @half(i32 x, i32 y){
%0 = sdiv i32 22, 2
ret  i32 %0
}
define i32 @main(){
%0 = icmp ne i32 2, 0

br i1 %0, lable %IF_LABEL_0, lable %ELSE_LABEL_1
IF_LABEL_0:
add i32 3, 2
ELSE_LABEL_1:
add i32 5, 2
END_LABEL_2:
%1 = icmp ne i32 3, 0

br i1 %1, lable %IF_LABEL_3, lable %END_LABEL_4
IF_LABEL_3:
2
END_LABEL_4:
%2 = icmp ne i32 2, 0

br i1 %2, lable %IF_LABEL_5, lable %ELSE_LABEL_6
IF_LABEL_5:
1
ELSE_LABEL_6:
0
END_LABEL_7:
%3 = icmp ne i32 0, 5
%4 = icmp ne i32 0, 2
%5 = and i32 %3, %4
%6 = icmp ne i32 0, 10
%7 = icmp ne i32 0, %5
%8 = or i32 %6, %7

br i1 %8, lable %IF_LABEL_13, lable %END_LABEL_14
IF_LABEL_13:
%9 = add i32 3, 2
%10 = mul i32 5, 2
sub i32 %9, %10
END_LABEL_14:
LOOP_ENTRY_20:
%11 = icmp ne i32 0, 3
%12 = icmp ne i32 0, 1
%13 = and i32 %11, %12
%14 = icmp ne i32 0, 2
%15 = icmp ne i32 0, %13
%16 = or i32 %14, %15

br i1 %16, lable %LOOP_BODY_21, lable %LOOP_END_22
LOOP_BODY_21:
add i32 3, 2
%17 = mul i32 5, 2
sub i32 1, %17
br label %LOOP_ENTRY_20
LOOP_END_22:
LOOP_ENTRY_28:
%18 = icmp ne i32 0, 1
%19 = icmp ne i32 0, 2
%20 = and i32 %18, %19
%21 = icmp ne i32 0, %20
%22 = icmp ne i32 0, 3
%23 = and i32 %21, %22

br i1 %23, lable %LOOP_BODY_29, lable %LOOP_END_30
LOOP_BODY_29:
%24 = mul i32 3, 5
add i32 1, %24
br label %LOOP_ENTRY_28
LOOP_END_30:
ret  i32 0
}
