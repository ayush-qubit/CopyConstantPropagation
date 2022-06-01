; ModuleID = './outputs/test5.ll'
source_filename = "./inputs/test5.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%struct.A = type { i32 }

@a = common dso_local global i32 0, align 4

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 {
entry:
  %retval = alloca i32, align 4
  %x = alloca i32, align 4
  %y = alloca i32, align 4
  %aa = alloca %struct.A, align 4
  store i32 0, i32* %retval, align 4
  store i32 10, i32* %x, align 4
  store i32 20, i32* %y, align 4
  %tmp = load i32, i32* %x, align 4
  %b = getelementptr inbounds %struct.A, %struct.A* %aa, i32 0, i32 0
  store i32 %tmp, i32* %b, align 4
  %b1 = getelementptr inbounds %struct.A, %struct.A* %aa, i32 0, i32 0
  %tmp1 = load i32, i32* %b1, align 4
  store i32 %tmp1, i32* @a, align 4
  %tmp2 = load i32, i32* @a, align 4
  ret i32 %tmp2
}

attributes #0 = { noinline nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"Ubuntu clang version 10.0.1-++20210313014613+ef32c611aa21-1~exp1~20210313125226.6"}
