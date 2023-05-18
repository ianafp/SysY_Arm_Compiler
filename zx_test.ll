array = addrspace(4) global i32 0, align 4
define i32 @half(i32 x, i32 y){
%0 = sdiv i32 22, 2
ret  i32 %0
}
define i32 @main(){
add i32 1, 2
%0 = icmp ne i32 0, 0
%1 = icmp ne i32 0, 1
%2 = or i32 %0, %1

br i1 %2, lable %IF_LABEL_2, lable %ELSE_LABEL_3
IF_LABEL_2:
2
ELSE_LABEL_3:
ret void
END_LABEL_4:
ret  i32 0
}
