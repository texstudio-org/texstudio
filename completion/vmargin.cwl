# vmargin package
# Matthew Bertucci 4/21/2022 for v2.5

#keyvals:\usepackage/vmargin#c
shiftmargins
portrait
landscape
nohf
#endkeyvals

\setpapersize{size%keyvals}
\setpapersize[landscape|portrait]{size%keyvals}
\setpapersize{custom}{%<width%>}{%<height%>}

#keyvals:\setpapersize,\usepackage/vmargin#c
A0
A1
A2
A3
A4
A5
A6
A7
A8
A9
B0
B1
B2
B3
B4
B5
B6
B7
B8
B9
C0
C1
C2
C3
C4
C5
C6
C7
C8
C9
USletter
USlegal
USexecutive
#endkeyvals

#keyvals:\setpapersize
custom
#endkeyvals

\PaperWidth##L
\PaperHeight##L
\ifLandscape
\Landscapetrue#S
\Landscapefalse#S
\setmargins{left}{top}{textwidth}{textheight}{headheight}{headsep}{footheight}{footskip}
\setmarginsrb{left}{top}{right}{bottom}{headheight}{headsep}{footheight}{footskip}
\setmargnohf{left}{top}{textwidth}{textheight}
\setmargnohfrb{left}{top}{right}{bottom}
\setmarg{left}{top}{textwidth}{textheight}
\setmargrb{left}{top}{right}{bottom}
\shiftmargins

\Vmargin#S
\filedate#S
\filename#S
\fileversion#S