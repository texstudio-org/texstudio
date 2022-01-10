# metastr package
# Matthew Bertucci 1/10/2022 for v1.1.2

#include:hyperref
#include:hyperxmp
#include:keyval

#keyvals:\usepackage/metastr#c
hyperref#true,false
hyperxmp#true,false
checkdef#true,false
cclogo#true,false
cclogocurr=#dollar,euro,yen
cclogoshape=#box,slim
xmppdfinfo#true,false
draft#true,false
titlematter#true,false
course#true,false
loadlang=#en,de,fr,es
#endkeyvals

\metadef{reg}
\metaset{reg}{def}
\metaset[var]{reg}{def}
\metasetlang{ln-CN}
\metasetlang*{ln-CN}

\metaget[var]{reg}{def}
\metaif[]{reg}{true}{false}
\metaunset{reg}
\metaunset[var]{reg}
\metaappend{reg}{def}
\metaappend[var]{reg}{def}
\metaprepend{reg}{def}
\metaprepend[var]{reg}{def}
\metaaddsep{reg}{sep}{def}
\metaaddsep[var]{reg}{sep}{def}

\metapick[var]{reg}
\metaifpick[var]{reg}{true}{false}
\metacompose[var]{reg}{prefix}{postfix}{empty}
\metatitleline[var]{reg}
\metatitlelinetwo[var1]{reg1}[var2]{reg2}

\metawritepdfinfo
\metawritepdfaux
\metawritepdfpreamble
\metawritepdfcontact
\metawritepdfrights
\metawritepdf

\metacopyright{preset%keyvals}
#keyvals:\metacopyright
plain
parts
doc
doc-parts
reserved
publicdomain
#endkeyvals
\metalicense{preset%keyvals}
#keyvals:\metalicense
consent
consent-noncom
lppl
#endkeyvals
\metalicensecc{license%keyvals}
#keyvals:\metalicensecc
by
by-sa
by-nd
by-nc
by-nc-sa
by-nc-nd
zero
pd
#endkeyvals

\metaterm
\metatranslate[ln]{term}
\metasetterm[ln]{reg}{def}

\metasetup{options%keyvals}
#keyvals:\metasetup#c
draft#true,false
#endkeyvals

\metacomma#*
\metatilde#*