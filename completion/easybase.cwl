# easybase package
# Matthew Bertucci 2022/08/12 for v1.69

#include:l3keys2e
#include:etoolbox
#include:ctex
#include:fontspec
#include:spbmark
# loads both option of spbmark
#include:ulem
#include:enumitem
# loads shortlabels and inline options of enumitem
#include:chemformula
#include:siunitx
#include:pifont
#include:geometry
#include:marginnote
#include:pdfpages
#include:multicol
#include:fancyhdr
#include:titletoc
#include:caption
#include:tabularray
#include:tabularraylibrarybooktabs
#include:listings
#include:amsthm
#include:thmtools
#include:hyperref
# loads svgnames option of xcolor
 
#keyvals:\usepackage/easybase#c
draft
paper=#a0paper,a1paper,a2paper,a3paper,a4paper,a5paper,a6paper,b0paper,b1paper,b2paper,b3paper,b4paper,b5paper,b6paper,c0paper,c1paper,c2paper,c3paper,c4paper,c5paper,c6paper,b0j,b1j,b2j,b3j,b4j,b5j,b6j,ansiapaper,ansibpaper,ansicpaper,ansidpaper,ansiepaper,letterpaper,executivepaper,legalpaper
floatpage#true,false
theorem#true,false
class=#book,article
book
article
# options passed to ctex package
GBK
UTF8
zhmap=#true,false,zhmCJK
zihao=#-4,5,false
heading#true,false
sub3section
sub4section
scheme=#chinese,plain
linespread=%<number%>
fontset=#adobe,fandol,founder,mac,macnew,macold,ubuntu,windows,none
punct=#quanjiao,banjiao,kaiming,CCT,plain
space=#true,false,auto
autoindent=
#endkeyvals

\frontmatter
\frontmatter[numstyle%keyvals]
\frontmatter*
\frontmatter*[numstyle%keyvals]

#keyvals:\frontmatter#c,\frontmatter*#c
arabic
roman
Roman
alph
Alph
#endkeyvals

\mainmatter
\mainmatter*
\backmatter
\cleardoublepage[pagestyle%keyvals]
\blankpagestyle{pagestyle%keyvals}

#keyvals:\cleardoublepage#c,\blankpagestyle#c
plain
empty
headings
myheadings
#endkeyvals

\tableofcontents[options%keyvals]
\tableofcontents[options%keyvals](代码钩子)
\tableofcontents*
\tableofcontents*[options%keyvals]
\tableofcontents*[options%keyvals](代码钩子)
\listoffigures[options%keyvals]
\listoffigures*
\listoffigures*[options%keyvals]
\listoftables[options%keyvals]
\listoftables*
\listoftables*[options%keyvals]
\listoflstlistings
\listoflstlistings[options%keyvals]
\listoflstlistings*
\listoflstlistings*[options%keyvals]

#keyvals:\tableofcontents#c,\tableofcontents*#c,\listoffigures#c,\listoffigures*#c,\listoftables#c,\listoftables*#c,\listoflstlistings#c,\listoflstlistings*#c
plan=#cn,bi,both
bicontentsname=%<英文目录标题%>
level=%<标题命令%>
multoc=%<整数%>
title={%<中文目录标题,英文目录标题%>}
bilist=#mix,new
format=%<目录标题格式%>
aftertitle=%<标题后代码%>
pagestyle=%<页面风格%>
#endkeyvals

\bichapter{title}{short english title}#L1
\bichapter[short chinese title%text]{title}{short english title}#L1
\bichapter*{title}{short english title}#L1
\bichapter*[short chinese title%text]{title}{short english title}#L1
\bisection{title}{short english title}#L2
\bisection[short chinese title%text]{title}{short english title}#L2
\bisection*{title}{short english title}#L2
\bisection*[short chinese title%text]{title}{short english title}#L2
\bisubsection{title}{short english title}#L3
\bisubsection[short chinese title%text]{title}{short english title}#L3
\bisubsection*{title}{short english title}#L3
\bisubsection*[short chinese title%text]{title}{short english title}#L3
\thebichapter#*
\thebisection#*
\thebisubsection#*

#keyvals:\ctexset
chapter/biname={%<英文目录前名字,英文目录后名字%>}
chapter/binmuber=%<英文目录数字输出命令%>
#endkeyvals

\appendix[前名字,后名字]
\appendix[前名字,后名字](数字输出命令)
\appendix(数字输出命令)

\BeforeAddBitoc{英文标题加入目录前的代码}
\BeforeAddBitoc*{英文标题加入目录前的代码}

#keyvals:\ctexset
style={%<options%>}
style/color=#none,seaside,energy,cyberpunk
style/color-every=%<HTML 颜色代码%>
style/multoc=%<整数%>
style/withpart#true,false
style/fntnumwith=#part,chapter,page
style/uppercase=#all,first,none,none*
style/brackets={%<左括号,右括号%>}
style/figurepath={%<路径名 1%>}{%<路径名 2%>}%<...{路径名 n}%>
style/hyphen-figure=%<图片连字符%>
style/hyphen-table=%<表格连字符%>
style/hyphen-listing=%<代码连字符%>
style/hyphen-equation=%<公式连字符%>
style/hyphen-every=%<连字符%>
style/spvmove=##L
style/sphmove=##L
style/sbvmove=##L
style/sbhmove=##L
style/nohmove
style/novmove
style/spcmd=%<格式命令%>
style/sbcmd=%<格式命令%>
style/spbhmove=##L
style/spbcmd={%<上标格式,下标格式%>}
style/vsep={%<上标偏移,下标偏移%>}
style/halign=#l,c,r
refset={%<options%>}
refset/linktype=#edge,colors,none
refset/linkcolor=#fresh,cutepink,navyblue,crimson
refset/linkcolor-every=%<HTML 颜色代码%>
refset/linktoc=#none,section,page,all
spread={%<options%>}
spread/line=%<数值%>
spread/table=%<数值%>
spread/math=%<数值%>
spread/caption-figure=%<数值%>
spread/caption-table=%<数值%>
spread/caption-listing=%<数值%>
spread/caption-every=%<数值%>
spread/footnote=%<数值%>
spread/every=%<数值%>
subfont={%<options%>}
subfont/caption-table=%<字体命令%>
subfont/caption-figure=%<字体命令%>
subfont/caption-listing=%<字体命令%> 
subfont/caption-every=%<字体命令%> 
subfont/footnote=%<字体命令%>
subfont/marginpar=%<字体命令%> 
bibset={%<options%>}
bibset/backend=#bibtex,biblatex
bibset/bibstyle=%<bibstyle%>
bibset/citestyle=%<标注风格%>
bibset/datafile=%<数据库列表%>
bibset/bititle=%<title%>
thmset={%<options%>}
geoset={%<options%>}
geoset/headruleskip=##L
geoset/footruleskip=##L
geoset/hdivide={%<左边距,页面文本宽度%>,%<右边距%>}
geoset/hmargin={%<左边距,右边距%>}
geoset/textheight=%<页面文本高度%>
geoset/nofoot#true,false
hdrset={%<options%>}
hdrset/chap-mark=%<标题标记%>
hdrset/sec-mark=%<标题标记%>
hdrset/subsec-mark= %<标题标记%>
hdrset/chap-label={%<距离命令%>}
hdrset/chap-label=[%<数字输出命令%>]{%<距离命令%>}
hdrset/sec-label={%<距离命令%>}
hdrset/sec-label=[%<数字输出命令%>]{%<距离命令%>}
hdrset/subsec-label={%<距离命令%>}
hdrset/subsec-label=[%<数字输出命令%>]{%<距离命令%>}
hdrset/headrule=%<横线命令%>
hdrset/footrule=%<横线命令%>
hdrset/footnoterule=%<横线命令%>
hdrset/headrulewd=##L
hdrset/footnoterulewd=##L
hdrset/footnotetype=#plain,hang,flush,bottom
hdrset/fnfirstindent=##L
hdrset/fnafterindent=##L
hdrset/fnparskip=##L
hdrset/fntext-pos=#normal,super
hdrset/fnmark-num=#plain,pifont,pifont*,pisans,pisans*,short num
hdrset/fntext-num=#plain,pifont,pifont*,pisans,pisans*,short num
hdrset/fnmarktext-num=#plain,pifont,pifont*,pisans,pisans*,short num
hdrset/fnmark-vmove=##L
hdrset/fnmark-hmove=##L
hdrset/fntext-vmove=##L
hdrset/fnmarktext-form=%<format code%>
hdrset/fncustom-format=%<format code%>
hdrset/fnboth-format=%<format code%>
hdrset/fnpara-format=%<格式代码%>
hdrset/fntext-code={%<前代码,后代码%>}
tocset={%<options%>}
tocset/tocformat=%<条目格式%>
tocset/tocformat+=%<条目格式%>
tocset/tocindent=%<刚性长度%>
tocset/tocrule=%<引导线命令%>
tocset/tocafter=%<距离命令%>
tocset/tocbelow=%<距离命令%>
tocset/tocline=%<条目定义%>
tocset/hang#true,false
tocset/lolskip=##L
tocset/between=%<代码钩子%>
tocset/bibetween=%<代码钩子%>
tocset/dotalign#true,false
tocset/pagenumwd=##L
tocset/tocafter-every=%<距离命令%>
tocset/tocindent-every=%<刚性长度%>
tocset/tocrule-every=%<引导线命令%>
#endkeyvals

\ebstyle{options%keyvals}

#keyvals:\ebstyle
color=#none,seaside,energy,cyberpunk
color-every=%<HTML 颜色代码%>
multoc=%<整数%>
withpart#true,false
fntnumwith=#part,chapter,page
uppercase=#all,first,none,none*
brackets={%<左括号,右括号%>}
figurepath={%<路径名 1%>}{%<路径名 2%>}%<...{路径名 n}%>
hyphen-figure=%<图片连字符%>
hyphen-table=%<表格连字符%>
hyphen-listing=%<代码连字符%>
hyphen-equation=%<公式连字符%>
hyphen-every=%<连字符%>
spvmove=##L
sphmove=##L
sbvmove=##L
sbhmove=##L
nohmove
novmove
spcmd=%<格式命令%>
sbcmd=%<格式命令%>
spbhmove=##L
spbcmd={%<上标格式,下标格式%>}
vsep={%<上标偏移,下标偏移%>}
halign=#l,c,r
#endkeyvals

\ebrefset{options%keyvals}

#keyvals:\ebrefset
linktype=#edge,colors,none
linkcolor=#fresh,cutepink,navyblue,crimson
linkcolor-every=%<HTML 颜色代码%>
linktoc=#none,section,page,all
#endkeyvals

\ebspread{options%keyvals}

#keyvals:\ebspread
line=%<数值%>
table=%<数值%>
math=%<数值%>
caption-figure=%<数值%>
caption-table=%<数值%>
caption-listing=%<数值%>
caption-every=%<数值%>
footnote=%<数值%>
every=%<数值%>
#endkeyvals

\ebsubfont{options%keyvals}

#keyvals:\ebsubfont
caption-table=%<字体命令%>
caption-figure=%<字体命令%>
caption-listing=%<字体命令%> 
caption-every=%<字体命令%> 
footnote=%<字体命令%>
marginpar=%<字体命令%> 
#endkeyvals

\ebbibset{options%keyvals}

#keyvals:\ebbibset
backend=#bibtex,biblatex
bibstyle=%<bibstyle%>
citestyle=%<标注风格%>
datafile=%<数据库列表%>
bititle=%<title%>
#endkeyvals

\ebthmset{options}

\ebgeoset{options%keyvals}

#keyvals:\ebgeoset
headruleskip=##L
footruleskip=##L
hdivide={%<左边距,页面文本宽度%>,%<右边距%>}
hmargin={%<左边距,右边距%>}
textheight=%<页面文本高度%>
nofoot#true,false
#endkeyvals

\ebhdrset{options%keyvals}

#keyvals:\ebhdrset
chap-mark=%<标题标记%>
sec-mark=%<标题标记%>
subsec-mark= %<标题标记%>
chap-label={%<距离命令%>}
chap-label=[%<数字输出命令%>]{%<距离命令%>}
sec-label={%<距离命令%>}
sec-label=[%<数字输出命令%>]{%<距离命令%>}
subsec-label={%<距离命令%>}
subsec-label=[%<数字输出命令%>]{%<距离命令%>}
headrule=%<横线命令%>
footrule=%<横线命令%>
footnoterule=%<横线命令%>
headrulewd=##L
footnoterulewd=##L
footnotetype=#plain,hang,flush,bottom
fnfirstindent=##L
fnafterindent=##L
fnparskip=##L
fntext-pos=#normal,super
fnmark-num=#plain,pifont,pifont*,pisans,pisans*,short num
fntext-num=#plain,pifont,pifont*,pisans,pisans*,short num
fnmarktext-num=#plain,pifont,pifont*,pisans,pisans*,short num
fnmark-vmove=##L
fnmark-hmove=##L
fntext-vmove=##L
fnmarktext-format=%<format code%>
fncustom-format=%<format code%>
fnboth-format=%<format code%>
fnpara-format=%<格式代码%>
fntext-code={%<前代码,后代码%>}
#endkeyvals

\ebtocset{options%keyvals}

#keyvals:\ebtocset
tocformat=%<条目格式%>
tocformat+=%<条目格式%>
tocindent=%<刚性长度%>
tocrule=%<引导线命令%>
tocafter=%<距离命令%>
tocbelow=%<距离命令%>
tocline=%<条目定义%>
hang#true,false
lolskip=##L
between=%<代码钩子%>
bibetween=%<代码钩子%>
dotalign#true,false
pagenumwd=##L
tocafter-every=%<距离命令%>
tocindent-every=%<刚性长度%>
tocrule-every=%<引导线命令%>
#endkeyvals

\DeclareThemeColor{name,frame color,emph color,verb color}
\DeclareLinkColor{name,link color,url color,cite color}
\addtosubfont{字体类型}{字体命令}
\printbibliography
\printbibliography[options]
\markdouble{双页标题标记}
\markrule{线宽}
\markrule[长度](颜色名){线宽}[上间距|下间距]
\fnfirstindent#*
\fnafterindent#*
\fnparskip#*
\DefineFntSymbols{符号表名}{符号数量}{符号列表}
\setfntsymbol{符号表名}
\defupfntmark{脚注正文标记格式}
\defdownfntmark{脚注内容标记格式}
\notminipage{普通页内容}{迷你页内容}
\theupfootnote#*
\thedownfootnote#*
\Footnote{正文标记}{脚注文本%text}
\Footnote[内容标记]{正文标记}{脚注文本%text}
\Footnotetext{内容标记}{脚注文本%text}
\Footnotemark{正文标记}
\tocrule{引导点}
\tocrule[引导点间距](放大因子){引导点}[页码格式]
\tocrule*{引导点}
\tocrule*[引导点间距](放大因子){引导点}[页码格式]
\tocrule-{引导点}
\tocrule-[引导点间距](放大因子){引导点}[页码格式]
\RegisterTocName{条目名}
\DeclareFloatList{条目名}{扩展名}
\listnumberline{条目名}
\hangpara{缩进长度}{缩进开始行数}
\begin{hangparas}{缩进长度}{缩进开始行数}
\end{hangparas}

#keyvals:\ctexset
lstlistlistingname=%<代码目录标题名%>
lstlistingname=%<代码题注标题名%>
#endkeyvals

\deftcbstyle{name%specialDef}{tcolorbox keys}#s#%easybooktcbstyle
\addtotcbstyle{name}{tcolorbox keys}

#keyvals:\tcbset,\begin{tcolorbox},\tcbsetforeverylayer,\tcbox,\newtcolorbox,\renewtcolorbox,\newtcbox,\renewtcbox,\tcolorboxenvironment,\tcbsubtitle,\tcbsidebyside,\tcbsubskin,\tcbincludegraphics,\tcbincludepdf,\begin{tcbraster},\begin{tcbitemize},\tcbitem,\begin{tcboxedraster},\begin{tcboxeditemize},\begin{tcblisting},\tcbinputlisting,\newtcblisting,\renewtcblisting,\newtcbinputlisting,\renewtcbinputlisting,\newtcbtheorem,\renewtcbtheorem,\tcboxmath,\tcbhighmath,\usetcboxarray,\consumetcboxarray,\posterbox,\begin{posterboxenv},\tcboxfit,\newtcboxfit,\renewtcboxfit,\DeclareTColorBox,\NewTColorBox,\RenewTColorBox,\ProvideTColorBox,\DeclareTotalTColorBox,\NewTotalTColorBox,\RenewTotalTColorBox,\ProvideTotalTColorBox,\DeclareTCBox,\NewTCBox,\RenewTCBox,\ProvideTCBox,\DeclareTotalTCBox,\NewTotalTCBox,\RenewTotalTCBox,\ProvideTotalTCBox,\DeclareTCBListing,\NewTCBListing,\RenewTCBListing,\ProvideTCBListing,\DeclareTCBInputListing,\NewTCBInputListing,\RenewTCBInputListing,\ProvideTCBInputListing,\DeclareTCBoxFit,\NewTCBoxFit,\RenewTCBoxFit,\ProvideTCBoxFit,\DeclareTotalTCBoxFit,\NewTotalTCBoxFit,\RenewTotalTCBoxFit,\ProvideTotalTCBoxFit,\tcboxverb,\begin{docCommand},\begin{docCommand*},\begin{docCommands},\begin{docEnvironment},\begin{docEnvironment*},\begin{docEnvironments},\begin{docKey},\begin{docKey*},\begin{docKeys},\begin{docPathOperation},\begin{docPathOperation*},\begin{docPathOperations},\docValue,\docValue*,\docAuxCommand,\docAuxCommand*,\docAuxEnvironment,\docAuxEnvironment*,\docAuxKey,\docAuxKey*,\docCounter,\docCounter*,\docLength,\docLength*,\docColor,\docColor*,\begin{dispExample*},\begin{dispListing*},\tcbdocmarginnote
%easybooktcbstyle
tc-easybox
tc-ebparbox
tc-ebemph
tc-ebfbox
#endkeyvals

\begin{easybox}
\begin{easybox}[颜色名](段落标题)[配置选项]
\begin{easybox}*
\begin{easybox}*[颜色名](段落标题)[配置选项]
\end{easybox}
\begin{ebparbox}
\begin{ebparbox}[颜色名](段落标题)[配置选项]
\begin{ebparbox}*
\begin{ebparbox}*[颜色名](段落标题)[配置选项]
\end{ebparbox}

\ebemph{内容}
\ebemph[颜色名]{内容}[配置选项]
\ebfbox{内容}
\ebfbox[颜色名]{内容}[配置选项]

\counteruse{计数器}
\counteruse[编号](分隔符){计数器}[父计数器]
\counteruse*{计数器}
\counteruse*[编号](分隔符){计数器}[父计数器]
\counterwithin[⟨格式⟩]{⟨计数器⟩}{⟨父计数器⟩}
\counterwithin*[⟨格式⟩]{⟨计数器⟩}{⟨父计数器⟩}
\counterwithout[⟨格式⟩]{⟨计数器⟩}{⟨父计数器⟩}
\counterwithout*[⟨格式⟩]{⟨计数器⟩}{⟨父计数器⟩}

\begin{eqcomp}
\begin{eqcomp}[options%keyvals]
\end{eqcomp}
\symb{⟨符号⟩}
\symb{⟨符号⟩}[⟨引导符⟩]
\symb*{⟨符号⟩}
\symb*{⟨符号⟩}[⟨引导符⟩]
\seteqcomplist{键值列表 2}
\seteqcomp{options%keyvals}

#keyvals:\begin{eqcomp},\seteqcomp
width=##L
delim=%<引导符%>
space=##L
item-align=#l,c,r
delim-align=#l,c,r
enumitem=%<键值列表 2%>
intro=%<首行文字%>
font=%<符号字体%>
mode=#math,text
#endkeyvals

# not documented
\LoadPackage{package}#*u
\LoadPackage[options]{package}#*u
\listlstlistingname#*
\setspread{factor}#*
\bicontentsname#*

# from both option of spbmark
\sp{content}
\sp[keyvals]{content}
\sp[keyvals][height,depth]{content}#*
\sp{content}[keyvals%plain]#*
\sb{content}
\sb[keyvals]{content}
\sb[keyvals][height,depth]{content}#*
\sb{content}[keyvals%plain]#*
\textsuperscript{content}
\textsuperscript[keyvals]{content}
\textsuperscript[keyvals][height,depth]{content}#*
\textsuperscript{content}[keyvals%plain]#*
\textsubscript{content}
\textsubscript[keyvals]{content}
\textsubscript[keyvals][height,depth]{content}#*
\textsubscript{content}[keyvals%plain]#*

# from shortlabels option of enumitem
#keyvals:\begin{enumerate}#c,\begin{itemize}#c,\begin{description}#c,\begin{enumerate*}#c,\begin{itemize*}#c,\begin{description*}#c
A
a
I
i
1
#endkeyvals

# from inline option of enumitem
\begin{enumerate*}
\begin{enumerate*}[options%keyvals]
\end{enumerate*}
\begin{itemize*}
\begin{itemize*}[options%keyvals]
\end{itemize*}
\begin{description*}
\begin{description*}[options%keyvals]
\end{description*}

# from svgnames option of xcolor
AliceBlue#B
DarkKhaki#B
Green#B
LightSlateGrey#B
AntiqueWhite#B
DarkMagenta#B
GreenYellow#B
LightSteelBlue#B
Aqua#B
DarkOliveGreen#B
Grey#B
LightYellow#B
Aquamarine#B
DarkOrange#B
Honeydew#B
Lime#B
Azure#B
DarkOrchid#B
HotPink#B
LimeGreen#B
Beige#B
DarkRed#B
IndianRed#B
Linen#B
Bisque#B
DarkSalmon#B
Indigo#B
Magenta#B
Black#B
DarkSeaGreen#B
Ivory#B
Maroon#B
BlanchedAlmond#B
DarkSlateBlue#B
Khaki#B
MediumAquamarine#B
Blue#B
DarkSlateGray#B
Lavender#B
MediumBlue#B
BlueViolet#B
DarkSlateGrey#B
LavenderBlush#B
MediumOrchid#B
Brown#B
DarkTurquoise#B
LawnGreen#B
MediumPurple#B
BurlyWood#B
DarkViolet#B
LemonChiffon#B
MediumSeaGreen#B
CadetBlue#B
DeepPink#B
LightBlue#B
MediumSlateBlue#B
Chartreuse#B
DeepSkyBlue#B
LightCoral#B
MediumSpringGreen#B
Chocolate#B
DimGray#B
LightCyan#B
MediumTurquoise#B
Coral#B
DimGrey#B
LightGoldenrod#B
MediumVioletRed#B
CornflowerBlue#B
DodgerBlue#B
LightGoldenrodYellow#B
MidnightBlue#B
Cornsilk#B
FireBrick#B
LightGray#B
MintCream#B
Crimson#B
FloralWhite#B
LightGreen#B
MistyRose#B
Cyan#B
ForestGreen#B
LightGrey#B
Moccasin#B
DarkBlue#B
Fuchsia#B
LightPink#B
NavajoWhite#B
DarkCyan#B
Gainsboro#B
LightSalmon#B
Navy#B
DarkGoldenrod#B
GhostWhite#B
LightSeaGreen#B
NavyBlue#B
DarkGray#B
Gold#B
LightSkyBlue#B
OldLace#B
DarkGreen#B
Goldenrod#B
LightSlateBlue#B
Olive#B
DarkGrey#B
Gray#B
LightSlateGray#B
OliveDrab#B
Orange#B
Plum#B
Sienna#B
Thistle#B
OrangeRed#B
PowderBlue#B
Silver#B
Tomato#B
Orchid#B
Purple#B
SkyBlue#B
Turquoise#B
PaleGoldenrod#B
Red#B
SlateBlue#B
Violet#B
PaleGreen#B
RosyBrown#B
SlateGray#B
VioletRed#B
PaleTurquoise#B
RoyalBlue#B
SlateGrey#B
Wheat#B
PaleVioletRed#B
SaddleBrown#B
Snow#B
White#B
PapayaWhip#B
Salmon#B
SpringGreen#B
WhiteSmoke#B
PeachPuff#B
SandyBrown#B
SteelBlue#B
Yellow#B
Peru#B
SeaGreen#B
Tan#B
YellowGreen#B
Pink#B
Seashell#B
Teal#B
