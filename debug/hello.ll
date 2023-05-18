define i32 @main(){
%a = alloca i32 , i32 4, align 4
%0 = add i32 %a, 0
store i32 3, ptr %0
ret  i32 %a
}
