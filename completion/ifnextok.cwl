# ifnextok package
# Matthew Bertucci 11/26/2021 for v0.3

#keyvals:\usepackage/ifnextok#c
newline
center
tab
array
tabular
all
stdbreaks
#endkeyvals

\IfNextToken%<<match>%>{%<if%>}{%<else%>}#*
\NoNextSkipping#*
\RestoreNextSkipping#*
\INTpatch%<<replacer><macro>%>#*
\NextTestPatch%<<macro>%>#*
\INTstore%<<macro>%>#*
\INTrestore%<<macro>%>#*
\IfStarNextToken%<<token>%>#*
\StarTestPatch%<<macro>%>#*
\StoreStarSkipping#*
\RestoreStarSkipping#*
\NoStarSkipping#*
\IfNextSpace{if}{else}#*
\MakeNotSkipping{target}{on-space}#*
\StoreNewlineSkipping#*
\RestoreNewlineSkipping#*
\NoNewlineSkipping#*
\INTactOnEnv{action1}{action2}{envname}#*
\StoreSkippingCRs{envname}#*
\RestoreSkippingCRs{envname}#*
\NotSkippingCRs{envname}#*