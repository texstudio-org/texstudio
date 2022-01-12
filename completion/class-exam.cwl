# exam class
# Matthew Bertucci 1/10/2022 for v2.7

#include:ifthen

#keyvals:\documentclass/exam#c
answers
cancelspace
addpoints
#endkeyvals

\addpoints
\addquestionobject
\answerclearance#*
\answerline
\answerline[answer%text]
\answerlinelength#*
\answerskip#*
\begin{checkboxes}
\begin{choices}
\begin{coverpages}
\begin{EnvFullwidth}
\begin{EnvUplevel}
\begin{examframed}#*
\begin{examleftbar}#*
\begin{oneparcheckboxes}
\begin{oneparchoices}
\begin{parts}
\begin{questions}
\begin{solution}
\begin{solution}[space%l]
\begin{solutionbox}{size%l}
\begin{solutionorbox}
\begin{solutionorbox}[space%l]
\begin{solutionordottedlines}
\begin{solutionordottedlines}[space%l]
\begin{solutionorgrid}
\begin{solutionorgrid}[space%l]
\begin{solutionorlines}
\begin{solutionorlines}[space%l]
\begin{subparts}
\begin{subsubparts}
\begin{TheSolution}#*
\begingradingrange{%<range name%>}
\bhpgword{text}#*
\bhpgword{text}#*
\bhpword{text}#*
\bhpword{text}#*
\bhqword{text}#*
\bhsword{text}#*
\bhsword{text}#*
\bhtword{text}#*
\bhtword{text}#*
\bonusgradetable
\bonusgradetable[h or v]
\bonusgradetable[h or v][type%keyvals]
\bonuspart
\bonuspart[points]
\bonuspointformat{format commands}
\bonuspointname{text}
\bonuspointpoints{singular text%text}{plural text%text}
\bonuspoints#*
\bonuspointsinrange{%<range name%>}
\bonuspointsofquestion{number}
\bonuspointsonpage{page number}
\bonuspointtable
\bonuspointtable[h or v]
\bonuspointtable[h or v][type%keyvals]
\bonusqformat{format spec}
\bonusquestion
\bonusquestion[points]
\bonussubpart
\bonussubpart[points]
\bonussubsubpart
\bonussubsubpart[points]
\bonustitledquestion{title%text}
\bonustitledquestion{title%text}[points]
\bonustotalformat{format commands}
\boxedpoints
\bracketedpoints
\bvpgword{text}#*
\bvpword{text}#*
\bvqword{text}#*
\bvsword{text}#*
\bvtword{text}#*
\cancelspace
\cancelspacefalse#*
\cancelspacetrue#*
\cellwidth{length}
\cfoot[first page text%text]{text}
\cfoot{text}
\chbpword{text}#*
\chead[first page text%text]{text}
\chead{text}
\checkboxchar{symbol}
\checkboxeshook#*
\checkedchar{symbol}
\choice
\choicelabel#*
\choiceshook#*
\chpgword{text}#*
\chpword{text}#*
\chqword{text}#*
\chsword{text}#*
\chtword{text}#*
\colorfbox{color}{text}#*
\colorfillwithdottedlines
\colorfillwithlines
\colorgrids
\colorsolutionboxes
\combinedgradetable
\combinedgradetable[h or v]
\combinedgradetable[h or v][type%keyvals]
\combinedpointtable
\combinedpointtable[h or v]
\combinedpointtable[h or v][type%keyvals]
\ContinuedQuestion
\CorrectChoice
\correctchoice#*
\CorrectChoiceEmphasis{format commands}
\correctchoiceemphasis{format commands}#*
\covercfoot[first page text%text]{text}
\covercfoot{text}
\coverchead[first page text%text]{text}
\coverchead{text}
\coverextrafootheight[first page height%l]{height}
\coverextrafootheight{height}
\coverextraheadheight[first page height%l]{height}
\coverextraheadheight{height}
\coverfirstpagefooter{left%text}{center%text}{right%text}
\coverfirstpagefootrule#*
\coverfirstpageheader{left%text}{center%text}{right%text}
\coverfirstpageheadrule#*
\coverfooter{left%text}{center%text}{right%text}
\coverfootrule#*
\coverheader{left%text}{center%text}{right%text}
\coverheadrule#*
\coverlfoot[first page text%text]{text}
\coverlfoot{text}
\coverlhead[first page text%text]{text}
\coverlhead{text}
\coverrfoot[first page text%text]{text} 
\coverrfoot{text}
\coverrhead[first page text%text]{text}
\coverrhead{text}
\coverrunningfooter{left%text}{center%text}{right%text}
\coverrunningfootrule#*
\coverrunningheader{left%text}{center%text}{right%text}
\coverrunningheadrule#*
\cvbpword{text}#*
\cvpgword{text}#*
\cvpword{text}#*
\cvqword{text}#*
\cvsword{text}#*
\cvtword{text}#*
\dottedlinefillheight#*
\droppoints
\droptotalbonuspoints
\droptotalpoints
\end{checkboxes}
\end{choices}
\end{coverpages}
\end{EnvFullwidth}
\end{EnvUplevel}
\end{examframed}#*
\end{examleftbar}#*
\end{examshaded}#*
\end{examshaded}#*
\end{oneparcheckboxes}
\end{oneparchoices}
\end{parts}
\end{questions}
\end{solution}
\end{solutionbox}
\end{solutionorbox}
\end{solutionordottedlines}
\end{solutionorgrid}
\end{solutionorlines}
\end{subparts}
\end{subsubparts}
\end{TheSolution}#*
\endgradingrange{%<range name%>}
\extrafootheight[first page height%l]{height}
\extrafootheight{height}
\extraheadheight[first page height%l]{height}
\extraheadheight{height}
\extrawidth{width}
\filedate#S
\fileversion#S
\fillin
\fillin[answer%text]
\fillin[answer%text][length]
\fillinlinelength#*
\fillwithdottedlines{length}
\fillwithgrid{length}
\fillwithlines{length}
\firstpagefooter{left%text}{center%text}{right%text}
\firstpagefootrule
\firstpageheader{left%text}{center%text}{right%text}
\firstpageheadrule
\firstqinrange{%<range name%>}
\footer{left%text}{center%text}{right%text}
\footrule
\framedsolutions
\fullwidth{text}
\gradetable
\gradetable[h or v]
\gradetable[h or v][type%keyvals]
\gradetablestretch{factor}
\greeknum{counter}
\gridlinewidth#*
\gridsize#*
\half
\header{left%text}{center%text}{right%text}
\headrule
\hpgword{text}#*
\hpword{text}#*
\hqword{text}#*
\hsword{text}#*
\htword{text}#*
\ifcontinuation{true text%text}{false text%text}
\ifincomplete{true text%text}{false text%text}
\iflastpage{true text%text}{false text%text}
\ifprintanswers
\IncompleteQuestion
\lastqinrange{%<range name%>}
\lfoot[first page text%text]{text}
\lfoot{text}
\lhead[first page text%text]{text}
\lhead{text}
\linefill#*
\linefillheight#*
\linefillthickness#*
\makeemptybox{length}
\marginbonuspointname{text}
\marginpointname{text}
\marginpointssep#*
\marksnotpoints
\multicolumnbonusgradetable{numcols}
\multicolumnbonusgradetable{numcols}[type%keyvals]
\multicolumnbonuspointtable{numcols}
\multicolumnbonuspointtable{numcols}[type%keyvals]
\multicolumncombinedgradetable{numcols}
\multicolumncombinedgradetable{numcols}[type%keyvals]
\multicolumncombinedpointtable{numcols}
\multicolumncombinedpointtable{numcols}[type%keyvals]
\multicolumngradetable{numcols}
\multicolumngradetable{numcols}[type%keyvals]
\multicolumnpartialbonusgradetable{numcols}{range name}
\multicolumnpartialbonusgradetable{numcols}{range name}[type%keyvals]
\multicolumnpartialbonuspointtable{numcols}{range name}
\multicolumnpartialbonuspointtable{numcols}{range name}[type%keyvals]
\multicolumnpartialcombinedgradetable{numcols}{rangename}
\multicolumnpartialcombinedgradetable{numcols}{rangename}[type%keyvals]
\multicolumnpartialcombinedpointtable{numcols}{rangename}
\multicolumnpartialcombinedpointtable{numcols}{rangename}[type%keyvals]
\multicolumnpartialgradetable{numcols}{range name}
\multicolumnpartialgradetable{numcols}{range name}[type%keyvals]
\multicolumnpartialpointtable{numcols}{range name}
\multicolumnpartialpointtable{numcols}{range name}[type%keyvals]
\multicolumnpointtable{numcols}
\multicolumnpointtable{numcols}[type%keyvals]
\multirowbonusgradetable{numrows}
\multirowbonusgradetable{numrows}[type%keyvals]
\multirowbonuspointtable{numrows}
\multirowbonuspointtable{numrows}[type%keyvals]
\multirowcombinedgradetable{numrows}
\multirowcombinedgradetable{numrows}[type%keyvals]
\multirowcombinedpointtable{numrows}
\multirowcombinedpointtable{numrows}[type%keyvals]
\multirowgradetable{numrows}
\multirowgradetable{numrows}[type%keyvals]
\multirowpartialbonusgradetable{numrows}{range name}
\multirowpartialbonusgradetable{numrows}{range name}[type%keyvals]
\multirowpartialbonuspointtable{numrows}{range name}
\multirowpartialbonuspointtable{numrows}{range name}[type%keyvals]
\multirowpartialcombinedgradetable{numrows}{rangename}
\multirowpartialcombinedgradetable{numrows}{rangename}[type%keyvals]
\multirowpartialcombinedpointtable{numrows}{rangename}
\multirowpartialcombinedpointtable{numrows}{rangename}[type%keyvals]
\multirowpartialgradetable{numrows}{range name}
\multirowpartialgradetable{numrows}{range name}[type%keyvals]
\multirowpartialpointtable{numrows}{range name}
\multirowpartialpointtable{numrows}{range name}[type%keyvals]
\multirowpointtable{numrows}
\multirowpointtable{numrows}[type%keyvals]
\noaddpoints
\nobonusqformat
\noboxedpoints
\nobracketedpoints
\nocancelspace
\nocolorfillwithdottedlines#*
\nocolorfillwithlines#*
\nocolorgrids#*
\nocolorsolutionboxes
\nocoverfirstpagefootrule#*
\nocoverfirstpageheadrule#*
\nocoverfootrule#*
\nocoverheadrule#*
\nocoverrunningfootrule#*
\nocoverrunningheadrule#*
\nofirstpagefootrule#*
\nofirstpageheadrule#*
\nofootrule#*
\noheadrule#*
\nomorequestions
\nopointsinleftmargin#*
\nopointsinmargin
\nopointsinrightmargin#*
\noprintanswers
\noqformat
\noquestionsonthispage
\norunningfootrule#*
\norunningheadrule#*
\nounstarredvspace
\numbonuspoints
\numcoverpages
\numpages
\numparts
\numpoints
\numqinrange{%<range name%>}
\numquestions
\numsubparts
\numsubsubparts
\oddeven{odd text%text}{even text%text}
\part
\part[points]
\partialbonusgradetable{range name}
\partialbonusgradetable{range name}[h or v]
\partialbonusgradetable{range name}[h or v][type%keyvals]
\partialbonuspointtable{range name}
\partialbonuspointtable{range name}[h or v]
\partialbonuspointtable{range name}[h or v][type%keyvals]
\partialcombinedgradetable{range name}
\partialcombinedgradetable{range name}[h or v]
\partialcombinedgradetable{range name}[h or v][type%keyvals]
\partialcombinedpointtable{range name}
\partialcombinedpointtable{range name}[h or v]
\partialcombinedpointtable{range name}[h or v][type%keyvals]
\partialgradetable{range name}
\partialgradetable{range name}[h or v]
\partialgradetable{range name}[h or v][type%keyvals]
\partialpointtable{range name}
\partialpointtable{range name}[h or v]
\partialpointtable{range name}[h or v][type%keyvals]
\partlabel#*
\partshook#*
\PgInfo{question label}{page}#*
\pointformat{format commands}
\pointname{text}
\pointpoints{singular text%text}{plural text%text}
\points
\pointsdroppedatright
\pointsinleftmargin#*
\pointsinmargin
\pointsinrange{%<range name%>}
\pointsinrightmargin
\pointsofquestion{number}
\pointsonpage{page number}
\pointstwosided
\pointstwosidedreversed
\pointtable
\pointtable[h or v]
\pointtable[h or v][type%keyvals]
\printanswers
\printanswersfalse#*
\printanswerstrue#*
\qformat{format spec}
\question
\question[points]
\questionlabel#*
\questionshook#*
\rfoot[first page text%text]{text}
\rfoot{text}
\rhead[first page text%text]{text}
\rhead{text}
\rightpointsmargin#*
\runningfooter{left%text}{center%text}{right%text}
\runningfootrule
\runningheader{left%text}{center%text}{right%text}
\runningheadrule
\settabletotalbonuspoints{number}
\settabletotalpoints{number}
\shadedsolutions
\SolutionEmphasis{format commands}
\solutiontitle#*
\subpart
\subpart[points]
\subpartlabel#*
\subpartshook#*
\subsubpart
\subsubpart[points]
\subsubpartlabel#*
\subsubpartshook#*
\thechoice
\themarginpoints
\thenumparts#*
\thenumquestions#*
\thenumsubparts#*
\thenumsubsubparts#*
\thepartno
\thepoints
\thequestion
\thequestiontitle
\thesubpart
\thesubsubpart
\titledquestion{title%text}
\titledquestion{title%text}[points]
\totalbonuspoints
\totalformat{format commands}
\totalnumpages
\totalpoints
\unframedsolutions
\unstarredvspace
\uplevel{text}
\usehorizontalhalf
\useslantedhalf
\vpgword{text}#*
\vpword{text}#*
\vqword{text}#*
\vsword{text}#*
\vtword{text}#*

#keyvals:\gradetable,\multirowgradetable,\multicolumngradetable,\pointtable,\multirowpointtable,\multicolumnpointtable,\partialgradetable,\partialpointtable,\multirowpartialgradetable,\multirowpartialpointtable,\multicolumnpartialgradetable,\multicolumnpartialpointtable,\bonusgradetable,\bonuspointtable,\combinedgradetable,\combinedpointtable,\multicolumnbonusgradetable,\multicolumnbonuspointtable,\multicolumncombinedgradetable,\multicolumncombinedpointtable,\multicolumnpartialbonusgradetable,\multicolumnpartialbonuspointtable,\multicolumnpartialcombinedgradetable,\multicolumnpartialcombinedpointtable,\multirowbonusgradetable,\multirowbonuspointtable,\multirowcombinedgradetable,\multirowcombinedpointtable,\multirowpartialbonusgradetable,\multirowpartialbonuspointtable,\multirowpartialcombinedgradetable,\multirowpartialcombinedpointtable,\partialbonusgradetable,\partialbonuspointtable,\partialcombinedgradetable,\partialcombinedpointtable
questions
pages
#endkeyvals