# fbb package
# Matthew Bertucci 9/7/2021 for v1.16

#include:fontaxes
#include:fontenc
#include:textcomp
#include:etoolbox
#include:xstring
#include:mweights

\defigures
\infigures
\inffigures#*
\lfstyle
\nufigures
\osfstyle
\Qswash
\sufigures
\swshape
\textfrac{numerator}{denominator}
\textfrac[whole part]{numerator}{denominator}
\textin{text}
\textinf{text}#*
\textinferior{text}#*
\textlf{text}
\textosf{text}
\textsu{text}
\textsup{text}#*
\textsuperior{text}#*
\textde{text}
\textnu{text}
\texttlf{text}
\texttosf{text}
\tlfstyle
\tosfstyle
\useosf
\useproportional

#ifOption:swashQ
\Qnoswash
#endif
