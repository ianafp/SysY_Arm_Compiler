define i32 @half(i32 x, i32 y){
%1 = sdiv i32 22, 2
ret  i32 %1
}
define i32 @main(){
%1 = icmp ne i32 2, 0

br i1 %1, lable %IF_LABEL_1, lable %ELSE_LABEL_2
IF_LABEL_1:
add i32 3, 2
br label %END_LABEL_3
ELSE_LABEL_2:
add i32 5, 2
br label %END_LABEL_3
END_LABEL_3:
%2 = icmp ne i32 3, 0

br i1 %2, lable %IF_LABEL_4, lable %END_LABEL_5
IF_LABEL_4:
2
br label %END_LABEL_5
END_LABEL_5:
%3 = icmp ne i32 2, 0

br i1 %3, lable %IF_LABEL_6, lable %ELSE_LABEL_7
IF_LABEL_6:
1
br label %END_LABEL_8
ELSE_LABEL_7:
0
br label %END_LABEL_8
END_LABEL_8:
%4 = icmp ne i32 0, 5
%5 = icmp ne i32 0, 2
%6 = and i32 %4, %5
%7 = icmp ne i32 0, 10
%8 = icmp ne i32 0, %6
%9 = or i32 %7, %8

br i1 %9, lable %IF_LABEL_14, lable %END_LABEL_15
IF_LABEL_14:
%10 = add i32 3, 2
%11 = mul i32 5, 2
sub i32 %10, %11
br label %END_LABEL_15
END_LABEL_15:
LOOP_ENTRY_21:
%12 = icmp ne i32 0, 3
%13 = icmp ne i32 0, 1
%14 = and i32 %12, %13
%15 = icmp ne i32 0, 2
%16 = icmp ne i32 0, %14
%17 = or i32 %15, %16

br i1 %17, lable %LOOP_BODY_22, lable %LOOP_END_23
LOOP_BODY_22:
add i32 3, 2
%18 = mul i32 5, 2
sub i32 1, %18
br label %LOOP_ENTRY_21
LOOP_END_23:
LOOP_ENTRY_29:
%19 = icmp ne i32 0, 1
%20 = icmp ne i32 0, 2
%21 = and i32 %19, %20
%22 = icmp ne i32 0, %21
%23 = icmp ne i32 0, 3
%24 = and i32 %22, %23

br i1 %24, lable %LOOP_BODY_30, lable %LOOP_END_31
LOOP_BODY_30:
%25 = mul i32 3, 5
add i32 1, %25
br label %LOOP_ENTRY_29
LOOP_END_31:
ret  i32 0
}
