# isodate package
# Matthew Bertucci 11/24/2021 for v2.30

#include:ifthen
#include:substr

#keyvals:\usepackage/isodate#c
iso
num
short
orig
shortorig
Roman
roman
shortRoman
shortroman
american
austrian
british
danish
english
french
german
naustrian
ngerman
italian
norsk
norwegian
swedish
UKenglish
USenglish
inputenglish
inputbritish
inputUKenglish
inputamerican
inputUSenglish
inputtex
inputTeX
inputlatex
inputLaTeX
cleanlook
nocleanlook
printdayon
printdayoff
#endkeyvals

\isodate
\numdate
\numdate[counter]
\shortdate
\TeXdate
\origdate
\shortorigdate
\Romandate
\romandate
\shortRomandate
\shortromandate

\printyearoff
\printyearon
\printdayoff
\printdayon

\printdate{date}
\printdateTeX{yyyy/mm/dd}

\daterange{start date}{end date}
\isodash{symbol}

\isospacebeforeday{space cmd}
\isospacebeforemonth{space cmd}
\isospacebeforeyear{space cmd}

\shortyearsign{symbol}
\isorangesign{symbol}

\daymonthsepgerman{space cmd}
\monthyearsepgerman{space cmd}
\monthyearsepnodaygerman{space cmd}

\cleanlookdateon
\cleanlookdateoff

\ifisotwodigitday#*
\isotwodigitdaytrue
\isotwodigitdayfalse

\twodigitarabic{counter}

\dateinputformat{format%keyvals}
#keyvals:\dateinputformat
english
UKenglish
british
american
USenglish
tex
latex
TeX
LaTeX
#endkeyvals