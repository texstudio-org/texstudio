# pdfMsym package
# ponte-vecchio 2023-01-17 for v1.1.0

#include:pdftex
#include:luatex
#include:xetex

# 1. Initialisation
\pdfmsymsetscalefactor{%<fontsize%>}

# 2.1 Maths Symbols
\aint#m
\bigcircwedge#m
\bigdcup#m
\bigdwedge#m
\bigexists#m
\bigforall#m
\circwedge#m
\dcup#m
\divs#m
\dwedge#m
\lightning
\ndivs#m

## Arbitrary length symbols
\oiNint{%<number%>}#m
\biNint{%<number%>}#m

# 2.2 Vector Symbols
\lvecc{%<arg%>}#m
\overleftharp{%<arg%>}#m
\overleftrightharp{%<arg%>}#m
\overleftrightvecc{%<arg%>}#m
\overrightharp{%<arg%>}#m
\overrightleftharp{%<arg%>}#m
\straightlvecc{%<arg%>}#m
\straightvecc{%<arg%>}#m
\underleftharp{%<arg%>}#m
\underleftrightharp{%<arg%>}#m
\underleftrightvecc{%<arg%>}#m
\underlvecc{%<arg%>}#m
\underrightharp{%<arg%>}#m
\underrightleftharp{%<arg%>}#m
\understraightlvecc{%<arg%>}#m
\understraightvecc{%<arg%>}#m
\undervecc{%<arg%>}#m
\vecc{%<arg%>}#m

## Short forms
\shortlvecc{%<arg%>}#m
\shortoverleftharp{%<arg%>}#m
\shortoverleftrightharp{%<arg%>}#m
\shortoverleftrightvecc{%<arg%>}#m
\shortoverrightharp{%<arg%>}#m
\shortoverrightleftharp{%<arg%>}#m
\shortstraightlvecc{%<arg%>}#m
\shortstraightvecc{%<arg%>}#m
\shortunderleftharp{%<arg%>}#m
\shortunderleftrightharp{%<arg%>}#m
\shortunderleftrightvecc{%<arg%>}#m
\shortunderlvecc{%<arg%>}#m
\shortunderrightharp{%<arg%>}#m
\shortunderrightleftharp{%<arg%>}#m
\shortunderstraightlvecc{%<arg%>}#m
\shortunderstraightvecc{%<arg%>}#m
\shortundervecc{%<arg%>}#m
\shortvecc{%<arg%>}#m
\constvec%<vector macro%>{%<material%>}

## 2.3 Arrow Symbols
### Normal form
\varrightarrow#m
\varleftarrow#m
\varrightharp#m
\varleftharp#m
\varleftrightarrow#m
\varleftrightharp#m
\varrightleftharp#m
\varmapsto#m
\varhookrightarrow#m
\varhookleftarrow#m
\vardoublerightarrow#m
\vardoubleleftarrow#m
\varcirclerightarrow#m
\varcircleleftarrow#m
\varRightarrow#m
\varLeftarrow#m
\varCirclerightarrow#m
\varCircleleftarrow#m
\varSquarerightarrow#m
\varSquareleftarrow#m
\varRibbonrightarrow#m
\varRibbonleftarrow#m
\squaredarrow#m
\roundedarrow#m

### Long form
\longvarrightarrow#m
\longvarleftarrow#m
\longvarrightharp#m
\longvarleftharp#m
\longvarleftrightarrow#m
\longvarleftrightharp#m
\longvarrightleftharp#m
\longvarmapsto#m
\longvarhookrightarrow#m
\longvarhookleftarrow#m
\longvardoublerightarrow#m
\longvardoubleleftarrow#m
\longvarcirclerightarrow#m
\longvarcircleleftarrow#m
\longvarRightarrow#m
\longvarLeftarrow#m
\longvarCirclerightarrow#m
\longvarCircleleftarrow#m
\longvarSquarerightarrow#m
\longvarSquareleftarrow#m
\longvarRibbonrightarrow#m
\longvarRibbonleftarrow#m
\longsquaredarrow#m
\longroundedarrow#m

### Extendable form
\xvarrightarrow{%<arg%>}{%<arg%>}#m
\xvarleftarrow{%<arg%>}{%<arg%>}#m
\xvarrightharp{%<arg%>}{%<arg%>}#m
\xvarleftharp{%<arg%>}{%<arg%>}#m
\xvarleftrightarrow{%<arg%>}{%<arg%>}#m
\xvarleftrightharp{%<arg%>}{%<arg%>}#m
\xvarrightleftharp{%<arg%>}{%<arg%>}#m
\xvarmapsto{%<arg%>}{%<arg%>}#m
\xvarhookrightarrow{%<arg%>}{%<arg%>}#m
\xvarhookleftarrow{%<arg%>}{%<arg%>}#m
\xvardoublerightarrow{%<arg%>}{%<arg%>}#m
\xvardoubleleftarrow{%<arg%>}{%<arg%>}#m
\xvarcirclerightarrow{%<arg%>}{%<arg%>}#m
\xvarcircleleftarrow{%<arg%>}{%<arg%>}#m
\xvarRightarrow{%<arg%>}{%<arg%>}#m
\xvarLeftarrow{%<arg%>}{%<arg%>}#m
\xvarCirclerightarrow{%<arg%>}{%<arg%>}#m
\xvarCircleleftarrow{%<arg%>}{%<arg%>}#m
\xvarSquarerightarrow{%<arg%>}{%<arg%>}#m
\xvarSquareleftarrow{%<arg%>}{%<arg%>}#m
\xvarRibbonrightarrow{%<arg%>}{%<arg%>}#m
\xvarRibbonleftarrow{%<arg%>}{%<arg%>}#m
\xsquaredarrow{%<arg%>}{%<arg%>}#m
\xroundedarrow{%<arg%>}{%<arg%>}#m

## 2.4 Wide accents
\varwidehat{%<arg%>}#m
\varwidecheck{%<arg%>}#m
\varwidetilde{%<arg%>}#m

## 2.5 Extendable Operators
\suum#m
\prood#m

# 3. Defining your own symbols
## 3.1 Macros
\putsym{%<main symbol%>}{%<secondary symbol%>}#*
\putexsym{%<symbol%>}%<left cap%>%<right cap%>{%<height displacement%>}{%<skew%>}#*
\iNint{N}#m

# not documented
\pdfMsym#S
\pdfmsymsettransforms
\pdfMsymversion#S
\smallcircle#S
\strudelccode#S
