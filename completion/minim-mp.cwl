# minim-mp package
# Matthew Bertucci 2023/12/20 for v1.3

#include:luatex

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