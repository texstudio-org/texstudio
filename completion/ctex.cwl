# ctex package
# Darcy Hu <hot123tea123@gmail.com> 2016
#modified zepinglee 30 Jan 2021
# updated 26 June 2022 for v2.5.10

#include:zhnumber

# package only keys
#keyvals:\usepackage/ctex#c
GBK
UTF8
zhmap=#true,false,zhmCJK
zihao=#-4,5,false
heading#true,false
sub3section
sub4section
scheme=#chinese,plain
linespread=%<number%>
#endkeyvals

#ifOption:heading
\CTEXnumberline{arg}#*
#endif
#ifOption:heading=true
\CTEXnumberline{arg}#*
#endif

## Sec. 4.3
\songti
\heiti
\fangsong
\kaishu
\lishu
\youyuan
\yahei
\pingfang

\ctexset{options%keyvals}

# package or \ctexset keys
#keyvals:\ctexset,\usepackage/ctex#c
fontset=#adobe,fandol,founder,mac,macnew,macold,ubuntu,windows,none
#
# Sec. 5.3
punct=#quanjiao,banjiao,kaiming,CCT,plain
space=#true,false,auto
autoindent=
#endkeyvals

# \ctexset only keys
#keyvals:\ctexset
# Sec. 5.3
linestretch=
#
# Sec. 6.1
today=#small,big,old
#
# Sec. 6.2
contentsname=%<name%>
listfigurename=%<name%>
listtablename=%<name%>
figurename=%<name%>
tablename=%<name%>
abstractname=%<name%>
indexname=%<name%>
appendixname=%<name%>
bibname=%<name%>
proofname=%<name%>
refname=%<name%>
algorithmname=%<name%>
continuation=%<name%>
#
# Sec. 7.1
part={%<settings%>}
chapter={%<settings%>}
section={%<settings%>}
subsection={%<settings%>}
subsubsection={%<settings%>}
paragraph={%<settings%>}
subparagraph={%<settings%>}
#
# Sec. 7.1
part/numbering#true,false
chapter/numbering#true,false
section/numbering#true,false
subsection/numbering#true,false
subsubsection/numbering#true,false
paragraph/numbering#true,false
subparagraph/numbering#true,false
#
secnumdepth=
#
part/name=
chapter/name=
section/name=
subsection/name=
subsubsection/name=
paragraph/name=
subparagraph/name=
#
part/number=
chapter/number=
section/number=
subsection/number=
subsubsection/number=
paragraph/number=
subparagraph/number=
#
# Sec. 7.2
part/format=%<format commands%>
chapter/format=%<format commands%>
section/format=%<format commands%>
subsection/format=%<format commands%>
subsubsection/format=%<format commands%>
paragraph/format=%<format commands%>
subparagraph/format=%<format commands%>
#
part/format+=%<format commands%>
chapter/format+=%<format commands%>
section/format+=%<format commands%>
subsection/format+=%<format commands%>
subsubsection/format+=%<format commands%>
paragraph/format+=%<format commands%>
subparagraph/format+=%<format commands%>
#
part/nameformat=%<format commands%>
chapter/nameformat=%<format commands%>
section/nameformat=%<format commands%>
subsection/nameformat=%<format commands%>
subsubsection/nameformat=%<format commands%>
paragraph/nameformat=%<format commands%>
subparagraph/nameformat=%<format commands%>
#
part/nameformat+=%<format commands%>
chapter/nameformat+=%<format commands%>
section/nameformat+=%<format commands%>
subsection/nameformat+=%<format commands%>
subsubsection/nameformat+=%<format commands%>
paragraph/nameformat+=%<format commands%>
subparagraph/nameformat+=%<format commands%>
#
part/numberformat=%<format commands%>
chapter/numberformat=%<format commands%>
section/numberformat=%<format commands%>
subsection/numberformat=%<format commands%>
subsubsection/numberformat=%<format commands%>
paragraph/numberformat=%<format commands%>
subparagraph/numberformat=%<format commands%>
#
part/numberformat+=%<format commands%>
chapter/numberformat+=%<format commands%>
section/numberformat+=%<format commands%>
subsection/numberformat+=%<format commands%>
subsubsection/numberformat+=%<format commands%>
paragraph/numberformat+=%<format commands%>
subparagraph/numberformat+=%<format commands%>
#
part/titleformat=%<format commands%>
chapter/titleformat=%<format commands%>
section/titleformat=%<format commands%>
subsection/titleformat=%<format commands%>
subsubsection/titleformat=%<format commands%>
paragraph/titleformat=%<format commands%>
subparagraph/titleformat=%<format commands%>
#
part/titleformat+=%<format commands%>
chapter/titleformat+=%<format commands%>
section/titleformat+=%<format commands%>
subsection/titleformat+=%<format commands%>
subsubsection/titleformat+=%<format commands%>
paragraph/titleformat+=%<format commands%>
subparagraph/titleformat+=%<format commands%>
#
part/aftername=%<code%>
chapter/aftername=%<code%>
section/aftername=%<code%>
subsection/aftername=%<code%>
subsubsection/aftername=%<code%>
paragraph/aftername=%<code%>
subparagraph/aftername=%<code%>
#
part/aftername+=%<code%>
chapter/aftername+=%<code%>
section/aftername+=%<code%>
subsection/aftername+=%<code%>
subsubsection/aftername+=%<code%>
paragraph/aftername+=%<code%>
subparagraph/aftername+=%<code%>
#
part/aftertitle=%<code%>
chapter/aftertitle=%<code%>
section/aftertitle=%<code%>
subsection/aftertitle=%<code%>
subsubsection/aftertitle=%<code%>
paragraph/aftertitle=%<code%>
subparagraph/aftertitle=%<code%>
#
part/aftertitle+=%<code%>
chapter/aftertitle+=%<code%>
section/aftertitle+=%<code%>
subsection/aftertitle+=%<code%>
subsubsection/aftertitle+=%<code%>
paragraph/aftertitle+=%<code%>
subparagraph/aftertitle+=%<code%>
#
part/pagestyle=
chapter/pagestyle=
#
# Sec. 7.3
section/runin#true,false
subsection/runin#true,false
subsubsection/runin#true,false
paragraph/runin#true,false
subparagraph/runin#true,false
#
section/hang#true,false
subsection/hang#true,false
subsubsection/hang#true,false
paragraph/hang#true,false
subparagraph/hang#true,false
#
part/indent=##L
chapter/indent=##L
section/indent=##L
subsection/indent=##L
subsubsection/indent=##L
paragraph/indent=##L
subparagraph/indent=##L
#
part/beforeskip=##L
chapter/beforeskip=##L
section/beforeskip=##L
subsection/beforeskip=##L
subsubsection/beforeskip=##L
paragraph/beforeskip=##L
subparagraph/beforeskip=##L
#
part/afterskip=##L
chapter/afterskip=##L
section/afterskip=##L
subsection/afterskip=##L
subsubsection/afterskip=##L
paragraph/afterskip=##L
subparagraph/afterskip=##L
#
part/fixskip#true,false
chapter/fixskip#true,false
section/fixskip#true,false
subsection/fixskip#true,false
subsubsection/fixskip#true,false
paragraph/fixskip#true,false
subparagraph/fixskip#true,false
#
part/break=
chapter/break=
section/break=
subsection/break=
subsubsection/break=
paragraph/break=
subparagraph/break=
#
part/break+=
chapter/break+=
section/break+=
subsection/break+=
subsubsection/break+=
paragraph/break+=
subparagraph/break+=
#
part/afterindent#true,false
chapter/afterindent#true,false
section/afterindent#true,false
subsection/afterindent#true,false
subsubsection/afterindent#true,false
paragraph/afterindent#true,false
subparagraph/afterindent#true,false
#
# Sec. 7.4
tocdepth=
#
part/tocline=
chapter/tocline=
section/tocline=
subsection/tocline=
subsubsection/tocline=
paragraph/tocline=
subparagraph/tocline=
#
chapter/lofskip=##L
chapter/lotskip=##L
#
appendix/numbering#true,false
appendix/name=
appendix/number=
#
declarecharrange=
clearalternatefont={%<family1,family2,...%>}
resetalternatefont={%<family1,family2,...%>}
#endkeyvals

## Sec. 7.5
\CTEXthepart#*
\CTEXthechapter#*
\CTEXthesection#*
\CTEXthesubsection#*
\CTEXthesubsubsection#*
\CTEXtheparagraph#*
\CTEXthesubparagraph#*

\CTEXifname{contents with name}{contents with name}#*

## Sec. 8.1
\zihao{number}
\ziju{factor}
\ccwd

## Sec. 8.2
\chinese{counter}
#keyvals:\pagenumbering#c
chinese
#endkeyvals
\CTEXnumber{cmd}{number}#*d
\CTEXdigits{cmd}{number}#*d

## Sec. 8.3
\CTeX#*
