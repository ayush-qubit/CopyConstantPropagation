; ModuleID = './outputs/test1.ll'
source_filename = "./inputs/test1.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@a = dso_local global i32 0, align 4, !dbg !0
@b = dso_local global i32 0, align 4, !dbg !6

; Function Attrs: noinline nounwind uwtable
define dso_local void @foo() #0 !dbg !14 {
entry:
  %i = load i32, i32* @a, align 4, !dbg !17
  store i32 %i, i32* @b, align 4, !dbg !18
  call void @foo(), !dbg !19
  store i32 100, i32* @b, align 4, !dbg !20
  ret void, !dbg !21
}

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 !dbg !22 {
entry:
  %retval = alloca i32, align 4
  %x = alloca i32, align 4
  %y = alloca i32, align 4
  store i32 0, i32* %retval, align 4
  call void @llvm.dbg.declare(metadata i32* %x, metadata !25, metadata !DIExpression()), !dbg !26
  call void @llvm.dbg.declare(metadata i32* %y, metadata !27, metadata !DIExpression()), !dbg !28
  store i32 10, i32* %x, align 4, !dbg !29
  %i = load i32, i32* %x, align 4, !dbg !30
  store i32 %i, i32* %y, align 4, !dbg !31
  store i32 30, i32* %x, align 4, !dbg !32
  %i1 = load i32, i32* %y, align 4, !dbg !33
  store i32 %i1, i32* @a, align 4, !dbg !34
  %i2 = load i32, i32* @a, align 4, !dbg !35
  %cmp = icmp sgt i32 %i2, 40, !dbg !37
  br i1 %cmp, label %if.then, label %if.end, !dbg !38

if.then:                                          ; preds = %entry
  %i3 = load i32, i32* %x, align 4, !dbg !39
  store i32 %i3, i32* @a, align 4, !dbg !41
  br label %if.end, !dbg !42

if.end:                                           ; preds = %if.then, %entry
  %i4 = load i32, i32* @a, align 4, !dbg !43
  store i32 %i4, i32* %y, align 4, !dbg !44
  call void @foo(), !dbg !45
  store i32 50, i32* @a, align 4, !dbg !46
  call void @foo(), !dbg !47
  ret i32 0, !dbg !48
}

; Function Attrs: nofree nosync nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

attributes #0 = { noinline nounwind uwtable "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nofree nosync nounwind readnone speculatable willreturn }

!llvm.dbg.cu = !{!2}
!llvm.module.flags = !{!10, !11, !12}
!llvm.ident = !{!13}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(name: "a", scope: !2, file: !8, line: 3, type: !9, isLocal: false, isDefinition: true)
!2 = distinct !DICompileUnit(language: DW_LANG_C99, file: !3, producer: "Ubuntu clang version 12.0.1-++20210918042559+fed41342a82f-1~exp1~20210918143325.135", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !4, globals: !5, splitDebugInlining: false, nameTableKind: None)
!3 = !DIFile(filename: "inputs/test1.c", directory: "/mnt/d/College/CopyConstantPropagation/testcases")
!4 = !{}
!5 = !{!0, !6}
!6 = !DIGlobalVariableExpression(var: !7, expr: !DIExpression())
!7 = distinct !DIGlobalVariable(name: "b", scope: !2, file: !8, line: 3, type: !9, isLocal: false, isDefinition: true)
!8 = !DIFile(filename: "./inputs/test1.c", directory: "/mnt/d/College/CopyConstantPropagation/testcases")
!9 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!10 = !{i32 7, !"Dwarf Version", i32 4}
!11 = !{i32 2, !"Debug Info Version", i32 3}
!12 = !{i32 1, !"wchar_size", i32 4}
!13 = !{!"Ubuntu clang version 12.0.1-++20210918042559+fed41342a82f-1~exp1~20210918143325.135"}
!14 = distinct !DISubprogram(name: "foo", scope: !8, file: !8, line: 5, type: !15, scopeLine: 5, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!15 = !DISubroutineType(types: !16)
!16 = !{null}
!17 = !DILocation(line: 7, column: 9, scope: !14)
!18 = !DILocation(line: 7, column: 7, scope: !14)
!19 = !DILocation(line: 9, column: 5, scope: !14)
!20 = !DILocation(line: 11, column: 7, scope: !14)
!21 = !DILocation(line: 13, column: 1, scope: !14)
!22 = distinct !DISubprogram(name: "main", scope: !8, file: !8, line: 15, type: !23, scopeLine: 15, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!23 = !DISubroutineType(types: !24)
!24 = !{!9}
!25 = !DILocalVariable(name: "x", scope: !22, file: !8, line: 16, type: !9)
!26 = !DILocation(line: 16, column: 9, scope: !22)
!27 = !DILocalVariable(name: "y", scope: !22, file: !8, line: 16, type: !9)
!28 = !DILocation(line: 16, column: 11, scope: !22)
!29 = !DILocation(line: 17, column: 7, scope: !22)
!30 = !DILocation(line: 18, column: 9, scope: !22)
!31 = !DILocation(line: 18, column: 7, scope: !22)
!32 = !DILocation(line: 19, column: 7, scope: !22)
!33 = !DILocation(line: 20, column: 9, scope: !22)
!34 = !DILocation(line: 20, column: 7, scope: !22)
!35 = !DILocation(line: 22, column: 8, scope: !36)
!36 = distinct !DILexicalBlock(scope: !22, file: !8, line: 22, column: 8)
!37 = !DILocation(line: 22, column: 9, scope: !36)
!38 = !DILocation(line: 22, column: 8, scope: !22)
!39 = !DILocation(line: 23, column: 13, scope: !40)
!40 = distinct !DILexicalBlock(scope: !36, file: !8, line: 22, column: 13)
!41 = !DILocation(line: 23, column: 11, scope: !40)
!42 = !DILocation(line: 25, column: 5, scope: !40)
!43 = !DILocation(line: 27, column: 9, scope: !22)
!44 = !DILocation(line: 27, column: 7, scope: !22)
!45 = !DILocation(line: 29, column: 5, scope: !22)
!46 = !DILocation(line: 31, column: 7, scope: !22)
!47 = !DILocation(line: 33, column: 5, scope: !22)
!48 = !DILocation(line: 35, column: 5, scope: !22)
