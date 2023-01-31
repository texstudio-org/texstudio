# beamerbasenotes package
# Matthew Bertucci 1/30/2022 for v3.65

#keyvals:\setbeameroption#c
hide notes
show notes
show notes on second screen
show notes on second screen=#left,right,bottom,top
show only notes
show only slides with notes
#endkeyvals

\note{note text%text}
\note<overlay specification>{note text%text}
\note[options%keyvals]{note text%text}
\note[options%keyvals]<overlay specification>{note text%text}

#keyvals:\note
item
itemize
enumerate
#endkeyvals

\insertnote#*
\AtBeginNote{text}
\AtEndNote{text}
\insertslideintonotes{magnification}#*
