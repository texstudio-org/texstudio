# umlcd tikzlibrary
# Matthew Bertucci 2026/08/31 for v0.3dev

#include:tikzlibraryshapes.multipart
#include:tikzlibrarybackgrounds
#include:tikzlibraryfit

\begin{class}{class name%text}{x,y}
\begin{class}[TikZ options]{class name%text}{x,y}
\end{class}

\attribute{text}
\operation{text}
\operation[0]{%<text%>}

\begin{abstractclass}{class name%text}{x,y}
\begin{abstractclass}[TikZ options]{class name%text}{x,y}
\end{abstractclass}
\begin{interface}{interface name%text}{x,y}
\begin{interface}[TikZ options]{interface name%text}{x,y}
\end{interface}
\begin{object}{object name%text}{x,y}
\begin{object}[TikZ options]{object name%text}{x,y}
\end{object}

\instanceOf{class name}

\switchUmlcdSchool

\umlnote (%<name%>) {%<text%>};
\umlnote (%<name%>) at (%<coord%>) {%<text%>};
\umlnote[%<TikZ options%>] (%<name%>) {%<text%>};
\umlnote[%<TikZ options%>] (%<name%>) at (%<coord%>) {%<text%>};

\inherit{class name}
\implement{interface name}

\association{class1}{abovetext1}{belowtext1}{class2}{abovetext2}{belowtext2}
\unidirectionalAssociation{class1}{abovetext}{belowtext}{class2}
\aggregation{class1}{abovetext}{belowtext}{class2}
\composition{class1}{abovetext}{belowtext}{class2}

\begin{package}{package name%text}
\end{package}

# not documented
\begin{classAndInterfaceCommon}{TikZ options}{name%text}{x,y}#S
\end{classAndInterfaceCommon}#S
\calcuateNumberOfParts#S
\insertAttributesAndOperations#S
\theumlcdClassAbstractClassNum#S
\theumlcdClassAttributesNum#S
\theumlcdClassInterfaceNum#S
\theumlcdClassOperationsNum#S
\theumlcdClassSplitPartNum#S
\umlcdClassAbstractClass#S
\umlcdClassAbstractClassOld#S
\umlcdClassAttributes#S
\umlcdClassAttributesOld#S
\umlcdClassInterface#S
\umlcdClassInterfaceOld#S
\umlcdClassName#S
\umlcdClassOperations#S
\umlcdClassOperationsOld#S
\umlcdClassPos#S
\umlcdPackageFit#S
\umlcdPackageFitOld#S
\umlcdPackageName#S
\umldObjectName#S
\umldrawcolor#S
\umlfillcolor#S
\umltextcolor#S
\virtualoperation#S