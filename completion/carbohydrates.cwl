# carbohydrates package
# Matthew Bertucci 11/7/2021 for v0.1

#include:etoolbox
#include:chemfig
#include:xcolor
#include:tikzlibrarydecorations.pathmorphing

\carbohydrate{spec}
\carbohydrate[options%keyvals]{spec}

\newaldose{cmd}{spec}#d
\newaldose{cmd}[options%keyvals]{spec}#d
\renewaldose{cmd}{spec}
\renewaldose{cmd}[options%keyvals]{spec}

\allose
\allose[options%keyvals]
\altrose
\altrose[options%keyvals]
\glucose
\glucose[options%keyvals]
\mannose
\mannose[options%keyvals]
\gulose
\gulose[options%keyvals]
\idose
\idose[options%keyvals]
\galactose
\galactose[options%keyvals]
\talose
\talose[options%keyvals]
\ribose
\ribose[options%keyvals]
\arabinose
\arabinose[options%keyvals]
\xylose
\xylose[options%keyvals]
\lyxose
\lyxose[options%keyvals]
\desoxyribose
\desoxyribose[options%keyvals]
\erythrose
\erythrose[options%keyvals]
\threose
\threose[options%keyvals]
\glycerinaldehyde
\glycerinaldehyde[options%keyvals]

\setcarbohydrates{options%keyvals}
\setcarbohydratedefaults{csname}{options%keyvals}

#keyvals:\carbohydrate#c,\newaldose#c,\renewaldose#c,\allose#c,\altrose#c,\glucose#c,\mannose#c,\gulose#c,\idose#c,\galactose#c,\talose#c,\ribose#c,\arabinose#c,\xylose#c,\lyxose#c,\desoxyribose#c,\erythrose#c,\threose#c,\glycerinaldehyde#c,\setcarbohydrates#c,\setcarbohydratedefaults#c
model={fischer=%<skeleton or full%>}
model=haworth
model=chair
chain
ring
ring=#true,pyranose,furanose
anomer=#alpha,beta,undetermined
length=#6,5,4,3
hexose
pentose
tetrose
triose
3d#true,false
color={%<name%>}{%<color%>}
#endkeyvals
