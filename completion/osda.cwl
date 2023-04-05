# osda package
# Matthew Bertucci 2023/04/05 for v1.2.0

#include:footmisc
#include:flushend
#include:ifthen
#include:qrcode
#include:xcolor
#include:hyperref
#include:tikz
#include:pgfopts
#include:tikzlibrarysvg.path

\osdafootnote
\osdafootnote[options%keyvals]
\osdanotice
\osdanotice[options%keyvals]
\osdaset{options%keyvals}

#keyvals:\usepackage/osda#c,\osdafootnote,\osdanotice,\osdaset
auto#true,false
%<year%>
cc-by
cc-by-sa
cc-by-nc-sa
cc-by-nc-nd
arXiv
cc0
paper/url=%<URL%>
paper/doi=%<DOI%>
url=%<URL%>
doi=%<DOI%>
license/long=%<long name%>
license/short=%<short name%>
license/version=%<version%>
license/url=%<URL%>
proceedings/title=%<title%>
proceedings/startpage=%<number%>
proceedings/endpage=%<number%>
pages={%<startpage%>}{%<endpage%>}
workshop/counter=%<number%>
workshop/longname=%<name%>
workshop/acronym=%<acronym%>
location/city=%<city%>
location/country=%<country%>
date/month=%<month%>
date/day=%<day%>
date/year=%<year%>
hostconference/longname=%<name%>
hostconference/acronym=%<acronym%>
#endkeyvals

# not documented
\WrapLR{left-image}{right-image}{text}#*
\blfootnote{text}#*
\osdalogo{width}#*