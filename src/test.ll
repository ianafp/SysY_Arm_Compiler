  ; ModuleID = 'test.cpp'
source_filename = "test.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline norecurse nounwind optnone uwtable
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca [8 x [8 x i32]], align 16
  store i32 0, i32* %1, align 4
  %3 = bitcast [8 x [8 x i32]]* %2 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 16 %3, i8 0, i64 256, i1 false)
  %4 = bitcast i8* %3 to [8 x [8 x i32]]*
  %5 = getelementptr inbounds [8 x [8 x i32]], [8 x [8 x i32]]* %4, i32 0, i32 0
  %6 = getelementptr inbounds [8 x i32], [8 x i32]* %5, i32 0, i32 0
  store i32 1, i32* %6, align 16
  %7 = getelementptr inbounds [8 x i32], [8 x i32]* %5, i32 0, i32 1
  store i32 2, i32* %7, align 4
  %8 = getelementptr inbounds [8 x [8 x i32]], [8 x [8 x i32]]* %4, i32 0, i32 1
  %9 = getelementptr inbounds [8 x i32], [8 x i32]* %8, i32 0, i32 0
  store i32 3, i32* %9, align 16
  %10 = getelementptr inbounds [8 x i32], [8 x i32]* %8, i32 0, i32 1
  store i32 4, i32* %10, align 4
  %11 = getelementptr inbounds [8 x i32], [8 x i32]* %8, i32 0, i32 2
  store i32 5, i32* %11, align 8
  ret i32 0
}

; Function Attrs: argmemonly nofree nounwind willreturn writeonly
declare void @llvm.memset.p0i8.i64(i8* nocapture writeonly, i8, i64, i1 immarg) #1

attributes #0 = { mustprogress noinline norecurse nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { argmemonly nofree nounwind willreturn writeonly }

!llvm.module.flags = !{!0, !1, !2}
!llvm.ident = !{!3}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"uwtable", i32 1}
!2 = !{i32 7, !"frame-pointer", i32 2}
!3 = !{!"Ubuntu clang version 13.0.1-++20220120110924+75e33f71c2da-1~exp1~20220120231001.58"}
