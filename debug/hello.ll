define i32 @main(){
%1 = call  @getint()
%n = alloca i32 , align 4
%2 = ptrtoint i32*  %n to i64
%3 = sext i32 0 to i64
%4 = add i64 %2, %3
%5 = inttoptr i64 %4 to i32*
store i32 %1, i32*  %5
ret i32 0
}
