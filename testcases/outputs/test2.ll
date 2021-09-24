; ModuleID = './outputs/test2.ll'
source_filename = "./inputs/test2.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@b = dso_local global i32 0, align 4, !dbg !0
@a = dso_local global i32 0, align 4, !dbg !6

; Function Attrs: noinline nounwind uwtable
define dso_local void @foo() #0 !dbg !14 {
entry:
  %i = load i32, i32* @b, align 4, !dbg !17
  store i32 %i, i32* @a, align 4, !dbg !18
  ret void, !dbg !19
}

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 !dbg !20 {
entry:
  store i32 10, i32* @a, align 4, !dbg !23
  call void @foo(), !dbg !24
  store i32 20, i32* @b, align 4, !dbg !25
  call void @foo(), !dbg !26
  ret i32 0, !dbg !27
}

attributes #0 = { noinline nounwind uwtable "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!2}
!llvm.module.flags = !{!10, !11, !12}
!llvm.ident = !{!13}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(name: "b", scope: !2, file: !8, line: 4, type: !9, isLocal: false, isDefinition: true)
!2 = distinct !DICompileUnit(language: DW_LANG_C99, file: !3, producer: "Ubuntu clang version 12.0.1-++20210918042559+fed41342a82f-1~exp1~20210918143325.135", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !4, globals: !5, splitDebugInlining: false, nameTableKind: None)
!3 = !DIFile(filename: "inputs/test2.c", directory: "/mnt/d/College/CopyConstant/testcases")
!4 = !{}
!5 = !{!6, !0}
!6 = !DIGlobalVariableExpression(var: !7, expr: !DIExpression())
!7 = distinct !DIGlobalVariable(name: "a", scope: !2, file: !8, line: 4, type: !9, isLocal: false, isDefinition: true)
!8 = !DIFile(filename: "./inputs/test2.c", directory: "/mnt/d/College/CopyConstant/testcases")
!9 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!10 = !{i32 7, !"Dwarf Version", i32 4}
!11 = !{i32 2, !"Debug Info Version", i32 3}
!12 = !{i32 1, !"wchar_size", i32 4}
!13 = !{!"Ubuntu clang version 12.0.1-++20210918042559+fed41342a82f-1~exp1~20210918143325.135"}
!14 = distinct !DISubprogram(name: "foo", scope: !8, file: !8, line: 6, type: !15, scopeLine: 6, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!15 = !DISubroutineType(types: !16)
!16 = !{null}
!17 = !DILocation(line: 7, column: 4, scope: !14)
!18 = !DILocation(line: 7, column: 3, scope: !14)
!19 = !DILocation(line: 8, column: 1, scope: !14)
!20 = distinct !DISubprogram(name: "main", scope: !8, file: !8, line: 10, type: !21, scopeLine: 10, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!21 = !DISubroutineType(types: !22)
!22 = !{!9}
!23 = !DILocation(line: 11, column: 3, scope: !20)
!24 = !DILocation(line: 12, column: 2, scope: !20)
!25 = !DILocation(line: 13, column: 3, scope: !20)
!26 = !DILocation(line: 14, column: 2, scope: !20)
!27 = !DILocation(line: 15, column: 1, scope: !20)
