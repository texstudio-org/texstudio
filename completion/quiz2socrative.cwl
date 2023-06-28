# quiz2socrative package
# Matthew Bertucci 2022/06/11 for v1.0

#include:calc
#include:tikz
#include:etoolbox
#include:pgfmath
#include:graphicx
#include:xcolor
#include:moresize
#include:listofitems
#include:ifthen
#include:tikzlibrarypositioning
#include:tikzlibraryshapes.misc
#include:tikzlibraryshapes.geometric
#include:tikzlibrarybackgrounds
#include:tikzlibraryfit

#keyvals:\usepackage/quiz2socrative#c
pdfQuiz
socrativeQuiz
numbers
letters
italian
english
#endkeyvals

\socrativeMC{testo della domanda%text}{lista delle risposte%text}
\socrativeMC{testo della domanda%text}{lista delle risposte%text}[soluzione%text]
\socrativeMC[larghezza%l]{testo della domanda%text}{lista delle risposte%text}
\socrativeMC[larghezza%l]{testo della domanda%text}{lista delle risposte%text}[soluzione%text]
\socrativeTwoMC{testo della domanda%text}{risposta1%text}{risposta2%text}
\socrativeTwoMC{testo della domanda%text}{risposta1%text}{risposta2%text}[soluzione%text]
\socrativeTwoMC[larghezza%l]{testo della domanda%text}{risposta1%text}{risposta2%text}
\socrativeTwoMC[larghezza%l]{testo della domanda%text}{risposta1%text}{risposta2%text}[soluzione%text]
\socrativeThreeMC{testo della domanda%text}{risposta1%text}{risposta2%text}{risposta3%text}
\socrativeThreeMC{testo della domanda%text}{risposta1%text}{risposta2%text}{risposta3%text}[soluzione%text]
\socrativeThreeMC[larghezza%l]{testo della domanda%text}{risposta1%text}{risposta2%text}{risposta3%text}
\socrativeThreeMC[larghezza%l]{testo della domanda%text}{risposta1%text}{risposta2%text}{risposta3%text}[soluzione%text]
\socrativeFourMC{testo della domanda%text}{risposta1%text}{risposta2%text}{risposta3%text}{risposta4%text}
\socrativeFourMC{testo della domanda%text}{risposta1%text}{risposta2%text}{risposta3%text}{risposta4%text}[soluzione%text]
\socrativeFourMC[larghezza%l]{testo della domanda%text}{risposta1%text}{risposta2%text}{risposta3%text}{risposta4%text}
\socrativeFourMC[larghezza%l]{testo della domanda%text}{risposta1%text}{risposta2%text}{risposta3%text}{risposta4%text}[soluzione%text]
\socrativeFiveMC{testo della domanda%text}{risposta1%text}{risposta2%text}{risposta3%text}{risposta4%text}{risposta5%text}
\socrativeFiveMC{testo della domanda%text}{risposta1%text}{risposta2%text}{risposta3%text}{risposta4%text}{risposta5%text}[soluzione%text]
\socrativeFiveMC[larghezza%l]{testo della domanda%text}{risposta1%text}{risposta2%text}{risposta3%text}{risposta4%text}{risposta5%text}
\socrativeFiveMC[larghezza%l]{testo della domanda%text}{risposta1%text}{risposta2%text}{risposta3%text}{risposta4%text}{risposta5%text}[soluzione%text]
\socrativeTF{testo della domanda%text}
\socrativeTF{testo della domanda%text}[soluzione%text]
\socrativeTF[larghezza%l]{testo della domanda%text}
\socrativeTF[larghezza%l]{testo della domanda%text}[soluzione%text]
\socrativeSA{testo della domanda%text}
\socrativeSA{testo della domanda%text}[soluzione%text]
\socrativeSA[larghezza%l]{testo della domanda%text}
\socrativeSA[larghezza%l]{testo della domanda%text}[soluzione%text]
\hideBorder
\showBorder
\showSolution
\hideSolution

# not documented
\useNumbers#*
\useLetters#*
\useEnglish#*
\useItalian#*
\usePdf#*
\useSocrative#*
\therispostaCorrente#*
\therispostaGiusta#*
