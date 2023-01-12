# jlreq class
# Matthew Bertucci 2022/11/28 for release 2022/11/28

#include:l3keys2e
#include:etoolbox
#include:jlreq-helpers
#include:luatexja
#include:luatexja-adjust
#include:everyhook
#include:lmodern
#include:jlreq-complements

#keyvals:\documentclass/jlreq#c
uplatex
platex
lualatex
tate
report
book
oneside
twoside
onecolumn
twocolumn
titlepage
notitlepage
draft
final
landscape
openright
openany
leqno
fleqn
disablejfam
paper=#a0paper,a1paper,a2paper,a3paper,a4paper,a5paper,a6paper,a7paper,a8paper,a9paper,a10paper,b0paper,b1paper,b2paper,b3paper,b4paper,b5paper,b6paper,b7paper,b8paper,b9paper,b10paper,c2paper,c3paper,c4paper,c5paper,c6paper,c7paper,c8paper,b0j,b1j,b2j,b3j,b4j,b5j,b6j,b7j,b8j,b9j,b10j,letterpaper,legalpaper,executivepaper
fontsize=##L
jafontsize=##L
jafontscale=%<factor%>
line_length=##L
number_of_lines
gutter=##L
fore-edge=##L
head_space=##L
foot_space=##L
baselineskip=##L
linegap=##L
headfoot_sidemargin=##L
column_gap=##L
sidenote_length=##L
open_bracket_pos=#zenkaku_tentsuki,zenkakunibu_nibu,nibu_tentsuki
hanging_punctuation
use_reverse_pagination
#endkeyvals

#ifOption:book
\chapter{title}#L1
\chapter{title}[subtitle%text]#L1
\chapter[short title]{title}#L1
\chapter[short title]{title}[subtitle%text]#L1
\chapter*{title}#L1
\chapter*{title}[subtitle%text]#L1
\thechapter#*
\chaptermark{code}#*
\frontmatter
\mainmatter
\backmatter
#endif
#ifOption:article_type=book
\chapter{title}#L1
\chapter{title}[subtitle%text]#L1
\chapter[short title]{title}#L1
\chapter[short title]{title}[subtitle%text]#L1
\chapter*{title}#L1
\chapter*{title}[subtitle%text]#L1
\thechapter#*
\chaptermark{code}#*
\frontmatter
\mainmatter
\backmatter
#endif
#ifOption:report
\chapter{title}#L1
\chapter{title}[subtitle%text]#L1
\chapter[short title]{title}#L1
\chapter[short title]{title}[subtitle%text]#L1
\chapter*{title}#L1
\chapter*{title}[subtitle%text]#L1
\thechapter#*
\chaptermark{code}#*
#endif
#ifOption:article_type=report
\chapter{title}#L1
\chapter{title}[subtitle%text]#L1
\chapter[short title]{title}#L1
\chapter[short title]{title}[subtitle%text]#L1
\chapter*{title}#L1
\chapter*{title}[subtitle%text]#L1
\thechapter#*
\chaptermark{code}#*
#endif

\jlreqsetup{options%keyvals}

#keyvals:\jlreqsetup#c
reference_mark=#inline,interlinear
footnote_second_indent=##L
sidenote_type=#number,symbol
sidenote_symbol=%<symbol%>
sidenote_keyword_font=%<font commands%>
endnote_second_indent=##L
endnote_position=#headings,paragraph,{%<list of _<sectionname>s%>}
caption_font=%<font commands%>
caption_label_font=%<font commands%>
caption_after_label_space=##L
caption_label_format={%<code%>}
caption_align=#left,right,center,bottom,top
quote_indent=##L
quote_end_indent
quote_beforeafter_space
quote_fontsize=#normalsize,small,footnotesize,scriptsize,tiny
itemization_beforeafter_space=##L
itemization_itemsep=##L
theorem_beforeafter_space=##L
theorem_label_font=%<font commands%>
theorem_font=%<font commands%>
frontmatter_pagebreak=#cleardoublepage,clearpage
frontmatter_counter={%<counter%>={value=%<integer%>,the=%<code%>,restore=%<true|false%>}%<,...%>}
frontmatter_heading={%<sectionname%>={%<settings%>}%<,...%>}
frontmatter_pagestyle={%<<pagestyle>,restore=<true|false>%>}
frontmatter_pagination={%<<numstyle>,continuous,independent%>}
frontmatter_precode=%<code%>
frontmatter_postcode=%<code%>
mainmatter_pagebreak=#cleardoublepage,clearpage
mainmatter_counter={%<counter%>={value=%<integer%>,the=%<code%>}%<,...%>}
mainmatter_heading={%<sectionname%>={%<settings%>}%<,...%>}
mainmatter_pagestyle=%<pagestyle%>
mainmatter_pagination=%<numstyle%>
mainmatter_precode=%<code%>
mainmatter_postcode=%<code%>
backmatter_pagebreak=#cleardoublepage,clearpage
backmatter_counter={%<counter%>={value=%<integer%>,the=%<code%>}%<,...%>}
backmatter_heading={%<sectionname%>={%<settings%>}%<,...%>}
backmatter_pagestyle=%<pagestyle%>
backmatter_pagination={%<<numstyle>,continuous,independent%>}
backmatter_precode=%<code%>
backmatter_postcode=%<code%>
appendix_counter={%<counter%>={value=%<integer%>,the=%<code%>}%<,...%>}
appendix_heading={%<sectionname%>={%<settings%>}%<,...%>}
appendix_precode=%<code%>
appendix_postcode=%<code%>
#endkeyvals

\part{title}[subtitle%text]#L0
\part[short title]{title}[subtitle%text]#L0
\part*{title}[subtitle%text]#L0
\section{title}[subtitle%text]#L2
\section[short title]{title}[subtitle%text]#L2
\section*{title}[subtitle%text]#L2
\subsection{title}[subtitle%text]#L3
\subsection[short title]{title}[subtitle%text]#L3
\subsection*{title}[subtitle%text]#L3
\subsubsection{title}[subtitle%text]#L4
\subsubsection[short title]{title}[subtitle%text]#L4
\subsubsection*{title}[subtitle%text]#L4

\sidenote{heading%text}{text}
\sidenotemark{heading%text}#*
\sidenotemark[number]{heading%text}#*
\sidenotetext{heading%text}{text}#*
\sidenotetext[number]{heading%text}{text}#*
\endnote{text}
\endnote[number]{text}
\endnotemark#*
\endnotemark[number]#*
\endnotetext{text}#*
\endnotetext[number]{text}#*
\theendnotes
\warichu{text}
\warichu*{text}
\tatechuyoko{text}
\tatechuyoko*{text}
\jidori{width}{text}
\akigumi{width}{text}
\jafontsize{size}{skip}
\jlreqkanjiskip#*
\jlreqxkanjiskip#*

\NewTobiraHeading{sectionname}{level}{options%keyvals}
\RenewTobiraHeading{sectionname}{level}{options%keyvals}
\ProvideTobiraHeading{sectionname}{level}{options%keyvals}
\DeclareTobiraHeading{sectionname}{level}{options%keyvals}

#keyvals:\NewTobiraHeading#c,\RenewTobiraHeading#c,\ProvideTobiraHeading#c,\DeclareTobiraHeading#c,\ModifyHeading#c
type=#han,naka
pagestyle=%<pagestyle%>
label_format=%<code%>
format=%<code%>
number#true,false
#endkeyvals

\NewBlockHeading{sectionname}{level}{options%keyvals}
\RenewBlockHeading{sectionname}{level}{options%keyvals}
\ProvideBlockHeading{sectionname}{level}{options%keyvals}
\DeclareBlockHeading{sectionname}{level}{options%keyvals}

#keyvals:\NewBlockHeading#c,\RenewBlockHeading#c,\ProvideBlockHeading#c,\DeclareBlockHeading#c,\ModifyHeading#c
font=%<font commands%>
subtitle_font=%<font commands%>
label_format=%<code%>
subtitle_format=%<code%>
format=%<code%>
align=#left,center,right
indent=##L
end_indent=##L
after_label_space=##L
second_heading_text_indent=##L
subtitle_indent=##L
subtitle_break#true,false
allowbreak_if_evenpage#true,false
pagebreak=#clearpage,cleardoublepage,clearcolumn,nariyuki,begin_with_odd_page,begin_with_even_page
pagestyle=%<pagestyle%>
afterindent#true,false
column_spanning#true,false
number#true,false
lines=%<integer%>
before_lines=%<integer%>
after_lines=%<integer%>
before_space=##L
after_space=##L
#endkeyvals

\SetBlockHeadingSpaces{specs}

\NewRuninHeading{sectionname}{level}{options%keyvals}
\RenewRuninHeading{sectionname}{level}{options%keyvals}
\ProvideRuninHeading{sectionname}{level}{options%keyvals}
\DeclareRuninHeading{sectionname}{level}{options%keyvals}

#keyvals:\NewRuninHeading#c,\RenewRuninHeading#c,\ProvideRuninHeading#c,\DeclareRuninHeading#c,\ModifyHeading#c
font=%<font commands%>
indent=##L
after_label_space=##L
label_format=%<code%>
after_space=##L
number#true,false
#endkeyvals

\NewCutinHeading{sectionname}{level}{options%keyvals}
\RenewCutinHeading{sectionname}{level}{options%keyvals}
\ProvideCutinHeading{sectionname}{level}{options%keyvals}
\DeclareCutinHeading{sectionname}{level}{options%keyvals}
\ModifyHeading{sectionname}{options%keyvals}

#keyvals:\NewCutinHeading#c,\RenewCutinHeading#c,\ProvideCutinHeading#c,\DeclareCutinHeading#c,\ModifyHeading#c
font=%<font commands%>
indent=##L
after_space=##L
onelinemax=##L
twolinemax=##L
#endkeyvals

\SaveHeading{sectionname}{command}#d

#keyvals:\pagestyle#c,\thispagestyle#c
%jlreqpagestyle
#endkeyvals

\NewPageStyle{name%specialDef}{options%keyvals}#s#%jlreqpagestyle
\RenewPageStyle{name}{options%keyvals}
\ProvidePageStyle{name%specialDef}{options%keyvals}#s#%jlreqpagestyle
\DeclarePageStyle{name%specialDef}{options%keyvals}#s#%jlreqpagestyle
\ModifyPageStyle{pagestyle}{options%keyvals}

#keyvals:\NewPageStyle#c,\RenewPageStyle#c,\ProvidePageStyle#c,\DeclarePageStyle#c,\ModifyPageStyle#c
yoko
tate
running_head_font=%<font commands%>
nombre_font=%<font commands%>
running_head_position=
nombre_position=
nombre=%<code%>
odd_running_head=%<code%>
even_running_head=%<code%>
mark_format={odd=%<code%>,even=%<code,_<sectionname>=code,...%>}
running_head_ii_font=%<font commands%>
nombre_ii_font=%<font commands%>
running_head_ii_position=
nombre_ii_position=
nombre_ii=%<code%>
clear_markcommand#true,false
#endkeyvals

# not documented
\ifjlreqadjustreferencemark#S
\if西暦#*
\inlinenote*{text}
\inlinenote{text}
\inlinenotesize#*
\jaspace{type}#*
\jlreqadjustreferencemarkfalse#S
\jlreqadjustreferencemarktrue#S
\jlreqHeadingLabel#*
\jlreqHeadingSubtitle#*
\jlreqHeadingText#*
\jlreqparindent#*
\jlreqtateheadlength#*
\jlreqyokoheadlength#*
\lastnodechar#*
\thejlreqreversepage#*
\toclineskip#*
\和暦
\西暦
\西暦false#S
\西暦true#S
