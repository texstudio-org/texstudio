# vtable package
# Matthew Bertucci 1/18/2022 for v1.0

#include:array
#include:varwidth
#include:dashrule
#include:graphicx
#include:etoolbox
#include:calc
#include:forloop
#include:alphalph

\nextRow#t
\lb
\setMultiColRow{col num}{row num}{max width%l}{min width%l}{hmode}{vmode}{left sep%l}{right sep%l}{text}#t
\setMultiColumn{col num}{max width%l}{min width%l}{hmode}{vmode}{left sep%l}{right sep%l}{text}#t
\setMultiRow{col num}{text}#t
\setMultiRow{col num}[min height%l]{text}#t
\tableFormatedCell{max width%l}{hmode}{vmode}#t
\tableFormatedCell{max width%l}[min width%l]{hmode}{vmode}#t
\forceRowHeight{height}#t