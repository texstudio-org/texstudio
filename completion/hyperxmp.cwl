# hyperxmp package
# Matthew Bertucci 12/28/2021 for v0.20c

#include:kvoptions
#include:pdfescape
#include:stringenc
#include:intcalc
#include:iftex
#include:ifmtarg
#include:etoolbox
#include:ifthen
#include:luacode
#include:ifdraft
#include:hyperref
#include:totpages
#include:ifluatex

#keyvals:\usepackage/hyperxmp#c
verbose
final
clear-aux
no-files
use-files
use-aux
blank
#endkeyvals

#keyvals:\hypersetup
pdfaconformance=%<conformance%>
pdfapart=%<conformance level%>
pdfauthortitle=%<author title%>
pdfbookedition=%<book edition%>
pdfbytes=%<file size%>
pdfcaptionwriter=%<caption writer name%>
pdfcontactaddress=%<street address%>
pdfcontactcity=%<city%>
pdfcontactcountry=%<country%>
pdfcontactemail=%<email%>
pdfcontactphone=%<phone number%>
pdfcontactpostcode=%<postal code%>
pdfcontactregion=%<state or province%>
pdfcontacturl=%<URL%>
pdfcopyright=%<copyright text%>
pdfdate=%<date%>
pdfdocumentid=uuid:%<id num%>
pdfdoi=%<DOI%>
pdfeissn=%<electronic ISSN%>
pdfidentifier=%<identifier%>
pdfinstanceid=uuid:%<id num%>
pdfisbn=%<ISBN%>
pdfissn=%<print ISSN%>
pdfissuenum=%<issue number%>
pdflicenseurl=%<URL%>
pdfmetadate=%<date%>
pdfmetalang=%<meta language%>
pdfnumpages=%<number of pages%>
pdfpagerange={%<page ranges%>}
pdfpublication=%<publication%>
pdfpublisher=%<publisher%>
pdfpubstatus=%<publication status%>
pdfpubtype=%<publication type%>
pdfrendition=#default,draft,low-res,proof,screen,thumbnail
pdfsource=%<source file name%>
pdfsubtitle=%<subtitle%>
pdftype=#Collection,Dataset,Event,Image,InteractiveResource,MovingImage,PhysicalObject,Service,Software,Sound,StillImage,Text
pdfuapart=%<conformance level%>
pdfurl=%<URL%>
pdfversionid=%<version id%>
pdfvolumenum=%<volume number%>
pdfxstandard=%<PDF/X standard%>
keeppdfinfo
#endkeyvals

\xmplinesep#*

\xmpcomma
\xmpquote{text}
\xmptilde

\XMPLangAlt{language}{options%keyvals}

#keyvals:\XMPLangAlt
pdftitle=%<text%>
pdfsubject=%<subject%>
pdfcopyright=%<copyright text%>
#endkeyvals

\next#S

# deprecated
\XMPTruncateList{arg}#S
