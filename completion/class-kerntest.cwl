# kerntest package
# Matthew Bertucci 2022/07/20 for v2.4.2

#include:geometry
#include:helvet
#include:calc
#include:longtable
#include:array
#include:color
#include:ifthen
#include:keyval
#include:fontenc
# loads T1 option of fontenc

#keyvals:\documentclass/kerntest#c
family=%<font family%>
#endkeyvals

\kernsetup{options%keyvals}

#keyvals:\documentclass/kerntest#c,\kernsetup
encoding=%<font encoding%>
series=%<font series%>
shape=%<font shape%>
size=##L
baselineskip=##L
designsize=##L
example=%<text%>
papersize=%<geometry papersize%>
extraname=%<fontname extension%>
color#true,false
copyquotation#true,false
writeall#true,false
footer#true,false
#endkeyvals

\begin{kerntable}#\tabular
\end{kerntable}

\testkern{glyph1}{kerning1}{glyph2}{kerning2}{glyph3}
\mtxcomment{comment}

\encodingsetup{options%keyvals}

#keyvals:\encodingsetup
ligaturing=%<number%>
italicizing#true,false
#endkeyvals

\defglyphclass{side}{name}{glyphlist}
\newglyphclass{side}{name}{glyphlist}
\renewglyphclass{side}{name}{glyphlist}
\provideglyphclass{side}{name}{glyphlist}

\firstglyphinclass#S
\forallclasses{side}{glyph class}{action}#*
\forallinclass{side}{name}{glyph}{action}#*
\getclassofglyph{side}{glyph name}#*
\getkern{arg}#*
\getpsname{arg}#*
\getpsunit{arg}#*
\getslotnumber{arg}#*
\ifglyphinclass{side}{name}{glyph}{true}{false}#*
\leftkern#S
\mtxfile#*
\mtxfilename#*
\oldkerna#S
\oldkernb#S
\printglyph{arg}#*
\ProcessOptionsWithKV{family}#S
\psunit#*
\rightkern#S
\round{arg}#*
\saveslotnumber{arg1}{arg2}#*
\stoploop#*
\stoploop[var]#*
\textleft#S
\textright#S
\thisglyphname#S
\writemtxkern[opt]{arg1}{arg2}{arg3}#*
\writemtxkern{arg1}{arg2}{arg3}#*

oldcolor#B
newcolor#B

# from T1 option of fontenc
\DH#n
\dh#n
\dj#n
\DJ#n
\guillemetleft#n
\guillemetright#n
\guillemotleft#*n
\guillemotright#*n
\guilsinglleft#n
\guilsinglright#n
\Hwithstroke#n
\hwithstroke#n
\k{arg}#n
\NG#n
\ng#n
\quotedblbase#n
\quotesinglbase#n
\textogonekcentered{arg}#n
\textquotedbl#n
\th#n
\TH#n