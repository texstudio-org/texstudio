# ling-macros package
# Matthew Bertucci 11/22/2021 for v2.2

#include:gb4e
#include:stmaryrd
#include:amssymb
#include:pbox
#include:ulem
#include:upgreek
#include:relsize

\nl
\m{text}
\mc{text}
\mb
\ol{text}
\alert{text}
\term{text}
\ix{subscript}
\ux{subscript}
\superx{supscript}

\bex
\fex
\bxl
\fxl

\ben
\fen
\bit
\fit

\begin{context}
\end{context}

\underlying{input}
\becomes
\spoken{output}
\environ
\spot
\syll
\fmleft
\fmright
\fmat{left}{right} 
\prule{underlying form}{spoken form}{environment}
\iparule{underlying form}{spoken form}{environment}
\pruleset{underlying form}{spoken form}{text}{environment}
\iparuleset{underlying form}{spoken form}{text}{environment}

\head{arg}
\xbar{arg}
\lv
\feat{feature}
\textfeat{feature}
\dcopy{text}
\mroot{text}
\ufeat{feature}
\unv{feature}

\readas{arg}
\lam{variable}
\lamd{variable}{type}
\all{variable}
\some{variable}
\no{variable}
\ddet{variable}
\pri

\type{types}
\uptype{types}

\set{set}
\varset{set}
\cvarset{arg1}{arg2}

\funcnote{name}{domain}{range}{input-var}{rule}
\fleft
\func{domain}{range}
\fright

\scopebox{expression}
\innerscopebox{expression}

\den{arg}
\dena{arg}{assignment}
\denac{arg}{context}
\denamod{arg}{assignment}{modification}
\denacmod{arg}{context}{modification}

\denol{arg}
\denola{arg}{assignment}
\denolac{arg}{context}
\denolamod{arg}{assignment}{modification}
\denolacmod{arg}{context}{modification}

\lessthanten
\tenormore

\bexskip#*
\bxlskip#*
\bexsep#*
\bxlsep#*
\bexindent#*
\bxlindent#*
\fexskip#*
\fxlskip#*
\bexlabel#*
\bxllabel#*
\featuresize#*
\prulewidth#*
\environset{arg}#*
\scopewidth#*