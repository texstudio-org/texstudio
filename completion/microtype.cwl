# microtype.cwl
# Edson 27-12-2010
# doncherry/2014-10-03 for microtype v. 2.5a
# Matthew Bertucci 2023/03/07 for microtype v3.1

#include:keyval
#include:etoolbox

\microtypesetup{options%keyvals}

#keyvals:\microtypesetup,\usepackage/microtype#c
protrusion=#true,false,compatibility,nocompatibility,all,alltext,allmath,alltext-nott,allmath-nott,basictext,basicmath,smallcaps,footnotesize,scriptsize,normalfont,%microtypeset
expansion=#true,false,compatibility,nocompatibility,all,alltext,allmath,alltext-nott,allmath-nott,basictext,basicmath,smallcaps,footnotesize,scriptsize,normalfont,%microtypeset
activate=
tracking=#true,false,all,alltext,allmath,alltext-nott,allmath-nott,basictext,basicmath,smallcaps,footnotesize,scriptsize,normalfont,%microtypeset
kerning=#true,false,all,alltext,allmath,alltext-nott,allmath-nott,basictext,basicmath,smallcaps,footnotesize,scriptsize,normalfont,%microtypeset
spacing=#true,false,all,alltext,allmath,alltext-nott,allmath-nott,basictext,basicmath,smallcaps,footnotesize,scriptsize,normalfont,%microtypeset
factor=%<integer%>
patch=#all,none,item,toc,footnote,verbatim,eqnum
nopatch=#all,none,item,toc,footnote,verbatim,eqnum
unit=%<dimension%>
auto#true,false
stretch=%<integer%>
shrink=%<integer%>
step=%<integer%>
selected#true,false
letterspace=%<integer%>
disable=#true,false,ifdraft
final#true,false
verbose=#true,false,errors,silent
babel#true,false
DVIoutput#true,false
#endkeyvals

#keyvals:\usepackage/microtype#c
config=%<file name%>
#endkeyvals

\DeclareMicrotypeSet{name%specialDef}{fonts%keyvals}#s#%microtypeset
\DeclareMicrotypeSet[features]{name%specialDef}{fonts%keyvals}#s#%microtypeset
\DeclareMicrotypeSet*{name%specialDef}{fonts%keyvals}#s#%microtypeset
\DeclareMicrotypeSet*[features]{name%specialDef}{fonts%keyvals}#s#%microtypeset

\UseMicrotypeSet{name}
\UseMicrotypeSet[features]{name}
\DeclareMicrotypeSetDefault{name}
\DeclareMicrotypeSetDefault[features]{name}

\SetProtrusion{fonts}{settings}
\SetProtrusion[options%keyvals]{fonts}{settings}

#keyvals:\SetProtrusion
name=
load=
factor=%<integer%>
unit=
preset=
inputenc=
context=
#endkeyvals

\SetExpansion{fonts}{settings}
\SetExpansion[options%keyvals]{fonts}{settings}

#keyvals:\SetExpansion
name=
load=
preset=
inputenc=
context=
auto#true,false
stretch=%<integer%>
shrink=%<integer%>
step=%<integer%>
factor=
#endkeyvals

\SetTracking{fonts}{settings}
\SetTracking[options%keyvals]{fonts}{settings}

#keyvals:\SetTracking
name=
unit=
context=
spacing=
outer spacing=
outer kerning=
no ligatures=
#endkeyvals

\SetExtraKerning{fonts}{settings}
\SetExtraKerning[options%keyvals]{fonts}{settings}

#keyvals:\SetExtraKerning
name=
load=
factor=%<integer%>
preset=
inputenc=
unit=
context=
#endkeyvals

\SetExtraSpacing{fonts}{settings}
\SetExtraSpacing[options%keyvals]{fonts}{settings}

#keyvals:\SetExtraSpacing
name=
load=
factor=%<integer%>
preset=
inputenc=
context=
unit=
#endkeyvals

\DeclareCharacterInheritance{fonts%keyvals}{list}
\DeclareCharacterInheritance[features]{fonts%keyvals}{list}

\DeclareMicrotypeVariants{suffixes}
\DeclareMicrotypeVariants*{suffixes}
\DeclareMicrotypeAlias{font}{alias}
\LoadMicrotypeFile{font}
\DeclareMicrotypeFilePrefix{prefix}

\microtypecontext{context%keyvals}
\begin{microtypecontext}{context%keyvals}
\end{microtypecontext}
\textmicrotypecontext{context%keyvals}{text}
\DeclareMicrotypeBabelHook{languages}{context%keyvals}

#keyvals:\microtypecontext,\begin{microtypecontext},\textmicrotypecontext,\DeclareMicrotypeBabelHook
protrusion=
expansion=
activate=
tracking=
spacing=
kerning=
#endkeyvals

\textls{text}
\textls[amount]{text}
\textls*{text}
\textls*[amount]{text}
\lsstyle
\lslig{ligature}

\DisableLigatures{fonts%keyvals}
\DisableLigatures[characters]{fonts%keyvals}

#keyvals:\DeclareMicrotypeSet,\DeclareMicrotypeSet*,\DeclareCharacterInheritance,\DisableLigatures
encoding=
family=
series=
shape=
size=
font=
#endkeyvals

\leftprotrusion{text}
\rightprotrusion{text}
\noprotrusionifhmode#*
