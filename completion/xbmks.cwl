# xbmks package
# Matthew Bertucci 1/22/2022 for v2.0.3

#include:xkeyval
#include:ifpdf
#include:ifxetex
#include:hyperref

#keyvals:\usepackage/xbmks#c
dvipsone
dvips
pdftex
luatex
xetex
#endkeyvals

\xbmksetup{options%keyvals}

#keyvals:\xbmksetup
docbundle={%<name1,name2,...%>}
colors={%<int=<color>,ext=<color>%>}
styles={%<style1,style2,...%>}
#endkeyvals

\pdfbookmarkx{text}{name}
\pdfbookmarkx[level]{text}{name}
\pdfbookmarkx{text}[keyvals]{name}
\pdfbookmarkx[level]{text}[keyvals]{name}

\currentpdfbookmarkx{text}{name}
\currentpdfbookmarkx{text}[keyvals]{name}

\subpdfbookmarkx{text}{name}
\subpdfbookmarkx{text}[keyvals]{name}

\belowpdfbookmarkx{text}{name}
\belowpdfbookmarkx{text}[keyvals]{name}

#keyvals:\pdfbookmarkx,\currentpdfbookmarkx,\subpdfbookmarkx,\belowpdfbookmarkx
action={%<PDF action%>}
color=#%color
style=
#endkeyvals

\bWebCustomize#S
\eWebCustomize#S
\xbmksetupi{options}#S
\xbmkcsarg{arg1}{arg2}#S