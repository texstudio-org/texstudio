# register package
# Matthew Bertucci 12/14/2021 for v2.0

#include:calc
#include:float
#include:graphicx
#include:ifthen
#include:xcolor

#keyvals:\usepackage/register#c
LyX
hyperref
TRflags
TRboxed
color
botcaption
nocaption
#endkeyvals

\begin{register}{placement}{name}{register offset}
\end{register}
\begin{register*}{placement}{name}{register offset}
\end{register*}

\listofregisters
\regfield{name}{length%plain}{start bit}{reset value}
\regfieldb{name}{length%plain}{start bit}
\regbits{name}{length%plain}{reset value}
\regnewline
\reglabel{reset label}
\reglabelb{reset label}#*
\TR{flag}

\begin{regdesc}
\end{regdesc}
\begin{reglist}
\end{reglist}

\GetTRPageRef{key}#*r
\TRfamily#*
\TRleftlabel{label}#*
\TRrightlabel{label}#*
\TRwidth#*
\TRwriteout{text}#*
\aux#S
\oldregdescsep#S
\regBitFamily#*
\regBitSize#*
\regBitWidth#*
\regDescFamily#*
\regDescSkip#*
\regFboxSep#*
\regFieldLen#*
\regFiller{arg}#*
\regFloatName#*
\regLabelAdjust#*
\regLabelFamily#*
\regLabelSize#*
\regListName#*
\regMakeFieldName{name}#*
\regResetDepth#*
\regResetDrop#*
\regResetHeight#*
\regResetName#*
\regResetSize#*
\regRotateFieldName#*
\regRsvdDrop#*
\regRsvdHeight#*
\regSpreadaux{arg1}{arg2}#*
\regSpread{arg}#*
\regUnderScore#*
\regWidth#*
\regdescsep#*
\regfieldColor#*
\regfieldColor{arg1}{arg2}{arg3}{arg4}{arg5}#*
\regfieldNoColor{arg1}{arg2}{arg3}{arg4}#*
\regfieldbColor{arg1}{arg2}{arg3}{arg4}#*
\regfieldbNoColor{arg1}{arg2}{arg3}#*
\regspace{bit width}#*
\setRegLengths#*
\thelowerbit#*
\theupperbit#*
\typesetRegBits{arg1}#*
\typesetRegColorBits{arg1}{arg2}#*
\typesetRegColorReset{arg1}{arg2}#*
\typesetRegReset{arg1}#*