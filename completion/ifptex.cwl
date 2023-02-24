# ifptex package
# Matthew Bertucci 2023/02/24 for v2.2b

#include:iftex

\ifptex
\ifpTeX#S
\ifuptex
\ifupTeX#S
\ifnativeuptex
\ifnativeupTeX#S
\ifptexng
\ifpTeXng#S
\ifstrictptex
\ifstrictpTeX#S
\ifstrictuptex
\ifstrictupTeX#S
\ifstrictptexng
\ifstrictpTeXng#S
\ifstrictplatex
\ifstrictuplatex
\ifporuplatex

\RequirepTeX
\RequireStrictpTeX
\RequireupTeX
\RequireStrictupTeX
\RequireNativeupTeX
\RequirepTeXng
\RequireStrictpTeXng
\RequireStrictpLaTeX
\RequireStrictupLaTeX
\RequirepOrupLaTeX

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
