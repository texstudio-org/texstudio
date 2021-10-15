# algorithmic package
# updated Matthew Bertucci 10/12/2021 for v0.1

#include:ifthen
#include:keyval

\begin{algorithmic}#\algorithm
\begin{algorithmic}[lines]#\algorithm
\end{algorithmic}

\STATE#/algorithmic

\IF{condition}#/algorithmic
\ENDIF#/algorithmic
\ELSE#/algorithmic
\ELSIF{condition}#/algorithmic

\FOR{condition}#/algorithmic
\ENDFOR#/algorithmic
\FORALL{condition}#/algorithmic
\TO#/algorithmic

\WHILE{condition}#/algorithmic
\ENDWHILE#/algorithmic

\REPEAT#/algorithmic
\UNTIL{condition}#/algorithmic

\LOOP#/algorithmic
\ENDLOOP#/algorithmic

\AND#/algorithmic
\OR#/algorithmic
\XOR#/algorithmic
\NOT#/algorithmic

\REQUIRE#/algorithmic

\ENSURE#/algorithmic

\RETURN#/algorithmic
\TRUE#/algorithmic
\FALSE#/algorithmic

\PRINT#/algorithmic

\COMMENT{text}#/algorithmic

\algsetup{options%keyvals}

#keyvals:\algsetup
indent=##L
linenosize=##L
linenodelimiter=
#endkeyvals

\STMT#*/algorithmic
\INPUTS{arg}#*
\ENDINPUTS#*
\OUTPUTS{arg}#*
\ENDOUTPUTS#*
\GLOBALS#*
\BODY{arg}#*
\ENDBODY#*
\algorithmicrequire#*
\algorithmicensure#*
\algorithmiccomment{text}#*
\algorithmicend#*
\algorithmicif#*
\algorithmicthen#*
\algorithmicelse#*
\algorithmicelsif#*
\algorithmicendif#*
\algorithmicfor#*
\algorithmicforall#*
\algorithmicdo#*
\algorithmicendfor#*
\algorithmicwhile#*
\algorithmicendwhile#*
\algorithmicloop#*
\algorithmicendloop#*
\algorithmicrepeat#*
\algorithmicuntil#*
\algorithmicprint#*
\algorithmicreturn#*
\algorithmicand#*
\algorithmicor#*
\algorithmicxor#*
\algorithmicnot#*
\algorithmicto#*
\algorithmicinputs#*
\algorithmicoutputs#*
\algorithmicglobals#*
\algorithmicbody#*
\algorithmictrue#*
\algorithmicfalse#*