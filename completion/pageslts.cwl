# pageslts package
# Matthew Bertucci 2024/11/20 for v2.0a

#include:kvoptions
#include:undolabl

#keyvals:\usepackage/pageslts#c
pagecontinue#true,false
alphMult=#ab,bb,0
AlphMulti=#AB,BB,0
romanMult#true,false
RomanMulti#true,false
fnsymbolmult#true,false
#endkeyvals

\theCurrentPage
\theCurrentPageLocal
\lastpageref{label}
\lastpageref*{label}
\lastpages{numstyle%keyvals}{number}

#keyvals:\lastpages#c
arabic
roman
Roman
alph
Alph
#endkeyvals

# not documented
\AlphMult{number}#*
\alphMult{number}#*
\erroralphalph{cmd}{counter}#*
\expandPagenumbering{numstyle}#*
\extract{arg1}#S
\fnsymbolmult{number}#*
\lastpagereftext{arg1}#S
\lastpagereftextstar{arg1}#S
\lastpagereftxt{arg1}#S
\OrigPagenumbering{arg}#S
\Origthepage#S
\overrideLTSlabel{arg1}{arg2}#S
\pagesLTStmpA#S
\pagesLTStmpB#S
\pncmissing#S
\XRoman{counter}#*
\xroman{counter}#*
\pagesLTSlastpage#S
\pagesLTSlastpageHy#S
