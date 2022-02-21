# pst-tools package
# Matthew Bertucci 2/20/2022 for v0.12

#include:pstricks
#include:pst-xkey

\psPrintValue{PS code}
\psPrintValue[options%keyvals]{PS code}
\psPrintValueNew{PS code}#*
\psPrintValueNew[options%keyvals]{PS code}#*

#keyvals:\psPrintValue,\psPrintValueNew
printfont=%<font name%>
postString=%<string%>
trimSpaces#true,false
fontscale=%<scale in pts%>
valuewidth=%<number%>
decimals=%<number%>
xShift=%<shift in pts%>
algebraic#true,false
VarName=%<string%>
comma#true,false
#endkeyvals

#keyvals:\psPrintValueNew
round#true,false
science#true,false
#endkeyvals

\psRegisterList{name}{value list}

\randomi#*
\nextrandom#*
\setrannum{count register%cmd}{min}{max}#d
\setrandim{dimen register%cmd}{min}{max}#d
\pointless
\PoinTless#*
\ranval#*

\txG#S
\etxG#S
\PSTtoolsLoaded#S