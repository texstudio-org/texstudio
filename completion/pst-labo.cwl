# pst-labo package
# Matthew Bertucci 2023/05/18 for v2.06

#include:pstricks
#include:pst-plot
#include:multido
#include:pst-grad
#include:pst-xkey

\pstBullesChampagne
\pstBullesChampagne[value]
\pstFilaments{color}
\pstFilaments[value]{color}
\pstBilles
\pstBilles[value]
\pstBULLES{color}
\pstBULLES[value]{color}

\pstTournureCuivre
\pstTournureCuivre[value]
\pstClouFer
\pstClouFer[value]
\pstGrenailleZinc
\pstGrenailleZinc[value]

\pstTubeEssais
\pstTubeEssais[options%keyvals]
\pstChauffageTube
\pstChauffageTube[options%keyvals]
\pstBallon
\pstBallon[options%keyvals]
\pstChauffageBallon
\pstChauffageBallon[options%keyvals]
\pstEntonnoir
\pstEntonnoir[options%keyvals]
\pstEprouvette
\pstEprouvette[options%keyvals]
\pstpipette
\pstpipette[options%keyvals]
\pstDosage
\pstDosage[options%keyvals]
\pstDistillation(x1,y1)(x2,y2)
\pstDistillation[options%keyvals](x1,y1)(x2,y2)
\pstSeparateFunnel
\pstSeparateFunnel[options%keyvals]
\pstSupport

\chauffe#*
\Cristallisoir#*
\InterieurCristallisoir#*

\BulleX#S
\BulleY#S
\GrenailleX#S
\GrenailleY#S
\TournureX#S
\TournureY#S
\RAYONBULLE#S
\ClouX#S
\ClouY#S

\randomi#S
\nextrandom#S
\setrannum{count register%cmd}{min}{max}#*d
\setrandim{dimen register%cmd}{min}{max}#*d
\pointless#*
\PoinTless#S
\ranval#S
\PSTLabofileversion#S
\PSTLaboLoaded#S
Beige#B
GrisClair#B
GrisTresClair#B
OrangeTresPale#B
OrangePale#B
BleuClair#B
LightBlue#B
Copper#B
Marron#B
