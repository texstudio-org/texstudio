# microtype.cwl
# Edson 27-12-2010
# doncherry/2014-10-03 for microtype v. 2.5a
# Matthew Bertucci 7/22/2021 for microtype v. 2.8c

\microtypesetup{keyvals}

#keyvals:\microtypesetup
protrusion=#true,false,compatibility,nocompatibility,all,alltext,allmath,alltext-nott,allmath-nott,basictext,basicmath,smallcaps,footnotesize,scriptsize,normalfont
expansion=#true,false,compatibility,nocompatibility,all,alltext,allmath,alltext-nott,allmath-nott,basictext,basicmath,smallcaps,footnotesize,scriptsize,normalfont
activate=
tracking=#true,false,all,alltext,allmath,alltext-nott,allmath-nott,basictext,basicmath,smallcaps,footnotesize,scriptsize,normalfont
kerning=#true,false,all,alltext,allmath,alltext-nott,allmath-nott,basictext,basicmath,smallcaps,footnotesize,scriptsize,normalfont
spacing=#true,false,all,alltext,allmath,alltext-nott,allmath-nott,basictext,basicmath,smallcaps,footnotesize,scriptsize,normalfont
factor=%<integer%>
unit=%<dimension%>
auto#true,false
stretch=%<integer%>
shrink=%<integer%>
step=%<integer%>
selected#true,false
letterspace=%<integer%>
draft#true,false
final#true,false
verbose=#true,false,errors,silent
babel#true,false
DVIoutput#true,false
#endkeyvals

\DeclareMicrotypeSet[features]{name}{fonts%keyvals}
\DeclareMicrotypeSet*[features]{name}{fonts%keyvals}

\UseMicrotypeSet[features]{name}
\DeclareMicrotypeSetDefault[features]{name}

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
#endkeyvals

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

\DeclareCharacterInheritance[features]{fonts%keyvals}{list}

\DeclareMicrotypeVariants{suffixes}
\DeclareMicrotypeVariants*{suffixes}
\DeclareMicrotypeAlias{font}{alias}
\LoadMicrotypeFile{font}

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

\textls[amount]{text}
\textls*[amount]{text}
\lsstyle
\lslig{ligature}

\DisableLigatures[characters]{fonts%keyvals}

#keyvals:\DeclareMicrotypeSet,\DeclareMicrotypeSet*,\DeclareCharacterInheritance,\DisableLigatures
encoding=
family=
series=
shape=
size=
#endkeyvals
