; ModuleID = './outputs/test5.ll'
source_filename = "./inputs/test5.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%struct.A = type { i32 }

@a = dso_local global i32 0, align 4, !dbg !0

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 !dbg !12 {
entry:
  %retval = alloca i32, align 4
  %x = alloca i32, align 4
  %y = alloca i32, align 4
  %aa = alloca %struct.A, align 4
  store i32 0, i32* %retval, align 4
  call void @llvm.dbg.declare(metadata i32* %x, metadata !15, metadata !DIExpression()), !dbg !16
  call void @llvm.dbg.declare(metadata i32* %y, metadata !17, metadata !DIExpression()), !dbg !18
  call void @llvm.dbg.declare(metadata %struct.A* %aa, metadata !19, metadata !DIExpression()), !dbg !23
  store i32 10, i32* %x, align 4, !dbg !24
  store i32 20, i32* %y, align 4, !dbg !25
  %i = load i32, i32* %x, align 4, !dbg !26
  %b = getelementptr inbounds %struct.A, %struct.A* %aa, i32 0, i32 0, !dbg !27
  store i32 %i, i32* %b, align 4, !dbg !28
  %b1 = getelementptr inbounds %struct.A, %struct.A* %aa, i32 0, i32 0, !dbg !29
  %i1 = load i32, i32* %b1, align 4, !dbg !29
  store i32 %i1, i32* @a, align 4, !dbg !30
  %i2 = load i32, i32* @a, align 4, !dbg !31
  ret i32 %i2, !dbg !32
}

; Function Attrs: nofree nosync nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

attributes #0 = { noinline nounwind uwtable "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nofree nosync nounwind readnone speculatable willreturn }

!llvm.dbg.cu = !{!2}
!llvm.module.flags = !{!8, !9, !10}
!llvm.ident = !{!11}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(name: "a", scope: !2, file: !6, line: 3, type: !7, isLocal: false, isDefinition: true)
!2 = distinct !DICompileUnit(language: DW_LANG_C99, file: !3, producer: "Ubuntu clang version 12.0.1-++20210918042559+fed41342a82f-1~exp1~20210918143325.135", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !4, globals: !5, splitDebugInlining: false, nameTableKind: None)
!3 = !DIFile(filename: "inputs/test5.c", directory: "/mnt/d/College/CopyConstantPropagation/testcases")
!4 = !{}
!5 = !{!0}
!6 = !DIFile(filename: "./inputs/test5.c", directory: "/mnt/d/College/CopyConstantPropagation/testcases")
!7 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!8 = !{i32 7, !"Dwarf Version", i32 4}
!9 = !{i32 2, !"Debug Info Version", i32 3}
!10 = !{i32 1, !"wchar_size", i32 4}
!11 = !{!"Ubuntu clang version 12.0.1-++20210918042559+fed41342a82f-1~exp1~20210918143325.135"}
!12 = distinct !DISubprogram(name: "main", scope: !6, file: !6, line: 8, type: !13, scopeLine: 8, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!13 = !DISubroutineType(types: !14)
!14 = !{!7}
!15 = !DILocalVariable(name: "x", scope: !12, file: !6, line: 9, type: !7)
!16 = !DILocation(line: 9, column: 9, scope: !12)
!17 = !DILocalVariable(name: "y", scope: !12, file: !6, line: 9, type: !7)
!18 = !DILocation(line: 9, column: 11, scope: !12)
!19 = !DILocalVariable(name: "aa", scope: !12, file: !6, line: 10, type: !20)
!20 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "A", file: !6, line: 4, size: 32, elements: !21)
!21 = !{!22}
!22 = !DIDerivedType(tag: DW_TAG_member, name: "b", scope: !20, file: !6, line: 5, baseType: !7, size: 32)
!23 = !DILocation(line: 10, column: 14, scope: !12)
!24 = !DILocation(line: 11, column: 7, scope: !12)
!25 = !DILocation(line: 12, column: 7, scope: !12)
!26 = !DILocation(line: 13, column: 12, scope: !12)
!27 = !DILocation(line: 13, column: 8, scope: !12)
!28 = !DILocation(line: 13, column: 10, scope: !12)
!29 = !DILocation(line: 14, column: 12, scope: !12)
!30 = !DILocation(line: 14, column: 7, scope: !12)
!31 = !DILocation(line: 15, column: 12, scope: !12)
!32 = !DILocation(line: 15, column: 5, scope: !12)
