# easylist package
# Matthew Bertucci 11/6/2021 for v1.4

#keyvals:\usepackage/easylist#c
pilcrow
at
sharp
ampersand
%<number of counters%>
#endkeyvals

\begin{easylist}
\begin{easylist}[style%keyvals]
\end{easylist}

#ifOption:ampersand
\begin{easylist}#\tabular
\begin{easylist}[style%keyvals]#\tabular
#endif

#keyvals:\begin{easylist}#c
tractatus
checklist
booktoc
articletoc
enumerate
itemize
#endkeyvals

\ListProperties(options%keyvals)
\NewList(options%keyvals)

#keyvals:\ListProperties#c,\NewList#c
Start%<n%>=%<number%>
Start%<n%>*=%<counter%>
Mark=%<punctuation%>
Mark%<n%>=%<punctuation%>
FinalMark=%<punctuation%>
FinalMark%<n%>=%<punctuation%>
Numbers=#r,R,l,L,z,a
Numbers%<n%>=#r,R,l,L,z,a
Hide=%<number%>
Hide%<n%>=%<number%>
Style=%<format%>
Style%<n%>=%<format%>
Style*=%<format%>
Style%<n%>*=%<format%>
Style**=%<format%>
Style%<n%>**=%<format%>
CtrCom=%<command%>
CtrCom%<n%>=%<command%>
Hang#true,false
Hang%<n%>#true,false
Align=%<move, fixed, or <dimen>%>
Align%<n%>=%<move, fixed, or <dimen>%>
Margin=##L
Margin%<n%>=##L
Progressive=##L
Progressive%<n%>=##L
Space=##L
Space%<n%>=##L
Space*=##L
Space%<n%>*=##L
Indent=##L
Indent%<n%>=##L
FinalSpace=##L
FinalSpace%<n%>=##L
#endkeyvals

\ifPilcrow#*
\Pilcrowtrue#*
\Pilcrowfalse#*
\ifAt#*
\Attrue#*
\Atfalse#*
\ifSharp#*
\Sharptrue#*
\Sharpfalse#*
\ifAmpersand#*
\Ampersandtrue#*
\Ampersandfalse#*
\ifDubiousFigure#*
\DubiousFiguretrue#*
\DubiousFigurefalse#*
