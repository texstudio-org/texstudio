# dbshow package
# Matthew Bertucci 1/21/2022 for v1.5

## Create, Display and Clear Database ##
\dbNewDatabase{database}{attr1=val1,attr2=val2,...}
\dbNewDatabase[base database]{database}{attr1=val1,attr2=val2,...}
\dbNewDatabase*{database}{attr1=val1,attr2=val2,...}
\dbNewDatabase*{database}{attr1=val1,attr2=val2,...}
\dbshow{style}{database}
\dbclear{database}

## \dbNewStyle and Style Options ##
\dbNewStyle{style}{database}{options%keyvals}
\dbNewStyle[base styles]{style}{database}{options%keyvals}

#keyvals:\dbNewStyle#c
filter=%<filter%>
raw-filter={%<conditional expr%>}
sort={%<attr spec1,attr spec2,...%>}
before-code=%<code%>
after-code=%<code%>
item-code=%<code%>
item-code*=%<code%>
item-before-code=%<code%>
item-after-code=%<code%>
%<<attr>%>/code=%<code%>
%<<attr>%>/code*=%<code%>
%<<attr>%>/before-code=%<code%>
%<<attr>%>/after-code=%<code%>
%<<attr>%>/item-code=%<code%>
%<<attr>%>/item-code*=%<code%>
%<<attr>%>/item-before-code=%<code%>
%<<attr>%>/item-after-code=%<code%>
%<<attr>%>/sep=%<separator%>
%<<attr>%>/format-code=%<code%>
%<<attr>%>/zfill#true,false
#endkeyvals

\dbdatesep{separator}

## Data Filters ##
\dbNewReviewPoints{name}{points}
\begin{dbFilters}{database}
\begin{dbFilters}*{database}
\end{dbFilters}
\dbNewConditional{name}{attr}{cond spec}
\dbNewConditional{name}{attr}{cond spec}[filter info]
\dbNewConditional*{name}{attr}{cond spec}
\dbNewConditional*{name}{attr}{cond spec}[filter info]
\dbNewCond{name}{attr}{cond spec}#*
\dbNewCond{name}{attr}{cond spec}[filter info]#*
\dbNewCond*{name}{attr}{cond spec}#*
\dbNewCond*{name}{attr}{cond spec}[filter info]#*
\dbNewRawFilter{name}{database}{attr}{cond spec}
\dbNewRawFilter{name}{database}{attr}{cond spec}[filter info]
\dbNewRawFilter*{name}{database}{attr}{cond spec}
\dbNewRawFilter*{name}{database}{attr}{cond spec}[filter info]
\dbCombineConditionals{name}{cond combination}
\dbCombineConditionals{name}{cond combination}[filter info]
\dbCombCond{name}{cond combination}#*
\dbCombCond{name}{cond combination}[filter info]#*

## Store and Use Data ##
\begin{dbitem}{database}
\begin{dbitem}{database}[attr1=val1,attr2=val2,...]
\end{dbitem}
\dbitemkv{database}
\dbitemkv{database}[attr1=val1,attr2=val2,...]

## \dbsave and \dbuse ##
\dbsave{attr}{data}
\dbsave*{attr}{data}
\dbuse{attr}

## Conditionals ##
\dbIfEmptyT{true code}
\dbIfEmptyF{false code}
\dbIfEmptyTF{true code}{false code}
\dbIfLastT{true code}
\dbIfLastF{false code}
\dbIfLastTF{true code}{false code}

## Expression Functions ##
\dbIntAbs{int expr}
\dbIntSign{int expr}
\dbIntDivRound{int expr1}{int expr2}
\dbIntDivTruncate{int expr1}{int expr2}
\dbIntMax{int expr1}{int expr2}
\dbIntMin{int expr1}{int expr2}
\dbIntMod{int expr1}{int expr2}
\dbFpSign{fp expr}

## Special Macros ##
\dbval
\dbtoday
\dbDatabase
\dbFilterName
\dbFilterInfo
\dbIndex
\dbarabic
\dbalph
\dbAlph
\dbroman
\dbRoman