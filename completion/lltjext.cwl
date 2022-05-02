# lltjext package
# Matthew Bertucci 4/9/2022 for v1.2k

#include:luatexja

\begin{tabular}<dir>{cols}
\begin{tabular}<dir>[pos]{cols}
\begin{tabular*}<dir>{width}[pos]{cols}#\tabular
\begin{tabular*}<dir>{width}{cols}#\tabular
\begin{array}<dir>{cols}#m
\begin{array}<dir>[pos]{cols}#m
\begin{minipage}<dir>{width}
\begin{minipage}<dir>[position]{width}
\begin{minipage}<dir>[position][height]{width}
\begin{minipage}<dir>[position][height][inner pos]{width}
\parbox<dir>{width}{text}
\parbox<dir>[position]{width}{text}
\parbox<dir>[position][height]{width}{text}
\parbox<dir>[position][height][inner-pos]{width}{text}
\pbox{contents%text}
\pbox[width]{contents%text}
\pbox[width][pos]{contents%text}
\pbox<dir>{contents%text}
\pbox<dir>[width]{contents%text}
\pbox<dir>[width][pos]{contents%text}
\begin{picture}<dir>(width,height)
\begin{picture}<dir>(width,height)(xoffset,yoffset)
\floatwidth#*
\floatheight#*
\floatruletick#*
\captionfloatsep#*
\captiondir#*
\captionwidth#*
\captionfontsetup#*
\layoutfloat{content%text}
\layoutfloat[pos]{content%text}
\layoutfloat(x,y){content%text}
\layoutfloat(x,y)[pos]{content%text}
\DeclareLayoutCaption{floatname}<dir>(width)[pos1pos2]#*
\layoutcaption#*
\pcaption{caption%text}
\rensujiskip
\rensuji{contents%text}
\rensuji[pos]{contents%text}
\Rensuji{contents%text}#S
\Rensuji[pos]{contents%text}#S
\prensuji{contents%text}#S
\prensuji[pos]{contents%text}#S
\Kanji{counter}
\kanji#*
\boutenchar
\bou{contents%text}
\kasen{contents%text}