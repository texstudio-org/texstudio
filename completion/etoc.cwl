# etoc package
# Matthew Bertucci 11/8/2021 for v1.09e

#include:multicol

## I. Overview ##
\etocstandardlines
\etocstandarddisplaystyle
\etoctoclines
 
\invisibletableofcontents
\invisiblelocaltableofcontents

## II. Arbitrarily many TOCs, and local ones too ##
\tableofcontents
\tableofcontents*
\localtableofcontents
\localtableofcontents*
\localtableofcontentswithrelativedepth{number}

\etocsetlevel{level name}{number}

\etocsettocdepth{level}
\etocsetnexttocdepth{level}

\etocsettocdepth.toc{level}

\etocobeytoctocdepth
\etocignoretoctocdepth

\etocdepthtag.toc{level name}
\etocsettagdepth{tag name}{level}

\etocobeydepthtags
\etocignoredepthtags

\etocglobaldefs
\etoclocaldefs

\etocchecksemptiness
\etocnotocifnotoc
\etocifwasempty{yes}{no}

\etoclocaltop

\etoctoccontentsline{levle name}{name}

## V. Commands for the toc line styles ##
\etocsetstyle{level name}{start}{prefix}{contents}{finish}
\etocname
\etocpage

\etocskipfirstprefix
\etociffirst{yes}{no}

\etocnumber
\etocifnumbered{yes}{no}

\etocthename
\etocthenumber
\etocthepage

\etoclink{link name}

\etocthelinkedname
\etocthelinkednumber
\etocthelinkedpage
\etocthelink

\etocsavedsectiontocline
\etocsavedparttocline
\etocsavedchaptertocline

## VI.Commands for the toc display style ##
\etocsettocstyle{before code}{after code}

\etocmulticolstyle{heading}
\etocmulticolstyle[num of cols]{heading}
\etocmulticol{heading}
\etocmulticol[num of cols]{heading}
\etocmulticol*{heading}
\etocmulticol*[num of cols]{heading}
\etoclocalmulticol{heading}
\etoclocalmulticol[num of cols]{heading}

\etoctocstyle{num of cols}{title%plain}
\etoctocstyle[kind]{num of cols}{title%plain}
\etoctocstylewithmarks{num of cols}{title%plain}{mark}
\etoctocstylewithmarks[kind]{num of cols}{title%plain}{mark}
\etoctocstylewithmarksnouc{num of cols}{title%plain}{mark}
\etoctocstylewithmarksnouc[kind]{num of cols}{title%plain}{mark}

\etocruledstyle{title%plain}
\etocruledstyle[num of cols]{title%plain}
\etocruled{title%plain}
\etocruled[num of cols]{title%plain}
\etoclocalruled{title%plain}
\etoclocalruled[num of cols]{title%plain}

\etocframedstyle{title%plain}
\etocframedstyle[num of cols]{title%plain}
\etocframed{title%plain}
\etocframed[num of cols]{title%plain}
\etoclocalframed{title%plain}
\etoclocalframed[num of cols]{title%plain}

\etocoldpar#*
\etocinnertopsep#*

\etocarticlestyle#*
\etocarticlestylenomarks#*
\etocbookstyle#*
\etocbookstylenomarks#*

\etocinline
\etocnopar#*
\etocdisplay

\etocaftertitlehook
\etocaftercontentshook
\etocbeforetitlehook
\etocaftertochook

## VII. Using and customizing the etoc own styles ##
\etocdefaultlines

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

## VIII. Tips ##
\etocsetlocaltop.toc{level name}

## XI. etoc and the outside world ##
\etocmemoirstyle#*
\etocmemoirtoctotocfmt{kind}{name}#*
\etocreportstyle#*
\etocreportstylenomarks#*
\etocscrartclstyle#*
\etocscrbookstyle#*
\etocscrreprtstyle#*
\etoctocloftstyle#*

## Not in main documentation ##
\etocmarkbothnouc{text}#*
\etocmarkboth{text}#*
\etoctableofcontents#*