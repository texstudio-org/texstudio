# jj_game class
# Matthew Bertucci 2022/05/10 for v3.1

#include:xkeyval
#include:ifpdf
#include:ifxetex
#include:web
#include:eforms
#include:verbatim
#include:comment
#include:calc

#keyvals:\documentclass/jj_game#c
pdftex
luatex
dvips
dvipsone
dvipdfm
dvipdfmx
xetex
debug
final
double
twoplayer
pro
forcredit
allowpeeking
nodesigngraphics
design=#jeopardy,florida,iceland,hornet,qatar,norway,germany,bahamas,spain,custom
lang=#english,german
# options passed to article class
a4paper
a5paper
b5paper
letterpaper
legalpaper
executivepaper
landscape
10pt
11pt
12pt
oneside
twoside
draft
titlepage
notitlepage
onecolumn
twocolumn
leqno
fleqn
openbib
#endkeyvals

\DeclareColors{keyvals}

#keyvals:\DeclareColors#c
fillCells: %<color%>
fillBanner: %<color%>
textBanner: %<color%>
textBoard: %<color%>
fillInstructions: %<color%>
fillGameBoard: %<color%>
fillQuestions: %<color%>
dollarColor: %<color%>
linkColor: %<color%>
#endkeyvals

\titleBanner{banner text%text}
\bannerTextFont#*
\bannerTextControl{text}#*

\GameDesign{keyvals}

#keyvals:\GameDesign#c
Cat: %<category%>
Cat: [%<font cmds%>] %<category%>
NumQuestions: %<integer%>
Goal: %<color%>
GoalPercentage: %<number%>
CellWidth: %<length%>
CellHeight: %<length%>
ExtraWidth: %<length%>
ExtraHeight: %<length%>
Champion: %<text%>
#endkeyvals

\APHidden{keyvals}
\APDollar{keyvals}
\APRight{keyvals}
\APWrong{keyvals}
\APScore{keyvals}

#keyvals:\APHidden#c
Champion: %<text%>
#endkeyvals

#keyvals:\APHidden#c,\APDollar#c,\APRight#c,\APWrong#c,\APScore#c
Font: %<font name%>
Size: %<number%>
TextColor: %<r g b%>
#endkeyvals

#keyvals:\APHidden#c,\APDollar#c,\APScore#c
BorderColor: %<r g b%>
FillColor: %<r g b%>
#endkeyvals

#keyvals:\APRight#c,\APWrong#c
Message: %<text%>
#endkeyvals

#keyvals:\APScore#c
CellHeight: %<length%>
CellWidth: %<length%>
AutoPlacement: %<true|false%>
Score: "%<text%>"
Currency: "%<symbol%>"
align: %<l|c|r%>
tpScaledCellWidth: %<factor%>
tpHighlightBorderColor: %<r g b%>
#endkeyvals

\ScoreBoard
\prependCurrency
\appendCurrency
\PlaceScoreBoard{code}
\begin{instructions}
\end{instructions}
\insertJJTitleBanner
\begin{Questions}
\end{Questions}
\begin{Category}{name}
\end{Category}
\begin{Question}#\tabular
\begin{Question}[num of columns]
\end{Question}
\Ans%<0|1%>
\begin{oAnswer}
\end{oAnswer}
\currencyHeading{text}
\aboveCurrencySkip{skip}
\contestantName{length}{width}
\contestantName[modifications]{length}{width}
\afterGameBoardInsertion{content%text}
\gameboardPrintButton
\printButtonCaption{text}
\printButtonLabel{text}
\contestantNameLabel{text}
\timestampLabel{text}
\timeStampFormat{text}

\setTwoPlayerOptions{keyvals}

#keyvals:\setTwoPlayerOptions#c
player1: %<name%>
player2: %<name%>
playerFmt: %<font commands%>
checkbox: %<true|false%>
#endkeyvals

\correctText{text}
\incorrectText{text}
\enterNamePlease{text}
\illegalAccessMsg{text}
\illegalAnswerTwiceMsg{text}
\playeriWinnerMsg{text}
\playeriiWinnerMsg{text}
\gameTiedMsg{text}
\bothLosersMsg{text}

\defineInstructionPageGraphic{imagefile}#g
\defineGameboardPageGraphic{imagefile}#g
\defineQuestionPagesGraphic{imagefile}#g

\includeFootBanner
\Goal

# not documented
\AAFAction#S
\AAVAction#S
\aboveanswersSkip#*
\bannerTextColor#S
\BboxHeight#S
\BboxWidth#S
\begin{solution}#S
\begin{verbatimwrite}#S
\bgb#S
\bgc#S
\bJJGInsertLayer#*
\calcPaperSize#S
\cell#S
\cellHeight#*
\cellWidth#*
\colnum#*
\convertToSetKeys{arg1}{arg2}#S
\corMsgnum#*
\currentCategory#S
\currQuiz#S
\debugfalse#S
\debugtrue#S
\defaultDollarColorAmt#S
\defaultfillBanner#S
\defaultfillCells#S
\defaultfillGameBoard#S
\defaultfillInstructions#S
\defaultfillQuestions#S
\defaultLinkColor#S
\defaulttextBanner#S
\defaulttextBoard#S
\dollarAP#S
\dollarColor#S
\doublefalse#S
\doubletrue#S
\eJJGInsertLayer#*
\end{solution}#S
\end{verbatimwrite}#S
\eqPTs#S
\errMsgnum#*
\EUR#S
\extraHeight#*
\extraWidth#*
\fillBanner#S
\fillCells#S
\fillGameBoard#S
\fillInstructions#S
\fillQuestions#S
\finalfalse#S
\finaltrue#S
\forpbx{arg}#S
\GameBoard#S
\gameboardPageTemplate#S
\gamebody#S
\gameCategories#S
\germanLocalization#S
\getBracArg#S
\getrow#S
\hmark{arg}#S
\ifdebug#S
\ifdouble#S
\iffinal#S
\ifjjgtwoplayer#S
\ifjjnopeeking#S
\instructionPageTemplate#S
\jjAdditionalCellJSActions#S
\jjAdditionalJSActions#*
\jjbothlosers#S
\jjCancelOutAeBProCatalog#S
\jjEnterNamePlease#S
\jjGameBoardPageBG#S
\jjgameTied#S
\jjgauthorURL#S
\jjgdesigngraphics#S
\jjgdriver#S
\jjgdummy#S
\jjgInputProCode#S
\jjgplayerihook#S
\jjgplayeriihook#S
\jjgtmplength#S
\jjgtwoplayerfalse#S
\jjgtwoplayertrue#S
\jjIllegalAccessMsg#S
\jjIllegalAnswerTwiceMsg#S
\jjImportForCreditCode#S
\JJinitSetup#S
\jjInputDesignChoice#S
\jjInstructionPageBG#S
\jjLangOpt#S
\jjnopeekingfalse#S
\jjnopeekingtrue#S
\jjplayeriiWinner#S
\jjplayeriWinner#S
\jjQuestionPagesBG#S
\jjTimeStampFormat#S
\makelink{arg}#S
\noPrintLayer{arg}#*
\numCategories#*
\numQuestions#*
\oField#S
\oiterate#S
\oloop{arg}#S
\orepeat#S
\outeriterate#S
\peekingOpenAction#S
\PoohBahBanner#S
\questionPagesTemplate#S
\Rect{text}#S
\redefineRespBoxActions#S
\resetMClabelsep#S
\rightAP#S
\rownum#*
\rulewidth#*
\scaleFactor#S
\setMClabelsep{arg}#S
\tableheight#*
\tablewidth#*
\textBanner#S
\textBoard#S
\theCurrencyAmt#S
\thejjgdriver#S
\thenewletter#S
\ThisPage#S
\thisxkvFamily#S
\twoplayerGame#S
\wrongAP#S