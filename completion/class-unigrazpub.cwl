# unigrazpub class
# Matthew Bertucci 2022/10/14 for v1.00

#include:l3keys2e
#include:class-scrbook
#include:roboto
#include:sourceserifpro
#include:anyfontsize
#include:geometry
#include:ragged2e
#include:scrlayer-scrpage
#include:csquotes
#include:biblatex-chicago
#include:graphicx
#include:doclicense
#include:hyperref

#keyvals:\documentclass/unigrazpub#c
collection#true,false
license-type=%<type%>
license-modifier=#by,by-sa,by-nd,by-nc,by-nc-sa,by-nc-nd
license-version=#1.0,3.0,4.0
#endkeyvals

\edition{edition%text}
\insertedition
\insertpublishersaddress
\insertauthor
\insertdate
\insertpublishers

\Article{title}#L1
\Article[options%keyvals]{title}#L1

#keyvals:\Article#c
author=%<author%>
authorkeys={%<author1,author2,...%>}
head=%<text%>
subtitle=%<text%>
imprint=%<text%>
doi=%<DOI%>
license-type=%<type%>
license-modifier=#by,by-sa,by-nd,by-nc,by-nc-sa,by-nc-nd
license-version=#1.0,3.0,4.0
#endkeyvals

\begin{abstract}[language]
\keywords{keywords%text}
\listofauthors

# not documented
\HUGE#*
\TocAuthorEntry{arg1}{arg2}#*
\currentarticlelabel#*
\citeimprint{bibid}#*c
\citearticleauthor{bibid}#*c
\publishersaddress{address%text}#*
