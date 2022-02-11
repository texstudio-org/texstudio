# a0poster class
# Matthew Bertucci 11/14/2021 for v1.22b

#keyvals:\documentclass/a0poster#c
landscape
portrait
a0b
a0
a1
a2
a3
posterdraft
final
#endkeyvals

\ifportrait#*
\portraittrue#*
\portraitfalse#*
\ifanullb#*
\anullbtrue#*
\anullbfalse#*
\ifanull#*
\anulltrue#*
\anullfalse#*
\ifaeins#*
\aeinstrue#*
\aeinsfalse#*
\ifazwei#*
\azweitrue#*
\azweifalse#*
\ifadrei#*
\adreitrue#*
\adreifalse#*
\ifposterdraft#*
\posterdrafttrue#*
\posterdraftfalse#*

\xkoord#*
\ykoord#*
\xscale#*
\yscale#*

#ifOption:portrait
\tausch
#endif

\Ausgabe#*

\veryHuge
\VeryHuge
\VERYHuge
