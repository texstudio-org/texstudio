# bigfoot package
# Matthew Bertucci 4/28/2022 for v2.1

#include:manyfoot
#include:suffix
#include:perpage

#keyvals:\usepackage/bigfoot#c
ruled
robust
fragile
verbose
#endkeyvals

\RestyleFootnote{type}{style}
\FootnoteSpecific{type}
\DefineFootnoteStack{name}
\PushFootnoteMark{stack name}
\PopFootnoteMark{stack name}
\hfootfraction#*
\vtypefraction#*
\FootnoteMinimum#*
\FootnoteMainMinimum#*
\bigfoottolerance#*
\footnotecarryratio#*