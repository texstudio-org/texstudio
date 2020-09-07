# unicode-math package
# rend3r, 6 Sep 2020
# muzimuzhi, 7 Sep 2020

# The 2946 math symbol commands listed in
#     https://github.com/wspr/unicode-math/blob/master/unicode-math-table.tex
# and documented in `texdoc unimath-symbols` are not recorded. Perhaps those
# commonly used and not yet recorded in latex-document.cwl and amssymb.cwl can 
# be added.

#include:expl3
#include:xparse
#include:l3keys2e
#include:fontspec
#include:fix-cm
#include:amsmath
# NOTE: Load "amssymb.cwl" for auto-completion, not for actual code dependency.
#include:amssymb

\unimathsetup{options%keyvals}
\setmathfont{font}
\setmathfont[font features]{font}#*
\setmathfont{font}[font features%keyvals]
\setmathfont[font features]{font}[font features%keyvals]#*
\setmathfontface{cmd}{font}#d
\setmathfontface{cmd}[font features]{font}#*d
\setmathfontface{cmd}{font}[font features%keyvals]#d
\setmathfontface{cmd}[font features]{font}[font features%keyvals]#d
\setoperatorfont{cmd}
\NewNegationCommand{symbol or cmd}{definition}

#keyvals:\unimathsetup
normal-style=#ISO,TeX,french,upright,literal
math-style=#ISO,TeX,french,upright,literal
bold-style=#ISO,TeX,upright,literal
sans-style=#italic,upright,literal
nabla=#italic,upright,literal
partial=#italic,upright,literal
colon=#TeX,literal
slash-delimiter=#ascii,frac,div
active-frac=#small,normalsize
mathrm=#text,sym
mathup=#text,sym
mathit=#text,sym
mathsf=#text,sym
mathbf=#text,sym
mathtt=#text,sym
trace=#on,debug,off
warnings-off=
#endkeyvals

#keyvals:\setmathfont#c,\setmathfontface#c
range=
script-font=
sscript-font=
script-features=
sscript-features=
version=
# and all the keys inherited from fontspec
#endkeyvals

\symnormal{text}#*m
\symliteral{text}#*m
\symbb{text}#*m
\symbbit{text}#*m
\symcal{text}#*m
\symscr{text}#*m
\symfrak{text}#*m
\symsfup{text}#*m
\symsfit{text}#*m
\symbfsf{text}#*m
\symbfup{text}#*m
\symbfit{text}#*m
\symbfcal{text}#*m
\symbfscr{text}#*m
\symbffrak{text}#*m
\symbfsfup{text}#*m
\symbfsfit{text}#*m
