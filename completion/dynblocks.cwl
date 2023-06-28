# dynblocks package
# Matthew Bertucci 2/10/2022 for v0.2b

#include:tikz
#include:etoolbox

#keyvals:\usepackage/dynblocks#c
customcolors
getthemecolors
roundedcorners
shadow
#endkeyvals

#ifOption:shadow
#include:tikzlibraryshadows
#endif

\opaqueblock<overlay specification>{text}
\opaqueblock<overlay specification>[width]{text}
\invblock<overlay specification>

\begin{dynblock}
\end{dynblock}

\setalignment{alignment%keyvals}

#keyvals:\setalignment#c
left
flush left
right
flush right
center
flush center
justify
none
#endkeyvals

\setvisopacity{opacity}
\setinvopacity{opacity}

\dynalert<overlay specification>{text}

\setwordscolor{color}

\setshadowopacity{opacity}

#ifOption:customcolors
\setblockcolor{color}
\setbordercolor{color}
\setinnercolor{color}
\setoutercolor{color}
\settopcolor{color}
\setbottomcolor{color}
\setleftcolor{color}
\setrightcolor{color}
#endif

\fancyblock<overlay specification>{text}
\fancyblock<overlay specification>[width]{text}
\vshadeblock<overlay specification>{text}
\vshadeblock<overlay specification>[width]{text}
\oshadeblock<overlay specification>{text}
\oshadeblock<overlay specification>[width]{text}

\thecol#*
\thebordercol#*
\myalert{text}#*
\printthistext{id}#*
\savetext{id}{text}#*
\thethistext#*
\intdimension#*
