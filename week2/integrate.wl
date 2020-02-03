(* ::Package:: *)

SetDirectory["~/spring20/comphys/week2/"];
exact = N[Integrate[Exp[x],{x, 0, 1}], 15];
Print[exact];
getres[n_,i_] := ReadList["!./integrate " <> ToString[n] <> " | awk '{print $"<> ToString[i]<>"}'", Number][[1]];
Print[N[getres[4,1],15]];
Print[N[getres[4,2],15]];
resleft = Table[{1/n, Abs[(getres[n,1] - exact)/exact]}, {n, {10, 100, 1000, 10000, 100000, 1000000, 10000000}}];
Print[resleft];
resmiddle = Table[{1/n, Abs[(getres[n,2] - exact)/exact]}, {n, {10, 100, 1000, 10000, 100000, 1000000, 10000000}}];
Print[resmiddle];
testcombined = Show[ListLogLogPlot[resleft],ListLogLogPlot[resmiddle], PlotRange -> All, Frame -> True];
Export["testleft.pdf", ListLogLogPlot[resleft,Frame -> True,PlotRange -> All,]];
Export["testmiddle.pdf", ListLogLogPlot[resmiddle,Frame -> True,PlotRange -> All]];
Export["testcombined.pdf", testcombined];



