# eq2db package
# Matthew Bertucci 2022/05/21 for v2.0

#include:xkeyval
#include:exerquiz

#keyvals:\usepackage/eq2db#c
eqRecord
eqEmail
eqText
taoas
custom=%<file name%>
tagged
submitAs=#FDF,HTML,XML
#endkeyvals

#ifOption:eqEmail
# loads eqemail.def
\htmlSubmitType#*
\insertHTMLs#*
#endif

#ifOption:eqText
# loads eqtext.def
\htmlSubmitType#*
\insertHTMLs#*
#endif

\addHiddenTextField[eforms params]{field}{value}#*
\addHiddenTextField{field}{value}#*
\addtohidden#*
\basicFieldsSet#*
\hiddenTextField[eforms params]{field}{value}
\hiddenTextField{field}{value}
\populateHiddenField{field}{value}
\populatehiddenfields#*
\rtnURL{URL}#U
\thisRtnURL