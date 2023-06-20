# pdfmanagement-testphase package
# Matthew Bertucci 2023/06/18 for v0.95x

#include:tagpdf-base
#include:l3bitset
#include:pdfmanagement-firstaid

## l3pdfmanagement
\PDFManagementAdd{resource path}{name}{value}

## l3docinit
# \DocumentMetadata{options} in latex-dev.cwl
\AddToDocumentProperties{property}{value}
\AddToDocumentProperties[label]{property}{value}
\GetDocumentProperties{label/property}
\ShowDocumentProperties

## documentmetadata-support.ltx
\documentmetadatasupportversion#S
\documentmetadatasupportdate#S

# deprecated
\DeclareDocumentMetadata{options}#S

# available if hyperref loaded
\url[options%keyvals]{URL}#U
\hrefurl{URL}{text}#U
\hrefurl[options%keyvals]{URL}{text}#U
\hrefpdf{file}{text}
\hrefpdf[options%keyvals]{file}{text}
\hrefrun{launch link%URL}{text}
\hrefrun[options%keyvals]{launch link%URL}{text}

#keyvals:\url
protocol=%<prefix%>
format=%<format commands%>
#endkeyvals

#keyvals:\hrefurl
urlencode
protocol=%<prefix%>
ismap
#endkeyvals

#keyvals:\hrefpdf
destination=%<dest name%>
page=%<number%>
pdfremotestartview=#Fit,FitB,FitH,FitV,FitBH,FitBV
afrelationship=%<PDF name%>
#endkeyvals

#keyvals:\hrefrun
run-parameter=%<parameter%>
#endkeyvals

#keyvals:\hypersetup
href/urlencode
href/protocol=%<prefix%>
href/destination=%<dest name%>
href/format=%<format commands%>
pdfcopyright=%<copyright text%>
pdftype=#Collection,Dataset,Event,Image,InteractiveResource,MovingImage,PhysicalObject,Service,Software,Sound,StillImage,Text
pdflicenseurl=%<URL%>
pdfauthortitle=%<author title%>
pdfcaptionwriter=%<caption writer name%>
pdfmetalang=%<meta language%>
pdfsource=%<source file name%>
pdfdocumentid=uuid:%<id num%>
pdfinstanceid=uuid:%<id num%>
pdfversionid=%<version id%>
pdfrendition=#default,draft,low-res,proof,screen,thumbnail
pdfpublication=%<publication%>
pdfpubtype=%<publication type%>
pdfbytes=%<file size%>
pdfnumpages=%<number of pages%>
pdfissn=%<print ISSN%>
pdfeissn=%<electronic ISSN%>
pdfisbn=%<ISBN%>
pdfbookedition=%<book edition%>
pdfpublisher=%<publisher%>
pdfvolumenum=%<volume number%>
pdfissuenum=%<issue number%>
pdfpagerange={%<page ranges%>}
pdfdoi=%<DOI%>
pdfurl=%<URL%>
pdfidentifier=%<identifier%>
pdfsubtitle=%<subtitle%>
pdfpubstatus=%<publication status%>
pdfcontactaddress=%<street address%>
pdfcontactcity=%<city%>
pdfcontactregion=%<state or province%>
pdfcontactpostcode=%<postal code%>
pdfcontactcountry=%<country%>
pdfcontactphone=%<phone number%>
pdfcontactemail=%<email%>
pdfcontacturl=%<URL%>
pdfdate=%<date%>
#endkeyvals
