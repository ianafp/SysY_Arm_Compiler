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
ret  i32 0
}
