# bibpes package
# Matthew Bertucci 2022/05/13 for v1.3

#include:xkeyval

#keyvals:\usepackage/bibpes#c
infolder=%<file path%>
outfolder=%<file path%>
txtfilein=%<base name%>
deffileout=%<base name%>
build
!build
#endkeyvals

\reportOnBibPes
\readbackDefFile
\bibpesBody

\ifreadOK#*
\readOKtrue#*
\readOKfalse#*
\inbiblepassage#*
\outbiblepassage#*
\iwo#S
\FN#S
\CO#S
\CF#S