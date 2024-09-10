# circledtext package
# Matthew Bertucci 2024/09/09 for v1.1.1

#include:xtemplate
#include:l3keys2e
#include:l3draw

\circledtext{text}
\circledtext[options%keyvals]{text}
\circledtextset{options%keyvals}

#keyvals:\circledtext,\circledtextset
basechar=%<base char%>
charf=%<format macros%>
boxtype=#o,o+,ox,ox+,x+,O,O+,OX,OX+,X+,oo,Oo,OO
charshrink=%<factor%>
resize=#none,real,base
xscale=%<factor%>
yscale=%<factor%>
width=##L
height=##L
boxlinewidth=##L
crosslinewidth=##L
crosscolorratio=%<percent%>
boxcolor=#%color
charcolor=#%color
boxfill=#%color
charstroke=#none,solid,dashed,invisible
dashpattern={%<len1,len2,...%>}
lowerbgcolor=#%color
upperbgcolor=#%color
shadowcolor=#%color
#endkeyvals

\charboxwd#*
\charboxht#*
