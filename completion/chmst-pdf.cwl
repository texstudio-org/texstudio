# chmst-pdf package
# Matthew Bertucci 2022/05/15 for v5.01

#include:chemist
#include:xymtx-pdf

#keyvals:\usepackage/chmst-pdf#c
chemtimes
#endkeyvals

\chmstpdfsw
\electronHldshiftarrow(xend,yend)(xstart,ystart)
\electronHldshiftarrow[direction](xend,yend)(xstart,ystart)
\electronHlushiftarrow(xstart,ystart)(xend,yend)
\electronHlushiftarrow[direction](xstart,ystart)(xend,yend)
\electronHrdshiftarrow(xend,yend)(xstart,ystart)
\electronHrdshiftarrow[direction](xend,yend)(xstart,ystart)
\electronHrushiftarrow(xstart,ystart)(xend,yend)
\electronHrushiftarrow[direction](xstart,ystart)(xend,yend)
\electronlshiftarrow(xend,yend)(xstart,ystart)
\electronlshiftarrow[direction](xend,yend)(xstart,ystart)
\electronrshiftarrow(xstart,ystart)(xend,yend)
\electronrshiftarrow[direction](xstart,ystart)(xend,yend)

\electronshiftArrowl(xstart,ystart)(xctrl1,yctrl1)(xctrl2,yctrl2)(xend,yend)
\electronshiftArrowr(xstart,ystart)(xctrl1,yctrl1)(xctrl2,yctrl2)(xend,yend)
\electronshiftHld(xstart,ystart)(xctrl1,yctrl1)(xctrl2,yctrl2)(xend,yend)
\electronshiftHlu(xstart,ystart)(xctrl1,yctrl1)(xctrl2,yctrl2)(xend,yend)
\electronshiftHrd(xstart,ystart)(xctrl1,yctrl1)(xctrl2,yctrl2)(xend,yend)
\electronshiftHru(xstart,ystart)(xctrl1,yctrl1)(xctrl2,yctrl2)(xend,yend)
\futuresubst{content}

# not documented
\electronAHshift#S
\electronshiftAH{arg1}#S
\leftharpoondownElement{arg1}#S
\leftharpoonupElement{arg1}#S
\newreactDEqarrow#S
\newreactEqarrow#S
\newreactLEqarrow#S
\newreactREqarrow#S
\newreactUEqarrow#S
\newreactVEqarrow#S
\newreactdarrow#S
\newreactdeqarrow#S
\newreactdlrarrow#S
\newreactduarrow#S
\newreacteqarrow#S
\newreactlarrow#S
\newreactleqarrow#S
\newreactlrarrow#S
\newreactnearrow#S
\newreactnwarrow#S
\newreactrarrow#S
\newreactreqarrow#S
\newreactsearrow#S
\newreactswarrow#S
\newreactuarrow#S
\newreactueqarrow#S
\newreactulrarrow#S
\newreactveqarrow#S
\newschemelarrow{arg1}{arg2}{arg3}{arg4}#S
\newschemelrarrow{arg1}{arg2}{arg3}{arg4}#S
\newschemerarrow{arg1}{arg2}{arg3}{arg4}#S
\rightharpoondownElement{arg1}#S
\rightharpoonupElement{arg1}#S