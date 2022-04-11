# ltj-latex package
# Matthew Bertucci 4/9/2022 for v20220311.0

#include:lltjfont
#include:lltjdefs
#include:lltjcore
#include:lltjp-atbegshi
#include:lltjp-geometry

\luatexjalatexLoaded#S

# following keys + commands added automatically when listings loaded
#keyvals:\lstset,\lstinline,\begin{lstlisting},\lstinputlisting,\lstMakeShortInline,\lstdefinelanguage,\lstdefinestyle
vsraw#true,false
vscmd=%<cmd%>
doubleletterspace=
#endkeyvals
\ltjlistingsvsstdcmd{arg}#S
\CatcodeTableLTJlistings#S