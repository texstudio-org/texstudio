# mftinc package
# Matthew Bertucci 2/22/2022 for v1.0a

#include:chngpage
#include:keyval
#include:lineno
#include:rawfonts

\setmftdefaults{options%keyvals}

\mftinput{file}#i

\begin{explaincode}
\begin{explaincode}[options]
\end{explaincode}

#keyvals:\begin{explaincode},\setmftdefaults
toprule=##L
bottomrule=##L
#endkeyvals

\begin{wrapcomment}
\end{wrapcomment}
\mfcomment

\fonttable{font name}
\fonttable[options%keyvals]{font name}

#keyvals:\fonttable,\setmftdefaults
tablewidth=##L
charrange={%<range%>}
#endkeyvals

\centerlargechars#*
\chartline#*
\chartstrut#*
\endchart#*
\evenline#*
\hex{arg}#*
\morechart#*
\next#S
\oct{arg}#*
\oddline#*
\reposition#*
\setdigs#*
\table#*
\testrow#*
\ifskipping#*
\skippingtrue#*
\skippingfalse#*