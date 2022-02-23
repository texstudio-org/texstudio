# testidx-glossaries package
# Matthew Bertucci 2/22/2022 for v1.2

#include:testidx
#include:glossaries
#include:glossaries-mcols

## 2 Package Options ##
#keyvals:\usepackage/testidx-glossaries#c
extra
noextra
makeindex
xindy
tex
bib2gls
manual
seekey
noseekey
noglsnumbers
glsnumbers
desc
nodesc
# options passed to testidx
ascii
noascii
german
ngerman
nogerman
stripaccents
nostripaccents
sanitize
nosanitize
showmarks
hidemarks
noshowmarks
verbose
noverbose
notestencaps
testencaps
prefix
noprefix
diglyphs
nodiglyphs
#endkeyvals

#ifOption:extra
#include:glossaries-extra
#endif

#ifOption:xindy
\GlsSetXdyLanguage{language}
\GlsSetXdyLanguage[glossary type]{language}
\GlsSetXdyCodePage{code}
\GlsAddXdyCounters{counter list}
\GlsAddXdyAttribute{name}
\GlsAddXdyLocation{name}{definition}
\GlsAddXdyLocation[prefix-location]{name}{definition}
\GlsSetXdyLocationClassOrder{location names}
\GlsSetXdyMinRangeLength{integer}
\GlsSetXdyFirstLetterAfterDigits{letter}
\GlsSetXdyNumberGroupOrder{relative location}
\GlsAddLetterGroup{arg1}{arg2}
\GlsAddSortRule{arg1}{arg2}
\GlsAddXdyAlphabet{name}{definition}
\GlsAddXdyStyle{xindy style}
\GlsSetXdyStyles{xindy styles}
#endif

#ifOption:bib2gls
#include:glossaries-extra
#include:glossaries-extra-bib2gls
#endif

\tstidxloadsamples

## 3 Basic Commands ##
\tstidxmakegloss
\tstidxmakegloss[options]#*
\tstidxprintglossaries
\tstidxprintglossary
\tstidxprintglossary[options%keyvals]

#keyvals:\tstidxprintglossary#c
type=
title=
toctitle=
style=
numberedsection=#false,nolabel,autolabel
nonumberlist#true,false
nogroupskip#true,false
nopostdot#true,false
entrycounter#true,false
subentrycounter#true,false
sort=#word,letter,standard,use,def,nocase,case
#endkeyvals

# not in main documentation
\seealsoname#S
\tstidx#S
\tstidxasciibibfiles#S
\tstidxbasebibfiles#S
\tstidxbibmakegloss{arg1}#S
\tstidxdefaultmakegloss#S
\tstidxglyphfile#S
\tstidxloadglsresource{arg1}#S
\tstidxnewappopt{arg1}{arg2}{arg3}{arg4}#S
\tstidxnewapp{arg1}{arg2}{arg3}#S
\tstidxnewartbook{arg1}{arg2}{arg3}{arg4}#S
\tstidxnewartfilm{arg1}{arg2}{arg3}{arg4}#S
\tstidxnewartphrase{arg1}{arg2}{arg3}{arg4}#S
\tstidxnewartplace{arg1}{arg2}{arg3}{arg4}#S
\tstidxnewbook{arg1}{arg2}{arg3}#S
\tstidxnewcs{arg1}{arg2}{arg3}#S
\tstidxnewdigraph{arg1}{arg2}{arg3}#S
\tstidxnewencapcsn{arg1}{arg2}{arg3}#S
\tstidxnewentry{arg1}{arg2}{arg3}#S
\tstidxnewenv{arg1}{arg2}{arg3}#S
\tstidxnewfilm{arg1}{arg2}{arg3}#S
\tstidxnewindexmarker{arg1}{arg2}{arg3}#S
\tstidxnewmathsym{arg1}{arg2}#S
\tstidxnewmath{arg1}{arg2}#S
\tstidxnewnumber{arg1}{arg2}{arg3}#S
\tstidxnewperson{arg1}{arg2}{arg3}{arg4}#S
\tstidxnewphraseseealso{arg1}{arg2}{arg3}{arg4}#S
\tstidxnewphrasesee{arg1}{arg2}{arg3}{arg4}#S
\tstidxnewphrase{arg1}{arg2}{arg3}#S
\tstidxnewplace{arg1}{arg2}{arg3}#S
\tstidxnewstyopt{arg1}{arg2}{arg3}{arg4}#S
\tstidxnewstyseealso{arg1}{arg2}{arg3}{arg4}#S
\tstidxnewsty{arg1}{arg2}{arg3}#S
\tstidxnewsubphrase{arg1}{arg2}{arg3}{arg4}#S
\tstidxnewsubwordseealso{arg1}{arg2}{arg3}{arg4}{arg5}#S
\tstidxnewsubwordsee{arg1}{arg2}{arg3}{arg4}{arg5}#S
\tstidxnewsubword{arg1}{arg2}{arg3}{arg4}#S
\tstidxnewsym{arg1}{arg2}{arg3}{arg4}#S
\tstidxnewtrigraph{arg1}{arg2}{arg3}#S
\tstidxnewutfdigraph{arg1}{arg2}{arg3}{arg4}{arg5}#S
\tstidxnewutfentrytext{arg1}{arg2}{arg3}{arg4}{arg5}{arg6}{arg7}{arg8}#S
\tstidxnewutfentry{arg1}{arg2}{arg3}{arg4}{arg5}{arg6}#S
\tstidxnewutfperson{arg1}{arg2}{arg3}#S
\tstidxnewutfphrase{arg1}{arg2}{arg3}{arg4}{arg5}#S
\tstidxnewutfplace{arg1}{arg2}{arg3}{arg4}{arg5}#S
\tstidxnewutfwordseealso{arg1}{arg2}{arg3}{arg4}{arg5}{arg6}#S
\tstidxnewutfwordsee{arg1}{arg2}{arg3}{arg4}{arg5}{arg6}#S
\tstidxnewutfword{arg1}{arg2}{arg3}{arg4}{arg5}#S
\tstidxnewwordseealso{arg1}{arg2}{arg3}{arg4}#S
\tstidxnewwordsee{arg1}{arg2}{arg3}{arg4}#S
\tstidxnewword{arg1}{arg2}{arg3}#S
\tstidxnoidxmakegloss#S
\tstidxtexfiles#S
\tstidxtogls#S
\tstidxtoidx#S
\tstidxutfbibfiles#S