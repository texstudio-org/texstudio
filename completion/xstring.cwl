# xstring package
# Matthew Bertucci 9/27/2021 for v1.84

\IfSubStr{string}{stringA}{true}{false}#*
\IfSubStr[number]{string}{stringA}{true}{false}#*
\IfSubStr*{string}{stringA}{true}{false}#*
\IfSubStr*[number]{string}{stringA}{true}{false}#*

\IfSubStrBefore{string}{stringA}{stringB}{true}{false}#*
\IfSubStrBefore[num1,num2]{string}{stringA}{stringB}{true}{false}#*
\IfSubStrBefore*{string}{stringA}{stringB}{true}{false}#*
\IfSubStrBefore*[num1,num2]{string}{stringA}{stringB}{true}{false}#*

\IfSubStrBehind{string}{stringA}{stringB}{true}{false}#*
\IfSubStrBehind[num1,num2]{string}{stringA}{stringB}{true}{false}#*
\IfSubStrBehind*{string}{stringA}{stringB}{true}{false}#*
\IfSubStrBehind*[num1,num2]{string}{stringA}{stringB}{true}{false}#*

\IfBeginWith{string}{stringA}{true}{false}#*
\IfBeginWith[number]{string}{stringA}{true}{false}#*
\IfBeginWith*{string}{stringA}{true}{false}#*
\IfBeginWith*[number]{string}{stringA}{true}{false}#*

\IfEndWith{string}{stringA}{true}{false}#*
\IfEndWith[number]{string}{stringA}{true}{false}#*
\IfEndWith*{string}{stringA}{true}{false}#*
\IfEndWith*[number]{string}{stringA}{true}{false}#*

\IfInteger{number}{true}{false}#*
\IfDecimal{number}{true}{false}#*
\integerpart#*
\decimalpart#*

\IfStrEq{stringA}{stringB}{true}{false}#*
\IfStrEq*{stringA}{stringB}{true}{false}#*

\IfEq{stringA}{stringB}{true}{false}#*

\IfStrEqCase{%<string%>}{%<{string1}{code1}{string2}{code2}...%>}#*
\IfStrEqCase{%<string%>}{%<{string1}{code1}{string2}{code2}...%>}[%<other cases code%>]#*
\IfStrEqCase*{%<string%>}{%<{string1}{code1}{string2}{code2}...%>}#*
\IfStrEqCase*{%<string%>}{%<{string1}{code1}{string2}{code2}...%>}[%<other cases code%>]#*

\IfEqCase{%<string%>}{%<{string1}{code1}{string2}{code2}...%>}#*
\IfEqCase{%<string%>}{%<{string1}{code1}{string2}{code2}...%>}[%<other cases code%>]#*
\IfEqCase*{%<string%>}{%<{string1}{code1}{string2}{code2}...%>}#*
\IfEqCase*{%<string%>}{%<{string1}{code1}{string2}{code2}...%>}[%<other cases code%>]#*

\StrBefore{string}{stringA}#*
\StrBefore[number]{string}{stringA}#*
\StrBefore{string}{stringA}[name%cmd]#*d
\StrBefore[number]{string}{stringA}[name%cmd]#*d
\StrBefore*{string}{stringA}#*
\StrBefore*[number]{string}{stringA}#*
\StrBefore*{string}{stringA}[name%cmd]#*d
\StrBefore*[number]{string}{stringA}[name%cmd]#*d

\StrBehind{string}{stringA}#*
\StrBehind[number]{string}{stringA}#*
\StrBehind{string}{stringA}[name%cmd]#*d
\StrBehind[number]{string}{stringA}[name%cmd]#*d
\StrBehind*{string}{stringA}#*
\StrBehind*[number]{string}{stringA}#*
\StrBehind*{string}{stringA}[name%cmd]#*d
\StrBehind*[number]{string}{stringA}[name%cmd]#*d

\StrCut{string}{stringA}{macroA%cmd}{macroB%cmd}#*d
\StrCut[number]{string}{stringA}{macroA%cmd}{macroB%cmd}#*d
\StrCut*{string}{stringA}{macroA%cmd}{macroB%cmd}#*d
\StrCut*[number]{string}{stringA}{macroA%cmd}{macroB%cmd}#*d

\StrBetween{string}{stringA}{stringB}#*
\StrBetween[num1,num2]{string}{stringA}{stringB}#*
\StrBetween{string}{stringA}{stringB}[name%cmd]#*d
\StrBetween[num1,num2]{string}{stringA}{stringB}[name%cmd]#*d
\StrBetween*{string}{stringA}{stringB}#*
\StrBetween*[num1,num2]{string}{stringA}{stringB}#*
\StrBetween*{string}{stringA}{stringB}[name%cmd]#*d
\StrBetween*[num1,num2]{string}{stringA}{stringB}[name%cmd]#*d

\StrSubstitute{string}{stringA}{stringB}#*
\StrSubstitute[number]{string}{stringA}{stringB}#*
\StrSubstitute{string}{stringA}{stringB}[name%cmd]#*d
\StrSubstitute[number]{string}{stringA}{stringB}[name%cmd]#*d
\StrSubstitute*{string}{stringA}{stringB}#*
\StrSubstitute*[number]{string}{stringA}{stringB}#*
\StrSubstitute*{string}{stringA}{stringB}[name%cmd]#*d
\StrSubstitute*[number]{string}{stringA}{stringB}[name%cmd]#*d

\StrDel{string}{stringA}#*
\StrDel[number]{string}{stringA}#*
\StrDel{string}{stringA}[name%cmd]#*d
\StrDel[number]{string}{stringA}[name%cmd]#*d
\StrDel*{string}{stringA}#*
\StrDel*[number]{string}{stringA}#*
\StrDel*{string}{stringA}[name%cmd]#*d
\StrDel*[number]{string}{stringA}[name%cmd]#*d

\StrGobbleLeft{string}{number}#*
\StrGobbleLeft{string}{number}[name%cmd]#*d
\StrLeft{string}{number}#*
\StrLeft{string}{number}[name%cmd]#*d
\StrGobbleRight{string}{number}#*
\StrGobbleRight{string}{number}[name%cmd]#*d
\StrRight{string}{number}#*
\StrRight{string}{number}[name%cmd]#*d

\StrChar{string}{number}#*
\StrChar{string}{number}[name%cmd]#*d
\StrChar*{string}{number}#*
\StrChar*{string}{number}[name%cmd]#*d

\StrMid{string}{numberA}{numberB}#*
\StrMid{string}{numberA}{numberB}[name%cmd]#*d

\StrLen{string}#*
\StrLen{string}[name%cmd]#*d

\StrCount{string}{stringA}#*
\StrCount{string}{stringA}[name%cmd]#*d

\StrPosition{string}{stringA}#*
\StrPosition[number]{string}{stringA}#*
\StrPosition{string}{stringA}[name%cmd]#*d
\StrPosition[number]{string}{stringA}[name%cmd]#*d

\StrCompare{stringA}{stringB}#*
\StrCompare{stringA}{stringB}[name%cmd]#*d
\StrCompare*{stringA}{stringB}#*
\StrCompare*{stringA}{stringB}[name%cmd]#*d
\comparenormal#*
\comparestrict#*
\savecomparemode#*
\restorecomparemode#*

\fullexpandarg#*
\noexpandarg#*
\normalexpandarg#*
\expandarg#*
\saveexpandmode#*
\restoreexpandmode#*

\noexploregroups#*
\exploregroups#*
\saveexploremode#*
\restoreexploremode#*

\StrFindGroup{arg}{identifier}#*
\StrFindGroup{arg}{identifier}[name%cmd]#*d
\groupID#*

\StrSplit{string}{number}{macroA%cmd}{macroB%cmd}#*d

\verbtocs{%<name%>}|%<characters%>|#*
\verbtocs{cmd}#Sd
\setverbdelim{character}#*

\tokenize{name%cmd}{control sequences}#*d

\StrExpand{string}{name%cmd}#*d
\StrExpand[number]{string}{name%cmd}#*d
\noexpandingroups#*
\expandingroups#*
\scancs{name%cmd}{string}#*d
\scancs[number]{name%cmd}{string}#*d

\StrRemoveBraces{string}#*
\StrRemoveBraces{string}[name%cmd]#*d