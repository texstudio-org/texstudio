# ifptex package
# Matthew Bertucci 1/21/2022 for v2.1

#include:iftex

\ifptex
\ifpTeX#*
\ifuptex
\ifupTeX#*
\ifnativeuptex
\ifnativeupTeX#*
\ifptexng
\ifpTeXng#*
\ifstrictptex
\ifstrictpTeX#*
\ifstrictuptex
\ifstrictupTeX#*
\ifstrictptexng
\ifstrictpTeXng#*

\RequirepTeX
\RequireStrictpTeX
\RequireupTeX
\RequireStrictupTeX
\RequireNativeupTeX
\RequirepTeXng
\RequireStrictpTeXng

\bxipIfptexLoaded#S

# deprecated
\ifNativeupTeX#S
\RequirenativeupTeX#S
\ifnewupTeX#S
\RequireNewupTeX#S
\RequireNativeNewupTeX#S