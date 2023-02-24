# ifptex package
# Matthew Bertucci 2023/02/23 for v2.2a

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
\ifstrictplatex
\ifstrictuplatex

\RequirepTeX
\RequireStrictpTeX
\RequireupTeX
\RequireStrictupTeX
\RequireNativeupTeX
\RequirepTeXng
\RequireStrictpTeXng
\RequireStrictpLaTeX
\RequireStrictupLaTeX

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
