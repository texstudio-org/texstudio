# toolbox package
# Matthew Bertucci 2022/06/25 for v5.1

\toolboxMakeDef{name}{replacement}#*
\toolboxMakeDef[prefix]{name}{replacement}#*
\toolboxFreeDef{name}#*
\toolboxFreeDef[prefix]{name}#*
\toolboxFreeDef*{name}#*
\toolboxFreeDef*[prefix]{name}#*
\toolboxFuturelet%<\macro%>{%<argument%>}#*
\toolboxFuturelet{cmd}#Sd
\toolboxGobbleNext{cmd}#*
\toolboxIfNextToken{token}{if}{else}#*
\toolboxToken#*
\toolboxIfNextGobbling{token}{if}{else}#*
\toolboxIfEmpty{arg}{if}{else}#*
\toolboxIfx{%<arg%>}%<\macro%>{%<if%>}{%<else%>}#*
\toolboxIfX{arg1}{arg2}{if}{else}#*
\toolboxIfElse{ifcmd}{if}{else}#*
\toolboxLoop{items}{action}#*
\toolboxLoopName{name}{items}{action}#*
\toolboxTokenLoop{tokens}{action}#*
\toolboxTokenLoopName{name}{tokens}{action}#*
\toolboxDef%<\macro%>{%<argumentlist%>}#*
\toolboxDef{cmd}#Sd
\toolboxSpace#*
\toolboxAppend%<\macro%>{%<argumentlist%>}#*
\toolboxAppend{cmd}#Sd
\toolboxSurround{%<content before%>}{%<content after%>}%<\macro%>#*
\toolboxTokDef{argumentlist}{cmd}#Sd
\toolboxTokDef{%<argumentlist%>}%<\macro%>#*
\toolboxSplitAt{argument}{search}{\beforestring%cmd}{\afterstring%cmd}#*
\toolboxSplitAt*{argument}{search}{\beforestring%cmd}{\afterstring%cmd}#*
\toolboxMakeSplit{search}{cmd}#*d
\toolboxMakeSplit*{search}{cmd}#*d
\toolboxFreeSplit{cmd}#*
\toolboxReplace{%<search%>}{%<replace%>}%<\macro%>#*
\toolboxReplaceSplit{%<replace%>}%<\splitcmd\macro%>#*
\toolboxMakeHarmless{cmd}#*
\toolboxDropBrace{cmd}#*
\toolboxIf{comparison}{def cmds}{cmd}#Sd
\toolboxIf%<\comparison%>{%<def cmds%>}%<\macro%>#*
\toolboxNewiftrue{name}#*
\toolboxNewiffalse{name}#*
\toolboxNewifTrue{name}#*
\toolboxNewifFalse{name}#*
\toolboxLet%<\macro%>{%<macroname%>}#*
\toolboxLet{cmd}#Sd
\toolboxWithNr{%<number%>}%<\cmd%>{%<macro%>}#*
\toolboxEmpty#*
\toolboxSpaceToken#*
\toolboxFirstOfTwo{arg1}{arg2}#*
\toolboxSecondOfTwo{arg1}{arg2}#*
\toolboxGobbleArg{arg}#*
