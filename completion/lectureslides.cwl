# lectureslides package
# Matthew Bertucci 3/8/2022 for v1.0

#include:pdfpages
#include:tocloft
#include:hyperref
#include:babel

#keyvals:\usepackage/lectureslides#c
portrait
landscape
#endkeyvals

\course{title}
\course[footnote%text]{title}

\lecture{title}{PDF file%file}#L2
\lecture{title}[start]{PDF file%file}#*L2
\lecture{title}[start][end]{PDF file%file}#L2

\lecturetitle{title}#*L2
\lectureslides{PDF file%file}#*
\lectureslides[start]{PDF file%file}#*
\lectureslides[start][end]{PDF file%file}#*
\tocline{arg}#*
\createdAt{text}#*
\orientation#*
\thispackage#S
\toclevel#S
