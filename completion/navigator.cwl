# navigator package
# Matthew Bertucci 11/6/2021 for v1.1

#include:yax

\finishpdffile

\anchor{name}
\anchor[options%keyvals]{name}

#keyvals:\anchor
up=##L
left=##L
fit=#xyz,fit,fith,fitv,fitb,fitbh,fitbv,fitr
zoom=%<number%>
#endkeyvals

\anchorname{name}

\outline{level}{title%plain}
\outline[options%keyvals]{level}{title%plain}
\outline{level}[name]{title%plain}
\outline[options%keyvals]{level}[name]{title%plain}

#keyvals:\outline
open#true,false
bold#true,false
italic#true,false
color=%<r g b%>
outlinecolor%<r g b%>
anchor=%<name%>
action%<name%>
#endkeyvals

\pdfdef{cmd}{definition}#d
\pdfdef{cmd}[args]{definition}#d

\jumplink{name}{text}
\jumplink[options%keyvals]{name}{text}
\urllink{URL}{text}#U
\urllink[options%keyvals]{URL}{text}#U
\javascriptlink{JavaScript code}{text}
\javascriptlink[options%keyvals]{JavaScript code}{text}
\actionlink{name}{text}
\actionlink[options%keyvals]{name}{text}
\rawactionlink{PDF code}{text}
\rawactionlink[options%keyvals]{PDF code}{text}
\annotation{PDF code}{text}
\annotation[options%keyvals]{PDF code}{text}

#keyvals:\jumplink,\urllink,\javascriptlink,\actionlink,\rawactionlink,\annotation,\openfilelink
border=%<number%>
color=%<r g b%>
linkcolor=%<r g b%>
dash=%<numbers%>
highlight=#none,invert,outline,push
pre=%<code%>
post=%<code%>
raw=%<PDF code%>
#endkeyvals

\urlaction{name}{URL}
\javascriptaction{name}{JavaScript code}

\embeddedfile{object name}{file}
\embeddedfile[description]{object name}{file}
\embeddedfile{object name}[alt filename]{file}
\embeddedfile[description]{object name}[alt filename]{file}

\openfilelink{file}{text}
\openfilelink[options%keyvals]{file}{text}
\openfilelink{file}[page]{text}
\openfilelink[options%keyvals]{file}[page]{text}

\pdfobject{name}{code}
\pdfdictobject{name}{code}
\pdfstreamobject{name}{stream}
\pdfstreamobject[raw code]{name}{stream}
\pdffileobject{name}{file}
\pdffileobject[raw code]{name}{file}
\pdfreserveobject{name}
\pdfensureobject{name}
\pdfobjectnumber{name}
\pdfrefobject{name}
\pdfobjectstatus{name}

\ifpdfobject{name}{true}{false}
\pdfstring{string}
