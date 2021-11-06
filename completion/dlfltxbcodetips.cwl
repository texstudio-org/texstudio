# dlfltxbcodetips package
# Matthew Bertucci 11/5/2021 for v0.5

#include:amsmath
#include:amssymb
#include:graphicx

\bigtimes#m
\nuparrow#m
\ndownarrow#m

\NewShadedTheorem{envname}[numbered like]{caption}#N
\NewShadedTheorem{envname}{caption}#N
\NewShadedTheorem{envname}{caption}[within]#N
\theoremframecommand#*

\InsertTheoremBreak
\InsertTheoremBreak*

\MathIndent
\SetMathIndent{math code}
\AddtoMathIndent{math code}
\PopMathIndent
\PopMathIndent*

\DeclareMathSet{identifier}
\DeclareMathSet[options%keyvals]{identifier}

#keyvals:\DeclareMathSet
format=
name=
prefix=
overwrite#true,false
#endkeyvals

\ProvidePGFPagesFourOnOneWithSpaceForNotes
\OverloadUnderscoreInMath