# thalie package
# Matthew Bertucci 12/28/2021 for v0.10c

#include:etoolbox
#include:pgfkeys
#include:pgfopts
#include:suffix
#include:tabularx
#include:translations
#include:xspace

\setthalieoptions{options%keyvals}

#keyvals:\usepackage/thalie#c,\setthalieoptions
characterstyle=#bold,margin,center,simple,arden,imprimerie-verse,imprimerie-prose
playstyle=#center,bigcenter,box,custom
actstyle=#center,bigcenter,box,custom
scenestyle=#center,bigcenter,box,custom
playlevel=#part,chapter,section,subsection,subsubsection,paragraph,subparagraph
actlevel=#part,chapter,section,subsection,subsubsection,paragraph,subparagraph
scenelevel=#part,chapter,section,subsection,subsubsection,paragraph,subparagraph
interludelevel=#play,act,scene
xspace#true,false
#endkeyvals

\play{title}
\play[short title]{title}
\play*{title}
\act{title}
\act[short title]{title}
\act*{title}
\scene{title}
\scene[short title]{title}
\scene*{title}
\interlude{title}
\interlude[short title]{title}
\interlude*{title}
\curtain

\customplay{counter}{title}#*
\customplay*{title}#*
\customact{counter}{title}#*
\customact*{title}#*
\customscene{counter}{title}#*
\customscene*{title}#*

\theact
\theplay
\thescene

\playmark{text}#*
\actmark{text}#*
\scenemark{text}#*

\begin{dramatis}
\begin{dramatis}[hidden]%<%>
\end{dramatis}

\characterspace

\character{name}
\character[options%keyvals]{name}

#keyvals:\character
desc=%<description%>
cmd=%<csname%>
drama=%<name%>
#endkeyvals

\begin{charactergroup}{description}
\begin{charactergroup}[width]{description}
\end{charactergroup}

\begin{dramatisenv}#*
\end{dramatisenv}#*
\dramatischaracter{name}{description}#*
\dramatischaractername{name}#*
\dramatischaracterdescription{description}#*

\disposablecharacter{name}
\disposablecharacter[directions]{name}

\setcharactername{csname}{name}

\speakswithoutdirection{name}#*
\speakswithdirection{name}{direction}#*

\did{directions}
\begin{dida}
\end{dida}
\onstage{directions}
\pause

\pauseverse
\resumeverse 
\adjustverse{length}

\playname#*
\actname#*
\scenename#*
\interludename#*
\pausename#*
\curtainname#*