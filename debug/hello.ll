define i32 @half(i32 %0, i32 %1){
%2 = sdiv i32 22, 2
ret  i32 %2
}
define i32 @main(){
add i32 1, 2
%0 = icmp ne i32 0, 0

br i1 %0, lable %IF_LABEL_0, lable %END_LABEL_1
IF_LABEL_0:
2
END_LABEL_1:
%1 = icmp ne i32 1, 0

br i1 %1, lable %IF_LABEL_2, lable %ELSE_LABEL_3
IF_LABEL_2:
3
ELSE_LABEL_3:
1
END_LABEL_4:
%2 = icmp ne i32 0, 0
%3 = icmp ne i32 0, 1
%4 = or i32 %2, %3

br i1 %4, lable %IF_LABEL_7, lable %END_LABEL_8
IF_LABEL_7:
IF_LABEL_0:
2
END_LABEL_1:
END_LABEL_8:
ret  i32 0
}
