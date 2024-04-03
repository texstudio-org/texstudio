# minim-mp package
# Matthew Bertucci 2024/04/03 for v1.6

#include:luatex

#keyvals:\usepackage/minim-mp#c
luamplib
#endkeyvals

#ifOption:luamplib
\mplibtextextlabel{choice%keyvals}
\mplibshowlog{choice%keyvals}
\mplibcodeinherit{choice%keyvals}
#keyvals:\mplibtextextlabel#c,\mplibshowlog#c,\mplibcodeinherit#c
enable
disable
#endkeyvals
\mplibsetformat{format name%keyvals}
#keyvals:\mplibsetformat#c
plain
metafun
#endkeyvals
\mplibnumbersystem{type%keyvals}
#keyvals:\mplibnumbersystem#c
scaled
double
decimal
#endkeyvals
\everymplib{metapost code}
\everymplib[instance name]{metapost code}
\everyendmplib{metapost code%definition}
\everyendmplib[instance name]{metapost code}
#endif

# from minim-mp.sty
\begin{metapost}
\begin{metapost}[options]
\end{metapost}

\newmetapostenvironment{envname}#N
\newmetapostenvironment[options]{envname}#N

\mpcolor{color}

\minimpcolor{color}#S
\dominimpcolor{color}{arg}#S
\mpcolorspectoks#S
\mpcolorruntoks#S
\mpcolorvaltoks#S

# from minim-mp.tex (loads minim-alloc and minim-pdfresources)
\directmetapost{metapost code}
\directmetapost[options]{metapost code}
\newmetapostinstance{cmd}#d
\newmetapostinstance[options]{cmd}#d

\convertmpcolours#S
\RtoG#S
\GtoG#S
\BtoG#S
\everymaketext#S

# from minim-alloc.tex
\voidbox#*
\ignore{arg}#*
\unbrace{arg}#*
\firstoftwo{arg1}{arg2}#*
\secondoftwo{arg1}{arg2}#*
\nextif#*
\nextifx#*
\nextifcat#*
\withoptions[default]{code}#*
\splitcommalist{code}{list}#*
\unset#*
\setluachunkname{cmd}{actual name}#*d

\hairspace#S
\threeperemspace#S
\fourperemspace#S
\decompressedpdf#S

# from minim-pdfresources.tex
# no user commands
