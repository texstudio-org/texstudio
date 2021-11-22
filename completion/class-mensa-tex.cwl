# mensa-tex class
# Matthew Bertucci 11/14/2021

#include:array
#include:colortbl
#include:datetime2
#include:datetime2-calc
#include:geometry
#include:graphicx
#include:lmodern
#include:textcomp
#include:xcolor

\mensaname{cafeteria name}
\institute{institute name}
\setimage{content}

\startdate{YYYY-MM-DD}
\monday{menu1}{menu2}{dessert}{dinner}
\tuesday{menu1}{menu2}{dessert}{dinner}
\wednesday{menu1}{menu2}{dessert}{dinner}
\thursday{menu1}{menu2}{dessert}{dinner}
\friday{menu1}{menu2}{dessert}{dinner}

\longremarks{text}
\shortremarks{text}
\sup{text}

\vgt
\vgn

\setbgcolor{color}
\setcolorfg{color}
\setctextcolor{color}
\bgcolor
\colorfg
\ctextcolor

\menuname#*
\dessertname#*
\dinnername#*
\dietname#*
\shortdate#*
\dowshortdate#*
\longdate#*
\daterange#*

\wdayname{day}#*
\swdayname{day}#*