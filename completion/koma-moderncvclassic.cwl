# koma-moderncvclassic package
# Matthew Bertucci 2022/07/21 for v0.5

#include:ifthen
#include:ifpdf
#include:xcolor
#include:lmodern
#include:marvosym
#include:url
#include:graphicx
#include:hyperref

#keyvals:\usepackage/koma-moderncvclassic#c
myblue
blue
red
green
cyan
magenta
yellow
black
white
gray
darkgray
lightgray
#endkeyvals

\cvline{margintext%text}{linetext%text}
\cvline[spacing%l]{margintext%text}{linetext%text}
\cventry{years%text}{degree or job title%text}{institution or employer%text}{city%text}{grade%text}{description%text}
\cvlanguage{language}{level}{comment%text}
\cvcomputer{category}{programs}{category}{programs}
\photo{width}{imagefile}#g
\photo[noframe]{width}{imagefile}#g
\cvdoubleitem{heading1%text}{text1%text}{heading2%text}{text2%text}#n
\cvdoubleitem[spacing%l]{heading1%text}{text1%text}{heading2%text}{text2%text}#n
\link{URL}#U
\link[text]{URL}#U
\httplink{URL}#U
\httplink[text]{URL}#U
\emaillink{address%URL}#U
\emaillink[text]{address%URL}#U

# not documented
\acadtitlefont#*
\acadtitlestyle{text}#*
\addressfont#*
\addresssymbol#*
\addresstyle{text}#*
\cvcompcolumnwidth#*
\doubleitemmaincolumnwidth#*
\emailsymbol#*
\familynamefont#*
\familynamestyle{text}#*
\faxsymbol#*
\firstnamefont#*
\firstnamestyle{text}#*
\hintfont#*
\hintscolumnwidth#*
\hintstyle{text}#*
\listdoubleitemmaincolumnwidth#*
\listitemmaincolumnwidth#*
\listitemsymbol#*
\listitemsymbolwidth#*
\maincolumnwidth#*
\maketitledetailsnewline#*
\maketitledetailswidth#*
\maketitlenamefullwidth#*
\maketitlenamemaxwidth#*
\maketitlenamewidth#*
\mobilesymbol#*
\mycolor#*
\myhintscolumnwidth#*
\phonesymbol#*
\photoname#*
\photowidth#*
\pictureframe#*
\providelength{cmd}#*d
\quotefont#*
\quotestyle{text}#*
\quotewidth#*
\sectionstyle{text}#*
\separatorcolumnwidth#*
\subsectionstyle{text}#*

myblue#B
colortheme#B
firstnamecolor#B
familynamecolor#B
acadtitlecolor#B
addresscolor#B
quotecolor#B
sectionrectanglecolor#B
sectiontitlecolor#B
subsectiontitlecolor#B
hintcolor#B