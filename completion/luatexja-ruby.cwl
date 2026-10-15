# luatexja-ruby package
# Matthew Bertucci 2026/10/08 for v0.71

#include:luatexja

\ltjruby{親|文|字}{おや|も|じ}
\ltjruby[options%keyvals]{親|文|字}{おや|も|じ}
\ruby{親|文|字}{おや|も|じ}
\ruby[options%keyvals]{親|文|字}{おや|も|じ}
\ltjsetruby{options%keyvals}
\ltjkenten{親文字}
\ltjkenten[options%keyvals]{親文字}
\kenten{親文字}
\kenten[options%keyvals]{親文字}

#keyvals:\ltjruby,\ruby,\ltjsetruby,\ltjkenten,\kenten
pre=%<real%>
post=%<real%>
mode=
intrude_jfmgk#true,false
intrude_kanjiskip#true,false
intrude_xkanjiskip#true,false
stretchruby={%<left%>}{%<middle%>}{%<right%>}
stretch={%<left%>}{%<middle%>}{%<right%>}
stretchbol={%<left%>}{%<middle%>}{%<right%>}
stretcheol={%<left%>}{%<middle%>}{%<right%>}
maxmargin=%<real%>
size=%<real%>
intergap=%<real%>
rubysmash#true,false
ybaseheight=%<real%>
tbaseheight=%<real%>
baseheight=%<real%>
yrubydepth=%<real%>
trubydepth=%<real%>
rubydepth=%<real%>
kenten=%<command%>
fontcmd=%<command%>
always_highlight_protrusion#true,false
naka
kata
#endkeyvals

#keyvals:\ltjsetparameter,\ltjglobalsetparameter
rubypreintrusion={%<chr_code,pre_int%>}
rubypostintrusion={%<chr_code,post_int%>}
#endkeyvals

#keyvals:\ltjgetparameter
rubypreintrusion
rubypostintrusion
#endkeyvals
