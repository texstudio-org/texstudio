# plext package
# Matthew Bertucci 2022/07/21 for v1.2m

#include:platex

\floatwidth#*
\floatheight#*
\floatruletick#*
\captionfloatsep#*
\captiondir#*
\captionwidth#*
\captionfontsetup#*
\layoutfloat{content}
\layoutfloat[pos]{content}
\layoutfloat(width,height){content}
\layoutfloat(width,height)[pos]{content}
\DeclareLayoutCaption{type}<dir>(width)[⟨pos1⟩⟨pos2⟩]
\layoutcaption<dir>(width)[pos]
\pcaption{text}
\pcaption[short text]{text}
\pbox{obj}
\pbox[width]{obj}
\pbox[width][pos]{obj}
\pbox<dir>{obj}
\pbox<dir>[width]{obj}
\pbox<dir>[width][pos]{obj}
\rensuji{text}
\rensuji[pos%keyvals]{text}
\rensuji*{text}
\rensuji*[pos%keyvals]{text}
#keyvals:\rensuji#c,\rensuji*#c
l
c
r
#endkeyvals
\rensujiskip#*
\Rensuji{text}#S
\Rensuji[pos]{text}#S
\Rensuji*{text}#S
\Rensuji*[pos]{text}#S
\prensuji{text}#S
\prensuji[pos]{text}#S
\prensuji*{text}#S
\prensuji*[pos]{text}#S
\Kanji{counter}
\kanji %<number%>
\boutenchar#*
\bou{text}
\kasen{text}