# pas-tableur package
# Matthew Bertucci 12/28/2021 for v2.1

#include:tikz
#include:tikzlibrarycalc
#include:xstring
#include:xkeyval

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
c
l
r
width=##L
color=#%color
#endkeyvals

\selecCell{colonne}{ligne}
\multiSelec{colonnes}{lignes}

\fileversion#S
\filedate#S
