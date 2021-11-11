# uri package
# Matthew Bertucci 11/8/2021 for v2.0b

#include:kvoptions
#include:url

\urisetup{options%keyvals}

#keyvals:\urisetup
arxivpre={%|}
arxivpost={%|}
asinpre={%|}
asinpost={%|}
doipre={%|}
doipost={%|}
hdlpre={%|}
hdlpost={%|}
nbnpre={%|}
nbnpost={%|}
oclcpre={%|}
oclcpost={%|}
oidpre={%|}
oidpost={%|}
pubmedpre={%|}
pubmedpost={%|}
tinyuripre={%|}
tinyuripost={%|}
tinypuripre={%|}
tinypuripost={%|}
wcpre={%|}
wcpost={%|}
xmpppre={%|}
xmpppost={%|}
citeurlpre={%|}
citeurlpost={%|}
mailtopre={%|}
mailtopost={%|}
ukoelnpre={%|}
ukoelnpost={%|}
#endkeyvals

\uref{URL}{link text}#U
\arxiv{arXiv path}#U
\asin{Amazon number}#U
\doi{DOI number}#U
\hdl{handle.net path}#U
\nbn{NBN spec}#U
\oclc{WorldCat number}#U
\oid{OID number}#U
\pubmed{PubMed number}#U
\tinyuri{TinyURL path}#U
\tinypuri{TinyURL path}#U
\wc{WebCite path}#U
\citeurl{URL}#U
\mailto{address}#U
\mailto[subject]{address}#U
\ukoeln{UKoeln address}#U