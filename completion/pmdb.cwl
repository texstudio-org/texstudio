# pmdb package
# Matthew Bertucci 2022/05/13 for v1.0

#include:eforms

#keyvals:\usepackage/qrcstamps#c
dbmode
!dbmode
tight
!tight
#endkeyvals

\pmInput{file}#i
\pmInput[arg]{file}#i
\pmInput*{file}#i
\pmInput*[arg]{file}#i
\InputParas
\InputQuizItems
\InputItems
\InputProbs
\ifpmdbtight#*
\pmdbtighttrue
\pmdbtightfalse
\pmCBPresets{eforms parameters}
\useEditLnk
\useEditBtn
\editSourceBtn{width}{height}
\editSourceBtn[eforms parameters]{width}{height}
\editSourceOn
\editSourceOff
\editSourceLnk{width}{height}{text}
\editSourceLnk[eforms parameters]{width}{height}{text}
\displayChoices{width}{height}
\displayChoices[eforms parameters]{width}{height}
\clrChoices{width}{height}
\clrChoices[eforms parameters]{width}{height}
\displayChoiceCA{string}
\displayChoiceTU{string}
\clrChoicesCA{string}
\clrChoicesTU{string}

# not documented
\altCBMargins#*
\cbInQzMargin#*
\cbSelectInput{arg1}#*
\ckBxInput{arg1}#*
\doinput{arg1}#*
\donext#*
\editSourcefalse#*
\editSourcetrue#*
\ifeditSource#*
\ifpmdbDQs#*
\ifpmdbFP#*
\ifpmdbmode#*
\ifqzInput#*
\Input#*
\inputConta#*
\inputConti#*
\inputContii{arg1}#*
\insertCkBx{arg1}#*
\isItFullPath{arg1}#*
\ItemHook{arg1}#*
\pmAlignCB#*
\pmAlignCBAlt#*
\pmdbDQsfalse#*
\pmdbDQstrue#*
\pmdbFPfalse#*
\pmdbFPtrue#*
\pmdbmodefalse#*
\pmdbmodetrue#*
\pmHook#*
\pmiarg#*
\pmInputChk#*
\pmInputWarni#*
\pmInputWarnii#*
\qzInputfalse#*
\qzInputtrue#*
\removedqs#*
\removesemis{arg1}#*
\saveQNo#*
\setCBsMarg#*