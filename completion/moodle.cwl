# moodle package
# Matthew Bertucci 2023/01/29 for v1.0

#include:xkeyval
#include:environ
#include:amssymb
#include:iftex
#include:etoolbox
#include:xpatch
#include:array
#include:ifplatform
#include:shellesc
#include:readprov
#include:fancybox
#include:getitems

#keyvals:\usepackage/moodle#c
draft
handout
final
nostamp
tikz
svg
section
section*
subsection
subsection*
feedbackleft
feedbackright
samepage
LMS=%<major.minor%>
pluginfile
#endkeyvals

#ifOption:handout
#include:randomlist
#endif

#ifOption:svg
#include:graphicx
#endif

#ifOption:tikz
#include:tikz
#include:varwidth
\embedaspict{LaTeX content%text}
#endif

\begin{quiz}{category name%text}
\begin{quiz}[options%keyvals]{category name%text}
\end{quiz}

\moodleset{options%keyvals}

\setcategory{category name%text}
\setsubcategory{subcategory name%text}

\item*
\item[options]
\item[options]*

\begin{truefalse}{question name%text}
\begin{truefalse}[options%keyvals]{question name%text}
\end{truefalse}
\begin{multi}{question name%text}
\begin{multi}[options%keyvals]{question name%text}
\end{multi}
\begin{numerical}{question name%text}
\begin{numerical}[options%keyvals]{question name%text}
\end{numerical}
\begin{shortanswer}{question name%text}
\begin{shortanswer}[options%keyvals]{question name%text}
\end{shortanswer}
\begin{essay}{question name%text}
\begin{essay}[options%keyvals]{question name%text}
\end{essay}
\begin{matching}{question name%text}
\begin{matching}[options%keyvals]{question name%text}
\end{matching}
\begin{cloze}{question name%text}
\begin{cloze}[options%keyvals]{question name%text}
\end{cloze}
\begin{description}{question name%text}
\begin{description}[options%keyvals]{question name%text}
\end{description}
\begin{}{question name%text}
\begin{}[options%keyvals]{question name%text}
\end{}
\begin{}{question name%text}
\begin{}[options%keyvals]{question name%text}
\end{}

#keyvals:\begin{quiz},\moodleset,\begin{truefalse},\begin{multi},\begin{numerical},\begin{shortanswer},\begin{essay},\begin{matching},\begin{cloze}
points=%<number%>
default grade=%<number%>
penalty=%<fraction%>
fraction=%<number%>
fractiontol=%<value%>
feedback={%<text%>}
tags={%<tag1,tag2,...%>}
shuffle#true,false
numbering=#alph,Alph,arabic,roman,Roman,none
single#true,false
sanction=%<number%>
multiple#true,false
allornothing#true,false
tolerance=%<value%>
case sensitive#true,false
usecase#true,false
response required
response format=#html,file,html+file,text,monospaced
response field lines=#5,10,15,20,25,30,25,40
attachments allowed=#0,1,2,3,unlimited
attachments required=#0,1,2,3
template={%<text%>}
drag and drop#true,false
dd#true,false
vertical
horizontal
inline
ppi=%<pixels per inch%>
#endkeyvals

\blank

\htmlonly{HTML content}
\htmlonly[LaTeX content%text]{HTML content}
\htmlregister{cmd}
\moodleregisternewcommands

#keyvals:\includegraphics
ppi=%<pixels per inch%>
#endkeyvals

\ghostscriptcommand{executable filename}
\imagemagickcommand{executable filename}
\optipngcommand{executable filename}
\PDFtoSVGcommand{executable filename}
\SVGtoPDFcommand{executable filename}
\optiSVGcommand{executable filename}

\verbatiminput{file}
\VerbatimInput{file}
\VerbatimInput[options%keyvals]{file}
\BVerbatimInput{file}
\BVerbatimInput[options%keyvals]{file}
\LVerbatimInput{file}
\LVerbatimInput[options%keyvals]{file}
\inputminted{language}{file}
\inputminted[options%keyvals]{language}{file}

#keyvals:\VerbatimInput,\BVerbatimInput,\LVerbatimInput,\inputminted
gobble=%<integer%>
autogobble#true,false
tabsize=%<integer%>
numbers=#none,left,right,both
firstnumber=%<auto|last|<integer>%>
firstline=%<integer%>
lastline=%<integer%>
numberblanklines#true,false
highlightlines={%<line ranges%>}
style=%<style name%>
#endkeyvals

\moodledate#S
\moodleversion#S

# not documented
\ConvertToBaseLXIV{arg1}{arg2}#S
\DeclareGraphicsAlien{arg1}{arg2}{arg3}#S
\DeclareMediaFormat{arg1}{arg2}{arg3}#S
\DeleteFilecommand#S
\DevNullcommand#S
\ExportTikz#S
\OptimizeExport#S
\OutputFile#S
\SourceFile#S
\TikzExportExtension#S
\TikzExportMIME#S
\advancemathmodecounter{arg1}#S
\aftertext#S
\baselxivcommand#S
\calculateindent{arg1}#S
\closemoodleout#S
\cmdline#S
\converttohtmlmacro{arg1}{arg2}#S
\displaymathleftdelim#S
\displaymathrightdelim{arg1}#S
\ds#S
\endclozemode#S
\filenamewithsuffixtomacro{arg1}{arg2}{arg3}#S
\gscmdline#S
\includegraphics{arg1}{arg2}#S
\inlinemathleftdelim#S
\inlinemathrightdelim{arg1}#S
\jobnamewithsuffixtomacro{arg1}{arg2}#S
\mathtext#S
\MoveFilecommand#S
\newxml#S
\normalcatcodes#S
\oldhref#S
\oldincludegraphics#S
\oldurl#S
\openclozemode#S
\openmoodleout#S
\otherampersand#S
\othercaret#S
\otherdollar#S
\otherequal#S
\otherhash#S
\otherlbrace#S
\otherlbracket#S
\otherpercent#S
\otherrbracket#S
\othersemicol#S
\otherspace#S
\othertilde#S
\passvalueaftergroup{arg1}#S
\questiontext{arg1}#S
\retokenizingcatcodes#S
\savebaselxivdata#S
\saveclozemultichoiceanswer{arg1}#S
\saveclozenumericalanswer{arg1}#S
\saveclozeshortansweranswer{arg1}#S
\savematchinganswer{arg1}#S
\savemultianswer{arg1}#S
\savenumericalanswer{arg1}#S
\saveshortansweranswer{arg1}#S
\savetruefalseanswer{arg1}#S
\swaptotrueendenvironment{arg1}{arg2}#S
\targetext#S
\targetfmt#S
\testforquote{arg1}{arg2}#S
\texttorescan#S
\tikzifexternalizing{arg1}{arg2}#S
\toadd#S
\verbcatcodes#S
\writeclozequestion#S
\writeessayquestion#S
\writematchingquestion#S
\writemultiquestion#S
\writenumericalquestion#S
\writeshortanswerquestion#S
\writetomoodle[opt]{arg1}#S
\writetomoodle{arg1}#S
\writetruefalsequestion#S
\xa{arg1}#S
\xmlDisplayVerbatimBox#S
