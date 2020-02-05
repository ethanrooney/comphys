(* ::Package:: *)

SetDirectory["~/spring20/comphys/week2/"];
(* Problem 1 Using bin widths of 0.25, 0.1, and 0.02,
 plot your numeric integral as a function of x alongside
 the analytic answer; 
 you should have four curves on the same set of axes.  
 Since the numeric
 integral is defined only at multiples of the bin width,
 your plot for the numeric integrals will
 consist of the values at those intervals connected by lines.
 Make two separate plots for na\:0308ive
 and midpoint integrators.  
 Discuss how the bin width and the choice of integrator affect the
error
*)

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



