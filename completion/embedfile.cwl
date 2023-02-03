# embedfile package
# Matthew Bertucci 10/17/2021 for v2.11

#include:infwaerr
#include:iftex
#include:pdftexcmds
#include:ltxcmds
#include:kvsetkeys
#include:kvdefinekeys
#include:pdfescape

\embedfile{file}
\embedfile[options%keyvals]{file}
\embedfilesetup{options%keyvals}

#keyvals:\embedfile#c,\embedfilesetup#c
filespec=
ucfilespec=
filesystem=
mimetype=
desc=%<description%>
afrelationship=%<PDF name%>
stringmethod=#psd,escape
id=
#endkeyvals

#keyvals:\embedfilesetup#c
view=#details,tile,hidden
initialfile=
#endkeyvals

\embedfilefinish#*

\embedfilefield{key%plain}{options%keyvals}

#keyvals:\embedfilefield
type=#text,date,number,file,desc,moddate,size
title=
visible#true,false
edit#true,false
#endkeyvals

\embedfilesort{key-sort-list}

\embedfileifobjectexists{id}{type%keyvals}{then}{else}
\embedfilegetobject{id}{type%keyvals}

#keyvals:\embedfileifobjectexists,\embedfilegetobject
EmbeddedFile
Filespec
#endkeyvals
