# abntex2 class
# Matthew Bertucci 2022/05/19 for v1.9.7

#include:ifthen
#include:class-memoir
#include:textcase
#include:hyperref
#include:bookmark
#include:babel
# loads brazil option of babel
#include:enumitem
#include:calc

#keyvals:\documentclass/abntex2#c
article
twocolumn
chapter=TITLE
section=TITLE
subsection=TITLE
subsubsection=TITLE
subsubsubsection=TITLE
sumario=#abnt-6027-2012,tradicional
# options passed to memoir class
10pt
11pt
12pt
14pt
17pt
20pt
25pt
30pt
36pt
48pt
60pt
9pt
a3paper
a4paper
a5paper
a6paper
b3paper
b4paper
b5paper
b6paper
broadsheetpaper
crownvopaper
dbillpaper
demyvopaper
draft
ebook
executivepaper
extrafontsizes
final
fleqn
foolscapvopaper
fullptlayout
imperialvopaper
landscape
largecrownvopaper
largepostvopaper
ledgerpaper
legalpaper
leqno
letterpaper
mcrownvopaper
mdemyvopaper
mediumvopaper
mlargecrownvopaper
ms
msmallroyalvopaper
oldfontcommands
oldpaper
onecolumn
oneside
openany
openbib
openleft
openright
postvopaper
pottvopaper
royalvopaper
showtrims
smalldemyvopaper
smallroyalvopaper
statementpaper
superroyalvopaper
twoside
#endkeyvals

\ABNTEXfontereduzida#*
\pretextualchapter{title}#L1
\titulo{texto do título%text}
\imprimirtitulo
\tituloestrangeiro{exto do título%text}
\imprimirtituloestrangeiro
\autor{%<nome do(s) autor(es)%>}
\imprimirautor
\data{mês e ano ou data em português}
\imprimirdata
\instituicao{nome da instituição%text}
\imprimirinstituicao
\local{localidade de apresentação do documento%text}
\imprimirlocal
\preambulo{preâmbulo do documento%text}
\imprimirpreambulo
\tipotrabalho{tipo do trabalho%text}
\imprimirtipotrabalho
\orientador{%<nome do(s) orientador(es)%>}
\orientador[%<rótulo%>]{%<nome do(s) orientador(es)%>}
\imprimirorientador
\imprimirorientadorRotulo
\coorientador{%<nome do(s) coorientador(es)%>}
\coorientador[%<rótulo%>]{%<nome do(s) coorientador(es)%>}
\imprimircoorientador
\imprimircoorientadorRotulo
\phantompart
\pretextual
\imprimircapa
\begin{capa}
\end{capa}
\imprimirfolhaderosto
\imprimirfolhaderosto[nome da folha de rosto%text]
\imprimirfolhaderosto*
\imprimirfolhaderosto*[nome da folha de rosto%text]
\folhaderostoname
\folhaderostocontent#*
\begin{fichacatalografica}
\end{fichacatalografica}
\begin{errata}
\begin{errata}[nome da errata%text]
\end{errata}
\errataname
\begin{folhadeaprovacao}
\begin{folhadeaprovacao}[nome da folha de aprovação%text]
\end{folhadeaprovacao}
\folhadeaprovacaoname
\assinatura{texto a ser impresso%text}
\ABNTEXsignwidth#*
\ABNTEXsignthickness#*
\ABNTEXsignskip#*
\begin{dedicatoria}
\begin{dedicatoria}[nome da dedicatória%text]
\end{dedicatoria}
\dedicatorianame
\begin{agradecimentos}
\begin{agradecimentos}[nome dos agradecimentos%text]
\end{agradecimentos}
\agradecimentosname
\begin{epigrafe}
\begin{epigrafe}[nome da epígrafe%text]
\end{epigrafe}
\epigraphname
\begin{resumo}
\begin{resumo}[nome do resumo%text]
\end{resumo}
\resumoname
\begin{resumoumacoluna}
\begin{resumoumacoluna}[nome do resumo%text]
\end{resumoumacoluna}
\begin{siglas}
\end{siglas}
\listadesiglasname
\begin{simbolos}
\end{simbolos}
\listadesimbolosname
\subsubsubsection{title}#L5
\subsubsubsection[short title]{title}#L5
\subsubsubsection*{title}#L5
\textual
\ABNTEXchapterfont#*
\ABNTEXchapterfontsize#*
\ABNTEXpartfont#*
\ABNTEXpartfontsize#*
\ABNTEXsectionfont#*
\ABNTEXsectionfontsize#*
\ABNTEXsubsectionfont#*
\ABNTEXsubsectionfontsize#*
\ABNTEXsubsubsectionfont#*
\ABNTEXsubsubsectionfontsize#*
\ABNTEXsubsubsubsectionfont#*
\ABNTEXsubsubsubsectionfontsize#*
\begin{citacao}
\begin{citacao}[language]
\end{citacao}
\ABNTEXcitacaorecuo#*
\begin{alineas}
\begin{alineas}[options%keyvals]
\end{alineas}
\begin{subalineas}
\begin{subalineas}[options%keyvals]
\end{subalineas}
\begin{incisos}
\begin{incisos}[options%keyvals]
\end{incisos}
\ABNTEXcaptiondelim#*
\IBGEtab{Nome e rótulo%text}{Conteúdo da tabela%text}{Conteúdo da legenda%text}
\ibgetab{Nome e rótulo%text}{Conteúdo da tabela%text}{Conteúdo da legenda%text}#*
\fonte{Descrição%text}
\fonte[Rótulo%text]{Descrição%text}
\nota{Nota%text}
\nota[Rótulo%text]{Nota%text}
\IBGEtabfontsize#*
\postextual
\apendices
\begin{apendicesenv}
\end{apendicesenv}
\apendicename
\apendicesname
\partpage
\partapendices
\anexos
\begin{anexosenv}
\end{anexosenv}
\anexoname
\anexosname
\partanexos
\abnTeX
\coorientadorname
\fontename
\notaname
\orientadorname

#keyvals:\begin{alineas}#c,\begin{subalineas}#c,\begin{incisos}#c
topsep=##L
partopsep=##L
parsep=##L
itemsep=##L
leftmargin=##L
rightmargin=##L
listparindent=##L
labelwidth=##L
labelsep=##L
itemindent=##L
label=%<commands%>
label*=%<commands%>
ref=%<commands%>
font=%<commands%>
format=%<commands%>
align=#left,right,parleft
labelindent=##L
left=%<labelindent%>
left=%<labelindent%> .. %<leftmargin%>
widest
widest=%<string%>
widest*=%<integer%>
labelsep*=##L
labelindent*=##L
start=%<integer%>
resume
resume=%<series name%>
resume*
resume*=%<series name%>
series=%<series name%>
beginpenalty=%<integer%>
midpenalty=%<integer%>
endpenalty=%<integer%>
before=%<code%>
before*=%<code%>
after=%<code%>
after*=%<code%>
first=%<code%>
first*=%<code%>
style=#standard,unboxed,nextline,sameline,multiline
noitemsep
nosep
wide
wide=%<parindent%>
itemjoin=%<string%>
itemjoin*=%<string%>
afterlabel=%<string%>
mode=#unboxed,boxed
#endkeyvals

# from brazil option of babel
\captionsbrazil#*
\datebrazil#*
\extrasbrazil#*
\noextrasbrazil#*
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
\ord
\orda
\ro#*
\ra#*

# not documented
\ABNTEXcaptionfontedelim
\ABNTEXchapterupperifneeded{text}#*
\ABNTEXcsign{arg}#*
\ABNTEXisarticle#*
\ABNTEXistwocolumn#*
\ABNTEXsectionupperifneeded{text}#*
\ABNTEXsign{arg}#*
\ABNTEXsubsectionupperifneeded{text}#*
\ABNTEXsubsubsectionupperifneeded{text}#*
\ABNTEXsubsubsubsectionupperifneeded{text}#*
\begin{folhaderosto*}#*
\begin{folhaderosto*}[title%text]#*
\begin{folhaderosto}#*
\begin{folhaderosto}[title%text]#*
\cftbeforesubsubsubsectionskip#*
\cftlastnumwidth#*
\cftsubsubsubsectionfont#*
\chapternamenumlength#*
\configurecaptions#*
\configureseparator#*
\end{folhaderosto*}#*
\end{folhaderosto}#*
\imprimirfolhaderostonostar{title%text}#*
\imprimirfolhaderostostar{title%text}#*
\myptabbox#*
\myptabboxwidth#*
\olddate#S
\PRIVATEapendiceconfig{arg1}{arg2}#*
\PRIVATEbookmarkthis{arg1}#*
\PRIVATEclearpageifneeded#*
\setsubsubsubsecheadstyle#*
\switchchapname{arg}#*
\theforeigntitle#*
\tocinnonumchapter#*
\tocpartanexos#*
\tocpartapendices#*
\tocprintchapter#*
\tocprintchapternonum#*