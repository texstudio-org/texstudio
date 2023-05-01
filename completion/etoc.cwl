# etoc package
# Matthew Bertucci 2023/05/01 for v1.2a

#include:kvoptions
#include:multicol

#keyvals:\usepackage/etoc#c
lof
lot
deeplevels#true,false
#endkeyvals

#ifOption:lof
\locallistoffigures
\etoclocallistoffigureshook#*
#endif

#ifOption:lot
\locallistoftables
\etoclocallistoftableshook#*
#endif

\etocsetup{keyvals}

#keyvals:\etocsetup,\usepackage/etoc#c
maintoctotoc#true,false
localtoctotoc#true,false
localloftotoc#true,false
locallottotoc#true,false
ouroboros#true,false
#endkeyvals

### Overview ###
\tableofcontents
\tableofcontents*
\localtableofcontents
\localtableofcontents*
\etocclasstocstyle
\etocetoclocaltocstyle
\etocusertocstyle
\etocstandardlines
\etoctoclines
\etocdefaultlines
\etocstoretocstyleinto{cmd}#d
\etocstorelinestylesinto{cmd}#d
\etocstorethislinestyleinto{name or number}{cmd}#d
\etocifislocal{true}{false}
\etocifislocaltoc{true}{false}
\etocifislocallof{true}{false}
\etocifislocallot{true}{false}
\etocifmaintoctotoc{true}{false}
\etociflocaltoctotoc{true}{false}
\etociflocalloftotoc{true}{false}
\etociflocallottotoc{true}{false}
\etocifisstarred{true}{false}
\etoclocalheadtotoc{level name}{text}
\etocglobalheadtotoc{level name}{text}
\etoclevel{level name}
\etocthelevel{level name}
\etocthemaxlevel
\etocifunknownlevelTF{level name}{true}{false}
\etocdivisionnameatlevel{number}
\etocetoclocaltocmaketitle#*
\etocetoclistoffiguresmaketitle#*
\etocetoclistoftablesmaketitle#*
\localcontentsname#*
\locallistfigurename#*
\locallisttablename#*
\etocclasslocaltocmaketitle#*
\etocclasslocallofmaketitle#*
\etocclasslocallotmaketitle#*
\etocclassmaintocaddtotoc#*
\etocclasslocaltocaddtotoc#*
\etocclasslocallofaddtotoc#*
\etocclasslocallotaddtotoc#*

### The etoc styling commands ###
\etocsettocstyle{before toc}{after toc}
\etocarticlestyle#*
\etocarticlestylenomarks#*
\etocreportstyle#*
\etocreportstylenomarks#*
\etocbookstyle#*
\etocbookstylenomarks#*
\etocmemoirstyle#*
\etocscrartclstyle#*
\etocscrreprtstyle#*
\etocscrbookstyle#*
\etoctocloftstyle#*
\etocinline
\etocnopar#*
\etocdisplay
\etocmulticolstyle{heading%text}
\etocmulticolstyle[num of cols]{heading%text}
\etocmulticol{heading%text}
\etocmulticol[num of cols]{heading%text}
\etocmulticol*{heading%text}
\etocmulticol*[num of cols]{heading%text}
\etoclocalmulticol{heading%text}
\etoclocalmulticol[num of cols]{heading%text}
\etoctocstyle{num of cols}{title%text}
\etoctocstyle[kind]{num of cols}{title%text}
\etoctocstylewithmarks{num of cols}{title%plain}{mark}
\etoctocstylewithmarks[kind]{num of cols}{title%text}{mark}
\etoctocstylewithmarksnouc{num of cols}{title%text}{mark}
\etoctocstylewithmarksnouc[kind]{num of cols}{title%text}{mark}
\etocruledstyle{title%text}
\etocruledstyle[num of cols]{title%text}
\etocruled{title%text}
\etocruled[num of cols]{title%text}
\etoclocalruled{title%text}
\etoclocalruled[num of cols]{title%text}
\etocframedstyle{title%text}
\etocframedstyle[num of cols]{title%text}
\etocframed{title%text}
\etocframed[num of cols]{title%text}
\etoclocalframed{title%text}
\etoclocalframed[num of cols]{title%text}
\etocabovetocskip#*
\etocbelowtocskip#*
\etoccolumnsep#*
\etocmulticolsep#*
\etocmulticolpretolerance#*
\etocmulticoltolerance#*
\etocdefaultnbcol#*
\etocinnertopsep#*
\etoctoprule#*
\etoctoprulecolorcmd#*
\etocinnerleftsep#*
\etocinnerrightsep#*
\etocinnerbottomsep#*
\etocleftrule#*
\etocrightrule#*
\etocbottomrule#*
\etocleftrulecolorcmd#*
\etocrightrulecolorcmd#*
\etocbottomrulecolorcmd#*
\etocbkgcolorcmd#*
\etocframedmphook#*
\etocoldpar#*
\etocinnertopsep#*
\etocaftertitlehook#*
\etocaftercontentshook#*
\etocbeforetitlehook#*
\etocaftertochook#*
\etocsetstyle{level name}{start}{prefix}{contents}{finish}
\etocname
\etocnumber
\etocpage
\etocskipfirstprefix
\etociffirst{true}{false}
\etocxiffirst{true}{false}
\etocifnumbered{true}{false}
\etocxifnumbered{true}{false}
\etocthename
\etocthenumber
\etocthepage
\etoclink{text}
\etocthelinkedname
\etocthelinkednumber
\etocthelinkedpage
\etocthelink
\etocsetlevel{level name}{number}
\etocglobaldefs
\etoclocaldefs
\etocfontminustwo#*
\etocfontminusone#*
\etocfontzero#*
\etocfontone#*
\etocfonttwo#*
\etocfontthree#*
\etocsepminustwo#*
\etocsepminusone#*
\etocsepzero#*
\etocsepone#*
\etocseptwo#*
\etocsepthree#*
\etocminustwoleftmargin#*
\etocminustworightmargin#*
\etocminusoneleftmargin#*
\etocminusonerightmargin#*
\etocbaselinespreadminustwo#*
\etocbaselinespreadminusone#*
\etocbaselinespreadzero#*
\etocbaselinespreadone#*
\etocbaselinespreadtwo#*
\etocbaselinespreadthree#*
\etoctoclineleaders#*
\etocabbrevpagename#*
\etocpartname#*
\etocbookname#*

### Control of contents ###
\etoctableofcontents#*
\etockeeporiginaltableofcontents#*
\localtableofcontentswithrelativedepth{number}
\invisibletableofcontents
\invisiblelocaltableofcontents
\etocsettocdepth{level}
\etocsetnexttocdepth{level}
\etocsettocdepth.toc{level}
\etocimmediatesettocdepth.toc{level}
\etocobeytoctocdepth
\etocignoretoctocdepth
\etocdepthtag.toc{tag name}
\etocimmediatedepthtag.toc{tag name}
\etocsettagdepth{tag name}{level}
\etocobeydepthtags
\etocignoredepthtags
\etocsetlocaltop.toc{level name}
\etocimmediatesetlocaltop.toc{level name}
\etoclocaltop
\etocchecksemptiness
\etocdoesnotcheckemptiness
\etocnotocifnotoc
\etocifwasempty{true}{false}
\etocxifwasempty{true}{false}

### Advanced examples ###
\etoctoccontentsline{level name}{name}
\etoctoccontentsline*{level name}{name}{bookmark level}
\etocimmediatetoccontentsline{level name}{name}
\etocimmediatetoccontentsline*{level name}{name}{bookmark level}

### not documented
\etocclasslocalperhapsaddtotoc{arg}#S
\etoclocaltableofcontentshook#S
\etocmarkbothnouc{text}#S
\etocmarkboth{text}#S
\etocoriginaltableofcontents#S
\etocsettoclineforclasstoc{arg1}{arg2}#S
\etocsettoclineforclasslistof{arg1}{arg2}{arg3}#S
\etoctocloftlocalperhapsaddtotoc{arg}#S
\etoctocbibindstyle#S

# deprecated
\etocstandarddisplaystyle#S
\etocmemoirtoctotocfmt{kind}{name}#S
