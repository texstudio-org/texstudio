# ifptex package
# Matthew Bertucci 4/16/2022 for v2.2

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

\upTeXguessedversion
\RequireupTeXAtLeast{version}
\RequireNativeupTeXAtLeast{version}

\bxipIfptexLoaded#S

# deprecated
\ifNativeupTeX#S
\RequirenativeupTeX#S
\ifnewupTeX#S
\RequireNewupTeX#S
\RequireNativeNewupTeX#S
