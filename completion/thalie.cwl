# thalie package
# Matthew Bertucci 2022/12/12 for v0.13a

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
\begin{dramatis}[options%keyvals]
\end{dramatis}

#keyvals:\begin{dramatis}
hidden#true,false
defaultcast=%<cast%>
#endkeyvals

\character{name}
\character[options%keyvals]{name}

#keyvals:\character
desc=%<description%>
cmd=%<csname%>
drama=%<name%>
cast=%<cast%>
#endkeyvals

\begin{charactergroup}{description}
\begin{charactergroup}[width]{description}
\end{charactergroup}

\begin{castgroup}{name}
\begin{castgroup}[options%keyvals]{name}
\end{castgroup}

#keyvals:\begin{castgroup}
desc=%<description%>
cmd=%<csname%>
drama=%<name%>
#endkeyvals

\cast{cast}

\characterspace

\begin{dramatisenv}#*
\end{dramatisenv}#*
\begin{dramatischaractergroup}{width}{description}#*
\end{dramatischaractergroup}#*
\begin{dramatischaractercastgroup}{name}{description}{cast}#*
\end{dramatischaractercastgroup}#*
\dramatischaracter{name}{description}{cast}#*
\dramatischaractername{name}#*
\dramatischaracterdescription{description}#*
\dramatischaractercast{cast}#*
\dramatiscast{cast}#*

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
