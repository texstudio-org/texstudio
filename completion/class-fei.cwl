# fei class
# Matthew Bertucci 2022/07/02 for v4.10.3

#include:kvoptions
#include:newtxtext
#include:class-memoir
#include:inputenc
#include:fontenc
# loads T1 option of fontenc
#include:microtype
#include:babel
# loads english and brazil options of babel
#include:csquotes
#include:indentfirst
#include:mathtools
#include:lmodern
#include:icomma
#include:graphicx
#include:morewrites
#include:algorithm2e
# loads portuguese option of algorithm2e
#include:amsthm
#include:thmtools
#include:enumitem
#include:pdfpages
#include:ifthen
#include:imakeidx
#include:pdfx
#include:biblatex
# loads style=abnt option of biblatex

#keyvals:\documentclass/fei#c
font=#times,arial,arimo
draft
final
symbols
acronym
record
abbr-shortcuts
sublist
deposito
numeric
oneside
twoside
backrefs
algo-as-figure
nopdfa
#endkeyvals

#ifOption:font=arial
#include:uarial
#endif

#ifOption:font=arimo
#include:arimo
#endif

#ifOption:symbols
#include:glossaries-extra
# loads xindy option of glossaries-extra
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
# loads symbols option of glossaries-extra
\printsymbols
\printsymbols[options%keyvals]
\glsxtrnewsymbol{label}{symbol}#l
\glsxtrnewsymbol[options%keyvals]{label}{symbol}#l
\printunsrtsymbols#*
\printunsrtsymbols[options%keyvals]#*
#endif

#ifOption:acronym
#include:glossaries-extra
# loads xindy option of glossaries-extra
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
# loads acronym option of glossaries-extra
\printacronyms
\printacronyms[options%keyvals]
\printunsrtacronyms#*
\printunsrtacronyms[options%keyvals]#*
#endif

#ifOption:record
#include:glossaries-extra
# loads xindy option of glossaries-extra
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
# loads record option of glossaries-extra
#include:glossaries-extra-bib2gls
#endif

#ifOption:abbr-shortcuts
#include:glossaries-extra
# loads xindy option of glossaries-extra
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
# loads shortcuts=abbr option of glossaries-extra
\newabbr{label}{short}{long}#l
\newabbr[options%keyvals]{label}{short}{long}#l
#endif

\begin{agradecimentos}
\end{agradecimentos}
\begin{axioma}
\begin{axioma}[heading%text]
\end{axioma}
\begin{conjectura}
\begin{conjectura}[heading%text]
\end{conjectura}
\begin{corolario}
\begin{corolario}[heading%text]
\end{corolario}
\begin{definicao}
\begin{definicao}[heading%text]
\end{definicao}
\begin{desenho}
\end{desenho}
\begin{diagrama}
\end{diagrama}
\begin{epigrafe}
\end{epigrafe}
\begin{esquema}
\end{esquema}
\begin{exemplo}
\begin{exemplo}[heading%text]
\end{exemplo}
\begin{fluxograma}
\end{fluxograma}
\begin{folhaderosto}
\end{folhaderosto}
\begin{fotografia}
\end{fotografia}
\begin{grafico}
\end{grafico}
\begin{hipotese}
\begin{hipotese}[heading%text]
\end{hipotese}
\begin{lema}
\begin{lema}[heading%text]
\end{lema}
\begin{mapa}
\end{mapa}
\begin{organograma}
\end{organograma}
\begin{paradoxo}
\begin{paradoxo}[heading%text]
\end{paradoxo}
\begin{planta}
\end{planta}
\begin{proposicao}
\begin{proposicao}[heading%text]
\end{proposicao}
\begin{prova}
\begin{prova}[heading%text]
\end{prova}
\begin{quadro}
\end{quadro}
\begin{resumo}
\end{resumo}
\begin{retrato}
\end{retrato}
\begin{teorema}
\begin{teorema}[heading%text]
\end{teorema}

\advisor{name}#*
\anexos
\cftdesenhoaftersnum#*
\cftdesenhoname#*
\cftdiagramaaftersnum#*
\cftdiagramaname#*
\cftesquemaaftersnum#*
\cftesquemaname#*
\cftfluxogramaaftersnum#*
\cftfluxogramaname#*
\cftfotografiaaftersnum#*
\cftfotografianame#*
\cftgraficoaftersnum#*
\cftgraficoname#*
\cftmapaaftersnum#*
\cftmapaname#*
\cftorganogramaaftersnum#*
\cftorganogramaname#*
\cftplantaaftersnum#*
\cftplantaname#*
\cftquadroaftersnum#*
\cftquadroname#*
\cftretratoaftersnum#*
\cftretratoname#*
\cidade{cidade%text}
\citefloat{bibid}#C
\citeonline{bibid}#C
\curso{curso}#*
\dedicatoria{text}
\desenhoname#*
\diagramaname#*
\epig{citacao%text}{Autor}
\esquemaname#*
\fichacatalografica
\fluxogramaname#*
\folhadeaprovacao
\fotografianame#*
\graficoname#*
\instituicao{instituição%text}
\keywords{keywords%text}
\mapaname#*
\oldlistofalgorithms#S
\oldnumberline#S
\oldprintbibliography#S
\oldprintindex#S
\organogramaname#*
\palavraschave{text}
\plantaname#*
\quadroname#*
\reformchapapp#*
\retratoname#*
\smallcaption{text}
\subtitulo{text}
\tocnumwidth#*

\ifglossaries#S
\glossariestrue#S
\glossariesfalse#S
\ifsublist#S
\sublisttrue#S
\sublistfalse#S
\ifdeposito#S
\depositotrue#S
\depositofalse#S
\ifnumeric#S
\numerictrue#S
\numericfalse#S
\ifoneside#S
\onesidetrue#S
\onesidefalse#S
\ifpdfa#S
\pdfatrue#S
\pdfafalse#S

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

# from english option of babel
\captionsenglish#*
\dateenglish#*
\extrasenglish#*
\noextrasenglish#*
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

# from brazil option of babel (repeats removed)
\captionsbrazil#*
\datebrazil#*
\extrasbrazil#*
\noextrasbrazil#*
\ord
\orda
\ro#*
\ra#*

# from portuguese option of algorithm2e
\Entrada{Entrada}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Saida{Saída}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Dados{Dados}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Resultado{Resultado}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Ate#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\KwRetorna{val}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Retorna{val}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Inicio{inside block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Repita{stop condition}{text loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lRepita{stop condition}{line of the loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\eSe{condition}{then block}{else block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Se{condition}{then block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uSe{condition}{then block without end}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lSe{condition}{then’s line text}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Senao{else block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uSenao{else block without else}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lSenao{else’s line text}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\SenaoSe{condition}{elseif block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uSenaoSe{condition}{elseif block without end}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lSenaoSe{condition}{elseif’s line text}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Selec{condition}{switch block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Caso{a case}{case block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uCaso{a case}{case block without end}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lCaso{a case}{case’s line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Outro{otherwise block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lOutro{otherwise’s line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Para{condition}{text loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lPara{condition}{line text loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\ParaPar{condition}{text loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lParaPar{condition}{line text loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\ParaCada{condition}{text loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lParaCada{condition}{line text loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\ParaTodo{condition}{text loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lParaTodo{condition}{line text loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Enqto{stop condition}{text loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lEnqto{stop condition}{text loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*

# from style=abnt option of biblatex
#keyvals:\usepackage/biblatex#c,\ExecuteBibliographyOptions#c
# from abnt.bbx
ittitles#true,false
scbib#true,false
nosl#true,false
nosn#true,false
noslsn#true,false
repeattitles#true,false
repeatfirstfields#true,false
repeatfields#true,false
usedashes#true,false
indent#true,false
extradate#true,false
extrayear#true,false
justify#true,false
pretty#true,false
citecount#true,false
# from abnt.cbx
sccite#true,false
#endkeyvals
# from abnt.bbx
#include:xpatch
\origbibsetup#S
\FirstWordUpper{text}#*
\FirstWordSC{text}#*
\FirstWordLCSC{text}#*
\traceparam{arg}#S
\paramL#S
\traceparamA#S
\traceparamB#S
\traceparamS#S
\traceparamC{arg}#S
\traceparamD{arg}#S
\traceparamE#S
\smartuppercase{text}#*
\smartlowercase{text}#*
\smartlcsc{text}#*
\smartsc{text}#*
\UpperOrSC{text}#*
\NormalOrSC{text}#*
\iffieldregex{field}{regex}{true}{false}#*
\iffieldendswithpunct{field}{true}{false}#*
\IfGivenIsInitial{arg1}{arg2}#*
\multinamedelimorig#S
\finalnamedelimorig#S
\abntnum{number}#*
\bibnameunderscore#*
\nopunctdash#*
# from abnt.cbx
\UpperOrSCCite{text}#*
\NormalOrSCCite{text}#*
\IfGivenIsInit{arg1}{arg2}#*
\origmkbibnamefamily#S
\origmkbibnamegiven#S
\origmkbibnameprefix#S
\origmkbibnamesuffix#S
\FirstWord{text}#*
\addapud#*
\apud{bibid}{bibid}#C
\apud(post){bibid}{bibid}#*C
\apud(pre)(post){bibid}{bibid}#C
\apud(pre)(post)[post]{bibid}[post]{bibid}#*C
\apud[post]{bibid}[post]{bibid}#*C
\apud[pre][post]{bibid}[pre][post]{bibid}#*C
\apud(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C
\plaincite[prenote][postnote]{bibid}#*C
\plaincite[postnote]{bibid}#*C
\plaincite{bibid}#*C
\citelastname[prenote][postnote]{bibid}#*C
\citelastname[postnote]{bibid}#*C
\citelastname{bibid}#*C
\textapud{bibid}{bibid}#C
\textapud{bibid}[post]{bibid}#*C
\textapud[post]{bibid}{bibid}#*C
\textapud[post]{bibid}[post]{bibid}#C
\textapud[pre][post]{bibid}[pre][post]{bibid}#C
\citeyearorsh*[prenote][postnote]{bibid}#*C
\citeyearorsh*[postnote]{bibid}#*C
\citeyearorsh*{bibid}#*C