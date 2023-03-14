# caption.cwl
# Edson 2010
# Matthew Bertucci updated 2023/03/12 for v3.6j

#include:caption3
#include:ltcaption

# note that most package options defined in caption3, listed in caption3.cwl

#keyvals:\captionsetup#c,\captionsetup*#c,\usepackage/caption#c,\DeclareCaptionStyle#c,\bicaptionsetup#c,\bicaptionsetup*#c,\subcaptionsetup#c,\subcaptionsetup*#c
list-entry=#default,list-entry,entry
hypcap#true,false
hypcapspace=##L
type=%<float type%>
type*=%<float type%>
subtype=%<float type%>
subtype*=%<float type%>
#endkeyvals

#keyvals:\usepackage/caption#c
compatibility#true,false
config=%<file name%>
#endkeyvals

#ifOption:font=onehalfspacing
#include:setspace
#endif
#ifOption:labelfont=onehalfspacing
#include:setspace
#endif
#ifOption:textfont=onehalfspacing
#include:setspace
#endif
#ifOption:font+=onehalfspacing
#include:setspace
#endif
#ifOption:labelfont+=onehalfspacing
#include:setspace
#endif
#ifOption:textfont+=onehalfspacing
#include:setspace
#endif

#ifOption:font=doublespacing
#include:setspace
#endif
#ifOption:labelfont=doublespacing
#include:setspace
#endif
#ifOption:textfont=doublespacing
#include:setspace
#endif
#ifOption:font+=doublespacing
#include:setspace
#endif
#ifOption:labelfont+=doublespacing
#include:setspace
#endif
#ifOption:textfont+=doublespacing
#include:setspace
#endif

#ifOption:font=sansmath
#include:sansmath
#endif
#ifOption:labelfont=sansmath
#include:sansmath
#endif
#ifOption:textfont=sansmath
#include:sansmath
#endif
#ifOption:font+=sansmath
#include:sansmath
#endif
#ifOption:labelfont+=sansmath
#include:sansmath
#endif
#ifOption:textfont+=sansmath
#include:sansmath
#endif

#ifOption:justification=RaggedRight
#include:ragged2e
#endif
#ifOption:justification=RaggedLeft
#include:ragged2e
#endif

#ifOption:justification=Justified
#include:ragged2e
#endif
#ifOption:justification=Centering
#include:ragged2e
#endif
#ifOption:justification=RaggedRight
#include:ragged2e
#endif
#ifOption:justification=RaggedLeft
#include:ragged2e
#endif

\caption[list entry%text]{heading%text}
\caption{heading%text}
\caption*{heading%text}

\captionof{float type}[list entry%text]{heading%text}
\captionof{float type}{heading%text}
\captionof*{float type}{heading%text}

\captionlistentry[float type]{list entry%text}
\captionlistentry{list entry%text}

\ContinuedFloat
\ContinuedFloat*
\theContinuedFloat#*

\piccaptiontype{float type}#*

\begin{captionblock}{width}
\begin{captionblock}[position]{width}
\begin{captionblock}[position][height]{width}
\begin{captionblock}[position][height][inner-pos]{width}
\end{captionblock}
\begin{captiongroup}#*
\end{captiongroup}#*
\begin{captiongroup*}#*
\end{captiongroup*}#*
\captionbox*{heading%text}[width][inner-pos]{content%text}
\captionbox*{heading%text}[width]{content%text}
\captionbox*{heading%text}{content%text}
\captionbox[list entry]{heading%text}[width][inner-pos]{content%text}
\captionbox[list entry]{heading%text}[width]{content%text}
\captionbox[list entry]{heading%text}{content%text}
\captionbox{heading%text}[width][inner-pos]{content%text}
\captionbox{heading%text}[width]{content%text}
\captionbox{heading%text}{content%text}
\captiontext*[number]{text}
\captiontext*{text}
\captiontext[number]{text}
\captiontext{text}
\flushsubcaptionlistentries#*
\nextfloat
\nextfloat*
\phantomcaption
\setcaptionsubtype*
\setcaptionsubtype{float type}
\setcaptiontype*
\setcaptiontype{float type}

# only available if longtable package loaded
\begin{longtable*}#S
\end{longtable*}#S

# deprecated
\continuedfloat#S
\thecontinuedfloat#S
