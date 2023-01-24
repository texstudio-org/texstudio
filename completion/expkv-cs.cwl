# expkv-cs package
# Matthew Bertucci 2023/01/23 for v1.3

#include:expkv-pop

## Define Macros and Primary Keys ##
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

## Secondary Key ##
\ekvcSecondaryKeys{cmd}{keyvals}#*d

## Changing the Initial Values ##
\ekvcChange{cmd}{keyvals}#*d

## Flags ##
\ekvcFlagNew%<⟨flag⟩%>#*
\ekvcFlagNew{cmd}#Sd
\ekvcFlagHeight%<⟨flag⟩%>#*
\ekvcFlagRaise%<⟨flag⟩%>#*
\ekvcFlagSetTrue%<⟨flag⟩%>#*
\ekvcFlagSetFalse%<⟨flag⟩%>#*
\ekvcFlagIf%<⟨flag⟩%>{%<true%>}{%<false%>}#*
\ekvcFlagIfRaised%<⟨flag⟩%>{%<true%>}{%<false%>}#*
\ekvcFlagReset%<⟨flag⟩%>#*
\ekvcFlagResetGlobal%<⟨flag⟩%>#*
\ekvcFlagGetHeight%<⟨flag⟩%>{%<next%>}#*
\ekvcFlagGetHeights{flag-list}{next}#*

## Freedom for Keys! ##
\ekvcPass{cmd}{key%plain}{value}#*

## Useless Macros ##
\ekvcDate#S
\ekvcVersion#S
