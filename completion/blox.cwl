# blox package
# Matthew Bertucci 12/14/2021 for v2.51

#include:ifthen
#include:pgffor
#include:tikz
#include:tikzlibraryshapes

\bXInput{name}#/tikzpicture
\bXInput[label]{name}#/tikzpicture
\bXOutput{name}{preceding node}#/tikzpicture
\bXOutput[distance%l]{name}{previous node}#/tikzpicture
\bXLinkName{previous node}{label}#/tikzpicture
\bXLinkName[distance%l]{previous node}{label}#/tikzpicture
\bXBloc{name}{contents}{previous node}#/tikzpicture
\bXBloc[distance%l]{name}{contents}{previous node}#/tikzpicture
\bXBlocL{name}{contents}{previous node}#/tikzpicture
\bXBlocL[distance%l]{name}{contents}{previous node}#/tikzpicture
\bXBlocr{name}{contents}{previous node}#/tikzpicture
\bXBlocr[distance%l]{name}{contents}{previous node}#/tikzpicture
\bXBlocrL{name}{contents}{previous node}#/tikzpicture
\bXBlocrL[distance%l]{name}{contents}{previous node}#/tikzpicture
\bXBlocPotato{name}{contents}{previous node}#/tikzpicture
\bXBlocPotato[distance%l]{name}{contents}{previous node}#/tikzpicture
\bXonlyOneBloc{input label}{block label}{output label}#/tikzpicture
\bXonlyOneBloc[distance%l]{input label}{block label}{output label}#/tikzpicture

\bXComp{name}{previous node}#/tikzpicture
\bXComp[distance%l]{name}{previous node}#/tikzpicture
\bXComp*{name}{previous node}#/tikzpicture
\bXComp*[distance%l]{name}{previous node}#/tikzpicture
\bXSum{name}{previous node}{a}{b}{c}#/tikzpicture
\bXSum[distance%l]{name}{previous node}{a}{b}{c}#/tikzpicture
\bXCompa{name}{previous node}#/tikzpicture
\bXCompa[distance%l]{name}{previous node}#/tikzpicture
\bXCompa*{name}{previous node}#/tikzpicture
\bXCompa*[distance%l]{name}{previous node}#/tikzpicture
\bXSuma{name}{previous node}#/tikzpicture
\bXSuma[distance%l]{name}{previous node}#/tikzpicture
\bXSuma*{name}{previous node}#/tikzpicture
\bXSuma*[distance%l]{name}{previous node}#/tikzpicture
\bXCompb{name}{previous node}#/tikzpicture
\bXCompb[distance%l]{name}{previous node}#/tikzpicture
\bXCompb*{name}{previous node}#/tikzpicture
\bXCompb*[distance%l]{name}{previous node}#/tikzpicture
\bXSumb{name}{previous node}#/tikzpicture
\bXSumb[distance%l]{name}{previous node}#/tikzpicture
\bXSumb*{name}{previous node}#/tikzpicture
\bXSumb*[distance%l]{name}{previous node}#/tikzpicture
\bXCompSum{name}{previous node}{n}{s}{w}{e}#/tikzpicture
\bXCompSum[distance%l]{name}{previous node}{n}{s}{w}{e}#/tikzpicture
\bXCompSum*{name}{previous node}{n}{s}{w}{e}#/tikzpicture
\bXCompSum*[distance%l]{name}{previous node}{n}{s}{w}{e}#/tikzpicture

\bXLink{previous node}{next node}#/tikzpicture
\bXLink[label]{previous node}{next node}#/tikzpicture
\bXLinkxy{previous node}{next node}#/tikzpicture
\bXLinkxy[label]{previous node}{next node}#/tikzpicture
\bXLinkyx{previous node}{next node}#/tikzpicture
\bXLinktyx{previous node}{next node}#/tikzpicture
\bXLinktb{previous node}{next node}#/tikzpicture
\bXReturn{previous node}{next node}{label}#/tikzpicture
\bXReturn[distance%l]{previous node}{next node}{label}#/tikzpicture

\bXChain{previous node}{list}#/tikzpicture
\bXChain[distance%l]{previous node}{list}#/tikzpicture
\bXChainReturn{previous node}{list}#/tikzpicture
\bXChainReturn[distance%l]{previous node}{list}#/tikzpicture
\bXLoop{previous node}{list}#/tikzpicture
\bXLoop[distance%l]{previous node}{list}#/tikzpicture
\lastx#*

\bXBranchx{previous node}{name}#/tikzpicture
\bXBranchx[distance%l]{previous node}{name}#/tikzpicture
\bXNodeShiftx#S/tikzpicture
\bXBranchy{previous node}{name}#/tikzpicture
\bXBranchy[distance%l]{previous node}{name}#/tikzpicture
\bXNodeShifty#S/tikzpicture

\bXDefaultLineStyle#*
\bXLineStyle{TikZ keys}
\bXStyleBlocDefault#*
\bXStyleBloc{TikZ keys}
\bXStyleSumDefault#*
\bXStyleSum{TikZ keys}
\bXLabelStyleDefault#*
\bXLabelStyle{TikZ keys}
\bXStylePotatoDefault#*
\bXStylePotato{TikZ keys}
