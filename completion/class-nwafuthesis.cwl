# nwafuthesis class
# Matthew Bertucci 2023/04/19 for v1.25


#include:xtemplate
#include:l3keys2e
#include:class-ctexbook
#include:xeCJK
#include:amsmath
#include:unicode-math
#include:geometry
#include:fancyhdr
#include:titletoc
#include:footmisc
#include:ntheorem
# loads thmmarks option of ntheorem
#include:enumitem
# loads shortlabels option of enumitem
#include:graphicx
#include:caption
#include:bicaption
#include:xcolor
#include:biblatex
# loads style=gb7714-NWAFU option of biblatex
#include:hyperref
#include:pifont

#keyvals:\documentclass/nwafuthesis#c
type=#doctor,master,bachelor
oneside
twoside
draft#true,false
#endkeyvals

\nwafuset{键值列表%keyvals}

#keyvals:\nwafuset#c
style={%<键值列表%>}
style/font=#garamond,libertinus,lm,palatino,times,times*,none
style/cjk-font=#adobe,fandol,founder,mac,sinotype,sourcehan,windows,none
style/font-size=#-4,5
style/fullwidth-stop=#catcode,mapping,false
style/footnote-style=#plain,libertinus,libertinus*,libertinus-sans,pifont,pifont*,pifont-sans,pifont-sans*,xits,xits-sans,xits-sans*
style/hyperlink=#border,color,none
style/hyperlink-color=#default,classic,elegant,fantasy,material,business,science,summer,autumn,graylevel,prl
style/bib-resource={%<文件%>}
style/logo={%<文件%>}
style/logo-size=##L
style/logo-size={%<宽度,高度%>}
style/auto-make-cover#true,false
style/withchapter#true,false
style/withsig#true,false
style/anonymous#true,false
style/chapnum=#zh,en
info={%<键值列表%>}
info/degree=#academic,professional
info/btype=#paper,design
info/title={%<中文标题%>}
info/title*={%<英文标题%>}
info/author={%<姓名%>}
info/author*={%<英文姓名或拼音%>}
info/supervisor={%<姓名%>}
info/supervisor*={%<英文姓名或拼音%>}
info/cosupervisor={%<姓名%>}
info/cosupervisor*={%<英文姓名或拼音%>}
info/department={%<名称%>}
info/department*={%<英文名称%>}
info/major={%<名称%>}
info/major*={%<英文名称%>}
info/researchfield={%<名称%>}
info/researchfield*={%<英文名称%>}
info/professionaltype={%<名称%>}
info/professionaltype*={%<英文名称%>}
info/professionalfield={%<名称%>}
info/professionalfield*={%<英文名称%>}
info/mastertype={%<研究生学位英文名称%>}
info/student-id={%<数字%>}
info/class-id={%<数字%>}
info/grade={%<数字%>}
info/enroll={%<数字%>}
info/school-id={%<数字%>}
info/date={%<日期%>}
info/date*={%<英文日期%>}
info/defensedate={%<日期%>}
info/secret-level=#none,i,ii,iii,iv
info/instructors={%<成员 1, 成员 2, ...%>}
info/defensecommittees={%<{单位, 姓名, 职称}, {单位, 姓名, 职称}, ...%>}
info/foundation={%<{来源, 名称, 编号}, {来源, 名称, 编号}, ...%>}
info/clc={%<分类号%>}
info/udc={%<UDC码%>}
abstract={%<键值列表%>}
abstract/abstractfile={%<中文摘要文件名%>}
abstract/abstractfile*={%<英文摘要文件名%>}
abstract/keywords={%<中文关键字%>}
abstract/keywords*={%<英文关键字%>}
abstract/notationfile={%<主要符号对照表文件名%>}
theorem={%<键值列表%>}
theorem/style=#plain,margin,change,break,marginbreak,changebreak
theorem/header-font={%<字体%>}
theorem/body-font={%<字体%>}
theorem/qed={%<符号%>}
theorem/counter={%<计数器%>}
#endkeyvals

\frontmatter[编号格式]
\frontmatter*
\frontmatter*[编号格式]
\mainmatter*

\begin{axiom}
\begin{axiom}[小标题%text]
\end{axiom}
\begin{corollary}
\begin{corollary}[小标题%text]
\end{corollary}
\begin{definition}
\begin{definition}[小标题%text]
\end{definition}
\begin{example}
\begin{example}[小标题%text]
\end{example}
\begin{lemma}
\begin{lemma}[小标题%text]
\end{lemma}
\begin{proof}
\begin{proof}[小标题%text]
\end{proof}
\begin{theorem}
\begin{theorem}[小标题%text]
\end{theorem}

\newtheorem{envname}{title%plain}#N
\newtheorem[options%keyvals]{envname}{title%plain}#N
\newtheorem*{envname}{title%plain}#N
\newtheorem*[options%keyvals]{envname}{title%plain}#N

#keyvals:\newtheorem,\newtheorem*
style=#plain,margin,change,break,marginbreak,changebreak
header-font={%<字体%>}
body-font={%<字体%>}
qed={%<符号%>}
counter={%<计数器%>}
#endkeyvals

\bibmatter
\bibmatter*
\begin{acknowledgement}
\end{acknowledgement}
\begin{resume}
\end{resume}
\researchitem
\researchitem[个人简历分类名称]
\begin{publications}
\end{publications}
\begin{achievements}
\end{achievements}

\nwafuthesis
\datezh
\dateen
\fakebold{文字内容%text}
\fakebold[加粗系数]{文字内容%text}

\makecoveri#*
\makecoverii#*
\makecoveriii#*
\makecoveriv#*
\makecoverv#*
\makecovervi#*
\makecovervii#*
\makecovers#*
\makefront#*

\begin{abstract*}
\end{abstract*}
\begin{notation}#\tabular
\begin{notation}[cols]#\tabular
\end{notation}

\cleardoublepage[页面风格]

# not documented
\gbcaselocalset#S
\nwafufoot[places]{footer}#S
\nwafufoot{footer}#S
\nwafuhead[places]{header}#S
\nwafuhead{header}#S
\NWAFUNumberLine{arg}#S
\publicationskip#S
\resumitem#S
\resumitem[opt]#S
\tocrule*{arg}#S
\tocrule{arg}#S

# from shortlabels option of enumitem
#keyvals:\begin{enumerate}#c,\begin{itemize}#c,\begin{description}#c,\begin{enumerate*}#c,\begin{itemize*}#c,\begin{description*}#c
A
a
I
i
1
#endkeyvals

# from thmmarks option of ntheorem
\theoremsymbol{symbol}
\theendNonectr#S
\thecurrNonectr#S
\ifsetendmark#S
\setendmarktrue#S
\setendmarkfalse#S

# from style=gb7714-NWAFU option of biblatex
#keyvals:\usepackage/biblatex#c,\ExecuteBibliographyOptions#c
# from gb7714-NWAFU.bbx (loads gb7714-2015.bbx)
citexref#true,false
gbmedium#true,false
gbannote#true,false
gbfieldtype#true,false
gbfootbibfmt#true,false
gbfnperpage#true,false
gbfootbib#true,false
gbstyle#true,false
gbtype#true,false
gbcodegbk#true,false
gbstrict#true,false
gbtitlelink#true,false
gbctexset#true,false
gbnoauthor#true,false
gbfieldstd#true,false
gbpub#true,false
gbpunctin#true,false
gblanorder=#chineseahead,englishahead,%<string%>
gbcitelocal=#gb7714-2015,chinese,english
gbbiblocal=#gb7714-2015,chinese,english
gblocal=#gb7714-2015,chinese,english
gbbiblabel=#bracket,parens,plain,dot,box,circle
gbnamefmt=#uppercase,lowercase,givenahead,familyahead,pinyin,quanpin,reverseorder
gbalign=#right,left,center,gb7714-2015,gb7714-2015ay
# from gb7714-NWAFU.cbx (loads gb7714-2015ay.cbx)
gblabelref#true,false
gbcitelabel=#bracket,parens,plain,dot,box,circle
#endkeyvals
# from gb7714-NWAFU.bbx (loads gb7714-2015.bbx)
\nwafubibfont#*
# from gb7714-2015.bbx
#include:xstring
\versionofgbtstyle#S
\versionofbiblatex#S
\defversion{arg1}{arg2}{arg3}#S
\switchversion{arg1}{arg2}#S
\testCJKfirst{field}#*
\multivolparser{arg}#*
\multinumberparser{arg}#*
\BracketLift#*
\gbleftparen#*
\gbrightparen#*
\gbleftbracket#*
\gbrightbracket#*
\execgbfootbibfmt#*
\SlashFont#*
\footbibmargin#*
\footbiblabelsep#*
\execgbfootbib#*
\thegbnamefmtcase#*
\mkgbnumlabel{arg}#*
\thegbalignlabel#*
\thegbcitelocalcase#*
\thegbbiblocalcase#*
\lancnorder#S
\lanjporder#S
\lankrorder#S
\lanenorder#S
\lanfrorder#S
\lanruorder#S
\execlanodeah#*
\thelanordernum#*
\execlanodudf{string}#*
\setlocalbibstring{string}{text}
\setlocalbiblstring{string}{text}
\dealsortlan#*
\bibitemindent#*
\biblabelextend#*
\setaligngbstyle#*
\lengthid#*
\lengthlw#*
\itemcmd#*
\setaligngbstyleay#*
\publocpunct#*
\bibtitlefont#*
\bibauthorfont#*
\bibpubfont#*
\execgbfdfmtstd#*
\aftertransdelim#*
\gbcaselocalset#*
\gbpinyinlocalset#*
\gbquanpinlocalset#*
\defdoublelangentry{match}{fieldvalue}
\entrykeya#S
\entrykeyb#S
\userfieldabcde#S
# from gb7714-NWAFU.cbx (loads gb7714-2015ay.cbx)
\mkbibleftborder#*
\mkbibrightborder#*
\compextradelim#*
\upcite{bibid}#*C
\upcite[postnote]{bibid}#*C
\upcite[prenote][postnote]{bibid}#*C
\pagescite{bibid}#C
\pagescite[postnote]{bibid}#C
\pagescite[prenote][postnote]{bibid}#C
\yearpagescite{bibid}#C
\yearpagescite[postnote]{bibid}#C
\yearpagescite[prenote][postnote]{bibid}#C
\yearcite{bibid}#C
\yearcite[postnote]{bibid}#C
\yearcite[prenote][postnote]{bibid}#C
\authornumcite{bibid}#C
\authornumcite[postnote]{bibid}#C
\authornumcite[prenote][postnote]{bibid}#C
\citet{bibid}#*C
\citet[postnote]{bibid}#*C
\citet[prenote][postnote]{bibid}#*C
\citep{bibid}#*C
\citep[postnote]{bibid}#*C
\citep[prenote][postnote]{bibid}#*C
\citets{bibid}{bibid}#*C
\citets(post){bibid}{bibid}#*C
\citets(pre)(post){bibid}{bibid}#*C
\citets(pre)(post)[post]{bibid}[post]{bibid}#*C
\citets[post]{bibid}[post]{bibid}#*C
\citets[pre][post]{bibid}[pre][post]{bibid}#*C
\citets(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#*C
\citetns{bibid}#*C
\citetns[postnote]{bibid}#*C
\citetns[prenote][postnote]{bibid}#*C
\citepns{bibid}#*C
\citepns[postnote]{bibid}#*C
\citepns[prenote][postnote]{bibid}#*C
\inlinecite{bibid}#*C
\inlinecite[postnote]{bibid}#*C
\inlinecite[prenote][postnote]{bibid}#*C
\citec{bibid}#C
\citec[postnote]{bibid}#C
\citec[prenote][postnote]{bibid}#C
\citecs{bibid}{bibid}#C
\citecs(post){bibid}{bibid}#*C
\citecs(pre)(post){bibid}{bibid}#C
\citecs(pre)(post)[post]{bibid}[post]{bibid}#*C
\citecs[post]{bibid}[post]{bibid}#*C
\citecs[pre][post]{bibid}[pre][post]{bibid}#*C
\citecs(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C
\authornumcites{bibid}{bibid}#C
\authornumcites(post){bibid}{bibid}#*C
\authornumcites(pre)(post){bibid}{bibid}#C
\authornumcites(pre)(post)[post]{bibid}[post]{bibid}#*C
\authornumcites[post]{bibid}[post]{bibid}#*C
\authornumcites[pre][post]{bibid}[pre][post]{bibid}#*C
\authornumcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C
