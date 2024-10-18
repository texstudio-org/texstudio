# scrjura package
# Matthew Bertucci 2024/10/15 for v3.42

#include:contract
#include:scrlogo

#keyvals:\usepackage/scrjura#c
# all options passed to contract package
juratotoc=%<true|false|<integer>%>
juratocindent=##L
juratocnumberwidth=##L
contract
juratitlepagebreak#true,false
clausemark=#both,false,off,no,forceboth,forceright,right
parnumber=#auto,true,false,manual
ref=#long,numeric,clauseonly,onlyclause,ClauseOnly,OnlyClause,parlong,longpar,ParL,parnumeric,numericpar,ParN,paroff,nopar,parshort,shortpar,ParS,sentencelong,longsentence,SentenceL,sentencenumeric,numericsentence,SentenceN,sentenceoff,nosentence,sentenceshort,shortsentence,SentenceS,short
#endkeyvals
