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
\begin{algorithm2e}
\begin{algorithm2e}[placement]
\end{algorithm2e}
\begin{algorithm2e*}#*
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
\begin{algorithm*}#*
\begin{algorithm*}[placement]#*
\end{algorithm*}#*
\begin{function}
\begin{function}[placement]
\end{function}
\begin{function*}#*
\begin{function*}[placement]#*
\end{function*}#*
\begin{procedure}
\begin{procedure}[placement]
\end{procedure}
\begin{procedure*}#*
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
\nl#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
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
\KwIn{input}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\KwOut{output}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\KwData{input}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\KwHData{input}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\KwResult{output}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*

# Basic keywords and blocks
\KwTo#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\KwRet{value}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Return{value}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Begin{block inside}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Begin(begin comment){block inside}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*

# comments
\tcc{comments%text}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\tcc*{comments%text}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\tcc*[alignment]{comments%text}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\tcp{comments%text}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\tcp*{comments%text}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\tcp*[alignment]{comments%text}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*

#keyvals:\tcc*,\tcp*
r
l
h
f
#endkeyvals

# if then else macros
\If{condition}{then block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\If(then comment){condition}{then block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uIf{condition}{then block without end}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uIf(then comment){condition}{then block without end}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lIf{condition}{then line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lIf(if comment){condition}{then line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\ElseIf{elseif block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\ElseIf(elseif comment){elseif block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uElseIf{elseif block without end}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uElseIf(elseif comment){elseif block without end}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lElseIf{elseif line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lElseif(elseif line){elseif block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Else{else block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Else(else comment){else block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uElse{else block without end}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uElse(else block comment){else block without end}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lElse{else line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lElse(else comment){else line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\eIf{condition}{then block}{else block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\eIf(then comment){condition}{then block}(else comment){else block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\eIf(then comment){condition}{then block}{else block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\eIf{condition}{then block}(else comment){else block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\leIf{condition}{then line}{else line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\leIf(comment){condition}{then line}{else line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*

# multiple condition selection
\Switch(switch comment){condition}{switch block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Switch{condition}{switch block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Case{case}{case block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Case(case comment){case}{case block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uCase{case}{case block without end}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uCase(case comment){case}{case block without end}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lCase{case}{case line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lCase(case comment){case}{case line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Other{otherwise block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Other(other comment){otherwise block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uOther{otherwise text}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uOther(other comment){otherwise text}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lOther{otherwise line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lOther(other comment){otherwise line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*

# loops with test at beginning
\For{condition}{for block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\For(for comment){condition}{for block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lFor{condition}{for line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lFor(for comment){condition}{for line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\While{condition}{while block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\While(while comment){condition}{while block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lWhile{condition}{while line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lWhile(while comment){condition}{while line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\ForPar{condition}{foreach block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\ForPar(foreach comment){condition}{foreach block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\ForEach{condition}{foreach block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\ForEach(foreach comment){condition}{foreach block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lForEach{condition}{foreach line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lForEach(foreach comment){condition}{foreach line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\ForAll{condition}{forall block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\ForAll(forall comment){condition}{forall block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lForAll{condition}{forall line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lForAll(forall comment){condition}{forall line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*

# loops with test at end
\Repeat{end condition}{repeat block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Repeat(repeat comment){end condition}{repeat block}(until comment)#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Repeat(repeat comment){end condition}{repeat block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Repeat{end condition}{repeat block}(until comment)#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lRepeat{end condition}{repeat line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lRepeat(repeat comment){end condition}{repeat line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*

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
\HDonnees{données}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Donnees{données}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Res{résultats}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Entree{entrées}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Sortie{sorties}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\KwA#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Retour{valeur}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Deb{intérieur du bloc}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Repeter{condition d’arrêt}{bloc de la boucle}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Si{condition}{bloc du alors}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\eSi{condition}{bloc du alors}{bloc du sinon}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uSi{condition}{bloc du alors sans fin}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lSi{condition}{ligne du alors}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\SinonSi{condition}{bloc du sinonsi}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uSinonSi{condition}{bloc du sinonsi sans fin}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lSinonSi{condition}{bloc du sinonsi sans fin}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Sinon{bloc du sinon}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uSinon{bloc du sinon sans fin}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lSinon{ligne du sinon}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Suivant{condition}{bloc du suivant-cas-alors}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Cas{cas où}{bloc de ce cas}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uCas{cas où}{bloc de ce cas sans fin}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lCas{cas où}{ligne de ce cas}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Autre{bloc de l’alternative}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lAutre{bloc de l’alternative}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Pour{condition}{bloc de la boucle}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lPour{condition}{ligne de la boucle}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\PourPar{condition}{bloc de la boucle}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lPourPar{condition}{ligne de la boucle}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\PourCh{condition}{bloc de la boucle}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lPourCh{condition}{ligne de la boucle}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\PourTous{condition}{bloc de la boucle}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lPourTous{condition}{ligne de la boucle}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Tq{condition}{bloc de la boucle}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lTq{condition}{ligne de la boucle}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
#endif
#ifOption:frenchkw
\HDonnees{données}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Donnees{données}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Res{résultats}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Entree{entrées}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Sortie{sorties}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\KwA#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Retour{valeur}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Deb{intérieur du bloc}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Repeter{condition d’arrêt}{bloc de la boucle}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Si{condition}{bloc du alors}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\eSi{condition}{bloc du alors}{bloc du sinon}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uSi{condition}{bloc du alors sans fin}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lSi{condition}{ligne du alors}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\SinonSi{condition}{bloc du sinonsi}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uSinonSi{condition}{bloc du sinonsi sans fin}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lSinonSi{condition}{bloc du sinonsi sans fin}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Sinon{bloc du sinon}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uSinon{bloc du sinon sans fin}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lSinon{ligne du sinon}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Suivant{condition}{bloc du suivant-cas-alors}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Cas{cas où}{bloc de ce cas}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uCas{cas où}{bloc de ce cas sans fin}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lCas{cas où}{ligne de ce cas}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Autre{bloc de l’alternative}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lAutre{bloc de l’alternative}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Pour{condition}{bloc de la boucle}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lPour{condition}{ligne de la boucle}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\PourPar{condition}{bloc de la boucle}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lPourPar{condition}{ligne de la boucle}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\PourCh{condition}{bloc de la boucle}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lPourCh{condition}{ligne de la boucle}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\PourTous{condition}{bloc de la boucle}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lPourTous{condition}{ligne de la boucle}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Tq{condition}{bloc de la boucle}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lTq{condition}{ligne de la boucle}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
#endif

#ifOption:german
\Ein{Eingabe}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Aus{Ausgabe}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Daten{Daten}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Ergebnis{Ergebnis}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Bis{bis}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\KwZurueck{zurück}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Zurueck{zurück}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Beginn{Beginn}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Wiederh{stop condition}{loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lWiederh{stop condition}{line loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\eWenn{condition}{then text}{else text}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Wenn{condition}{then text}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uWenn{condition}{then text without end}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lWenn{condition}{then line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\SonstWenn{condition}{elseif text}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uSonstWenn{condition}{elseif text without end}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lSonstWenn{condition}{elseif line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Sonst{else text}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uSonst{else text without end}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lSonst{else line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Unterscheide{condition}{switch block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Fall{case of}{text}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uFall{case of}{text}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lFall{case of}{line text}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Anderes{default text}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lAnderes{default line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Fuer{condition}{loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lFuer{condition}{line loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\FuerPar{condition}{loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lFuerPar{condition}{line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\FuerJedes{condition}{loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lFuerJedes{condition}{line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\FuerAlle{condition}{loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lFuerAlle{condition}{line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Solange{condition}{loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lSolange{condition}{line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
#endif
#ifOption:germankw
\Ein{Eingabe}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Aus{Ausgabe}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Daten{Daten}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Ergebnis{Ergebnis}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Bis{bis}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\KwZurueck{zurück}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Zurueck{zurück}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Beginn{Beginn}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Wiederh{stop condition}{loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lWiederh{stop condition}{line loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\eWenn{condition}{then text}{else text}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Wenn{condition}{then text}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uWenn{condition}{then text without end}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lWenn{condition}{then line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\SonstWenn{condition}{elseif text}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uSonstWenn{condition}{elseif text without end}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lSonstWenn{condition}{elseif line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Sonst{else text}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uSonst{else text without end}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lSonst{else line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Unterscheide{condition}{switch block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Fall{case of}{text}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uFall{case of}{text}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lFall{case of}{line text}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Anderes{default text}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lAnderes{default line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Fuer{condition}{loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lFuer{condition}{line loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\FuerPar{condition}{loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lFuerPar{condition}{line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\FuerJedes{condition}{loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lFuerJedes{condition}{line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\FuerAlle{condition}{loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lFuerAlle{condition}{line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Solange{condition}{loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lSolange{condition}{line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
#endif

#ifOption:czech
\Vst{input}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Vyst{input}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Vysl{input}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
#endif
#ifOption:czechkw
\Vst{input}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Vyst{input}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Vysl{input}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
#endif

#ifOption:portuguese
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
#endif
#ifOption:portuguesekw
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
#endif

#ifOption:italiano
\KwIng{Ingresso}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\KwUsc{Uscita}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\KwDati{Dati}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\KwRisult{Risultato}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\KwA#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\KwRitorna{ritorna}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Ritorna{ritorna}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Inizio{inside block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Ripeti{stop condition}{text loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lRipeti{stop condition}{line of the loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\eSea{condition}{then block}{else block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Sea{condition}{then block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uSea{condition}{then block without end}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lSea{condition}{then’s line text}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\AltSe{else block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uAltSe{else block without else}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lAltSe{else’s line text}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Altrimenti{condition}{elseif block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uAltrimenti{condition}{elseif block without end}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lAltrimenti{condition}{elseif’s line text}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Per{condition}{text loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lPer{condition}{line text loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\PerPar{condition}{text loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lPerPar{condition}{line text loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\PerCiascun{condition}{text loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lPerCiascun{condition}{line text loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\PerTutti{condition}{text loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lPerTutti{condition}{line text loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Finche{stop condition}{text loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lFinche{stop condition}{text loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
#endif
#ifOption:italianokw
\KwIng{Ingresso}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\KwUsc{Uscita}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\KwDati{Dati}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\KwRisult{Risultato}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\KwA#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\KwRitorna{ritorna}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Ritorna{ritorna}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Inizio{inside block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Ripeti{stop condition}{text loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lRipeti{stop condition}{line of the loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\eSea{condition}{then block}{else block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Sea{condition}{then block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uSea{condition}{then block without end}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lSea{condition}{then’s line text}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\AltSe{else block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uAltSe{else block without else}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lAltSe{else’s line text}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Altrimenti{condition}{elseif block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uAltrimenti{condition}{elseif block without end}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lAltrimenti{condition}{elseif’s line text}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Per{condition}{text loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lPer{condition}{line text loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\PerPar{condition}{text loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lPerPar{condition}{line text loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\PerCiascun{condition}{text loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lPerCiascun{condition}{line text loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\PerTutti{condition}{text loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lPerTutti{condition}{line text loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Finche{stop condition}{text loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lFinche{stop condition}{text loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
#endif

#ifOption:spanish
\Datos{Datos}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Resultado{Resultado}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Entrada{Entrada}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Salida{Salida}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\KwA#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\KwDevolver{value}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Devolver{value}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Inicio{inside block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\eSSi{condition}{then block}{else block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\SSi{condition}{then block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uSSi{condition}{then block without end}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lSSi{condition}{then line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\EnOtroCasoSi{condition}{elseif block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uEnOtroCasoSi{condition}{elseif block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lEnOtroCasoSi{condition}{elseif line without end}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\EnOtroCaso{else block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uEnOtroCaso{else block without end}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lEnOtroCaso{else line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Seleccionar{seleccionar}{caso block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uSeleccionar{seleccionar}{caso block without end}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Caso{seleccionar}{caso block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lCaso{seleccionar}{caso line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Otro{sinó block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lOtro{sinó line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Para{condition}{loop block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lPara{condition}{loop line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\ParaPara{condition}{loop block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lParaPara{condition}{loop line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\EnParalelo{condition}{loop block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lEnParalelo{condition}{loop line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Mientras{condition}{loop block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lMientras{condition}{loop line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\ParaCada{condition}{loop block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lParaCada{condition}{loop line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\ParaTodo{condition}{loop block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lParaTodo{condition}{loop line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Repetir{stop condition}{loop block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lRepetir{stop condition}{line loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
#endif
#ifOption:spanishkw
\Datos{Datos}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Resultado{Resultado}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Entrada{Entrada}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Salida{Salida}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\KwA#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\KwDevolver{value}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Devolver{value}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Inicio{inside block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\eSSi{condition}{then block}{else block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\SSi{condition}{then block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uSSi{condition}{then block without end}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lSSi{condition}{then line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\EnOtroCasoSi{condition}{elseif block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uEnOtroCasoSi{condition}{elseif block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lEnOtroCasoSi{condition}{elseif line without end}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\EnOtroCaso{else block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uEnOtroCaso{else block without end}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lEnOtroCaso{else line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Seleccionar{seleccionar}{caso block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uSeleccionar{seleccionar}{caso block without end}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Caso{seleccionar}{caso block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lCaso{seleccionar}{caso line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Otro{sinó block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lOtro{sinó line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Para{condition}{loop block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lPara{condition}{loop line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\ParaPara{condition}{loop block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lParaPara{condition}{loop line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\EnParalelo{condition}{loop block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lEnParalelo{condition}{loop line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Mientras{condition}{loop block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lMientras{condition}{loop line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\ParaCada{condition}{loop block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lParaCada{condition}{loop line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\ParaTodo{condition}{loop block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lParaTodo{condition}{loop line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Repetir{stop condition}{loop block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lRepetir{stop condition}{line loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
#endif

#ifOption:croatian
\KwUlaz{input}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\KwIzlaz{input}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\KwPodatci{input}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\KwRezultat{input}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\KwDo#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\KwVrati#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Vrati#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Pocetak{inside block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Ponavljaj{stop condition}{loop block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lPonavljaj{stop condition}{line loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\eAko{condition}{then block}{else block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Ako{condition}{then block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uAko{condition}{then block without end}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lAko{condition}{then line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\InaceAko{condition}{elseif block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uInaceAko{condition}{elseif block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lInaceAko{condition}{elseif line without end}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Inace{else block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uInace{else block without end}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lInace{else line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Granaj{condition}{Seleccionar caso block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uGranaj{seleccionar}{caso block without end}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Slucaj{case}{case block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uSlucaj{case}{case block without end}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lSlucaj{case}{case line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\OstaliSlucajevi{otherwise block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lOstaliSlucajevi{otherwise line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uOstaliSlucajevi{otherwise text}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Za{condition}{loop block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lZa{condition}{loop line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\ZaPar{condition}{loop block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lZaPar{condition}{loop line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\ZaSvaki{condition}{loop block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lZaSvaki{condition}{loop line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\ZaSvaku{condition}{loop block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lZaSvaku{condition}{loop line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\ZaSvako{condition}{loop block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lZaSvako{condition}{loop line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\ZaSve{condition}{loop block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lZaSve{condition}{loop line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Dok{condition}{loop block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lDok{condition}{loop line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
#endif
#ifOption:croatiankw
\KwUlaz{input}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\KwIzlaz{input}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\KwPodatci{input}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\KwRezultat{input}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\KwDo#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\KwVrati#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Vrati#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Pocetak{inside block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Ponavljaj{stop condition}{loop block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lPonavljaj{stop condition}{line loop}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\eAko{condition}{then block}{else block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Ako{condition}{then block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uAko{condition}{then block without end}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lAko{condition}{then line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\InaceAko{condition}{elseif block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uInaceAko{condition}{elseif block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lInaceAko{condition}{elseif line without end}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Inace{else block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uInace{else block without end}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lInace{else line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Granaj{condition}{Seleccionar caso block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uGranaj{seleccionar}{caso block without end}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Slucaj{case}{case block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uSlucaj{case}{case block without end}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lSlucaj{case}{case line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\OstaliSlucajevi{otherwise block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lOstaliSlucajevi{otherwise line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\uOstaliSlucajevi{otherwise text}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Za{condition}{loop block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lZa{condition}{loop line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\ZaPar{condition}{loop block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lZaPar{condition}{loop line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\ZaSvaki{condition}{loop block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lZaSvaki{condition}{loop line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\ZaSvaku{condition}{loop block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lZaSvaku{condition}{loop line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\ZaSvako{condition}{loop block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lZaSvako{condition}{loop line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\ZaSve{condition}{loop block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lZaSve{condition}{loop line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\Dok{condition}{loop block}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
\lDok{condition}{loop line}#/algocf,algocf*,algorithm,algorithm*,function,function*,procedure,procedure*,algorithm2e,algorithm2e*
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
\begin{algocf*}#*
\begin{algocf*}[placement]#*
\begin{algocf}#*
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
