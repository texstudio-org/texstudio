# LuaTeX primitives
# Matthew Bertucci updated 2023/03/31 for v1.16

### from LuaTeX Reference Manual ###
## 2 Basic TeX enhancements ##
# 2.1 Introduction #
\luatexbanner#*
\luatexversion#*
\luatexrevision#*
\formatname#*

# 2.2 UNICODE text support #
\Uchar%<<number>%>#*

# 2.3 Attributes #
\attribute%<<16-bit number>%>=%<32-bit number>%>#*
\attributedef%<\csname%>=%<<16-bit number>%>#*
\attributedef{cmd}#Sd

# 2.4 LUA related primitives #
\directlua{lua code%definition}
\latelua{lua code%definition}
\lateluafunction%<<number>%>#*
\luaescapestring{TeX code}#*
\luafunction%<<number>%>#*
\luafunctioncall%<<number>%>#*
\luadef%<\csname%>#*
\luadef{cmd}#Sd
\luabytecode%<<number>%>#*
\luabytecodecall%<<number>%>#*

# 2.5 Catcode tables #
\catcodetable%<<15-bit number>%>#*
\initcatcodetable%<<15-bit number>%>#*
\savecatcodetable%<<15-bit number>%>#*

# 2.6 Suppressing errors #
\suppressfontnotfounderror = %<<0 or 1>%>#*
\suppresslongerror = %<<0 or 1>%>#*
\suppressifcsnameerror = %<<0 or 1>%>#*
\suppressoutererror = %<<0 or 1>%>#*
\suppressmathparerror = %<<0 or 1>%>#*
\suppressprimitiveerror = %<<0 or 1>%>#*

# 2.7 Fonts #
\fontid#*
\setfontid#*
\noligs%<<integer>%>#*
\nokerns%<<integer>%>#*
\nospaces#*

# 2.8 Tokens, commands and strings #
\scantextokens#*
\toksapp#*
\tokspre#*
\etoksapp#*
\etokspre#*
\gtoksapp#*
\gtokspre#*
\xtoksapp#*
\xtokspre#*
\csstring#*
\begincsname#*
\lastnamedcs#*
\clearmarks%<<16-bit number>%>#*
\alignmark#*
\aligntab#*
\letcharcode%<<charcode>%>=%<\csname%>#*
\glet%<\csname1%>=%<\csname2%>#*
\glet{cmd}#Sd
\immediateassignment#*
\immediateassigned#*
\ifcondition#*

# 2.9 Boxes, rules and leaders #
\outputbox = %<<integer>%>#*
\vpack#*
\hpack#*
\tpack#*
\saveboxresource#*
\saveimageresource#*
\useboxresource#*
\useimageresource#*
\lastsavedboxresourceindex#*
\lastsavedimageresourceindex#*
\lastsavedimageresourcepages#*
\nohrule#*
\novrule#*
\gleaders#*

# 2.10 Languages #
\hyphenationmin = %<<integer>%>#*
\boundary#*
\noboundary#*
\protrusionboundary#*
\wordboundary#*
\glyphdimensionsmode = %<<0,1,2,or 3>%>#*

# 2.11 Control and debugging #
\outputmode = %<<0 or 1>%>#*
\draftmode = %<<0 or 1>%>#*

## 3 Modifications ##
# 3.1 The merged engines #
\pagebottomoffset#*
\pagetopoffset#*
\pagerightoffset#*
\pageleftoffset#*
\partokencontext#*
\partokenname#*
\showstream#*
\eTeXgluestretchorder#*
\eTeXglueshrinkorder#*

# 3.2 The backend primitives #
\pdfextension %<command%>#*
\pdfvariable %<name%>#*
\pdffeedback %<name%>#*
\deferred#*
\pagewidth#*
\pageheight#*
\adjustspacing#*
\protrudechars#*
\ignoreligaturesinfont#*
\expandglyphsinfont#*
\copyfont#*
\savepos#*
\lastxpos#*
\lastypos#*
\pxdimen#*
\insertht#*
\normaldeviate#*
\uniformdeviate#*
\setrandomseed#*
\randomseed#*
\primitive#*
\ifprimitive#*
\ifabsnum#*
\ifabsdim#*

# 3.3 Directions #
\textdir#*
\linedir#*
\breakafterdirmode = %<<0 or 1>%>#*
\shapemode = %<<0,1,2,or 3>%>#*
\pardir#*
\pagedir#*
\pardir#*
\bodydir#*
\mathdir#*
\boxdir#*
\textdirection = %<<0 or 1>%>#*
\pardirection = %<<0 or 1>%>#*
\pagedirection = %<<0 or 1>%>#*
\bodydirection = %<<0 or 1>%>#*
\mathdirection = %<<0 or 1>%>#*
\boxdirection = %<<0 or 1>%>#*
\linedirection = %<<0 or 1>%>#*

## 5 Languages, characters, fonts and glyphs ##
# 5.2 Characters, glyphs and discretionaries #
\firstvalidlanguage = %<<0 or 1>%>#*
\hjcode#*
\hyphenationbounds#*
\automatichyphenmode = %<<0,1,or 2>%>#*
\explicitdiscretionary#*
\automaticdiscretionary#*

# 5.3 The main control loop #
\leftghost#*
\rightghost#*
\exhyphenchar=%<<char>%>#*
\hyphenpenaltymode#*
\automatichyphenpenalty#*
\explicithyphenpenalty#*
\prehyphenchar=%<<char>%>#*
\posthyphenchar=%<<char>%>#*
\preexhyphenchar=%<<char>%>#*
\postexhyphenchar=%<<char>%>#*

# 5.4 Loading patterns and exceptions #
\exceptionpenalty#*

## 6 Font structure ##
# 6.5 The font library #
\discretionaryligaturemode = %<<0,1,or 2>%>#*

## 7 Math ##
# 7.2 Unicode math characters #
\Umathchardef#*
\Umathchardef{cmd}#Sd
\Umathcharnumdef#*
\Umathcharnumdef{cmd}#Sd
\Umathcode#*
\Udelcode#*
\Umathchar#*
\Umathaccent#*
\Udelimiter#*
\Uradical#*
\Umathcharnum#*
\Umathcodenum#*
\Udelcodenum#*
\Uroot#*
\Uoverdelimiter#*
\Uunderdelimiter#*
\Udelimiterover#*
\Udelimiterunder#*
\variablefam#*

# 7.3 Math styles #
\mathstyle#*
\Ustack#*
\crampeddisplaystyle#*
\crampedtextstyle#*
\crampedscriptstyle#*
\crampedscriptscriptstyle#*

# 7.4 Math parameter settings #
\Umathquad#*
\Umathaxis#*
\Umathoperatorsize#*
\Umathoverbarkern#*
\Umathoverbarrule#*
\Umathoverbarvgap#*
\Umathunderbarkern#*
\Umathunderbarrule#*
\Umathunderbarvgap#*
\Umathradicalkern#*
\Umathradicalrule#*
\Umathradicalvgap#*
\Umathradicaldegreebefore#*
\Umathradicaldegreeafter#*
\Umathradicaldegreeraise#*
\Umathstackvgap#*
\Umathstacknumup#*
\Umathstackdenomdown#*
\Umathfractionrule#*
\Umathfractionnumvgap#*
\Umathfractionnumup#*
\Umathfractiondenomvgap#*
\Umathfractiondenomdown#*
\Umathfractiondelsize#*
\Umathlimitabovevgap#*
\Umathlimitabovebgap#*
\Umathlimitabovekern#*
\Umathlimitbelowvgap#*
\Umathlimitbelowbgap#*
\Umathlimitbelowkern#*
\Umathoverdelimitervgap#*
\Umathoverdelimiterbgap#*
\Umathunderdelimitervgap#*
\Umathunderdelimiterbgap#*
\Umathsubshiftdrop#*
\Umathsubshiftdown#*
\Umathsupshiftdrop#*
\Umathsupshiftup#*
\Umathsubsupshiftdown#*
\Umathsubtopmax#*
\Umathsupbottommin#*
\Umathsupsubbottommax#*
\Umathsubsupvgap#*
\Umathspaceafterscript#*
\Umathconnectoroverlapmin#*
\Umathskewedfractionhgap#*
\Umathskewedfractionvgap#*

# 7.5 Math spacing #
\mathsurroundmode = %<<mode>%>#*
\mathsurroundskip%<<length>%>#*
\Umathordordspacing#*
\Umathordopspacing#*
\Umathordbinspacing#*
\Umathordrelspacing#*
\Umathordopenspacing#*
\Umathordclosespacing#*
\Umathordpunctspacing#*
\Umathordinnerspacing#*
\Umathopordspacing#*
\Umathopopspacing#*
\Umathopbinspacing#*
\Umathoprelspacing#*
\Umathopopenspacing#*
\Umathopclosespacing#*
\Umathoppunctspacing#*
\Umathopinnerspacing#*
\Umathbinordspacing#*
\Umathbinopspacing#*
\Umathbinbinspacing#*
\Umathbinrelspacing#*
\Umathbinopenspacing#*
\Umathbinclosespacing#*
\Umathbinpunctspacing#*
\Umathbininnerspacing#*
\Umathrelordspacing#*
\Umathrelopspacing#*
\Umathrelbinspacing#*
\Umathrelrelspacing#*
\Umathrelopenspacing#*
\Umathrelclosespacing#*
\Umathrelpunctspacing#*
\Umathrelinnerspacing#*
\Umathopenordspacing#*
\Umathopenopspacing#*
\Umathopenbinspacing#*
\Umathopenrelspacing#*
\Umathopenopenspacing#*
\Umathopenclosespacing#*
\Umathopenpunctspacing#*
\Umathopeninnerspacing#*
\Umathcloseordspacing#*
\Umathcloseopspacing#*
\Umathclosebinspacing#*
\Umathcloserelspacing#*
\Umathcloseopenspacing#*
\Umathcloseclosespacing#*
\Umathclosepunctspacing#*
\Umathcloseinnerspacing#*
\Umathpunctordspacing#*
\Umathpunctopspacing#*
\Umathpunctbinspacing#*
\Umathpunctrelspacing#*
\Umathpunctopenspacing#*
\Umathpunctclosespacing#*
\Umathpunctpunctspacing#*
\Umathpunctinnerspacing#*
\Umathinnerordspacing#*
\Umathinneropspacing#*
\Umathinnerbinspacing#*
\Umathinnerrelspacing#*
\Umathinneropenspacing#*
\Umathinnerclosespacing#*
\Umathinnerpunctspacing#*
\Umathinnerinnerspacing#*
\mathdisplayskipmode = %<<0,1,2,or 3>%>#*
\matheqdirmode = %<<integer>%>#*
\Umathnolimitsupfactor#*
\Umathnolimitsubfactor#*
\mathnolimitsmode = %<<mode>%>#*
\mathitalicsmode = %<<0 or 1>%>#*
\mathscriptboxmode = %<<0,1,2,or 3>%>#*
\mathscriptcharmode = %<<mode>%>#*
\mathscriptsmode = %<<mode>%>#*
\mathpenaltiesmode = %<<mode>%>#*
\prebinoppenalty = %<<penalty>%>#*
\prerelpenalty = %<<penalty>%>#*
\matheqnogapstep = %<<integer>%>#*

# 7.6 Math constructs #
\mathdelimitersmode = %<<mode>%>#*
\Uhextensible#*
\Uvextensible#*
\Uskewed#*
\Uskewedwithdelims#*
\Udelimiter#*
\Uleft#*
\Umiddle#*
\Uright#*

# 7.7 Extracting values #
\Umathcode %<<char> <class> <fam> <slot>%>#*
\Umathcharclass%<<char>%>#*
\Umathcharfam%<<char>%>#*
\Umathcharslot%<<char>%>#*
\predisplaygapfactor = %<<factor>%>#*

# 7.8 Math mode #
\Usuperscript#*
\Usubscript#*
\Ustartmath#*
\Ustopmath#*
\Ustartdisplaymath#*
\Ustopdisplaymath#*
\Unosuperscript{text%plain}#*
\Unosubscript{text%plain}#*

# 7.9 Goodies #
\mathflattenmode = %<<mode>%>#*
\mathdefaultsmode = %<<mode>%>#*
\mathoption#*

## 8 Nodes ##
\localinterlinepenalty#*
\localbrokenpenalty#*
\localleftbox#*
\localrightbox#*

## 10 The TeX related libraries ##
\compoundhyphenmode#*
\dviextension#*
\dvifeedback#*
\dvivariable#*
\endlocalcontrol#*
\eTeXminorversion#*
\eTeXVersion#*
\fixupboxesmode#*
\luacopyinputnodes#*
\mathrulesfam#*
\mathrulesmode#*
\mathrulethicknessmode#*

### from ltluatex.tex v1.1x ###
\newattribute{attribute%cmd}#*d
\newcatcodetable{catcodetable%cmd}#*d
\newluafunction{function}#*d
\newluacmd{cmd}#*d
\newprotectedluacmd{cmd}#*d
\newwhatsit{whatsit%cmd}#*d
\newluabytecode{bytecode%cmd}#*d
\newluachunkname{chunkname%cmd}#*d
\setattribute{attribute}{value}#*
\unsetattribute{attribute}#*
