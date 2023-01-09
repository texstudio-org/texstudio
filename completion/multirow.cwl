# mode: multirow.sty
# denisbitouze, 15.03.2015
# Matthew Bertucci 10/1/2021 for v2.8

#keyvals:\usepackage/multirow#c
debug
longtable
supertabular
#endkeyvals

\multirow{number of rows}{width or *}{text}
\multirow[vpos%keyvals]{number of rows}{width or *}{text}
\multirow{number of rows}[bigstruts]{width or *}{text}#*
\multirow{number of rows}{width or *}[vmove%l]{text}#*
\multirow[vpos%keyvals]{number of rows}[bigstruts]{width or *}[vmove%l]{text}#*

#keyvals:\multirow
c
t
b
#endkeyvals

\multirowsetup#*
\multirowdebugtrue#*
\multirowdebugfalse#*
\bigstrutjot#*

#ifOption:supertabular
\STneed{length}
#endif
