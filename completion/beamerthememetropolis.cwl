# metropolis beamertheme
# Matthew Bertucci 2/1/2022 for v1.2

# Dependency Tree:
# beamerthememetropolis.sty
# ├── etoolbox.sty
# ├── pgfopts.sty
# ├── beamercolorthememetropolis.sty
# │   └── pgfopts.sty
# ├── beamerfontthememetropolis.sty
# │   ├── etoolbox.sty
# │   ├── ifxetex.sty
# │   ├── ifluatex.sty
# │   ├── pgfopts.sty
# │   └── fontspec.sty
# ├── beamerinnerthememetropolis.sty
# │   ├── etoolbox.sty
# │   ├── keyval.sty
# │   ├── calc.sty
# │   ├── pgfopts.sty
# │   └── tikz.sty
# └── beamerouterthememetropolis.sty
#     ├── etoolbox.sty
#     ├── calc.sty
#     └── pgfopts.sty

#include:etoolbox
#include:pgfopts
#include:ifxetex
#include:ifluatex
#include:fontspec
#include:keyval
#include:calc
#include:tikz

\metroset{options%keyvals}

#keyvals:\usetheme/metropolis,\metroset
titleformat=#regular,smallcaps,allsmallcaps,allcaps
titleformat plain=#regular,smallcaps,allsmallcaps,allcaps
sectionpage=#none,simple,progressbar
subsectionpage=#none,simple,progressbar
numbering=#none,counter,fraction
progressbar=#none,head,frametitle,foot
block=#transparent,fill
background=#dark,light
titleformat title=#regular,smallcaps,allsmallcaps,allcaps
titleformat subtitle=#regular,smallcaps,allsmallcaps,allcaps
titleformat section=#regular,smallcaps,allsmallcaps,allcaps
titleformat frame=#regular,smallcaps,allsmallcaps,allcaps
#endkeyvals

\plain{title%text}#*
\plain[format%keyvals]{title%text}#*

#keyvals:\plain
regular
smallcaps
allsmallcaps
allcaps
#endkeyvals

\mreducelistspacing#*

# pgfplots integration
#keyvals:\begin{axis}#c,\begin{loglogaxis}#c,\begin{semilogxaxis}#c,\begin{semilogyaxis}#c,\addplot#c,\addplot3#c,\addplot+#c,\pgfplotsset#c,\begin{groupplot}#c,\begin{smithchart}#c,\begin{polaraxis}#c,\begin{ternaryaxis}#c
mlineplot
mbarplot
horizontal mbarplot
disable thousands separator
#endkeyvals

# from beamercolorthememetropolis.sty
mDarkBrown#B
mDarkTeal#B
mLightBrown#B
mLightGreen#B

# from beamerfontthememetropolis.sty
\thefontsnotfound#*
\checkfont{font name}#*
\iffontsavailable{font list}{true}{false}#*

# from beamerinnerthememetropolis.sty
# no user commands

# from beamerouterthememetropolis.sty
# no user commands