# nccboxes package
# Matthew Bertucci 1/23/2022 for v1.2

\jhbox{prototype}{text}
\jhbox{prototype}[pos%keyvals]{text}

#keyvals:\jhbox
l
c
r
s
#endkeyvals

\jvbox{prototype}{text}
\jvbox{prototype}[pos%keyvals]{text}
\jparbox{prototype}{text}{width}
\jparbox{prototype}[pos%keyvals]{width}{text}


#keyvals:\jvbox,\jparbox
t
c
b
#endkeyvals

\addbox{height-adjust%l}{depth-adjust%l}{text}
\pbox{body%text}
\pbox[pos]{body%text}
\picbox{picture code}
\Strut/%<value%>/
\Strutletter
\tstrut
\bstrut
\tbstrut
\Strutstretch

\cbox{body%text}
\cbox[pos]{body%text}
\cbox/%<value%>/{%<body%>}
\cbox/%<value%>/[%<pos%>]{%<body%>}
\cbox*{body%text}
\cbox*[pos]{body%text}
\cbox*/%<value%>/{%<body%>}
\cbox*/%<value%>/[%<pos%>]{%<body%>}

\cboxstyle
\tc{field%text}