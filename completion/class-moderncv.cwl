# denisbitouze, 02.03.2013
# Matthew Bertucci updated 11/22/2021 for v2.2.0

#include:etoolbox
#include:ifthen
#include:xcolor
#include:colortbl
#include:ifxetex
#include:ifluatex
#include:inputenc
#include:fontenc
#include:lmodern
#include:url
#include:hyperref
#include:graphicx
#include:fancyhdr
#include:tweaklist
#include:calc
#include:xparse
#include:microtype
#include:moderncvcollection
#include:moderncvcompatibility
#include:expl3

\ifxetexorluatex#*
\xetexorluatextrue#*
\xetexorluatexfalse#*

\nopagenumbers#n
\pagenumberwidth#*
\name{first name}{last name}#n
\title{title%text}
\address{street}{city}{country}#n
\born{date}
\email{address%URL}#U
\homepage{URL}#U
\phone{number}
\phone[type%keyvals]{number}
#keyvals:\phone
fixed
mobile
fax
#endkeyvals
\SplitMyMacro#S
\social{user name}
\social[type%keyvals]{user name}
\social[type%keyvals][URL]{user name}#U
#keyvals:\social
linkedin
xing
twitter
github
gitlab
stackoverflow
bitbucket
skype
orcid
researchgate
researcherid
telegram
whatsapp
signal
matrix
googlescholar
#endkeyvals
\extrainfo{extra info%text}
\listitemsymbol#*
\addresssymbol#*
\bornsymbol#*
\mobilephonesymbol#*
\fixedphonesymbol#*
\faxphonesymbol#*
\emailsymbol#*
\homepagesymbol#*
\linkedinsocialsymbol#*
\xingsocialsymbol#*
\twittersocialsymbol#*
\githubsocialsymbol#*
\gitlabsocialsymbol#*
\stackoverflowsocialsymbol#*
\bitbucketsocialsymbol#*
\skypesocialsymbol#*
\orcidsocialsymbol#*
\researchgatesocialsymbol#*
\researcheridsocialsymbol#*
\googlescholarsocialsymbol#*
\telegramsocialsymbol#*
\whatsappsocialsymbol#*
\matrixsocialsymbol#*
\signalsocialsymbol#*
\enclname#*
\makefooter
\moderncvstyle{style%keyvals}#n
\moderncvstyle[options]{style%keyvals}#n
#keyvals:\moderncvstyle#c
banking
casual
classic
empty
fancy
oldstyle
#endkeyvals
\moderncvhead{header variant number}
\moderncvhead[options]{header variant number}#*
\moderncvbody{body variant number}
\moderncvbody[options]{body variant number}#*
\moderncvfoot{foot variant number}
\moderncvfoot[options]{foot variant number}#*
\moderncvcolor{color-scheme%keyvals}
#keyvals:\moderncvcolor#c
black
blue
burgundy
green
grey
orange
purple
red
#endkeyvals
\moderncvicons{icon set%keyvals}
#keyvals:\moderncvicons
awesome
letters
marvosym
#endkeyvals
\recomputeheadlengths#*
\recomputebodylengths#*
\recomputefootlengths#*
\recomputelengths#*
\photo{imagefile}#g
\photo[width]{imagefile}#g
\photo[width][frame thickness%l]{imagefile}#g
\quote{text}#n
\namefont#*
\titlefont#*
\addressfont#*
\quotefont#*
\sectionfont#*
\subsectionfont#*
\hintfont#*
\pagenumberfont#*
\namestyle{text}#*
\titlestyle{text}#*
\addressstyle{text}#*
\quotestyle{text}#*
\sectionstyle{text}#*
\subsectionstyle{text}#*
\hintstyle{text}#*
\pagenumberstyle{text}#*
\recomputecvheadlengths#*
\recomputecvbodylengths#*
\recomputecvfootlengths#*
\recomputecvlengths#*
\makenewline#*
\makecvtitle#n
\makecvhead#*
\makecvfoot#*
\cvitem{heading%text}{text}
\cvitem[spacing%l]{heading%text}{text}
\cvdoubleitem{heading1%text}{text1%text}{heading2%text}{text2%text}#n
\cvdoubleitem[spacing%l]{heading1%text}{text1%text}{heading2%text}{text2%text}#n
\cvlistitem{item%text}#n
\cvlistitem[spacing%l]{item%text}#n
\cvlistdoubleitem{item1%text}{item2%text}#n
\cvlistdoubleitem[spacing%l]{item1%text}{item2%text}#n
\cventry{years%text}{degree or job title%text}{institution or employer%text}{city%text}{grade%text}{description%text}#n
\cventry[spacing%l]{years%text}{degree or job title%text}{institution or employer%text}{city%text}{grade%text}{description%text}#n
\cvitemwithcomment{item%text}{item description%text}{comment%text}#n
\link{URL}#U
\link[text]{URL}#U
\httplink{URL}#U
\httplink[text]{URL}#U
\httpslink{URL}#U
\httpslink[text]{URL}#U
\emaillink{address%URL}#U
\emaillink[text]{address%URL}#U
\tellink{phone number}
\tellink[text]{phone number}
\onlynumberslink{arg}#*
\thecvcolumnscounter#*
\thecvcolumnsautowidthcounter#*
\thetmpiteratorcounter#*
\cvcolumnsdummywidth#*
\cvcolumnswidth#*
\cvcolumnsautowidth#*
\cvcolumnautowidth#*
\begin{cvcolumns}#n
\end{cvcolumns}#n
\cvcolumn{head%text}{content%text}#/cvcolumns
\cvcolumn[width]{head%text}{content%text}#/cvcolumns
\cvcolumncell{arg}#*
\bibindent#*
\bibliographyhead{title}#L2
\newblock#*
\recipient{recipient}{recipient address}#n
\opening{opening%text}#n
\closing{closing%text}#n
\enclosure{enclosure%text}#n
\enclosure[alternative name%text]{enclosure%text}#n
\recomputeletterheadlengths#*
\recomputeletterbodylengths#*
\recomputeletterfootlengths#*
\recomputeletterlengths#*
\makelettertitle#n
\makeletterhead#*
\makeletterfoot#*
\makeletterclosing#n
\separatorcolumnwidth#*
\maincolumnwidth#*
\doubleitemcolumnwidth#*
\separatorrulewidth#*
\listitemsymbolwidth#*
\listitemcolumnwidth#*
\listdoubleitemcolumnwidth#*
\cventryyearbox#*
\cventrytitleboxwidth#*

# from moderncvskillmatrix.sty
\cvskill{integer}
\setcvskillcolumns[width]
\setcvskillcolumns[width][factor]
\setcvskillcolumns[width][factor][exp-width%l]
\setcvskilllegendcolumns[width]
\setcvskilllegendcolumns[width][factor]
\cvskilllegend{name}
\cvskilllegend[padding%l]{name}
\cvskilllegend[padding%l][1st][2nd][3rd][4th][5th]{name}#*
\cvskilllegend*{name}
\cvskilllegend*[padding%l]{name}
\cvskilllegend*[padding%l][1st][2nd][3rd][4th][5th]{name}#*
\cvskillplainlegend{name}
\cvskillplainlegend[padding%l]{name}
\cvskillplainlegend[padding%l][1st][2nd][3rd][4th][5th]{name}#*
\cvskillplainlegend*{name}
\cvskillplainlegend*[padding%l]{name}
\cvskillplainlegend*[padding%l][1st][2nd][3rd][4th][5th]{name}#*
\cvskillhead[padding%l]
\cvskillhead[padding%l][name1][name2][name3][name4]#*
\cvskillentry{category%text}{level}{name%text}{years}{comment%text}
\cvskillentry[padding%l]{category%text}{level}{name%text}{years}{comment%text}
\cvskillentry*{category%text}{level}{name%text}{years}{comment%text}
\cvskillentry*[padding%l]{category%text}{level}{name%text}{years}{comment%text}

# from moderncvfooti.sty
\footsymbol#*
\footbox#*
\foottempbox#*
\footboxwidth#*
\addtofoot{element}#*
\addtofoot[symbol]{element}#*
\flushfoot#*

# from moderncvhead<num>.sty
\quotewidth#*
\makecvheadnamewidth#*
\makecvheadpicturebox#*
\makecvheaddetailswidth#*
\makecvheadpicturewidth#*
\makecvheadnamebox#*
\makeheaddetailssymbol#*
\makeheaddetailsbox#*
\makeheaddetailstempbox#*
\makeheaddetailswidth#*
\makeheaddetailsboxwidth#*
\addtomakeheaddetails{element}#*
\addtomakeheaddetails[symbol]{element}#*
\flushmakeheaddetails#*
\makehead#*
\makecvheadinfo{arg}#*
\makecvheadinfobox#*
\makecvheadinfoheight#*

# from T1 option of fontenc
\DH#n
\NG#n
\dj#n
\ng#n
\k{arg}#n
\guillemotleft#*n
\guillemotright#*n
\guilsinglleft#n
\guilsinglright#n
\quotedblbase#n
\quotesinglbase#n
\textquotedbl#n
\DJ#n
\th#n
\TH#n
\dh#n
\Hwithstroke#*n
\hwithstroke#*n
\textogonekcentered{arg}#*n
\guillemetleft#n
\guillemetright#n