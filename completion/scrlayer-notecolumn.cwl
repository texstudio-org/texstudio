# scrlayer-notecolumn package
# Matthew Bertucci 11/19/2021 for v0.3.3694

#include:scrlayer
#include:scrlogo

#keyvals:\KOMAoptions#c
autoclearnotecolumns=#true,on,yes,false,off,no
#endkeyvals

\DeclareNoteColumn{note-column name}
\DeclareNoteColumn[options%keyvals]{note-column name}
\DeclareNewNoteColumn{note-column name}
\DeclareNewNoteColumn[options%keyvals]{note-column name}
\ProvideNoteColumn{note-column name}
\ProvideNoteColumn[options%keyvals]{note-column name}
\RedeclareNoteColumn{note-column name}
\RedeclareNoteColumn[options%keyvals]{note-column name}

#keyvals:\DeclareNoteColumn#c,\DeclareNewNoteColumn#c,\ProvideNoteColumn#c,\RedeclareNoteColumn#c
font=%<font attribute%>
marginpar
normalmarginpar
position=##L
reversemarginpar
width=##L
#endkeyvals

\makenote{note%text}
\makenote[note-column name]{note%text}
\makenote*{note%text}
\makenote*[note-column name]{note%text}
\restoreinnote#*
\clearnotecolumn
\clearnotecolumn[note-column name]
\clearnotecolumns
\clearnotecolumns[note-column name list]
\syncwithnotecolumn
\syncwithnotecolumn[note-column name]
\syncwithnotecolumns
\syncwithnotecolumns[note-column name list]
