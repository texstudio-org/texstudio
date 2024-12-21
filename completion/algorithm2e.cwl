# algorithm2e package
# updated 3/28/2022 for v5.2

#include:ifthen
#include:ifoddpage
#include:xspace
#include:relsize

#keyvals:\usepackage/algorithm2e#c
algo2e
algochapter
algonl
algopart
algoruled
algosection
boxed
boxruled
commentsnumbered
croatian
croatiankw
czech
czechkw
displayblockmarkers
displaygroupmarkers
dotocloa
endfloat
english
englishkw
figure
fillcomment
french
frenchkw
german
germankw
hangingcomment
hanginginout
inoutnumbered
italiano
italianokw
lined
linesnumbered
linesnumberedhidden
longend
ngerman
ngermankw
noalgohanging
noend
nofillcomment
nokwfunc
noline
norelsize
noresetcount
nosemicolon
oldcommands
onelanguage
plain
plainruled
portuguese
portuguesekw
procnumbered
resetcount
rightnl
ruled
scleft
shortend
slide
slovak
slovakkw
spanish
spanishkw
sright
titlenotnumbered
titlenumbered
turkish
turkishkw
tworuled
vlined
#endkeyvals

#ifOption:algo2e
\begin{algorithm2e}#\algorithm
\begin{algorithm2e}[placement]
\end{algorithm2e}
\begin{algorithm2e*}#*\algorithm
\begin{algorithm2e*}[placement]#*
\end{algorithm2e*}#*
\listofalgorithmes
#endif

#ifOption:dotocloa
#include:tocbibind
#endif

#ifOption:endfloat
#include:endfloat
\thepostalgo#*
#endif

#ifOption:oldcommands
\SetNoLine#S
\SetNoline#S
\SetVline#S
\SetLine#S
\dontprintsemicolon#S
\printsemicolon#S
\incmargin{length}#S
\decmargin{length}#S
\Setnlskip{length}#S
\setnlskip{length}#S
\setalcapskip{length}#S
\setalcaphskip{length}#S
\nlSty{text}#S
\Setnlsty{font csname}{text before}{text after}#S
\linesnumbered#S
\linesnumberedhidden#S
\linesnotnumbered#S
\showln#S
\showlnlabel{text%plain}#S
\nocaptionofalgo#S
\restorecaptionofalgo#S
\restylealgo{style}#S
\Titleofalgo{text}#S
\SetKwIf{if csname}{elseif csname}{else csname}{if text}{then text}{elseif text}{else text}{endif text}#S
\gSi#S
\gSinonSi#S
\gSinon#S
\gIf#S
\gElsIf#S
\gElse#S
\gElseIf#S
\gWenn#S
\gSonstWenn#S
\gSonst#S
\gSe#S
\gSenaoSe#S
\gSenao#S
\gSea#S
\gAltSe#S
\gAltrimenti#S
\Ret#S
\Data#S
\Result#S
#endif

#ifOption:slide
#include:color
#endif

#  Environments defined in the package
\begin{algorithm}
\begin{algorithm}[placement]
\end{algorithm}
\begin{algorithm*}#*\algorithm
\begin{algorithm*}[placement]#*
\end{algorithm*}#*
\begin{function}#\algorithm
\begin{function}[placement]
\end{function}
\begin{function*}#*\algorithm
\begin{function*}[placement]#*
\end{function*}#*
\begin{procedure}#\algorithm
\begin{procedure}[placement]
\end{procedure}
\begin{procedure*}#*\algorithm
\begin{procedure*}[placement]#*
\end{procedure*}#*

\SetAlgorithmName{name}{autoref name}{listofalgorithms name}
\SetAlgoProcName{name}{autoref name}
\SetAlgoFuncName{name}{autoref name}

# global code typesetting commands
\DontPrintSemicolon
\PrintSemicolon#*
\BlankLine
\Indp#S
\Indm#S
\SetStartEndCondition{typo1}{typo2}{typo3}
\AlgoDisplayBlockMarkers
\AlgoDontDisplayBlockMarkers
\AlgoDisplayGroupMarkers
\AlgoDontDisplayGroupMarkers
\SetAlgoBlockMarkers{begin keywords}{end keywords}

# algorithm environment, caption, list of algorithms, ...
\listofalgorithms
\TitleOfAlgo{text}
\SetAlgoRefName{text%plain}
\SetAlgoRefRelativeSize{integer}
\SetAlgoCaptionSeparator{separator}
\SetCustomAlgoRuledWidth{length}
\AlCapSkip#*
\SetAlCapSkip{length}
\SetAlCapHSkip{length}
\SetTitleSty{type style}{type size}
\TitleSty{text}#*
\NoCaptionOfAlgo
\RestoreCaptionOfAlgo
\SetAlgoCaptionLayout{style csname}

# line numbering
\theAlgoLine#*
\LinesNumbered
\LinesNumberedHidden
\LinesNotNumbered
\nllabel{label}#l
\nl#/algorithm
\lnl{label}#*l
\nlset{text%plain}
\lnlset{text%plain}{label}#*l
\ShowLn
\ShowLnLabel{text%plain}#*
\SetNlSty{font csname}{text before}{text after}
\SetNlSkip{length}
\SetAlgoNlRelativeSize{number}

# math display
\begin{algomathdisplay}#\math
\end{algomathdisplay}

# standard styles
\AlFnt#*
\KwSty{text}#*
\FuncSty{text}#*
\FuncArgSty{text}#*
\ProgSty{text}#*
\ArgSty{text}#*
\DataSty{text}#*
\CommentSty{text}#*
\NlSty{text}#*
\ProcNameSty{text}#*
\ProcFnt#*
\ProcArgSty{text}#*
\ProcArgFnt#*
\BlockMarkersSty{text}#*
\AlCapSty{text}#*
\AlCapNameSty{text}#*
\AlCapFnt#*
\AlCapNameFnt#*
\ProcSty{text}#*
\ProcNameFnt#*
\ProcArgFnt#*
\AlTitleSty{text}#*
\AlTitleFnt#*
\SetAlFnt{font csname}
\SetKwSty{font csname}
\SetFuncSty{font csname}
\SetFuncArgSty{font csname}
\SetProgSty{font csname}
\SetArgSty{font csname}
\SetDataSty{font csname}
\SetCommentSty{font csname}
\SetProcNameSty{font csname}
\SetProcArgSty{font csname}
\SetBlockMarkersSty{font csname}
\SetAlCapFnt{font csname}
\SetAlCapNameFnt{font csname}
\SetAlTitleFnt{font csname}
\SetAlCapSty{font csname}
\SetAlCapNameSty{font csname}
\SetAlTitleSty{font csname}
\SetProcFnt{font csname}
\SetProcNameFnt{font csname}
\SetProcSty{font csname}
\SetProcArgFnt{font csname}

# controlling the layout of algorithms
\RestyleAlgo{style%keyvals}
#keyvals:\RestyleAlgo
plain
plainruled
boxed
ruled
algoruled
boxruled
tworuled
#endkeyvals
\SetAlgoVlined
\SetAlgoNoLine
\SetAlgoLined
\SetAlgoLongEnd
\SetAlgoShortEnd
\SetAlgoNoEnd
\SetInd{before space%l}{after space%l}
\SetAlgoHangIndent{length}
\SetVlineSkip{length}
\SetAlgoSkip{skip csname}
\SetAlgoInsideSkip{skip csname}
\algomargin#*
\IncMargin{length}
\DecMargin{length}
\interspacetitleruled#*
\interspacealgoruled#*
\interspacetitleboxruled#*

# comments
\SetSideCommentLeft
\SetSideCommentRight
\SetFillComment
\SetNoFillComment

# Input, output macros
\KwIn{input}#/algorithm
\KwOut{output}#/algorithm
\KwData{input}#/algorithm
\KwHData{input}#/algorithm
\KwResult{output}#/algorithm

# Basic keywords and blocks
\KwTo#/algorithm
\KwRet{value}#/algorithm
\Return{value}#/algorithm
\Begin{block inside}#/algorithm
\Begin(begin comment){block inside}#/algorithm

# comments
\tcc{comments%text}#/algorithm
\tcc*{comments%text}#/algorithm
\tcc*[alignment]{comments%text}#/algorithm
\tcp{comments%text}#/algorithm
\tcp*{comments%text}#/algorithm
\tcp*[alignment]{comments%text}#/algorithm

#keyvals:\tcc*,\tcp*
r
l
h
f
#endkeyvals

# if then else macros
\If{condition}{then block}#/algorithm
\If(then comment){condition}{then block}#/algorithm
\uIf{condition}{then block without end}#/algorithm
\uIf(then comment){condition}{then block without end}#/algorithm
\lIf{condition}{then line}#/algorithm
\lIf(if comment){condition}{then line}#/algorithm
\ElseIf{elseif block}#/algorithm
\ElseIf(elseif comment){elseif block}#/algorithm
\uElseIf{elseif block without end}#/algorithm
\uElseIf(elseif comment){elseif block without end}#/algorithm
\lElseIf{elseif line}#/algorithm
\lElseif(elseif line){elseif block}#/algorithm
\Else{else block}#/algorithm
\Else(else comment){else block}#/algorithm
\uElse{else block without end}#/algorithm
\uElse(else block comment){else block without end}#/algorithm
\lElse{else line}#/algorithm
\lElse(else comment){else line}#/algorithm
\eIf{condition}{then block}{else block}#/algorithm
\eIf(then comment){condition}{then block}(else comment){else block}#/algorithm
\eIf(then comment){condition}{then block}{else block}#/algorithm
\eIf{condition}{then block}(else comment){else block}#/algorithm
\leIf{condition}{then line}{else line}#/algorithm
\leIf(comment){condition}{then line}{else line}#/algorithm

# multiple condition selection
\Switch(switch comment){condition}{switch block}#/algorithm
\Switch{condition}{switch block}#/algorithm
\Case{case}{case block}#/algorithm
\Case(case comment){case}{case block}#/algorithm
\uCase{case}{case block without end}#/algorithm
\uCase(case comment){case}{case block without end}#/algorithm
\lCase{case}{case line}#/algorithm
\lCase(case comment){case}{case line}#/algorithm
\Other{otherwise block}#/algorithm
\Other(other comment){otherwise block}#/algorithm
\uOther{otherwise text}#/algorithm
\uOther(other comment){otherwise text}#/algorithm
\lOther{otherwise line}#/algorithm
\lOther(other comment){otherwise line}#/algorithm

# loops with test at beginning
\For{condition}{for block}#/algorithm
\For(for comment){condition}{for block}#/algorithm
\lFor{condition}{for line}#/algorithm
\lFor(for comment){condition}{for line}#/algorithm
\While{condition}{while block}#/algorithm
\While(while comment){condition}{while block}#/algorithm
\lWhile{condition}{while line}#/algorithm
\lWhile(while comment){condition}{while line}#/algorithm
\ForPar{condition}{foreach block}#/algorithm
\ForPar(foreach comment){condition}{foreach block}#/algorithm
\ForEach{condition}{foreach block}#/algorithm
\ForEach(foreach comment){condition}{foreach block}#/algorithm
\lForEach{condition}{foreach line}#/algorithm
\lForEach(foreach comment){condition}{foreach line}#/algorithm
\ForAll{condition}{forall block}#/algorithm
\ForAll(forall comment){condition}{forall block}#/algorithm
\lForAll{condition}{forall line}#/algorithm
\lForAll(forall comment){condition}{forall line}#/algorithm

# loops with test at end
\Repeat{end condition}{repeat block}#/algorithm
\Repeat(repeat comment){end condition}{repeat block}(until comment)#/algorithm
\Repeat(repeat comment){end condition}{repeat block}#/algorithm
\Repeat{end condition}{repeat block}(until comment)#/algorithm
\lRepeat{end condition}{repeat line}#/algorithm
\lRepeat(repeat comment){end condition}{repeat line}#/algorithm

# To define your own language keywords
\SetKwInput{csname}{name}
\SetKwInOut{csname}{name}
\ResetInOut{name}
\SetKw{csname}{name}
\SetKwHangingKw{csname}{name}
\SetKwData{csname}{name}
\SetKwArray{csname}{name}
\SetKwBlock{csname}{begin text}{end text}
\SetKwProg{csname}{name}{begin text}{end text}
\SetKwFunction{csname}{name}
\SetKwComment{csname}{begin text}{end text}
\SetKwIF{if csname}{elseif csname}{else csname}{if text}{then text}{elseif text}{else text}{endif text}
\SetKwSwitch{switch csname}{case csname}{other csname}{switch text}{do text}{case text}{other text}{endcase text}
\SetKwFor{csname}{for text}{do text}{endfor text}
\SetKwRepeat{csname}{repeat text}{until text}

# Other language predefined keywords
#ifOption:french
\HDonnees{données}#/algorithm
\Donnees{données}#/algorithm
\Res{résultats}#/algorithm
\Entree{entrées}#/algorithm
\Sortie{sorties}#/algorithm
\KwA#/algorithm
\Retour{valeur}#/algorithm
\Deb{intérieur du bloc}#/algorithm
\Repeter{condition d’arrêt}{bloc de la boucle}#/algorithm
\Si{condition}{bloc du alors}#/algorithm
\eSi{condition}{bloc du alors}{bloc du sinon}#/algorithm
\uSi{condition}{bloc du alors sans fin}#/algorithm
\lSi{condition}{ligne du alors}#/algorithm
\SinonSi{condition}{bloc du sinonsi}#/algorithm
\uSinonSi{condition}{bloc du sinonsi sans fin}#/algorithm
\lSinonSi{condition}{bloc du sinonsi sans fin}#/algorithm
\Sinon{bloc du sinon}#/algorithm
\uSinon{bloc du sinon sans fin}#/algorithm
\lSinon{ligne du sinon}#/algorithm
\Suivant{condition}{bloc du suivant-cas-alors}#/algorithm
\Cas{cas où}{bloc de ce cas}#/algorithm
\uCas{cas où}{bloc de ce cas sans fin}#/algorithm
\lCas{cas où}{ligne de ce cas}#/algorithm
\Autre{bloc de l’alternative}#/algorithm
\lAutre{bloc de l’alternative}#/algorithm
\Pour{condition}{bloc de la boucle}#/algorithm
\lPour{condition}{ligne de la boucle}#/algorithm
\PourPar{condition}{bloc de la boucle}#/algorithm
\lPourPar{condition}{ligne de la boucle}#/algorithm
\PourCh{condition}{bloc de la boucle}#/algorithm
\lPourCh{condition}{ligne de la boucle}#/algorithm
\PourTous{condition}{bloc de la boucle}#/algorithm
\lPourTous{condition}{ligne de la boucle}#/algorithm
\Tq{condition}{bloc de la boucle}#/algorithm
\lTq{condition}{ligne de la boucle}#/algorithm
#endif
#ifOption:frenchkw
\HDonnees{données}#/algorithm
\Donnees{données}#/algorithm
\Res{résultats}#/algorithm
\Entree{entrées}#/algorithm
\Sortie{sorties}#/algorithm
\KwA#/algorithm
\Retour{valeur}#/algorithm
\Deb{intérieur du bloc}#/algorithm
\Repeter{condition d’arrêt}{bloc de la boucle}#/algorithm
\Si{condition}{bloc du alors}#/algorithm
\eSi{condition}{bloc du alors}{bloc du sinon}#/algorithm
\uSi{condition}{bloc du alors sans fin}#/algorithm
\lSi{condition}{ligne du alors}#/algorithm
\SinonSi{condition}{bloc du sinonsi}#/algorithm
\uSinonSi{condition}{bloc du sinonsi sans fin}#/algorithm
\lSinonSi{condition}{bloc du sinonsi sans fin}#/algorithm
\Sinon{bloc du sinon}#/algorithm
\uSinon{bloc du sinon sans fin}#/algorithm
\lSinon{ligne du sinon}#/algorithm
\Suivant{condition}{bloc du suivant-cas-alors}#/algorithm
\Cas{cas où}{bloc de ce cas}#/algorithm
\uCas{cas où}{bloc de ce cas sans fin}#/algorithm
\lCas{cas où}{ligne de ce cas}#/algorithm
\Autre{bloc de l’alternative}#/algorithm
\lAutre{bloc de l’alternative}#/algorithm
\Pour{condition}{bloc de la boucle}#/algorithm
\lPour{condition}{ligne de la boucle}#/algorithm
\PourPar{condition}{bloc de la boucle}#/algorithm
\lPourPar{condition}{ligne de la boucle}#/algorithm
\PourCh{condition}{bloc de la boucle}#/algorithm
\lPourCh{condition}{ligne de la boucle}#/algorithm
\PourTous{condition}{bloc de la boucle}#/algorithm
\lPourTous{condition}{ligne de la boucle}#/algorithm
\Tq{condition}{bloc de la boucle}#/algorithm
\lTq{condition}{ligne de la boucle}#/algorithm
#endif

#ifOption:german
\Ein{Eingabe}#/algorithm
\Aus{Ausgabe}#/algorithm
\Daten{Daten}#/algorithm
\Ergebnis{Ergebnis}#/algorithm
\Bis{bis}#/algorithm
\KwZurueck{zurück}#/algorithm
\Zurueck{zurück}#/algorithm
\Beginn{Beginn}#/algorithm
\Wiederh{stop condition}{loop}#/algorithm
\lWiederh{stop condition}{line loop}#/algorithm
\eWenn{condition}{then text}{else text}#/algorithm
\Wenn{condition}{then text}#/algorithm
\uWenn{condition}{then text without end}#/algorithm
\lWenn{condition}{then line}#/algorithm
\SonstWenn{condition}{elseif text}#/algorithm
\uSonstWenn{condition}{elseif text without end}#/algorithm
\lSonstWenn{condition}{elseif line}#/algorithm
\Sonst{else text}#/algorithm
\uSonst{else text without end}#/algorithm
\lSonst{else line}#/algorithm
\Unterscheide{condition}{switch block}#/algorithm
\Fall{case of}{text}#/algorithm
\uFall{case of}{text}#/algorithm
\lFall{case of}{line text}#/algorithm
\Anderes{default text}#/algorithm
\lAnderes{default line}#/algorithm
\Fuer{condition}{loop}#/algorithm
\lFuer{condition}{line loop}#/algorithm
\FuerPar{condition}{loop}#/algorithm
\lFuerPar{condition}{line}#/algorithm
\FuerJedes{condition}{loop}#/algorithm
\lFuerJedes{condition}{line}#/algorithm
\FuerAlle{condition}{loop}#/algorithm
\lFuerAlle{condition}{line}#/algorithm
\Solange{condition}{loop}#/algorithm
\lSolange{condition}{line}#/algorithm
#endif
#ifOption:germankw
\Ein{Eingabe}#/algorithm
\Aus{Ausgabe}#/algorithm
\Daten{Daten}#/algorithm
\Ergebnis{Ergebnis}#/algorithm
\Bis{bis}#/algorithm
\KwZurueck{zurück}#/algorithm
\Zurueck{zurück}#/algorithm
\Beginn{Beginn}#/algorithm
\Wiederh{stop condition}{loop}#/algorithm
\lWiederh{stop condition}{line loop}#/algorithm
\eWenn{condition}{then text}{else text}#/algorithm
\Wenn{condition}{then text}#/algorithm
\uWenn{condition}{then text without end}#/algorithm
\lWenn{condition}{then line}#/algorithm
\SonstWenn{condition}{elseif text}#/algorithm
\uSonstWenn{condition}{elseif text without end}#/algorithm
\lSonstWenn{condition}{elseif line}#/algorithm
\Sonst{else text}#/algorithm
\uSonst{else text without end}#/algorithm
\lSonst{else line}#/algorithm
\Unterscheide{condition}{switch block}#/algorithm
\Fall{case of}{text}#/algorithm
\uFall{case of}{text}#/algorithm
\lFall{case of}{line text}#/algorithm
\Anderes{default text}#/algorithm
\lAnderes{default line}#/algorithm
\Fuer{condition}{loop}#/algorithm
\lFuer{condition}{line loop}#/algorithm
\FuerPar{condition}{loop}#/algorithm
\lFuerPar{condition}{line}#/algorithm
\FuerJedes{condition}{loop}#/algorithm
\lFuerJedes{condition}{line}#/algorithm
\FuerAlle{condition}{loop}#/algorithm
\lFuerAlle{condition}{line}#/algorithm
\Solange{condition}{loop}#/algorithm
\lSolange{condition}{line}#/algorithm
#endif

#ifOption:czech
\Vst{input}#/algorithm
\Vyst{input}#/algorithm
\Vysl{input}#/algorithm
#endif
#ifOption:czechkw
\Vst{input}#/algorithm
\Vyst{input}#/algorithm
\Vysl{input}#/algorithm
#endif

#ifOption:portuguese
\Entrada{Entrada}#/algorithm
\Saida{Saída}#/algorithm
\Dados{Dados}#/algorithm
\Resultado{Resultado}#/algorithm
\Ate#/algorithm
\KwRetorna{val}#/algorithm
\Retorna{val}#/algorithm
\Inicio{inside block}#/algorithm
\Repita{stop condition}{text loop}#/algorithm
\lRepita{stop condition}{line of the loop}#/algorithm
\eSe{condition}{then block}{else block}#/algorithm
\Se{condition}{then block}#/algorithm
\uSe{condition}{then block without end}#/algorithm
\lSe{condition}{then’s line text}#/algorithm
\Senao{else block}#/algorithm
\uSenao{else block without else}#/algorithm
\lSenao{else’s line text}#/algorithm
\SenaoSe{condition}{elseif block}#/algorithm
\uSenaoSe{condition}{elseif block without end}#/algorithm
\lSenaoSe{condition}{elseif’s line text}#/algorithm
\Selec{condition}{switch block}#/algorithm
\Caso{a case}{case block}#/algorithm
\uCaso{a case}{case block without end}#/algorithm
\lCaso{a case}{case’s line}#/algorithm
\Outro{otherwise block}#/algorithm
\lOutro{otherwise’s line}#/algorithm
\Para{condition}{text loop}#/algorithm
\lPara{condition}{line text loop}#/algorithm
\ParaPar{condition}{text loop}#/algorithm
\lParaPar{condition}{line text loop}#/algorithm
\ParaCada{condition}{text loop}#/algorithm
\lParaCada{condition}{line text loop}#/algorithm
\ParaTodo{condition}{text loop}#/algorithm
\lParaTodo{condition}{line text loop}#/algorithm
\Enqto{stop condition}{text loop}#/algorithm
\lEnqto{stop condition}{text loop}#/algorithm
#endif
#ifOption:portuguesekw
\Entrada{Entrada}#/algorithm
\Saida{Saída}#/algorithm
\Dados{Dados}#/algorithm
\Resultado{Resultado}#/algorithm
\Ate#/algorithm
\KwRetorna{val}#/algorithm
\Retorna{val}#/algorithm
\Inicio{inside block}#/algorithm
\Repita{stop condition}{text loop}#/algorithm
\lRepita{stop condition}{line of the loop}#/algorithm
\eSe{condition}{then block}{else block}#/algorithm
\Se{condition}{then block}#/algorithm
\uSe{condition}{then block without end}#/algorithm
\lSe{condition}{then’s line text}#/algorithm
\Senao{else block}#/algorithm
\uSenao{else block without else}#/algorithm
\lSenao{else’s line text}#/algorithm
\SenaoSe{condition}{elseif block}#/algorithm
\uSenaoSe{condition}{elseif block without end}#/algorithm
\lSenaoSe{condition}{elseif’s line text}#/algorithm
\Selec{condition}{switch block}#/algorithm
\Caso{a case}{case block}#/algorithm
\uCaso{a case}{case block without end}#/algorithm
\lCaso{a case}{case’s line}#/algorithm
\Outro{otherwise block}#/algorithm
\lOutro{otherwise’s line}#/algorithm
\Para{condition}{text loop}#/algorithm
\lPara{condition}{line text loop}#/algorithm
\ParaPar{condition}{text loop}#/algorithm
\lParaPar{condition}{line text loop}#/algorithm
\ParaCada{condition}{text loop}#/algorithm
\lParaCada{condition}{line text loop}#/algorithm
\ParaTodo{condition}{text loop}#/algorithm
\lParaTodo{condition}{line text loop}#/algorithm
\Enqto{stop condition}{text loop}#/algorithm
\lEnqto{stop condition}{text loop}#/algorithm
#endif

#ifOption:italiano
\KwIng{Ingresso}#/algorithm
\KwUsc{Uscita}#/algorithm
\KwDati{Dati}#/algorithm
\KwRisult{Risultato}#/algorithm
\KwA#/algorithm
\KwRitorna{ritorna}#/algorithm
\Ritorna{ritorna}#/algorithm
\Inizio{inside block}#/algorithm
\Ripeti{stop condition}{text loop}#/algorithm
\lRipeti{stop condition}{line of the loop}#/algorithm
\eSea{condition}{then block}{else block}#/algorithm
\Sea{condition}{then block}#/algorithm
\uSea{condition}{then block without end}#/algorithm
\lSea{condition}{then’s line text}#/algorithm
\AltSe{else block}#/algorithm
\uAltSe{else block without else}#/algorithm
\lAltSe{else’s line text}#/algorithm
\Altrimenti{condition}{elseif block}#/algorithm
\uAltrimenti{condition}{elseif block without end}#/algorithm
\lAltrimenti{condition}{elseif’s line text}#/algorithm
\Per{condition}{text loop}#/algorithm
\lPer{condition}{line text loop}#/algorithm
\PerPar{condition}{text loop}#/algorithm
\lPerPar{condition}{line text loop}#/algorithm
\PerCiascun{condition}{text loop}#/algorithm
\lPerCiascun{condition}{line text loop}#/algorithm
\PerTutti{condition}{text loop}#/algorithm
\lPerTutti{condition}{line text loop}#/algorithm
\Finche{stop condition}{text loop}#/algorithm
\lFinche{stop condition}{text loop}#/algorithm
#endif
#ifOption:italianokw
\KwIng{Ingresso}#/algorithm
\KwUsc{Uscita}#/algorithm
\KwDati{Dati}#/algorithm
\KwRisult{Risultato}#/algorithm
\KwA#/algorithm
\KwRitorna{ritorna}#/algorithm
\Ritorna{ritorna}#/algorithm
\Inizio{inside block}#/algorithm
\Ripeti{stop condition}{text loop}#/algorithm
\lRipeti{stop condition}{line of the loop}#/algorithm
\eSea{condition}{then block}{else block}#/algorithm
\Sea{condition}{then block}#/algorithm
\uSea{condition}{then block without end}#/algorithm
\lSea{condition}{then’s line text}#/algorithm
\AltSe{else block}#/algorithm
\uAltSe{else block without else}#/algorithm
\lAltSe{else’s line text}#/algorithm
\Altrimenti{condition}{elseif block}#/algorithm
\uAltrimenti{condition}{elseif block without end}#/algorithm
\lAltrimenti{condition}{elseif’s line text}#/algorithm
\Per{condition}{text loop}#/algorithm
\lPer{condition}{line text loop}#/algorithm
\PerPar{condition}{text loop}#/algorithm
\lPerPar{condition}{line text loop}#/algorithm
\PerCiascun{condition}{text loop}#/algorithm
\lPerCiascun{condition}{line text loop}#/algorithm
\PerTutti{condition}{text loop}#/algorithm
\lPerTutti{condition}{line text loop}#/algorithm
\Finche{stop condition}{text loop}#/algorithm
\lFinche{stop condition}{text loop}#/algorithm
#endif

#ifOption:spanish
\Datos{Datos}#/algorithm
\Resultado{Resultado}#/algorithm
\Entrada{Entrada}#/algorithm
\Salida{Salida}#/algorithm
\KwA#/algorithm
\KwDevolver{value}#/algorithm
\Devolver{value}#/algorithm
\Inicio{inside block}#/algorithm
\eSSi{condition}{then block}{else block}#/algorithm
\SSi{condition}{then block}#/algorithm
\uSSi{condition}{then block without end}#/algorithm
\lSSi{condition}{then line}#/algorithm
\EnOtroCasoSi{condition}{elseif block}#/algorithm
\uEnOtroCasoSi{condition}{elseif block}#/algorithm
\lEnOtroCasoSi{condition}{elseif line without end}#/algorithm
\EnOtroCaso{else block}#/algorithm
\uEnOtroCaso{else block without end}#/algorithm
\lEnOtroCaso{else line}#/algorithm
\Seleccionar{seleccionar}{caso block}#/algorithm
\uSeleccionar{seleccionar}{caso block without end}#/algorithm
\Caso{seleccionar}{caso block}#/algorithm
\lCaso{seleccionar}{caso line}#/algorithm
\Otro{sinó block}#/algorithm
\lOtro{sinó line}#/algorithm
\Para{condition}{loop block}#/algorithm
\lPara{condition}{loop line}#/algorithm
\ParaPara{condition}{loop block}#/algorithm
\lParaPara{condition}{loop line}#/algorithm
\EnParalelo{condition}{loop block}#/algorithm
\lEnParalelo{condition}{loop line}#/algorithm
\Mientras{condition}{loop block}#/algorithm
\lMientras{condition}{loop line}#/algorithm
\ParaCada{condition}{loop block}#/algorithm
\lParaCada{condition}{loop line}#/algorithm
\ParaTodo{condition}{loop block}#/algorithm
\lParaTodo{condition}{loop line}#/algorithm
\Repetir{stop condition}{loop block}#/algorithm
\lRepetir{stop condition}{line loop}#/algorithm
#endif
#ifOption:spanishkw
\Datos{Datos}#/algorithm
\Resultado{Resultado}#/algorithm
\Entrada{Entrada}#/algorithm
\Salida{Salida}#/algorithm
\KwA#/algorithm
\KwDevolver{value}#/algorithm
\Devolver{value}#/algorithm
\Inicio{inside block}#/algorithm
\eSSi{condition}{then block}{else block}#/algorithm
\SSi{condition}{then block}#/algorithm
\uSSi{condition}{then block without end}#/algorithm
\lSSi{condition}{then line}#/algorithm
\EnOtroCasoSi{condition}{elseif block}#/algorithm
\uEnOtroCasoSi{condition}{elseif block}#/algorithm
\lEnOtroCasoSi{condition}{elseif line without end}#/algorithm
\EnOtroCaso{else block}#/algorithm
\uEnOtroCaso{else block without end}#/algorithm
\lEnOtroCaso{else line}#/algorithm
\Seleccionar{seleccionar}{caso block}#/algorithm
\uSeleccionar{seleccionar}{caso block without end}#/algorithm
\Caso{seleccionar}{caso block}#/algorithm
\lCaso{seleccionar}{caso line}#/algorithm
\Otro{sinó block}#/algorithm
\lOtro{sinó line}#/algorithm
\Para{condition}{loop block}#/algorithm
\lPara{condition}{loop line}#/algorithm
\ParaPara{condition}{loop block}#/algorithm
\lParaPara{condition}{loop line}#/algorithm
\EnParalelo{condition}{loop block}#/algorithm
\lEnParalelo{condition}{loop line}#/algorithm
\Mientras{condition}{loop block}#/algorithm
\lMientras{condition}{loop line}#/algorithm
\ParaCada{condition}{loop block}#/algorithm
\lParaCada{condition}{loop line}#/algorithm
\ParaTodo{condition}{loop block}#/algorithm
\lParaTodo{condition}{loop line}#/algorithm
\Repetir{stop condition}{loop block}#/algorithm
\lRepetir{stop condition}{line loop}#/algorithm
#endif

#ifOption:croatian
\KwUlaz{input}#/algorithm
\KwIzlaz{input}#/algorithm
\KwPodatci{input}#/algorithm
\KwRezultat{input}#/algorithm
\KwDo#/algorithm
\KwVrati#/algorithm
\Vrati#/algorithm
\Pocetak{inside block}#/algorithm
\Ponavljaj{stop condition}{loop block}#/algorithm
\lPonavljaj{stop condition}{line loop}#/algorithm
\eAko{condition}{then block}{else block}#/algorithm
\Ako{condition}{then block}#/algorithm
\uAko{condition}{then block without end}#/algorithm
\lAko{condition}{then line}#/algorithm
\InaceAko{condition}{elseif block}#/algorithm
\uInaceAko{condition}{elseif block}#/algorithm
\lInaceAko{condition}{elseif line without end}#/algorithm
\Inace{else block}#/algorithm
\uInace{else block without end}#/algorithm
\lInace{else line}#/algorithm
\Granaj{condition}{Seleccionar caso block}#/algorithm
\uGranaj{seleccionar}{caso block without end}#/algorithm
\Slucaj{case}{case block}#/algorithm
\uSlucaj{case}{case block without end}#/algorithm
\lSlucaj{case}{case line}#/algorithm
\OstaliSlucajevi{otherwise block}#/algorithm
\lOstaliSlucajevi{otherwise line}#/algorithm
\uOstaliSlucajevi{otherwise text}#/algorithm
\Za{condition}{loop block}#/algorithm
\lZa{condition}{loop line}#/algorithm
\ZaPar{condition}{loop block}#/algorithm
\lZaPar{condition}{loop line}#/algorithm
\ZaSvaki{condition}{loop block}#/algorithm
\lZaSvaki{condition}{loop line}#/algorithm
\ZaSvaku{condition}{loop block}#/algorithm
\lZaSvaku{condition}{loop line}#/algorithm
\ZaSvako{condition}{loop block}#/algorithm
\lZaSvako{condition}{loop line}#/algorithm
\ZaSve{condition}{loop block}#/algorithm
\lZaSve{condition}{loop line}#/algorithm
\Dok{condition}{loop block}#/algorithm
\lDok{condition}{loop line}#/algorithm
#endif
#ifOption:croatiankw
\KwUlaz{input}#/algorithm
\KwIzlaz{input}#/algorithm
\KwPodatci{input}#/algorithm
\KwRezultat{input}#/algorithm
\KwDo#/algorithm
\KwVrati#/algorithm
\Vrati#/algorithm
\Pocetak{inside block}#/algorithm
\Ponavljaj{stop condition}{loop block}#/algorithm
\lPonavljaj{stop condition}{line loop}#/algorithm
\eAko{condition}{then block}{else block}#/algorithm
\Ako{condition}{then block}#/algorithm
\uAko{condition}{then block without end}#/algorithm
\lAko{condition}{then line}#/algorithm
\InaceAko{condition}{elseif block}#/algorithm
\uInaceAko{condition}{elseif block}#/algorithm
\lInaceAko{condition}{elseif line without end}#/algorithm
\Inace{else block}#/algorithm
\uInace{else block without end}#/algorithm
\lInace{else line}#/algorithm
\Granaj{condition}{Seleccionar caso block}#/algorithm
\uGranaj{seleccionar}{caso block without end}#/algorithm
\Slucaj{case}{case block}#/algorithm
\uSlucaj{case}{case block without end}#/algorithm
\lSlucaj{case}{case line}#/algorithm
\OstaliSlucajevi{otherwise block}#/algorithm
\lOstaliSlucajevi{otherwise line}#/algorithm
\uOstaliSlucajevi{otherwise text}#/algorithm
\Za{condition}{loop block}#/algorithm
\lZa{condition}{loop line}#/algorithm
\ZaPar{condition}{loop block}#/algorithm
\lZaPar{condition}{loop line}#/algorithm
\ZaSvaki{condition}{loop block}#/algorithm
\lZaSvaki{condition}{loop line}#/algorithm
\ZaSvaku{condition}{loop block}#/algorithm
\lZaSvaku{condition}{loop line}#/algorithm
\ZaSvako{condition}{loop block}#/algorithm
\lZaSvako{condition}{loop line}#/algorithm
\ZaSve{condition}{loop block}#/algorithm
\lZaSve{condition}{loop line}#/algorithm
\Dok{condition}{loop block}#/algorithm
\lDok{condition}{loop line}#/algorithm
#endif

# not documented
\algocfautorefname#*
\algocffuncautorefname#*
\algocfprocautorefname#*
\algoendfloat#*
\algoheightrule#*
\algoheightruledefault#*
\AlgoLineautorefname#*
\algoplace#*
\algorithmautorefname#*
\algorithmcflinename#*
\algorithmcfname#*
\algotitleheightrule#*
\algotitleheightruledefault#*
\algowidth#*
\begin{algocf*}#*\algorithm
\begin{algocf*}[placement]#*
\begin{algocf}#*\algorithm
\begin{algocf}[placement]#*
\end{algocf*}#*
\end{algocf}#*
\enl#*
\functionautorefname#*
\Hlne#*
\Indentp{arg}#*
\Indmm#*
\Indpp#*
\inoutindent#*
\inoutsize#*
\InOutSizeDefined#*
\listalgorithmcfname#*
\listofalgocfs#*
\next#*
\procedureautorefname#*
\SetEndCharOfAlgoLine{arg}#*
\setLeftLinesNumbers#*
\SetNothing#*
\setRightLinesNumbers#*
\skipalgocfslide#*
\skiphlne#*
\skiplength#*
\skiplinenumber#*
\skiprule#*
\skiptext#*
\skiptotal#*
\test#*
\thealgocf#*
\thealgocfline#*
\thealgocfproc#*
\theHalgocf#*
\theHalgocffunc#*
\theHalgocfproc#*
\theHAlgoLine#*
\vespace#*
