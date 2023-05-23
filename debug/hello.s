; ModuleID = '../debug/hello.bc'
source_filename = "../debug/hello.ll"

define i32 @half(i32 %x, i32 %y) {
  %1 = sdiv i32 22, 2
  ret i32 %1
}

define i32 @main() {
  %1 = icmp ne i32 2, 0
  br i1 %1, label %IF_LABEL_0, label %ELSE_LABEL_1

IF_LABEL_0:                                       ; preds = %0
  %2 = add i32 3, 2
  br label %END_LABEL_2

ELSE_LABEL_1:                                     ; preds = %0
  %3 = add i32 5, 2
  br label %END_LABEL_2

END_LABEL_2:                                      ; preds = %ELSE_LABEL_1, %IF_LABEL_0
  %4 = icmp ne i32 3, 0
  br i1 %4, label %IF_LABEL_3, label %END_LABEL_4

IF_LABEL_3:                                       ; preds = %END_LABEL_2
  %5 = add i32 0, 2
  br label %END_LABEL_4

END_LABEL_4:                                      ; preds = %IF_LABEL_3, %END_LABEL_2
  %6 = icmp ne i32 2, 0
  br i1 %6, label %IF_LABEL_5, label %ELSE_LABEL_6

IF_LABEL_5:                                       ; preds = %END_LABEL_4
  %7 = add i32 0, 1
  br label %END_LABEL_7

ELSE_LABEL_6:                                     ; preds = %END_LABEL_4
  %8 = add i32 0, 2
  br label %END_LABEL_7

END_LABEL_7:                                      ; preds = %ELSE_LABEL_6, %IF_LABEL_5
  %9 = icmp ne i32 0, 5
  %10 = icmp ne i32 0, 2
  %11 = and i1 %9, %10
  %12 = icmp ne i1 false, false
  %13 = icmp ne i1 false, %11
  %14 = or i1 %12, %13
  br i1 %14, label %IF_LABEL_13, label %END_LABEL_14

IF_LABEL_13:                                      ; preds = %END_LABEL_7
  %15 = add i32 3, 2
  %16 = mul i32 5, 2
  %17 = sub i32 %15, %16
  br label %END_LABEL_14

END_LABEL_14:                                     ; preds = %IF_LABEL_13, %END_LABEL_7
  br label %LOOP_ENTRY_20

LOOP_ENTRY_20:                                    ; preds = %LOOP_BODY_21, %END_LABEL_14
  %18 = icmp ne i32 0, 3
  %19 = icmp ne i32 0, 1
  %20 = and i1 %18, %19
  %21 = icmp ne i1 false, false
  %22 = icmp ne i1 false, %20
  %23 = or i1 %21, %22
  br i1 %23, label %LOOP_BODY_21, label %LOOP_END_22

LOOP_BODY_21:                                     ; preds = %LOOP_ENTRY_20
  %24 = add i32 3, 2
  br label %LOOP_ENTRY_20

LOOP_END_22:                                      ; preds = %LOOP_ENTRY_20
  br label %LOOP_ENTRY_28

LOOP_ENTRY_28:                                    ; preds = %LOOP_BODY_29, %LOOP_END_22
  %25 = icmp ne i32 0, 1
  %26 = icmp ne i32 0, 2
  %27 = and i1 %25, %26
  %28 = icmp ne i1 false, %27
  %29 = icmp ne i1 false, true
  %30 = and i1 %28, %29
  br i1 %30, label %LOOP_BODY_29, label %LOOP_END_30

LOOP_BODY_29:                                     ; preds = %LOOP_ENTRY_28
  %31 = mul i32 3, 5
  br label %LOOP_ENTRY_28

LOOP_END_30:                                      ; preds = %LOOP_ENTRY_28
  ret i32 0
}
