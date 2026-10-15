# babelbidi package
# Matthew Bertucci 2026/10/14 for v0.3.0

#include:iftex
#include:xkeyval
#include:babel

#keyvals:\usepackage/babelbidi#c
bidi=#basic,bidi-r,default
layout=
fontcache#true,false
code=%<language%>
latin=%<language%>
ltr=%<language%>
rtl=%<language%>
#endkeyvals

\begin{RTL}
\end{RTL}
\begin{LTR}
\end{LTR}
\begin{latin}
\end{latin}

\fontfallback{language}{list of languages}
\LRE{text}
\LR{text}#*
\RLE{text}
\RL{text}#*
\latintoday
\latinttfamily
\lr{text}
\rl{text}
\setparLTR#*
\setparRTL#*

\deflatinfont{command}[options%keyvals]{font}#d
\deflatinfont{command}{font}#d
\setlatinmonofont[options%keyvals]{font}
\setlatinmonofont{font}
\setlatinsansfont[options%keyvals]{font}
\setlatinsansfont{font}
\setlatintextfont[options%keyvals]{font}
\setlatintextfont{font}
\settextfont[options%keyvals]{font}
\settextfont{font}