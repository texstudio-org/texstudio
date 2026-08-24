# matrixdiagrams package
# Matthew Bertucci 2026/08/19 for v1.0

#include:tikz
#include:calc
#include:tikzlibrarybending
#include:tikzlibrarymatrix
#include:tikzlibrarypositioning
#include:tikzlibrarycalc

\matrixdiagram[scale][aspect]{content}
\matrixdiagram[scale]{content}
\matrixdiagram{content}
\mdBidiagLower
\mdBidiagUpper
\mdBlank
\mdDiag
\mdDiagBand
\mdDiagBandFrom{x1}{y1}{x2}{y2}
\mdDiagBandNFrom{n}{x1}{y1}{x2}{y2}
\mdDiagBandN{n}
\mdDiagFrom{x1}{y1}{x2}{y2}
\mdFill[color]{x0}{y0}{x1}{y1}
\mdFill{x0}{y0}{x1}{y1}
\mdH
\mdHessenberg
\mdHessenberg[color]
\mdHLine{y}
\mdIdentity
\mdLabel[fill]{x}{y}{text}
\mdLabelCenter{text}
\mdLabelRaw[fill]{x}{y}{text}
\mdLabelRaw{x}{y}{text}
\mdLabel{x}{y}{text}
\mdSpike{x}{y}{dir}
\mdVLine{x}