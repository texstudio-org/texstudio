# othelloboard package
# Matthew Bertucci 2/2/2022 for v0.6

#include:color
#include:graphicx
#include:ifthen
#include:pict2e
#include:stringstrings
#include:xstring

\begin{othelloboard}{scale}
\end{othelloboard}

\dotmarkings

\othelloarrayfirstrow{num1}{num2}{num3}{num4}{num5}{num6}{num7}{num8}
\othelloarraysecondrow{num1}{num2}{num3}{num4}{num5}{num6}{num7}{num8}
\othelloarraythirdrow{num1}{num2}{num3}{num4}{num5}{num6}{num7}{num8}
\othelloarrayfourthrow{num1}{num2}{num3}{num4}{num5}{num6}{num7}{num8}
\othelloarrayfifthrow{num1}{num2}{num3}{num4}{num5}{num6}{num7}{num8}
\othelloarraysixthrow{num1}{num2}{num3}{num4}{num5}{num6}{num7}{num8}
\othelloarrayseventhrow{num1}{num2}{num3}{num4}{num5}{num6}{num7}{num8}
\othelloarrayeighthrow{num1}{num2}{num3}{num4}{num5}{num6}{num7}{num8}

\begin{othelloboardnorefs}{scale}
\end{othelloboardnorefs}

\annotationsfirstrow{txt1}{txt2}{txt3}{txt4}{txt5}{txt6}{txt7}{txt8}
\annotationssecondrow{txt1}{txt2}{txt3}{txt4}{txt5}{txt6}{txt7}{txt8}
\annotationsthirdrow{txt1}{txt2}{txt3}{txt4}{txt5}{txt6}{txt7}{txt8}
\annotationsfourthrow{txt1}{txt2}{txt3}{txt4}{txt5}{txt6}{txt7}{txt8}
\annotationsfifthrow{txt1}{txt2}{txt3}{txt4}{txt5}{txt6}{txt7}{txt8}
\annotationssixthrow{txt1}{txt2}{txt3}{txt4}{txt5}{txt6}{txt7}{txt8}
\annotationsseventhrow{txt1}{txt2}{txt3}{txt4}{txt5}{txt6}{txt7}{txt8}
\annotationseighthrow{txt1}{txt2}{txt3}{txt4}{txt5}{txt6}{txt7}{txt8}

\posannotation{square name}{annotation string}

\drawtranscript{longstring}
\drawboardfromstring{longstring}

# not documented
\blackdiamond#*
\blackdisc#*
\countblackdiscs#*
\countwhitediscs#*
\gridrefs#*
\othelloannotation{num}{text}#*
\othellodiscfromstring{arg}#*
\othellodisc{arg}#*
\othellogrid#*
\othellonormaltext{text}#*
\othellowhitetext{text}#*
\resetalldisccolours#*
\scalefactor#*
\thedisccolouraa#S
\thedisccolourad#S
\thedisccolourag#S
\thedisccolourbb#S
\thedisccolourbe#S
\thedisccolourbh#S
\thedisccolourcc#S
\thedisccolourcf#S
\thedisccolourda#S
\thedisccolourdd#S
\thedisccolourdg#S
\thedisccoloureb#S
\thedisccolouree#S
\thedisccoloureh#S
\thedisccolourfc#S
\thedisccolourff#S
\thedisccolourga#S
\thedisccolourgd#S
\thedisccolourgg#S
\thedisccolourhb#S
\thedisccolourhe#S
\thedisccolourhh#S
\thenumberbdiscs#S
\thenumberwdiscs#S
\whitediamond#*
\whitedisc#*