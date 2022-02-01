# beamerbasemisc package
# Matthew Bertucci 1/30/2022 for v3.65

\headcommand{code}#*
\dohead#*
\inserttotalframenumber#*
\insertmainframenumber#*
\partentry{arg1}{arg2}#*
\slideentry{arg1}{arg2}{arg3}{arg4}{arg5}{arg6}#*
\sectionentry{arg1}{arg2}{arg3}{arg4}{arg5}#*
\bibname#*
\algorithmname#*
\chaptername#*

#keyvals:\insertshortauthor,\insertshortdate,\insertshortinstitute,\insertshortpart,\insertshorttitle,\insertshortsubtitle,\insertshortframetitle
respectlinebreaks#true,false
width=##L
center#true,false
spill#true,false
#endkeyvals

\includegraphics<overlay specification>{imagefile}#g
\includegraphics<overlay specification>[options%keyvals]{imagefile}#g
\pgfuseimage<overlay specification>{image name}#*
\pgfimage<overlay specification>[options%keyvals]{imagefile}#*g
\pgfimage<overlay specification>{imagefile}#*g