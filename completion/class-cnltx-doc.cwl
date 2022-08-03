# cnltx-doc class
# Matthew Bertucci 10/18/2021 for v0.15

#include:cnltx-tools
#include:cnltx-names
#include:cnltx-example
#include:class-scrartcl
#include:scrlayer-scrpage
#include:multicol
#include:ragged2e
#include:marginnote
#include:hyperref

#keyvals:\documentclass/cnltx-doc#c
load-preamble#true,false
load-preamble-#true,false
load-preamble+#true,false
add-index#true,false
adapt-layout#true,false
babel-options={%<options%>}
scrartcl={%<options%>}
#endkeyvals

\sinceversion{version}
\changedversion{version}

\newnote{cmd}{definition}#d
\newnote{cmd}[args]{definition}#d
\newnote{cmd}[args][default]{definition}#*d
\newnote*{cmd}{definition}#d
\newnote*{cmd}[args]{definition}#d
\newnote*{cmd}[args][default]{definition}#*d

\newpackagename{cmd}{name}#d

\lppl
\LPPL
\license[maintenance status]
\license*[maintenance status]
\ctan
\CTAN
\CTANurl{name}
\CTANurl[directory]{name}
\email{email address}
\website{web address%URL}#U
\securewebsite{web address%URL}#U
\needpackage{name}
\needpackage[directory]{name}
\needclass{name}
\needclass[directory]{name}

\begin{commands}
\end{commands}
\begin{options}
\end{options}
\begin{environments}
\end{environments}

#keyvals:\setcnltx#c
list-setup={%<definitions%>}
expandable-sign={%<definitions%>}
package={%<package%>}
class={%<class%>}
name={%<name%>}
title={%<title%>}
authors={%<author list%>}
version=%<number%>
date=
info={%<package/class info%>}
subtitle={%<subtitle%>}
url={%<url%>}
email={%<email address%>}
abstract={%<abstract%>}
build-title#true,false
quote-format={%<definitions%>}
quote-author-format={%<definitions%>}
index-prologue={%<text%>}
index-space=##L
index-setup={%<options%>}
makeindex-setup={%<options%>}
index-style={%<style file%>}
#endkeyvals

\command{name}#/commands
\command{name}[after]#/commands
\command*{name}#/commands
\command*{name}[after]#/commands
\Default{code}#/commands,options
\Default*{code}#/commands,options
\Default!{code}#/commands,options
\expandable#/commands
\unexpandable#/commands
\expandablesign#*
\expandablesymbol#*
\unexpandablesymbol#*

\opt{name}#/options
\opt*{name}#/options
\keyval{name}{value}#/options
\keyval*{name}{value}#/options
\keyval-{name}{value}#/options
\keylit{name}{value}#/options
\keylit*{name}{value}#/options
\keylit-{name}{value}#/options
\keychoice{name}{list of choices}#/options
\keychoice*{name}{list of choices}#/options
\keybool{name}#/options
\keybool*{name}#/options
\Module{name}#/options
\Module*{name}#/options
\Module!{name}#/options

\environment{name}#/environments
\environment*{name}#/environments
\environment{name}[after]#/environments
\environment*{name}[after]#/environments

\begin{cnltxquote}
\begin{cnltxquote}[author/reference]
\end{cnltxquote}

#ifOption:load-preamble
#include:ifxetex
#include:ifluatex
#include:fontenc
#include:libertine
#include:libertinehologopatch
#include:microtype
#include:fnpct
#include:babel
# from T1 option of fontenc
\DH#n
\dh#n
\dj#n
\DJ#n
\guillemetleft#n
\guillemetright#n
\guillemotleft#*n
\guillemotright#*n
\guilsinglleft#n
\guilsinglright#n
\Hwithstroke#n
\hwithstroke#n
\k{arg}#n
\NG#n
\ng#n
\quotedblbase#n
\quotesinglbase#n
\textogonekcentered{arg}#n
\textquotedbl#n
\th#n
\TH#n
#endif
#ifOption:load-preamble=true
#include:ifxetex
#include:ifluatex
#include:libertine
#include:libertinehologopatch
#include:microtype
#include:fnpct
#include:babel
# from T1 option of fontenc
\DH#n
\dh#n
\dj#n
\DJ#n
\guillemetleft#n
\guillemetright#n
\guillemotleft#*n
\guillemotright#*n
\guilsinglleft#n
\guilsinglright#n
\Hwithstroke#n
\hwithstroke#n
\k{arg}#n
\NG#n
\ng#n
\quotedblbase#n
\quotesinglbase#n
\textogonekcentered{arg}#n
\textquotedbl#n
\th#n
\TH#n
#endif

#ifOption:load-preamble-
#include:ifxetex
#include:ifluatex
#include:microtype
#include:fnpct
#include:babel
#endif
#ifOption:load-preamble-=true
#include:ifxetex
#include:ifluatex
#include:microtype
#include:fnpct
#include:babel
#endif

#ifOption:add-index
#include:imakeidx
#endif
#ifOption:add-index=true
#include:imakeidx
#endif

#ifOption:add-bib
#include:biblatex
#endif
#ifOption:add-bib=true
#include:biblatex
#endif

#ifOption:load-preamble+
#include:ifxetex
#include:ifluatex
#include:fontenc
#include:libertine
#include:libertinehologopatch
#include:microtype
#include:fnpct
#include:babel
#include:imakeidx
#include:biblatex
# from T1 option of fontenc
\DH#n
\dh#n
\dj#n
\DJ#n
\guillemetleft#n
\guillemetright#n
\guillemotleft#*n
\guillemotright#*n
\guilsinglleft#n
\guilsinglright#n
\Hwithstroke#n
\hwithstroke#n
\k{arg}#n
\NG#n
\ng#n
\quotedblbase#n
\quotesinglbase#n
\textogonekcentered{arg}#n
\textquotedbl#n
\th#n
\TH#n
#endif
#ifOption:load-preamble+=true
#include:ifxetex
#include:ifluatex
#include:fontenc
#include:libertine
#include:libertinehologopatch
#include:microtype
#include:fnpct
#include:babel
#include:imakeidx
#include:biblatex
# from T1 option of fontenc
\DH#n
\dh#n
\dj#n
\DJ#n
\guillemetleft#n
\guillemetright#n
\guillemotleft#*n
\guillemotright#*n
\guilsinglleft#n
\guilsinglright#n
\Hwithstroke#n
\hwithstroke#n
\k{arg}#n
\NG#n
\ng#n
\quotedblbase#n
\quotesinglbase#n
\textogonekcentered{arg}#n
\textquotedbl#n
\th#n
\TH#n
#endif

#ifOption:load-microtype
#include:microtype
#endif
#ifOption:load-microtype=true
#include:microtype
#endif

\begin{cnltxlist}#*
\end{cnltxlist}#*
\cnltxpackagenameformat{text}#*
\visualizespaces{text}#*
\visiblespace#*
