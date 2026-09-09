# pas-tableur package
# Matthew Bertucci 2026/09/08 for v3.01

#include:tikz
#include:tikzlibrarycalc
#include:xstring
#include:xkeyval
#include:customenvs-macros

grayTopCell#B
grayBottomCell#B
graySepCell#B
blueSelecCellTop#B
blueSelecCellBottom#B
blueSelec#B

\tableur{colonnes}
\tableur[nombre de lignes]{colonnes}
\tableur*{col1/dim1,col2/dim2,...}
\tableur*[nombre de lignes]{col1/dim1,col2/dim2,...}

\tabcolwidth{width}
\tabnumlinewidth{width}
\tablineheight{height}

\helvbx

\celtxt{colonne}{ligne}{texte}
\celtxt[options%keyvals]{colonne}{ligne}{texte}
\celtxt*{colonne}{ligne}{texte}
\celtxt*[options%keyvals]{colonne}{ligne}{texte}

#keyvals:\celtxt,\celtxt*
align=#center,left,right
c
l
r
ajust#true,false
width=##L
color=#%color
font=%<font commands%>
#endkeyvals

\renumLine{numéro}{text}
\renumLineSelect{numéro}{text}

\selecCell{colonne}{ligne}
\multiSelec{colonnes}{lignes}
\multimultiSelec{ligne1}{ligne2}{ligne3}

\gentableur{colonnes}
\gentableur{colonnes}[hauteurs]
\gentableur[nombre de lignes]{colonnes}
\gentableur[nombre de lignes]{colonnes}[hauteurs]
\plagecouleur{colonne de depart-ligne de depart}{colonne finale-ligne finale}
\plagecouleur[color]{colonne de depart-ligne de depart}{colonne finale-ligne finale}
\plagebordures{colonne de depart-ligne de depart}{colonne finale-ligne finale}
\plagebordures[color]{colonne de depart-ligne de depart}{colonne finale-ligne finale}

\celbordures#S
\celcouleur[opt]{arg}#S
\celcouleur{arg}#S
\colonnetxt#S
\filedate#S
\fileversion#S
\GtblrFetchHeight{arg}#S
\lignetxt#S
\remplircases#S