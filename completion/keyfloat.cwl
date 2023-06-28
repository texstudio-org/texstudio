# keyfloat package
# Matthew Bertucci 11/29/2021 for v2.06

#include:etoolbox
#include:xkeyval
#include:graphicx
#include:caption
#include:subcaption
#include:calc
#include:rotating
#include:placeins
#include:wrapfig

\keyfig{keyvals}{imagefile}#g
\keyfig[loc]{keyvals}{imagefile}#g
\keyfig*{keyvals}{imagefile}#*g
\keyfig*[loc]{keyvals}{imagefile}#*g

\keytab{keyvals}{tabular contents}
\keytab[loc]{keyvals}{tabular contents}
\keytab*{keyvals}{tabular contents}#*
\keytab*[loc]{keyvals}{tabular contents}#*

\keyflt{float type}{keyvals}{contents}
\keyflt[loc]{float type}{keyvals}{contents}
\keyflt*{float type}{keyvals}{contents}#*
\keyflt*[loc]{float type}{keyvals}{contents}#*

\keyfigbox{keyvals}{box contents}
\keyfigbox[loc]{keyvals}{box contents}
\keyfigbox*{keyvals}{box contents}#*
\keyfigbox*[loc]{keyvals}{box contents}#*

\keyparbox{keyvals}{box contents}
\keyparbox[loc]{keyvals}{box contents}
\keyparbox*{keyvals}{box contents}#*
\keyparbox*[loc]{keyvals}{box contents}#*

\begin{keyfigure}{keyvals}
\begin{keyfigure}[loc]{keyvals}
\begin{keyfigure}*{keyvals}#*
\begin{keyfigure}*[loc]{keyvals}#*
\end{keyfigure}

\begin{keytable}{keyvals}
\begin{keytable}[loc]{keyvals}
\begin{keytable}*{keyvals}#*
\begin{keytable}*[loc]{keyvals}#*
\end{keytable}

\begin{keyfloat}{float type}{keyvals}
\begin{keyfloat}[loc]{float type}{keyvals}
\begin{keyfloat}*{float type}{keyvals}#*
\begin{keyfloat}*[loc]{float type}{keyvals}#*
\end{keyfloat}

\begin{keyfloats}{num cols}
\begin{keyfloats}{num cols}[keyvals]
\end{keyfloats}

\begin{keysubfigs}{num cols}{keyvals}
\begin{keysubfigs}{num cols}{keyvals}[shared keyvals]
\begin{keysubfigs}[loc]{num cols}{keyvals}#*
\begin{keysubfigs}[loc]{num cols}{keyvals}[shared keyvals]
\begin{keysubfigs}*{num cols}{keyvals}#*
\begin{keysubfigs}*{num cols}{keyvals}[shared keyvals]#*
\begin{keysubfigs}*[loc]{num cols}{keyvals}#*
\begin{keysubfigs}*[loc]{num cols}{keyvals}[shared keyvals]#*
\end{keysubfigs}

\begin{keysubtabs}{num cols}{keyvals}
\begin{keysubtabs}{num cols}{keyvals}[shared keyvals]
\begin{keysubtabs}[loc]{num cols}{keyvals}#*
\begin{keysubtabs}[loc]{num cols}{keyvals}[shared keyvals]
\begin{keysubtabs}*{num cols}{keyvals}#*
\begin{keysubtabs}*{num cols}{keyvals}[shared keyvals]#*
\begin{keysubtabs}*[loc]{num cols}{keyvals}#*
\begin{keysubtabs}*[loc]{num cols}{keyvals}[shared keyvals]#*
\end{keysubtabs}

\begin{keysubfloats}{float type}{num cols}{keyvals}
\begin{keysubfloats}{float type}{num cols}{keyvals}[shared keyvals]
\begin{keysubfloats}[loc]{float type}{num cols}{keyvals}#*
\begin{keysubfloats}[loc]{float type}{num cols}{keyvals}[shared keyvals]
\begin{keysubfloats}*{float type}{num cols}{keyvals}#*
\begin{keysubfloats}*{float type}{num cols}{keyvals}[shared keyvals]#*
\begin{keysubfloats}*[loc]{float type}{num cols}{keyvals}#*
\begin{keysubfloats}*[loc]{float type}{num cols}{keyvals}[shared keyvals]#*
\end{keysubfloats}

\begin{keywrap}{width}{keyfloat}
\end{keywrap}

\begin{marginfigure}
\begin{marginfigure}[offset%l]
\end{marginfigure}

\begin{margintable}
\begin{margintable}[offset%l]
\end{margintable}

## note the keyval completer does not handle the "\begin{float}*"-type environments well
## keys available to all environments
#keyvals:\keyfig#c,\keyfig*#c,\keytab#c,\keytab*#c,\keyflt#c,\keyflt*#c,\keyfigbox#c,\keyfigbox*#c,\keyparbox#c,\keyparbox*#c,\begin{keyfigure}#c,\begin{keytable}#c,\begin{keyfloat}#c,\begin{keyfloats}#c,\begin{keysubfigs}#c,\begin{keysubtabs}#c,\begin{keysubfloats}#c
c={%<caption%>}
cstar={%<caption%>}
sc={%<short caption%>}
cont
l=##l
t={%<text%>}
tc={%<text%>}
tl={%<text%>}
tr={%<text%>}
#endkeyvals

## keys not available in "sub-" environments
#keyvals:\keyfig#c,\keyfig*#c,\keytab#c,\keytab*#c,\keyflt#c,\keyflt*#c,\keyfigbox#c,\keyfigbox*#c,\keyparbox#c,\keyparbox*#c,\begin{keyfigure}#c,\begin{keytable}#c,\begin{keyfloat}#c,\begin{keyfloats}#c
lw=%<factor%>
w=##L
h=##L
kar
s=%<factor%>
r=%<degrees%>
f
ft
stretch=%<factor%>
mo=##L
wn=%<integer%>
wp=#r,l,i,o,R,L,I,O
wo=##L
wlw=%<factor%>
ww=##L
va=
#endkeyvals

## "artist" keys used by figures
#keyvals:\keyfig#c,\keyfig*#c,\keyfigbox#c,\keyfigbox*#c,\begin{keyfigure}#c,\begin{keysubfigs}#c
ap=%<author prefix%>
aup=%<author prefix%>
af=%<first name%>
auf=%<first name%>
al=%<last name%>
aul=%<last name%>
as=%<author suffix%>
aus=%<author suffix%>
#endkeyvals

\KFLTtightframe{contents}#*
\KFLTlooseframe{contents}#*
\KFLTtightframewidth#*
\KFLTlooseframewidth#*
\KFLTimageboxwidth#*

\begin{figurehere}#*
\end{figurehere}#*
\begin{tablehere}#*
\end{tablehere}#*

\tdartistcenter#S
\tdartistjustify#S
\tdartistleft#S
\tdartistright#S
\tdartisttextcenter#S
\tdartisttextjustify#S
\tdartisttextleft#S
\tdartisttextright#S
\tdauthorcenter#S
\tdauthorjustify#S
\tdauthorleft#S
\tdauthorright#S
\tdauthortextcenter#S
\tdauthortextjustify#S
\tdauthortextleft#S
\tdauthortextright#S
