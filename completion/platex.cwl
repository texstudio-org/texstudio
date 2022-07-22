# pLaTeX commands
# Matthew Bertucci 2022/07/21 for v2021-11-15

#include:ptex
#include:latex-document
#include:latex-dev

# use of #* roughly tracks latex-document.cwl and latex-dev.cwl

## from plcore.ltx
\pfmtname#*
\pfmtversion#*
\plIncludeInRelease{date}{command}{description}#*
\plEndIncludeInRelease#*
\Cht#*
\cht#*
\Cdp#*
\cdp#*
\Cwd#*
\cwd#*
\Cvs#*
\cvs#*
\Chs#*
\chs#*
\cHT#*
\afont#*
\tstrutbox#*
\zstrutbox#*
\ystrutbox#*
\tstrut#*
\zstrut#*
\ystrut#*
\DeclareYokoKanjiEncoding{encoding}{text-settings}{math-settings}#*
\DeclareTateKanjiEncoding{encoding}{text-settings}{math-settings}#*
\DeclareKanjiEncodingDefaults{text-settings}{math-settings}#*
\KanjiEncodingPair{encoding1}{encoding2}#*
\DeclareKanjiFamily{encoding}{family}{loading-settings}#*
\DeclareKanjiSubstitution{encoding}{family}{series}{shape}#*
\DeclareErrorKanjiFont{encoding}{family}{series}{shape}{size}#*
\reDeclareMathAlphabet{math-alph%cmd}{latin-math-alph%definition}{japanese-math-alph%definition}#*d
\DeclareRelationFont{enc1}{fam1}{series1}{shape1}{enc2}{fam2}{series2}{shape2}#*
\SetRelationFont{enc1}{fam1}{series1}{shape1}{enc2}{fam2}{series2}{shape2}#*
\userelfont
\adjustbaseline
\romanencoding{encoding}
\kanjiencoding{encoding}
\romanfamily{family}
\kanjifamily{family}
\romanseries{series}
\kanjiseries{series}
\romanseriesforce{series}#*
\kanjiseriesforce{series}#*
\romanshape{shape}
\kanjishape{shape}
\romanshapeforce{shape}#*
\kanjishapeforce{shape}#*
\usekanji{encoding}{family}{series}{shape}#*
\useroman{encoding}{family}{series}{shape}#*
\kanjiseriesdefault#*
\mcfamily
\gtfamily
\mathmc{text%plain}#m
\mathgt{text%plain}#m
\textmc{text}
\textgt{text}
\fixcompositeaccent#*
\nofixcompositeaccent#*
\<#*
\removejfmglue#*
\iftombow#*
\tombowfalse#*
\tombowtrue#*
\iftombowdate#*
\tombowdatetrue#*
\tombowdatefalse#*
\maketombowbox#*
\printglossary
\hour#*
\minute#*
# deprecated
\DeclareKanjiEncoding{encoding}{text-settings}{math-settings}#S

## from pldefs.ltx
\mcdefault#*
\gtdefault#*
\kanjiencodingdefault#*
\kanjifamilydefault#*
\kanjiseriesdefault#*
\kanjishapedefault#*
