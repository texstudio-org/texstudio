# emisa class
# Matthew Bertucci 2022/06/28 for v2.3.0

#include:inputenc
#include:fontenc
# loads T1 option of fontenc
#include:textcomp
#include:microtype
#include:babel
#include:float
#include:caption
#include:graphicx
#include:xcolor
# loads table option of xcolor
#include:etoolbox
#include:biblatex
# loads style=emisa option of biblatex
#include:csquotes
#include:twoopt
#include:environ
#include:paralist
# loads defblank option of paralist
#include:afterpage
#include:xspace
#include:calc
#include:geometry
#include:eso-pic
#include:placeins
#include:newtxtext
#include:amsmath
#include:amssymb
#include:newtxmath
#include:newtxtt
#include:booktabs
#include:listings
#include:ntheorem
# loads standard option of ntheorem
#include:url
#include:hyperref
#include:cleveref
#include:doclicense

#keyvals:\documentclass/emisa#c
british
UKenglish
american
USenglish
draft
final
referee
noreferee
review
noreview
cleveref
nocleveref
cover
nocover
nomicrotype
#endkeyvals

#ifOption:british
\captionsbritish#*
\datebritish#*
\extrasbritish#*
\noextrasbritish#*
\englishhyphenmins#*
\britishhyphenmins#*
\americanhyphenmins#*
\prefacename#*
\bibname#*
\chaptername#*
\enclname#*
\ccname#*
\headtoname#*
\pagename#*
\seename#*
\alsoname#*
\proofname#*
\glossaryname#*
#endif

#ifOption:UKenglish
\captionsUKenglish#*
\dateUKenglish#*
\extrasUKenglish#*
\noextrasUKenglish#*
\englishhyphenmins#*
\britishhyphenmins#*
\americanhyphenmins#*
\prefacename#*
\bibname#*
\chaptername#*
\enclname#*
\ccname#*
\headtoname#*
\pagename#*
\seename#*
\alsoname#*
\proofname#*
\glossaryname#*
#endif

#ifOption:american
\captionsamerican#*
\dateamerican#*
\extrasamerican#*
\noextrasamerican#*
\englishhyphenmins#*
\britishhyphenmins#*
\americanhyphenmins#*
\prefacename#*
\bibname#*
\chaptername#*
\enclname#*
\ccname#*
\headtoname#*
\pagename#*
\seename#*
\alsoname#*
\proofname#*
\glossaryname#*
#endif

#ifOption:USenglish
\captionsUSenglish#*
\dateUSenglish#*
\extrasUSenglish#*
\noextrasUSenglish#*
\englishhyphenmins#*
\britishhyphenmins#*
\americanhyphenmins#*
\prefacename#*
\bibname#*
\chaptername#*
\enclname#*
\ccname#*
\headtoname#*
\pagename#*
\seename#*
\alsoname#*
\proofname#*
\glossaryname#*
#endif

\begin{article}{title elements}
\end{article}
\title[short title%text]{text}
\title[short title%text][ToC title%text]{text}
\subtitle{text}
\subtitle[short subtitle%text]{text}
\subtitle[short subtitle%text][ToC subtitle%text]{text}
\author[short author]{name}
\author[short author][ToC author]{name}
\address{address}
\address[letter of address]{}
\author*{name}{email%URL}#U
\abstract{text}
\keywords{word1 \and word2 \and ...%text}
\acknowledgements{text}
\authornote{text}
\meta{metatype}
\type{type}
\eg
\ie
\cf
\etal
\emisaabbrv{cmd}{text}#d
\OMG
\BPM
\BPMN
\UML
\emisainitialism{cmd}{text}#d
\begin{sourcecode}#V
\begin{sourcecode}[options%keyvals]#V
\end{sourcecode}
\begin{sourcecode*}#V
\begin{sourcecode*}[options%keyvals]#V
\end{sourcecode*}
\begin{java}#V
\begin{java}[options%keyvals]#V
\end{java}
\begin{java*}#V
\begin{java*}[options%keyvals]#V
\end{java*}

#keyvals:\begin{sourcecode},\begin{sourcecode*},\begin{java},\begin{java*}
inputpath=%<path%>
aboveskip=##L
belowskip=##L
lineskip=##L
boxpos=#b,c,t
print#true,false
showlines#true,false
emptylines=%<number%>
emptylines=*%<number%>
gobble=%<number%>
style=%<style name%>
language=%<language%>
language=[%<dialect%>]%<language%>
alsolanguage=%<language%>
alsolanguage=[%<dialect%>]%<language%>
defaultdialect=[%<dialect%>]%<language%>
printpod#true,false
usekeywordsintag#true,false
tagstyle=%<style%>
markfirstintag=%<style%>
makemacrouse#true,false
basicstyle=%<style%>
identifierstyle=%<style%>
commentstyle=%<style%>
stringstyle=%<style%>
keywordstyle=%<style%>
keywordstyle=[%<number%>]%<style%>
keywordstyle=[%<number%>]*%<style%>
ndkeywordstyle=%<style%>
classoffset=%<number%>
texcsstyle=%<style%>
texcsstyle=[%<class number%>]%<style%>
texcsstyle=*[%<class number%>]%<style%>
directivestyle=%<style%>
emph={%<identifier list%>}
emph=[%<number%>]{%<identifier list%>}
moreemph={%<identifier list%>}
moreemph=[%<number%>]{%<identifier list%>}
deleteemph={%<identifier list%>}
deleteemph=[%<number%>]{%<identifier list%>}
emphstyle={%<style%>}
emphstyle=[%<number%>]{%<style%>}
delim=[%<type%>][%<style%>]%<delimiters%>
delim=*[%<type%>][%<style%>]%<delimiters%>
delim=**[%<type%>][%<style%>]%<delimiters%>
moredelim=[%<type%>][%<style%>]%<delimiters%>
moredelim=*[%<type%>][%<style%>]%<delimiters%>
moredelim=**[%<type%>][%<style%>]%<delimiters%>
deletedelim=[%<type%>][%<style%>]%<delimiters%>
deletedelim=*[%<type%>][%<style%>]%<delimiters%>
deletedelim=**[%<type%>][%<style%>]%<delimiters%>
extendedchars#true,false
inputencoding=%<encoding%>
upquote#true,false
tabsize=%<number%>
showtabs#true,false
tab=%<tokens%>
showspaces#true,false
showstringspaces#true,false
formfeed=%<tokens%>
numbers=#none,left,right
stepnumber=%<number%>
numberfirstline#true,false
numberstyle=%<style%>
numbersep=##L
numberblanklines#true,false
firstnumber=%<auto|last|<number>%>
name=%<name%>
title=%<title text%>
caption={%<caption text%>}
caption={[%<short%>]%<caption text%>}
label=##l
nolol#true,false
numberbychapter#true,false
captionpos=%<subset of tb%>
abovecaptionskip=##L
belowcaptionskip=##L
linewidth=##L
xleftmargin=##L
xrightmargin=##L
resetmargins#true,false
breaklines#true,false
breakatwhitespace#true,false
prebreak=%<tokens%>
postbreak=%<tokens%>
breakindent=##L
breakautoindent#true,false
frame=%<type%>
frameround=
framesep=##L
rulesep=##L
framerule=##L
framexleftmargin=##L
framexrightmargin=##L
framextopmargin=##L
framexbottommargin=##L
backgroundcolor=#%color
rulecolor=#%color
fillcolor=#%color
rulesepcolor=#%color
frameshape={%<top shape%>}{%<left shape%>}{%<right shape%>}{%<bottom shape%>}
index={%<identifiers%>}
index=[%<number%>]{%<identifiers%>}
index=[%<number%>][%<keyword classes%>]{%<identifiers%>}
moreindex={%<identifiers%>}
moreindex=[%<number%>]{%<identifiers%>}
moreindex=[%<number%>][%<keyword classes%>]{%<identifiers%>}
deleteindex={%<identifiers%>}
deleteindex=[%<number%>]{%<identifiers%>}
deleteindex=[%<number%>][%<keyword classes%>]{%<identifiers%>}
indexstyle=%<one-parameter macro%>
indexstyle=[%<number%>]%<one-parameter macro%>
columns=%<alignment%>
columns=[%<c|l|r%>]%<alignment%>
flexiblecolumns#true,false
keepspaces#true,false
basewidth=##L
fontadjust#true,false
texcl#true,false
mathescape#true,false
escapechar=%<character%>
escapeinside=%<<char1><char2>%>
escapebegin=%<tokens%>
escapeend=%<tokens%>
fancyvrb#true,false
fvcmdparams=%<<cmd1> <num1> ...%>
morefvcmdparams=%<<cmd1> <num1> ...%>
literate={%<replace%>}{%<replacement text%>}{%<length%>}%<...%>
literate=*{%<replace%>}{%<replacement text%>}{%<length%>}%<...%>
rangebeginprefix=%<prefix%>
rangebeginsuffix=%<suffix%>
rangeendprefix=%<prefix%>
rangeendsuffix=%<suffix%>
rangeprefix=%<prefix%>
rangesuffix=%<suffix%>
includerangemarker#true,false
multicols=%<number%>
float
float=%<subset of tbph%>
float=*%<subset of tbph%>
floatplacement=%<place specifiers%>
firstline=%<number%>
lastline=%<number%>
linerange={%<first1-last1,first2-last2,...%>}
consecutivenumbers#true,false
keywordsprefix=%<prefix%>
keywords={%<list of keywords%>}
keywords=[%<number%>]{%<list of keywords%>}
morekeywords={%<list of keywords%>}
morekeywords=[%<number%>]{%<list of keywords%>}
deletekeywords={%<list of keywords%>}
deletekeywords=[%<number%>]{%<list of keywords%>}
ndkeywords={%<list of keywords%>}
moreendkeywords={%<list of keywords%>}
deleteendkeywords={%<list of keywords%>}
texcs={%<list of csnames%>}
texcs=[%<class number%>]{%<list of csnames%>}
moretexcs={%<list of csnames%>}
moretexcs=[%<class number%>]{%<list of csnames%>}
deletetexcs={%<list of csnames%>}
deletetexcs=[%<class number%>]{%<list of csnames%>}
directives={%<list of compiler directives%>}
moredirectives={%<list of compiler directives%>}
deletedirectives={%<list of compiler directives%>}
sensitive#true,false
alsoletter={%<character sequence%>}
alsodigit={%<character sequence%>}
alsoother={%<character sequence%>}
otherkeywords={%<keywords%>}
tag=%<<char1><char2>%>
string=%<delimiter%>
string=[%<b|d|m|bd|s%>]%<delimiter%>
morestring=%<delimiter%>
morestring=[%<b|d|m|bd|s%>]%<delimiter%>
deletestring=%<delimiter%>
deletestring=[%<b|d|m|bd|s%>]%<delimiter%>
comment=%<delimiter(s)%>
comment=[%<type%>]%<delimiter(s)%>
morecomment=%<delimiter(s)%>
morecomment=[%<type%>]%<delimiter(s)%>
deletecomment=%<delimiter(s)%>
deletecomment=[%<type%>]%<delimiter(s)%>
keywordcomment={%<keywords%>}
morekeywordcomment={%<keywords%>}
deletekeywordcomment={%<keywords%>}
keywordcommentsemicolon={%<keywords%>}{%<keywords%>}{%<keywords%>}
podcomment#true,false
#endkeyvals

## for editorial staff only
\editor{name}#*
\received{date}#*
\accepted{date}#*
\volume{number}#*
\issue{number}{year}#*
\specialissuetitle{text}#*
\CCBYNCSAFour#*
\CCBYNCSAThree#*
\license{text}#*
\licence{text}#*

# not documented
\AtPageDeadCenter{code}#*
\abstractfont#*
\addtocentry[opt]{arg1}{arg2}{arg3}#*
\addtocentry{arg1}{arg2}{arg3}#*
\affiliationaddressfont#*
\affiliationauthorfont#*
\affiliationemailfont#*
\affiliationfont#*
\authorfont#*
\basecoverfont#*
\begin{articleappendix}#*
\end{articleappendix}#*
\begin{articleappendix*}#*
\end{articleappendix*}#*
\begin{cfp}#*
\end{cfp}#*
\begin{editorialcontent}{arg}#*
\end{editorialcontent}#*
\begin{editorial}#*
\begin{editorial}[heading%text]#*
\end{editorial}#*
\bleed#*
\cfpname#*
\copyrightholder{name}#*
\copyrightyear{year}#*
\coverIII{code}#*
\coverII{code}#*
\coverIVbgname#*
\coverIV{code}#*
\coverIbgname#*
\coverI{code}#*
\coveroff#*
\coveron#*
\coverpage{code}#*
\coverpage[pagenum]{code}#*
\covertitlefont#*
\covervolumefont#*
\displayskipstretch#*
\doitext#*
\doi{DOI}#*
\editorialboardbody{arg}#*
\editorialboardname{arg}#*
\editorialboxmaxheight#*
\editorialname#*
\email{email%URL}#*U
\footruleoff#*
\footruleon#*
\footrulewidth#*
\footrule{arg}#*
\gislogoname#*
\guidelinesbody{arg}#*
\guidelinesname{arg}#*
\headbox{arg1}{arg2}{arg3}{arg4}{arg5}{arg6}{arg7}{arg8}#*
\headfootruleheight#*
\headmargin#*
\headmarkstyle{arg}#*
\headpageoffset#*
\headwidth#*
\imprintbody{arg}#*
\imprintname{arg}#*
\issn{ISSN}#*
\journalname{text}#*
\journalsubtitle{text}#*
\markarticle#*
\markeditorial#*
\markhead{arg1}{arg2}#*
\outdoi#*
\outputarticleappendix#*
\pagebg{color}#*
\pagefootfont#*
\pageheadfont#*
\pagenumfont#*
\picturepage[pagestyle]{code}#*
\picturepage{code}#*
\sectionfont#*
\setstretch{arg}#*
\sigEMISAlogoname#*
\sigmobislogoname#*
\sigmobispage#*
\sigmobispagefoot#*
\sigmobispagehead#*
\sigmobispagerule{text}#*
\specialissuetitleprefix{prefix}#*
\subtitlefont#*
\theaddresses#*
\thearticle#*
\thecovertitle#*
\thecovervolumeline#*
\theevenheadpage#*
\theheadvolume#*
\theoddheadpage#*
\thispagebackground{code}#*
\thispagebackground[pagestyle]{code}#*
\titlefont#*

coverbgcolor#B
covertextcolor#B
headtextcolor#B
boxframecolor#B
boxbgcolor#B

# from T1 option of fontenc
\DH#n
\dh#n
\dj#n
\DJ#n
\guillemetleft#n
\guillemetright#n
\guillemotleft#*n
\guillemotright#*n
\guilsinglleft#n
\guilsinglright#n
\Hwithstroke#n
\hwithstroke#n
\k{arg}#n
\NG#n
\ng#n
\quotedblbase#n
\quotesinglbase#n
\textogonekcentered{arg}#n
\textquotedbl#n
\th#n
\TH#n

# from table option of xcolor
#include:colortbl

# from style=emisa option of biblatex
\bibitemlabel{text}#*
\mkbibdateiso{arg1}{arg2}{arg3}#*

# from defblank option of paralist
\begin{asparablank}
\end{asparablank}
\begin{inparablank}
\end{inparablank}

# from standard option of ntheorem
\begin{Theorem}
\begin{Theorem}[heading%text]
\end{Theorem}
\begin{theorem}#*
\begin{theorem}[heading%text]#*
\end{theorem}#*
\begin{Lemma}
\begin{Lemma}[heading%text]
\end{Lemma}
\begin{lemma}#*
\begin{lemma}[heading%text]#*
\end{lemma}#*
\begin{Proposition}
\begin{Proposition}[heading%text]
\end{Proposition}
\begin{proposition}#*
\begin{proposition}[heading%text]#*
\end{proposition}#*
\begin{Corollary}
\begin{Corollary}[heading%text]
\end{Corollary}
\begin{corollary}#*
\begin{corollary}[heading%text]#*
\end{corollary}#*
\begin{Satz}
\begin{Satz}[heading%text]
\end{Satz}
\begin{satz}#*
\begin{satz}[heading%text]#*
\end{satz}#*
\begin{Korollar}
\begin{Korollar}[heading%text]
\end{Korollar}
\begin{korollar}#*
\begin{korollar}[heading%text]#*
\end{korollar}#*
\begin{Definition}
\begin{Definition}[heading%text]
\end{Definition}
\begin{definition}#*
\begin{definition}[heading%text]#*
\end{definition}#*
\begin{Example}
\begin{Example}[heading%text]
\end{Example}
\begin{example}#*
\begin{example}[heading%text]#*
\end{example}#*
\begin{Beispiel}
\begin{Beispiel}[heading%text]
\end{Beispiel}
\begin{beispiel}#*
\begin{beispiel}[heading%text]#*
\end{beispiel}#*
\begin{Anmerkung}
\begin{Anmerkung}[heading%text]
\end{Anmerkung}
\begin{anmerkung}#*
\begin{anmerkung}[heading%text]#*
\end{anmerkung}#*
\begin{Bemerkung}
\begin{Bemerkung}[heading%text]
\end{Bemerkung}
\begin{bemerkung}#*
\begin{bemerkung}[heading%text]#*
\end{bemerkung}#*
\begin{Remark}
\begin{Remark}[heading%text]
\end{Remark}
\begin{remark}#*
\begin{remark}[heading%text]#*
\end{remark}#*
\begin{Proof}
\begin{Proof}[heading%text]
\end{Proof}
\begin{proof}#*
\begin{proof}[heading%text]#*
\end{proof}#*
\begin{Beweis}
\begin{Beweis}[heading%text]
\end{Beweis}
\begin{beweis}#*
\begin{beweis}[heading%text]#*
\end{beweis}#*
\begin{Theorem*}
\begin{Theorem*}[heading%text]
\end{Theorem*}
\begin{theorem*}#*
\begin{theorem*}[heading%text]#*
\end{theorem*}#*
\begin{Lemma*}
\begin{Lemma*}[heading%text]
\end{Lemma*}
\begin{lemma*}#*
\begin{lemma*}[heading%text]#*
\end{lemma*}#*
\begin{Proposition*}
\begin{Proposition*}[heading%text]
\end{Proposition*}
\begin{proposition*}#*
\begin{proposition*}[heading%text]#*
\end{proposition*}#*
\begin{Corollary*}
\begin{Corollary*}[heading%text]
\end{Corollary*}
\begin{corollary*}#*
\begin{corollary*}[heading%text]#*
\end{corollary*}#*
\begin{Satz*}
\begin{Satz*}[heading%text]
\end{Satz*}
\begin{satz*}#*
\begin{satz*}[heading%text]#*
\end{satz*}#*
\begin{Korollar*}
\begin{Korollar*}[heading%text]
\end{Korollar*}
\begin{korollar*}#*
\begin{korollar*}[heading%text]#*
\end{korollar*}#*
\begin{Definition*}
\begin{Definition*}[heading%text]
\end{Definition*}
\begin{definition*}#*
\begin{definition*}[heading%text]#*
\end{definition*}#*
\begin{Example*}
\begin{Example*}[heading%text]
\end{Example*}
\begin{example*}#*
\begin{example*}[heading%text]#*
\end{example*}#*
\begin{Beispiel*}
\begin{Beispiel*}[heading%text]
\end{Beispiel*}
\begin{beispiel*}#*
\begin{beispiel*}[heading%text]#*
\end{beispiel*}#*
\begin{Anmerkung*}
\begin{Anmerkung*}[heading%text]
\end{Anmerkung*}
\begin{anmerkung*}#*
\begin{anmerkung*}[heading%text]#*
\end{anmerkung*}#*
\begin{Bemerkung*}
\begin{Bemerkung*}[heading%text]
\end{Bemerkung*}
\begin{bemerkung*}#*
\begin{bemerkung*}[heading%text]#*
\end{bemerkung*}#*
\begin{Remark*}
\begin{Remark*}[heading%text]
\end{Remark*}
\begin{remark*}#*
\begin{remark*}[heading%text]#*
\end{remark*}#*
\begin{Proof*}
\begin{Proof*}[heading%text]
\end{Proof*}
\begin{proof*}#*
\begin{proof*}[heading%text]#*
\end{proof*}#*
\begin{Beweis*}
\begin{Beweis*}[heading%text]
\end{Beweis*}
\begin{beweis*}#*
\begin{beweis*}[heading%text]#*
\end{beweis*}#*
