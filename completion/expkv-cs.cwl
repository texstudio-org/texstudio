# expkv-cs package
# Matthew Bertucci 11/3/2021 for v1.1a

#include:expkv

## 1.1 Define Macros and Primary Keys ##
\ekvcSplit{cmd}{primary keys}{definition}#*d
\ekvcSplitAndForward{cmd}{after}{primary keys}#*d
\ekvcSplitAndUse{cmd}{primary keys}#*d
\ekvcHash{cmd}{primary keys}{definition}#*d
\ekvcHashAndForward{cmd}{after}{primary keys}#*d
\ekvcHashAndUse{cmd}{primary keys}#*d
\ekvcValue{key%plain}{key list}#*
\ekvcValueFast{key%plain}{key list}#*
\ekvcValueSplit{key%plain}{key list}{next}#*
\ekvcValueSplitFast{key%plain}{key list}{next}#*

## 1.2 Secondary Key ##
\ekvcSecondaryKeys{cmd}{keyvals}#*d

## 1.3 Changing the Initial Values ##
\ekvcChange{cmd}{keyvals}#*d

## 1.5 Flags ##
\ekvcFlagNew%<<flag>%>#*
\ekvcFlagNew{cmd}#Sd
\ekvcFlagHeight%<<flag>%>#*
\ekvcFlagRaise%<<flag>%>#*
\ekvcFlagSetTrue%<<flag>%>#*
\ekvcFlagSetFalse%<<flag>%>#*
\ekvcFlagIf%<<flag>%>{%<true%>}{%<false%>}#*
\ekvcFlagIfRaised%<<flag>%>{%<true%>}{%<false%>}#*
\ekvcFlagReset%<<flag>%>#*
\ekvcFlagGetHeight%<<flag>%>{%<next%>}#*
\ekvcFlagGetHeights{flag-list}{next}#*

## 1.7 Freedom for Keys! ##
\ekvcPass{cmd}{key%plain}{value}#*

\ekvcDate#S
\ekvcVersion#S