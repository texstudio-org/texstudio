# ksruby package
# ponte-vecchio 2023-01-17 for v0.0.2

#keyvals:\usepackage/ksruby#c
rubysep=%<dim%>%l
rubysize=%<size%>
rubyeachchar#true,false
rubywidth#true,false
rubyheight#true,false
rubycenter=#c,l,r
#endkeyvals

\ksruby{%<below%>}{%<above%>}
\ksruby*{%<below%>}{%<above%>}
\ruby{%<below%>}{%<above%>
\ruby*{%<below%>}{%<above%>}

\ksrubycenterdefault{%<options%>}
\ksrubyheightdefault
\ksrubyheightdefault[false]
\ksrubywidthdefault
\ksrubywidthdefault[false]
\ksrubyeachchardefault
\ksrubyeachchardefault[false]
\ksrubysep{%<dim%>%l}
\ksrubysize{%<size%>}

\ksrubyextra{%<cmds%>}

#keyvals:ksrubycenter#c
c
l
r
#endkeyvals