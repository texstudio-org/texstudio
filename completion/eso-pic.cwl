# eso-pic package
# Matthew Bertucci 11/2/2021 for v3.0a

#include:keyval
#include:xcolor

#keyvals:\usepackage/eso-pic#c
pscoord#true,false
texcoord#true,false
grid#true,false
gridBG#true,false
gridunit=#mm,in,bp,pt
gridcolor=#%color
subgridcolor=#%color
subgridstyle=#solid,dotted
colorgrid#true,false
dvips#true,false
#endkeyvals

\AddToShipoutPictureBG{code}
\AddToShipoutPictureBG*{code}
\AddToShipoutPicture{code}#*
\AddToShipoutPicture*{code}#*
\AddToShipoutPictureFG{code}
\AddToShipoutPictureFG*{code}
\ClearShipoutPictureBG{code}
\ClearShipoutPicture{code}#*
\LenToUnit{arg}#*
\gridSetup{unit}{label factor}{delta}{Delta}{gap}
\gridSetup[unit name]{unit}{label factor}{delta}{Delta}{gap}
\AtPageUpperLeft{code}
\AtPageLowerLeft{code}
\AtPageCenter{code}
\AtTextUpperLeft{code}
\AtTextLowerLeft{code}
\AtTextCenter{code}
\AtStockUpperLeft{code}
\AtStockLowerLeft{code}
\AtStockCenter{code}
\ProcessOptionsWithKV{family}#S
