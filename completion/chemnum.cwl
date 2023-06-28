# chemnum package
# Matthew Bertucci 12/9/2021 for v1.3a

#include:l3keys2e
#include:translations
#include:chemgreek
#include:psfrag

\cmpd{IDs}
\cmpd[options%keyvals]{IDs}
\cmpd*{IDs}#*
\cmpd*[options%keyvals]{IDs}#*
\cmpd+{IDs}#*
\cmpd+[options%keyvals]{IDs}#*

\refcmpd{ID}
\refcmpd[options%keyvals]{ID}
\labelcmpd{ID}
\labelcmpd[options%keyvals]{ID}

\replacecmpd{ID}
\replacecmpd[options%keyvals]{ID}
\replacecmpd+{ID}#*
\replacecmpd+[options%keyvals]{ID}#*
\initcmpd{IDs}
\initcmpd[options%keyvals]{IDs}

\cmpdplain{ID}#*
\subcmpdplain{main ID}{sub ID}#*
\submaincmpdplain{main ID}{sub ID}#*
\cmpdproperty{ID}{property}#*
\subcmpdproperty{main ID}{sub ID}{property}#*
\newcmpdcounterformat{name}{command}#*
\resetcmpd#*
\resetcmpd[integer]#*
\cmpdshowdef{ID}#*
\cmpdshowref{ID}#*
\subcmpdshowdef{main ID}{sub ID}#*
\subcmpdshowref{main ID}{sub ID}#*
\setcmpdproperty{property}{main ID}{value}#*
\setcmpdlabel{main ID}{value}#*
\chemnumshowdef{arg}#*
\chemnumshowref{arg}#*
\cmpdprintlabelid{arg}#*
\cmpdshowlabelmargin{arg}#*
\cmpdshowlabelinline{arg}#*
\thecmpdmain#*

\setchemnum{options%keyvals}

#keyvals:\setchemnum
counter-within=%<counter%>
replace-auto#true,false
replace-tag=%<text%>
replace-tag-nr=%<integer%>
replace-style={%<code%>}
replace-pos={%<TeX pos%>}{%<PS pos%>}
init=#true,main,false,strict,main-strict
log=#true,false,silent,verbose
show-keys=#true,false,def,ref
hyperlinks#true,false

#endkeyvals

#keyvals:\setchemnum,\cmpd,\cmpd*,\cmpd+,\refcmpd,\labelcmpd,\replacecmpd,\replacecmpd+,\initcmpd
counter-format=#arabic,alph,Alph,roman,Roman,greek,Greek
sub-counter-format=#arabic,alph,Alph,roman,Roman,greek,Greek
compress#true,false
merge#true,false
pre-label-code={%<code%>}
post-label-code={%<code%>}
pre-main-label-code={%<code%>}
post-main-label-code={%<code%>}
main-sub-sep={%<token%>}
format={%<formatting commands%>}
list-label-sep={%<token%>}
sub-list-label-sep={%<token%>}
list-sep-two={%<code%>}
list-sep-more={%<code%>}
list-sep-last-two={%<code%>}
sub-list-sep-two={%<code%>}
sub-list-sep-more={%<code%>}
sub-list-sep-last-two={%<code%>}
sub-list-sep-range={%<code%>}
#endkeyvals

#keyvals:\cmpd,\cmpd*,\cmpd+,\refcmpd,\labelcmpd,\replacecmpd,\replacecmpd+,\initcmpd
sub-only#true,false
sub-all
#endkeyvals

#keyvals:\replacecmpd
tag=%<text%>
style={%<code%>}
pos={%<TeX pos%>}{%<PS pos%>}
#endkeyvals