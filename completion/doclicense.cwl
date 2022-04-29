# doclicense package
# Matthew Bertucci 2022/04/29 for v3.1.0

#include:kvoptions
#include:xifthen
#include:xstring
#include:etoolbox
#include:xspace
#include:verbatim
#include:hyperxmp
#include:ccicons
#include:graphicx
#include:hyperref
#include:csquotes

#keyvals:\usepackage/doclicense#c
type=%<type%>
modifier=#by,by-sa,by-nd,by-nc,by-nc-sa,by-nc-nd
version=#1.0,3.0,4.0
lang=#UKenglish,USenglish,acadian,american,australian,brazilian,british,bulgarian,canadian,canadien,catalan,chinese-gbk,chinese-utf8,croatian,english,french,galician,german,italian,japanese,marathi,newzealand,ngerman,polish,portuguese,russian,spanish
imagemodifier=%<modifier%>
imageposition=#right,left
imagewidth=##L
imagedistance=##L
hyphenation=%<macro%>
hyperxmp#true,false
#endkeyvals

#ifOption:hyphenation=RaggedRight
#include:ragged2e
#endif
#ifOption:hyphenation={RaggedRight}
#include:ragged2e
#endif

\doclicenseType
\doclicenseLongType
\doclicenseModifier
\doclicenseVersion
\doclicenseURL
\doclicenseName
\doclicenseLongName
\doclicenseNameRef
\doclicenseLongNameRef
\doclicenseText
\doclicenseLongText
\doclicenseLongTextForHyperref
\doclicensePlainFullText
\doclicensePlainFullTextFileName
\doclicenseFullText
\doclicenseFullTextFileName
\doclicenseTypeIcon
\doclicenseIcon
\doclicenseImage
\doclicenseImage[width]
\doclicenseImageFileName

\doclicenseThis

# deprecated
\doclicenseLicense#S
