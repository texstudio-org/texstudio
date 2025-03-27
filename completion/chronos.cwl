# chronos package
# Matthew Bertucci 2025/03/17 for v0.9.2

#include:svn-prov
#include:xcolor
#include:tikz
#include:etoolbox
#include:pgfcalendar
#include:calc
#include:fp
#include:tikzlibrarycalc
#include:tikzlibrarypositioning
#include:tikzlibraryfixedpointarithmetic
#include:tikzlibrarydecorations.text
#include:tikzlibraryfit
#include:tikzlibraryshadows
#include:tikzlibrarybackgrounds

#keyvals:\usepackage/chronos#c
simple color names#true,false
no simple color names#true,false
#endkeyvals

\begin{chronos}#\pictureHighlight
\begin{chronos}[options%keyvals]#\pictureHighlight
\end{chronos}

\bcelabel#*
\bceyearlabel#*
\celabel#*
\ceyearlabel#*
\chronosbaselineskip#*
\chronoscopyleft{keyvals}
\chronoscopyright{keyvals}
\chronosevent{keyvals}
\chronosinfo{keyvals}
\chronoslife{keyvals}
\chronosmaintitle{keyvals}
\chronosnewcolorscheme[existing scheme]{name}{keyvals}#*
\chronosnewcolorscheme{name}{keyvals}#*
\chronosnewcolourscheme[existing scheme]{name}{keyvals}#*
\chronosnewcolourscheme{name}{keyvals}#*
\chronosperiod{keyvals}
\chronosset{keyvals}
\chronosshowcolor*[cmd]{color}#*d
\chronosshowcolor*{color}#*
\chronosshowcolor[cmd]{color}#*d
\chronosshowcolor{color}#*
\chronosshowcolour*[cmd]{color}#*d
\chronosshowcolour*{color}#*
\chronosshowcolour[cmd]{color}#*d
\chronosshowcolour{color}#*
\chronosshowfeatures#*
\chronosshowfeatures[tag]#*
\chronosshowpreset#*
\chronostheory{keyvals}
\chronostheorycircle{keyvals}
\chronosyeari#*
\lineyshift#*
\timelineborderht#*
\timelineht#*
\timelinewd#*

\plstyle#*
\sishape#*
\textsi{text}#*
\textui{text}#*
\tlstyle#*
\uishape#*

\CSFreeBoolean{cmd}#*
\CSlet{csname}{cmd}#*
\CSletCS{csname}{csname}#*
\IfBooleanExprF{bool expr}{false code}#*
\IfBooleanExprT{bool expr}{true code}#*
\IfBooleanExprTF{bool expr}{true code}{false code}#*
\IfCSExistF{csname}{false code}#*
\IfCSExistT{csname}{true code}#*
\IfCSExistTF{csname}{true code}{false code}#*
\IfCSFreeF{csname}{false code}#*
\IfCSFreeT{csname}{true code}#*
\IfCSFreeTF{csname}{true code}{false code}#*
\IfExistF{cmd}{false code}#*
\IfExistT{cmd}{true code}#*
\IfExistTF{cmd}{true code}{false code}#*
\IfFreeF{cmd}{false code}#*
\IfFreeT{cmd}{true code}#*
\IfFreeTF{cmd}{true code}{false code}#*
\IfIntCompareF{int expr}{false code}#*
\IfIntCompareT{int expr}{true code}#*
\IfIntCompareTF{int expr}{true code}{false code}#*
\IntCompareBoolean{int expr1}{relation}{int expr2}#*
\LegacyBoolean{name}#*
\Undefine{cmd}#*

\byw{keyvals}#S
\cylchtheori{keyvals}#S
\digwyddiad{keyvals}#S
\gwybodaeth*{keyvals}#S
\gwybodaeth{keyvals}#S
\hawlfraint{keyvals}#S
\parhad{keyvals}#S
\prifdeitl{keyvals}#S
\theori{keyvals}#S

# documented as not useful
\chronosset*{keyvals}#S

# not documented
\testunteitl#S