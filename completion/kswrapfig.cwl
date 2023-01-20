# kswrapfig package
# ponte-vecchio 2023-01-17 for v0.004

#keyvals:\usepackage/kswrapfig#c
insbox
#endkeyvals


\kswrapfig[%<options%>]{%<figure%>}{%<text%>}
#keyvals:\kswrapfig#c
Pos=#r,l
Width=%<dim%>%l
InPos=#r,c,l
Sep=%<dim%>%l
Indent=%<dim%>%l
Lower=%<dim%>%l
Caption={%<text%>}
LastLineSkip=%<dim%>%l
FirstLineSkip=%<dim%>%l
List=%<env name%>
VAdjust=%<dim%>%l
UseBox#true,false
#endkeyvals

\kswrapfigline[%<options%>]{%<figure%>}{%<text%>}
#keyvals:\kswrapfigline#c
Line=%<num lines%>
Pos=#r,l,c
CaptionName=%<env name%>
#endkeyvals

#ifOption:usebox
\ksinsbox[%<position%>%keyvals]{%<number%>}{%<cmd%>}
#keyvals:\ksinsbox#c
r
l
c
#endkeyvals
#endif