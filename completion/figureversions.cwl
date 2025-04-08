# figureversions package
# Matthew Bertucci 2025/04/07 for v1.0

\lnfigures
\txfigures
\liningfigures{text}
\textfigures{text}
\prfigures
\tbfigures
\proportionalfigures{text}
\tabularfigures{text}
\tabularmath
\proportionalmath

\figureversion{options%keyvals}

#keyvals:\figureversion
text
osf
lining
lf
tabular
tab
proportional
prop
#endkeyvals

\fontfigurestyle{style}#*
\fontfigurealignment{alignment}#*
\fontbasefamily{family}#*
\mathweight{weight}#*
\mathfigurealignment{alignment}#*

\figureversions_new_figurestyle:nnn {%<⟨name⟩%>} {%<⟨proportional suffixes⟩%>} {%<⟨tabular suffixes⟩%>}#/%expl3
\figureversions_new_figurestyle:Vnn %<⟨var⟩%> {%<⟨proportional suffixes⟩%>} {%<⟨tabular suffixes⟩%>}#/%expl3
\figureversions_new_figureversion:nn {%<⟨option⟩%>} {%<⟨code⟩%>}#/%expl3