# attachfile2 package
# Matthew Bertucci 10/17/2021 for v2.11

#include:iftex
#include:keyval
#include:color
#include:infwaerr
#include:ltxcmds
#include:kvoptions
#include:pdftexcmds
#include:pdfescape
#include:hyperref
#include:hycolor

\attachfile{file}
\attachfile[options%keyvals]{file}
\noattachfile
\noattachfile[options%keyvals]
\notextattachfile{text}
\notextattachfile[options%keyvals]{text}
\textattachfile{file}{text}
\textattachfile[options%keyvals]{file}{text}
\attachfilesetup{options%keyvals}

#keyvals:\attachfile,\attachfilesetup,\noattachfile,\notextattachfile,\textattachfile
appearance#true,false
author=
color=
created=
date=
description=
icon=#Graph,Paperclip,PushPin,Tag
mimetype=
modified=
print#true,false
size=
subject=
timezone=
zoom#true,false
scale=
nofiles
ucfilespec=
annotname=
#endkeyvals