# arabluatex package
# Matthew Bertucci 4/8/2022 for v1.20

#include:iftex
#include:xkeyval
#include:xcolor
#include:luacolor
#include:etoolbox
#include:arabluatex-patch
#include:fontspec
#include:luacode
#include:xparse
#include:adjustbox
#include:xstring
#include:lua-ul

#keyvals:\usepackage/arabluatex#c
voc
fullvoc
novoc
trans
export#true,false
#endkeyvals

\arabicfont
\SetArbEasy
\SetArbEasy*
\SetArbDflt
\SetArbDflt*

\arb{Arabic text%definition}
\arb[mode%keyvals]{Arabic text%definition}
\begin{arab}
\begin{arab}[mode%keyvals]
\end{arab}

#keyvals:\arb,\begin{arab}
voc
fullvoc
novoc
trans
#endkeyvals

\arbnull
\abjad{number}
\aemph{Arabic text%definition}
\aemph*{Arabic text%definition}
\aoline{Arabic text%definition}
\aoline*{Arabic text%definition}
\auline{Arabic text%definition}

\begin{arabverse}
\begin{arabverse}[options%keyvals]
\end{arabverse}

#keyvals:\begin{arabverse}
mode=#voc,fullvoc,novoc,trans
width=##L
gutter=##L
metre=%<name%>
delim#true,false
utf#true,false
color=#%color
export#true,false
#endkeyvals

\SetHemistichDelim{delimiter}
\bayt{ṣadr}{aǧuz}\\
\bayt{ṣadr}[tadwīr]{aǧuz}\\
\bayt*{ṣadr}{aǧuz}\\#S
\bayt*{ṣadr}[tadwīr]{aǧuz}\\#S
\StretchBayt
\StretchBayt[true|false]
\abraces{Arabic text%definition}

\arbmark{shorthand%keyvals}
\arbmark[rl|lr]{shorthand%keyvals}

#keyvals:\arbmark#c
bismillah
salam
slm
jalla
%arbmark
#endkeyvals

\newarbmark{shorthand%specialDef}{RTL codepoint}{LTR codepoint}#s#%arbmark
\ayah{3-digit number}
\arbcolor{Arabic text%definition}
\arbcolor[color]{Arabic text%definition}

\SetTranslitConvention{mode%keyvals}

#keyvals:\SetTranslitConvention
dmg
loc
arabica
#endkeyvals

\SetTranslitStyle{style commands}
\SetTranslitFont{font selection commands}
\uc{word%definition}
\prname{Arabic proper name%definition}
\prname*{Arabic proper name%definition}#*
\arbup{Arabic text%definition}#*
\NoArbUp
\ArbUpDflt
\SetArbUp{formatting directives}

\SetInputScheme{scheme%keyvals}

#keyvals:\SetInputScheme
arabtex
buckwalter
#endkeyvals

\txarb{Unicode Arabic}
\begin{txarab}
\end{txarab}

\LR{arg%text}
\RL{arg%text}
\LRfootnote{text}
\RLfootnote{text}
\FixArbFtnmk
\LRmarginpar{right%text}
\LRmarginpar[left%text]{right%text}
\setRL
\setLR
\MkArbBreak{list of csnames}
\MkArbBreak*{list of csnames}
\SetArbOutSuffix{suffix}
\begin{arabexport}
\end{arabexport}
\arbpardir#*
\ArbOutFile{argument}
\ArbOutFile[newline]{argument}
\ArbOutFile*{argument}
\ArbOutFile*[newline]{argument}

# not in main documentation
\SetDefaultIndex{file}#*
\SetIndexMode{mode}#*
\Uc{word%definition}#*
\arind{root}#*
\arind[opt%keyvals]{root}#*
#keyvals:\arind
index
root
form
#endkeyvals
\begin{txarabtr}#*
\end{txarabtr}#*
\txtrans{arg}#*