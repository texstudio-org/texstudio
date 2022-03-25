# tocbibind.sty
# J. Sundermeyer
# modified Edson 30-12-2010

#keyvals:\usepackage/tocbibind#c
notbib
notindex
nottoc
notlot
notlof
chapter
section
numbib
numindex
other
none
#endkeyvals

\tocotherhead{headingname}#n
\tocbibname#n

\setindexname{name}#n
\settocname{name}#n
\setlotname{name}#n
\setlofname{name}#n
\settocbibname{name}#n

\simplechapter#n
\simplechapter[name]#n
\restorechapter#n
\simplechapterdelim#n

\tocchapter#n
\tocsection#n
\tocfile{text}{file-extension}#n

\tocetcmark{head}#*
\PRWPackageNote{package}{note text}#*
\PRWPackageNoteNoLine{package}{note text}#*
\bibsection#*
\begin{thebibitemlist}#*
\end{thebibitemlist}#*
