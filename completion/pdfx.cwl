# pdfx package
# Matthew Bertucci 11/30/2021 for v1.6.3

#include:iftex
#include:ifpdf
#include:ifxetex
#include:everyshi
#include:ifluatex
#include:pdftexcmds
#include:xcolor
#include:inputenc
#include:hyperref
#include:colorprofiles
#include:stringenc
#include:ifthen
#include:xmpincl

#keyvals:\usepackage/pdfx#c
a-1a
a-1b
a-2a
a-2b
a-2u
a-3a
a-3b
a-3u
e-1
e
ua-1
ua
vt-1
vt-2
vt-2s
x-1
x-1a
x-2
x-3
x-4
x-4p
x-5g
x-5n
x-5pg
useBOM
noBOM
noerr
pdf12
pdf13
pdf14
pdf15
pdf16
pdf17
nocharset
usecharset
latxmp
armxmp
cyrxmp
grkxmp
hebxmp
arbxmp
vnmxmp
ipaxmp
mathxmp
allxmp
LATxmp
KOIxmp
LGRxmp
AR8xmp
HEBxmp
#endkeyvals

# commands for use in xmp files, which may be included in a filecontents env
\sep#*
\Author{author}#*
\Title{title%text}#*
\Language{language}#*
\Keywords{keywords%text}#*
\Publisher{publisher}#*
\Subject{subject%text}#*
\Copyright{statement%text}#*
\CopyrightURL{URL}#*U
\Copyrighted{True or False}#*
\Owner{owner}#*
\CertificateURL{URL}#*U
\Contributor{contributor}#*
\Coverage{statement%text}#*
\Date{YYYY-MM-DD}#*
\PublicationType{type%keyvals}#*
#keyvals:\PublicationType#c
book
catalog
feed
journal
magazine
manual
newsletter
pamphlet
#endkeyvals
\Relation{relation%text}#*
\Source{document}#*
\Doi{DOI}#*
\ISBN{ISBN}#*
\URLlink{URL}#*U
\Journaltitle{title%text}#*
\Journalnumber{number}#*
\Volume{volume}#*
\Issue{issue}#*
\Firstpage{number}#*
\Lastpage{number}#*
\CoverDisplayDate{YYYY-MM-DD}#*
\CoverDate{YYYY-MM-DD}#*
\AuthoritativeDomain{extra names}#*
\Creator{tool%text}#*
\CreatorTool{tool%text}#*
\Org{organization}#*
\WebStatement{URL}#*U
\Advisory{statement%text}#*
\BaseURL{URL}#*U
\Identifier{identifier}#*
\Nickname{nickname}#*
\Thumbnails{thumbnails}#*
\MMversionID{id}#*
\Producer{producer}#*
\textLAT{text}#*
\textLII{text}#*
\textLIII{text}#*
\textLIV{text}#*
\textLTV{text}#*
\textLVI{text}#*
\textLVII{text}#*
\textLIIX{text}#*
\textLIX{text}#*
\textKOI{text}#*
\textLGR{text}#*
\textARM{text}#*
\textHEB{text}#*
\textHEBO{text}#*
\textLF#*

# document commands
\pdfxEnableCommands{commands}
\pdfxDisableCommands{commands}#*
\setRGBcolorprofile{file}{identifier}{info string}{registry URL%URL}
\setCMYKcolorprofile{file}{output intent}{identifier}{registry URL%URL}
\setEXTERNALprofile{profile}{output intent}{id}{regURL%URL}{colorspace}{ICCver}{providerURL%URL}{info}{checksum}#*
\pdfxSetRGBcolorProfileDir{path}
\pdfxSetCMYKcolorProfileDir{path}
\MacOSColordir#*
\MacOSLibraryColordir#*
\AdobeMacOSdir#*
\WindowsColordir#*
\showLICRs{arg}
\pdfxBookmark{section cmd}{title}{text}
\pdfxBookmark[short title]{section cmd}{title}{text}
\pdfxBookmarkString{cmd}{string}#*d
\LIIXUmapTeXnames
\LIIXUscriptcommands
\LIIXUtipacommands
\LIIXUmapmathletterlikes
\LIIXUmapmathspaces

\ifcyrxmp#*
\ifcyrKOIxmp#*
\ifgrkxmp#*
\ifgrkLGRxmp#*
\ifhebxmp#*
\ifhebHEBxmp#*
\ifarbxmp#*
\ifarmxmp#*
\ifarmSCIxmp#*
\ifdevxmp#*
\ifvnmxmp#*
\iflatEXTxmp#*
\iflatLATxmp#*
\ifipaxmp#*
\ifmathxmp#*
\ifexternalICCprofiles#*
\cyrxmptrue#*
\cyrKOIxmptrue#*
\grkxmptrue#*
\grkLGRxmptrue#*
\hebxmptrue#*
\hebHEBxmptrue#*
\arbxmptrue#*
\armxmptrue#*
\armSCIxmptrue#*
\devxmptrue#*
\vnmxmptrue#*
\latEXTxmptrue#*
\latLATxmptrue#*
\ipaxmptrue#*
\mathxmptrue#*
\externalICCprofilestrue#*
\cyrxmpfalse#*
\cyrKOIxmpfalse#*
\grkxmpfalse#*
\grkLGRxmpfalse#*
\hebxmpfalse#*
\hebHEBxmpfalse#*
\arbxmpfalse#*
\armxmpfalse#*
\armSCIxmpfalse#*
\devxmpfalse#*
\vnmxmpfalse#*
\latEXTxmpfalse#*
\latLATxmpfalse#*
\ipaxmpfalse#*
\mathxmpfalse#*
\externalICCprofilesfalse#*


# option specific commands
#ifOption:arbxmp
\LIIXUmaparabicletters
#endif

#ifOption:armxmp
\LIIXUmaparmenianletters
#endif

#ifOption:AR8xmp
\LIIXUmaparmenianletters
#endif

#ifOption:devxmp
\LIIXUmapdevaccents
#endif

#ifOption:grkxmp
\LIIXUmapgreekletters
#endif

#ifOption:hebxmp
\LIIXUmaphebrewletters
#endif

#ifOption:HEBxmp
\LIIXUmaphebrewletters
#endif

#ifOption:LGRxmp
\LIIXUmapgreekletters
#endif

#ifOption:LATxmp
\LIIXUmaplatinchars
\LIIXUcancelfontswitches
#endif

#ifOption:mathxmp
\LIIXUmapmathaccents
\LIIXUmapisomathgreek
\LIIXUmapmatharrowsA
\LIIXUmapmathoperatorsA
\LIIXUmapmathoperatorsB
\LIIXUmapmiscmathsymbolsA
\LIIXUmapsupparrowsA
\LIIXUmapsupparrowsB
\LIIXUmapmiscmathsymbolsB
\LIIXUmapsuppmathoperators
\LIIXUmapunimathgreek
\LIIXUmapmathalphabets
#endif

#ifOption:allxmp
\LIIXUmaparabicletters
\LIIXUmaparmenianletters
\LIIXUmaparmenianletters
\LIIXUmapdevaccents
\LIIXUmapgreekletters
\LIIXUmaphebrewletters
\LIIXUmaphebrewletters
\LIIXUmapgreekletters
\LIIXUmaplatinchars
\LIIXUcancelfontswitches
\LIIXUmapmathaccents
\LIIXUmapisomathgreek
\LIIXUmapmatharrowsA
\LIIXUmapmathoperatorsA
\LIIXUmapmathoperatorsB
\LIIXUmapmiscmathsymbolsA
\LIIXUmapsupparrowsA
\LIIXUmapsupparrowsB
\LIIXUmapmiscmathsymbolsB
\LIIXUmapsuppmathoperators
\LIIXUmapunimathgreek
\LIIXUmapmathalphabets
#endif

\AcrobatMenu#S
\TextCopyright#S
\insertbackfindforwardnavigationsymbol#S
\insertslidenavigationsymbol#S
\mathaccentV#S
\paddingline#S
\pdfinterwordspace#S
\pdfstringdefPreHook#S
\pdfxProducer#S
\pdfxSetColorProfileDir#S
\setCUSTOMcolorprofile#S
\setGRAYcolorprofile#S
\thepdfminorversion#S
\Type#S