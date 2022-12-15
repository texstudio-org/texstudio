# timing-diagrams package
# Matthew Bertucci 2022/06/23

#include:tikz
#include:tikzlibraryshadows
#include:tikzlibraryshape.callouts
#include:tikzlibrarydecorations.pathreplacing
#include:tikzlibrarydecorations.text
#include:ifthen

\boxheight#*
\tadvance{name}{x}{tikz code}
\tarrowCoord{(name1)}{(name2)}{text}
\tarrowLU{name1}{name2}{text}
\tarrowUL{name1}{name2}{text}
\tbox{name}{x}{text}
\tcalloutL[coord]{name}{text}
\tcalloutL{name}{text}
\tcalloutU[coord]{name}{text}
\tcalloutU{name}{text}
\tcaption{name}{text}
\tcatchup{name1}{name2}
\tendbrace{name}{text}
\tevent{name}
\teventA{name}{x}
\tlighttick{name}
\tline{name}{y}
\tlonglighttick{name}
\trecall{name}{remember-name}
\tremember{name}{remember-name}
\tsetcurrent{name}{coord}
\tsetcurrentabs{name}{x}
\tskip{name}{x}
\tskiparrowL{name}{x}{text}
\tskiparrowU{name}{x}{text}
\tskiptext{name}{x}{text}
\tskiptextCONF{name}{x}{node options}{text}
\tskiptextinbox{name}{x}{text}
\tskiptextL{name}{x}{text}
\tsmallbox{name}{x}{text}
\tstartbrace{name}
\tstrongtick{name}
\ttextarrowU[coord]{name}{text}
\ttextarrowU{name}{text}
\ttextL{name}{text}
\ttextM{name}{text}
\ttextU{name}{text}
\ttick{name}
\ttimeline{name}{x}
