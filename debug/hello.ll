@.str = private unnamed_addr constant [ 5 x i8 ]c"sadas\00", align 1
declare void @putint(i32)
declare void @putch(i32)
declare void @putarray(i32, i32*)
declare i32 @getint()
declare i32 @getch()
declare i32 @getarray(i32*)
declare void @starttime()
declare void @stoptime()
declare void @putf(i8*, i32, ...)

define i32 @main(){
%1 = bitcast [ 5 x i8 ]* @.str to i8*
call void @putf(i8*  %1)
ret i32 0
}
