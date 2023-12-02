# latex mode: LaTeX commands (package level)
# dani/2006-02-18
# muzimuzhi/8 Jul 2019
# Matthew Bertucci 2023/11/01 release

# commands with big Letters and others
\ActivateGenericHook{hook}#*
\AddToHook{hook}[label]{code}#*
\AddToHook{hook}{code}#*
\AddToHookNext{hook}{code}#*
\AddToHookNextWithArguments{hook}{code}#*
\AddToHookWithArguments{hook}[label]{code}#*
\AddToHookWithArguments{hook}{code}#*
\AddToNoCaseChangeList{command}#*
\AfterEndEnvironment[label]{environment}{code}#*
\AfterEndEnvironment{environment}{code}#*
\AssignSocketPlug{socket}{socket plug}#*
\AtBeginDocument[label]{code}#*
\AtBeginDocument{code}#*
\AtBeginDvi{code}#*
\AtBeginEnvironment[label]{environment}{code}#*
\AtBeginEnvironment{environment}{code}#*
\AtEndDocument[label]{code}#*
\AtEndDocument{code}#*
\AtEndDvi{code}#*
\AtEndEnvironment[label]{environment}{code}#*
\AtEndEnvironment{environment}{code}#*
\AtEndOfClass{code}#*
\AtEndOfPackage{code}#*
\BCPdata{keywords}#*
\BeforeBeginEnvironment[label]{environment}{code}#*
\BeforeBeginEnvironment{environment}{code}#*
\BooleanFalse
\BooleanTrue
\CaseSwitch{normal%text}{upper%text}{lower%text}{title%text}#*
\CheckCommand*{cmd}[args][default]{def}#*
\CheckCommand*{cmd}[args]{def}#*
\CheckCommand*{cmd}{def}#*
\CheckCommand{cmd}[args][default]{def}#*
\CheckCommand{cmd}[args]{def}#*
\CheckCommand{cmd}{def}#*
\CheckEncodingSubset{text cmd}{encoding}{error}{subset id}{symbol}#*
\ClassError{class name}{error text}{help text}#*
\ClassInfo{class name}{info text}#*
\ClassNote{class name}{note text%text}#*
\ClassNoteNoLine{class name}{note text%text}#*
\ClassWarning{class name}{warning text%text}#*
\ClassWarningNoLine{class name}{warning text%text}#*
\ClearHookNext{hook}#*
\ClearHookRule{hook}{label1}{label2}#*
\CurrentFile#*
\CurrentFilePath#*
\CurrentFilePathUsed#*
\CurrentFileUsed#*
\CurrentOption#*
\DebugHooksOff#*
\DebugHooksOn#*
\DebugMarksOff#*
\DebugMarksOn#*
\DebugShipoutsOff#*
\DebugShipoutsOn#*
\DebugSocketsOff#*
\DebugSocketsOn#*
\DeclareCaseChangeEquivalent{cmd}{replacement text}#*d
\DeclareCommandCopy{cmd}{copied cmd%definition}#d
\DeclareCurrentRelease{name}{date}#*
\DeclareDefaultHookRule{label1}{relation}{label2}#*
\DeclareDocumentCommand{cmd}{xargs}{def}#d
\DeclareDocumentEnvironment{envname}{xargs}{begdef}{enddef}#N
\DeclareEmphSequence{font cmd list}#*
\DeclareEncodingSubset{encoding}{family}{subset number}#*
\DeclareEnvironmentCopy{envname}{copied envname}#N
\DeclareErrorFont{encoding}{family}{series}{shape}{size}#*
\DeclareExpandableDocumentCommand{cmd}{xargs}{def}#*d
\DeclareFixedFont{cmd}{encoding}{family}{series}{shape}{size}#*d
\DeclareFontEncoding{encoding}{text-settings}{math-settings}#*
\DeclareFontEncodingDefaults{text-settings}{math-settings}#*
\DeclareFontFamily{encoding}{family}{loading-settings}#*
\DeclareFontFamilySubstitution{encoding}{family1}{family2}#*
\DeclareFontSeriesChangeRule{series1}{series2}{result1}{result2}#*
\DeclareFontSeriesDefault[family]{face}{series name}#*
\DeclareFontSeriesDefault{face}{series name}#*
\DeclareFontShape{encoding}{family}{series}{shape}{loading-info}{loading-settings}#*
\DeclareFontShapeChangeRule{shape1}{shape2}{result1}{result2}#*
\DeclareFontSubstitution{encoding}{family}{series}{shape}#*
\DeclareHookRule{hook}{label1}{relation}{label2}#*
\DeclareKeys[family]{declarations}#*
\DeclareKeys{declarations}#*
\DeclareLowercaseMapping[locale]{codepoint}{output}#*
\DeclareLowercaseMapping{codepoint}{output}#*
\DeclareMathAccent{cmd}{type}{sym-font}{slot}#*d
\DeclareMathAlphabet{math-alph%cmd}{encoding}{family}{series}{shape}#*d
\DeclareMathDelimiter{cmd}{type}{sym-font-1}{slot-1}{sym-font-2}{slot-2}#*d
\DeclareMathRadical{cmd}{sym-font-1}{slot-1}{sym-font-2}{slot-2}#*d
\DeclareMathSizes*{t-size}{mt-size}{s-size}{ss-size}#*
\DeclareMathSizes{t-size}{mt-size}{s-size}{ss-size}#*
\DeclareMathSymbol{cmd}{type}{sym-font}{slot}#*d
\DeclareMathVersion{version}#*
\DeclareOldFontCommand{cmd}{text-switch}{math-switch}#*d
\DeclareOption*{code}#*
\DeclareOption{option}{code}#*
\DeclarePreloadSizes{encoding}{family}{series}{shape}{sizes}#*
\DeclareRelease{name}{date}{file name}#*
\DeclareRobustCommand*{cmd}[args][default]{def}#*d
\DeclareRobustCommand*{cmd}[args]{def}#*d
\DeclareRobustCommand*{cmd}{def}#*d
\DeclareRobustCommand{cmd}[args][default]{def}#*d
\DeclareRobustCommand{cmd}[args]{def}#*d
\DeclareRobustCommand{cmd}{def}#*d
\DeclareSizeFunction{name}{code}#*
\DeclareSymbolFont{sym-font}{encoding}{family}{series}{shape}#*
\DeclareSymbolFontAlphabet{math-alph%cmd}{sym-font}#*d
\DeclareTextAccent{cmd}{encoding}{slot}#*d
\DeclareTextAccentDefault{cmd}{encoding}#*
\DeclareTextCommand{cmd}{encoding}[args][default]{definition}#*d
\DeclareTextCommand{cmd}{encoding}[args]{definition}#*d
\DeclareTextCommand{cmd}{encoding}{definition}#*d
\DeclareTextCommandDefault{cmd}{definition}#*d
\DeclareTextComposite{cmd}{encoding}{argument}{text}#*d
\DeclareTextCompositeCommand{cmd}{encoding%definition}{letter%definition}{definition}#*d
\DeclareTextFontCommand{cmd}{font-switches%definition}#*d
\DeclareTextSymbol{cmd}{encoding}{slot}#*d
\DeclareTextSymbolDefault{cmd}{encoding}#*
\DeclareTitlecaseMapping[locale]{codepoint}{output}#*
\DeclareTitlecaseMapping{codepoint}{output}#*
\DeclareUnicodeCharacter{hexadecimal}{definition}#*
\DeclareUnknownKeyHandler[family]{code}#*
\DeclareUnknownKeyHandler{code}#*
\DeclareUppercaseMapping[locale]{codepoint}{output}#*
\DeclareUppercaseMapping{codepoint}{output}#*
\DisableGenericHook{hook}#*
\DisableHook{hook}#*
\DiscardShipoutBox#*
\EndIncludeInRelease#*
\EndModuleRelease#*
\ExecuteOptions{optionlist}#*
\ExpandArgs{spec}#*
\ExplSyntaxOff#*
\ExplSyntaxOn#*
\FirstMark[region]{class%plain}#*
\FirstMark{class%plain}#*
\GenericError{continuation}{message%text}{help location%text}{help info%text}#*
\GenericInfo{continuation}{message%text}#*
\GenericWarning{continuation}{message%text}#*
\IfBlankF{arg}{false code}#*
\IfBlankT{arg}{true code}#*
\IfBlankTF{arg}{true code}{false code}#*
\IfBooleanF{arg}{false code}
\IfBooleanT{arg}{true code}
\IfBooleanTF{arg}{true code}{false code}
\IfClassAtLeastTF{class}{date}{true code}{false code}#*
\IfClassLoadedTF{class}{true code}{false code}#*
\IfClassLoadedWithOptionsTF{class}{options}{true code}{false code}#*
\IfExplAtLeastTF{date}{true code}{false code}#*
\IfFileAtLeastTF{file}{date}{true code}{false code}#*
\IfFileExists{file}{true code}{false code}#*
\IfFontSeriesContextTF{face}{true code}{false code}#*
\IfFormatAtLeastTF{date}{true code}{false code}#*
\IfHookEmptyTF{hook}{true code}{false code}#*
\IfLabelExistTF{label}{true code}{false code}#*
\IfMarksEqualTF[region]{class%plain}{pos1}{pos2}{true code}{false code}#*
\IfMarksEqualTF{class%plain}{pos1}{pos2}{true code}{false code}#*
\IfNoValueF{arg}{ValueCode}
\IfNoValueT{arg}{-NoValue-Code}
\IfNoValueTF{arg}{-NoValue-Code}{ValueCode}
\IfPackageAtLeastTF{package}{date}{true code}{false code}#*
\IfPackageLoadedTF{package}{true code}{false code}#*
\IfPackageLoadedWithOptionsTF{package}{options}{true code}{false code}#*
\IfPDFManagementActiveTF{true code}{false code}#*
\IfPropertyExistTF{property}{true code}{false code}#*
\IfPropertyRecordedTF{label}{property}{true code}{false code}#*
\IfTargetDateBefore{date}{before code}{after code}#*
\IfValueF{arg}{-NoValue-Code}#*
\IfValueT{arg}{ValueCode}#*
\IfValueTF{arg}{ValueCode}{-NoValue-Code}#*
\IncludeInRelease{date}{command}{description}#*
\IndentBox#*
\InputIfFileExists{file}{true code}{false code}#*i
\InsertMark{class%plain}{text}#*
\LastDeclaredEncoding#*
\LastMark[region]{class%plain}#*
\LastMark{class%plain}#*
\LaTeXReleaseInfo#*
\LinkTargetOff#*
\LinkTargetOn#*
\LoadClass[optionlist]{class}#*u
\LoadClass[optionlist]{class}[release]#*u
\LoadClass{class}#*u
\LoadClass{class}[release]#*u
\LoadClassWithOptions{class}#*u
\LoadClassWithOptions{class}[release]#*u
\LoadFontDefinitionFile{encoding}{family}#*
\LogHook{hook}#*
\LogSocket{socket}#*
\MakeLinkTarget*{target name}#*
\MakeLinkTarget[prefix]{counter}#*
\MakeLinkTarget{counter}#*
\MakeRobust{cmd}#*
\MessageBreak#*
\NeedsTeXFormat{format}#*
\NeedsTeXFormat{format}[release]#*
\NewCommandCopy{cmd}{copied cmd%definition}#d
\NewDocumentCommand{cmd}{xargs}{def}#d
\NewDocumentEnvironment{envname}{xargs}{begdef}{enddef}#N
\NewEnvironmentCopy{envname}{copied envname}#N
\NewExpandableDocumentCommand{cmd}{xargs}{def}#*d
\NewHook{hook}#*
\NewHookWithArguments{hook}{number}#*
\NewMarkClass{class%plain}#*
\NewMirroredHookPair{hook1}{hook2}#*
\NewMirroredHookPairWithArguments{hook1}{hook2}{number}#*
\NewModuleRelease{date}{name}#*
\NewProperty{property%specialDef}{setpoint}{default}{code}#*s#%latexproperties
\NewReversedHook{hook}#*
\NewReversedHookWithArguments{hook}{number}#*
\NewSocket{socket}{number of inputs}#*
\NewSocketPlug{socket}{socket plug}{code}#*
\NextLinkTarget{target name}#*
\OmitIndent#*
\OptionNotUsed#*
\PackageError{package name}{error text%text}{help text%text}#*
\PackageInfo{package name}{info text%text}#*
\PackageNote{package name}{note text%text}#*
\PackageNoteNoLine{package name}{note text%text}#*
\PackageWarning{package name}{warning text%text}#*
\PackageWarningNoLine{package name}{warning text%text}#*
\PassOptionsToClass{optionlist}{class}#*
\PassOptionsToPackage{optionlist}{package}#*
\PopDefaultHookLabel#*
\PreviousTotalPages#*
\ProcessedArgument#*
\ProcessKeyOptions#*
\ProcessKeyOptions[family]#*
\ProcessList{list}{cmd}#*
\ProcessOptions#*
\ProcessOptions*#*
\ProvideDocumentCommand{cmd}{xargs}{def}#d
\ProvideDocumentEnvironment{envname}{xargs}{begdef}{enddef}#N
\ProvideExpandableDocumentCommand{cmd}{xargs}{def}#*d
\ProvideHook{hook}#*
\ProvideMirroredHookPair{hook1}{hook2}#*
\ProvideReversedHook{hook}#*
\ProvidesClass{name}#*
\ProvidesClass{name}[release info]#*
\ProvidesFile{name}#*
\ProvidesFile{name}[release info]#*
\ProvidesPackage{name}#*
\ProvidesPackage{name}[release info]#*
\ProvideTextCommand{cmd}{encoding}[args][default]{definition}#*d
\ProvideTextCommand{cmd}{encoding}[args]{definition}#*d
\ProvideTextCommand{cmd}{encoding}{definition}#*d
\ProvideTextCommandDefault{cmd}{definition}#*d
\PushDefaultHookLabel{default label}#*
\RawIndent#*
\RawNoindent#*
\RawParEnd#*
\RawShipout#*
\ReadonlyShipoutCounter#*
\RecordProperties{label}{properties%keyvals}#*l
\RefProperty[local default]{label}{property%keyvals}#*r
\RefProperty{label}{property%keyvals}#*r
\RefUndefinedWarn{label}{property%keyvals}#*
\RemoveFromHook{hook}#*
\RemoveFromHook{hook}[label]#*
\RenewCommandCopy{cmd}{copied cmd%definition}
\RenewDocumentCommand{cmd}{xargs}{def}
\RenewDocumentEnvironment{envname}{xargs}{begdef}{enddef}
\RenewEnvironmentCopy{envname}{copied envname}
\RenewExpandableDocumentCommand{cmd}{xargs}{def}#*
\RequirePackage[options%keyvals]{package}#*u
\RequirePackage[options%keyvals]{package}[release]#*u
\RequirePackage{package}#u
\RequirePackage{package}[release]#*u
\RequirePackageWithOptions{package}#*u
\RequirePackageWithOptions{package}[release]#*u
\ReverseBoolean#*
\SetDefaultHookLabel{default label}#*
\SetKeys[family]{keyvals}#*
\SetKeys{keyvals}#*
\SetMathAlphabet{math-alph%cmd}{version}{encoding}{family}{series}{shape}#*d
\SetProperty{property}{setpoint}{default}{code}#*
\SetSymbolFont{sym-font}{version}{encoding}{family}{series}{shape}#*
\ShipoutBox#*
\ShipoutBoxDepth#*
\ShipoutBoxHeight#*
\ShipoutBoxWidth#*
\ShowCommand{cmd}#*
\ShowEnvironment{envname}#*
\ShowFloat{identifier}#*
\ShowHook{hook}#*
\ShowSocket{socket}#*
\SplitArgument{number}{tokens}#*
\SplitList{tokens}#*
\TextSymbolUnavailable{arg}#*
\TopMark[region]{class%plain}#*
\TopMark{class%plain}#*
\TrimSpaces#*
\UndeclareTextCommand{cmd}{encoding}#*
\UseHook{hook}#*
\UseHookWithArguments{%<hook%>}{%<number%>}{%<arg1%>}%<{arg2}...%>#*
\UseLegacyTextSymbols#*
\UseName{csname}#*
\UseOneTimeHook{hook}#*
\UseOneTimeHookWithArguments{%<hook%>}{%<number%>}{%<arg1%>}%<{arg2}...%>#*
\UseRawInputEncoding#*
\UseSocket{socket}#*
\UseTextAccent{encoding}{cmd}{text}#*
\UseTextSymbol{encoding}{cmd}#*

#keyvals:\RecordProperties#c,\RefProperty#c,\RefUndefinedWarn#c
abspage
page
pagenum
label
title
target
pagetarget
counter
xpos
ypos
%latexproperties
#endkeyvals

# expl3 commands
\ExplFileDate#S
\ExplLoaderFileDate#S
\ProvidesExplFile{name}{date}{version}{description}#*
\ProvidesExplClass{name}{date}{version}{description}#*
\ProvidesExplPackage{name}{date}{version}{description}#*
\GetIdInfo $Id: %<SVN info field%> $ {%<description%>}#*

# document metadata
\DocumentMetadata{options%keyvals}#*
#keyvals:\DocumentMetadata#c
backend=%<backend%>
pdfversion=%<version%>
uncompress
lang=%<lang%>
pdfstandard=#A-1b,A-2a,A-2b,A-2u,A-3a,A-3b,A-3u,A-4 
colorprofiles={%<options%>}
testphase=#phase-I,phase-II,phase-III
debug={%<options%>}
#endkeyvals
\IfDocumentMetadataTF{true code}{false code}#*

# counter, lengths and dimens
\setcounter{counter}{value}#*
\setlanguage{language}#*
\setlength{\gnat}{length}#*
\setpapersize{layout}#*
\settodepth{\gnat}{text}#*
\settoheight{\gnat}{text}#*
\settowidth{\gnat}{text}#*
\addtocontents{ext}{text}#*
\addtocounter{counter}{value}#*
\addtolength{\gnat}{length}#*
\addvspace{length}#*
\newcounter{foo}#*
\newcounter{foo}[counter]#*
\refstepcounter{counter}#*
\restorecr#*
\reversemarginpar#*
\stepcounter{counter}#*
\stretch{number}#*
\usecounter{counter}#*
\usefont{enc}{family}{series}{shape}#*
\value{counter}#*
\newfont{cmd}{fontname}#*d

# counter representative
\theenumi#*
\theenumii#*
\theenumiii#*
\theenumiv#*
\theequation#*
\thefigure#*
\thefootnote#*
\thempfn#*
\thempfootnote#*
\thepage#*
\theparagraph#*
\thepart#*
\thesection#*
\thesubparagraph#*
\thesubsection#*
\thesubsubsection#*
\thetable#*
\thetotalpages#*

# boxes
\savebox{box}[width][position]{text}#*
\savebox{box}[width]{text}#*
\savebox{box}{text}#*
\makebox[width][position]{text}#*
\makebox[width]{text}#*
\usebox{box}#*
\raisebox{raise%l}[height][depth]{text}#*
\raisebox{raise%l}[height]{text}#*
\raisebox{raise%l}{text}#*
\newsavebox{box%cmd}#*d

# variables
\belowcaptionskip#*
\binoppenalty#*
\bottomfraction#*
\dblfigrule#*
\dblfloatpagefraction#*
\dblfloatsep#*
\dbltextfloatsep#*
\dbltopfraction#*
\defaultscriptratio#*
\defaultscriptscriptratio#*
\doublerulesep#*
\footnotesep#*
\footskip#*
\intextsep#*
\itemindent#*
\itemsep#*L
\labelenumi#*
\labelenumii#*
\labelenumiii#*
\labelenumiv#*
\labelitemi#*
\labelitemii#*
\labelitemiii#*
\labelitemiv#*
\labelsep#*L
\labelwidth#*L
\leftmargin#*
\leftmargini#*
\leftmarginii#*
\leftmarginiii#*
\leftmarginiv#*
\leftmarginv#*
\leftmarginvi#*
\leftmark#*
\marginparpush#*
\marginparsep#*L
\marginparwidth#*L
\paperheight#*L
\paperwidth#*L
\tabbingsep#*
\tabcolsep#*
\topfigrule#*
\topfraction#*
\topmargin#*L
\topsep#*L
\totalheight#*L
\textfloatsep#*L
\textfraction#*
\abovecaptionskip#*
\addpenalty#*
\arraycolsep#*
\arrayrulewidth#*L
\arraystretch#*
\badness#*
\baselinestretch#*
\columnsep#*L
\columnseprule#*
\evensidemargin#*
\extracolsep#*
\fboxrule#*
\fboxsep#*
\floatpagefraction#*
\floatsep#*
\headheight#*L
\headsep#*L
\height#*L
\partopsep#*L
\parsep#*L
\hideskip#*
\stockheight#*L
\stockwidth#*L

# pdftex 2023-02-11
\efcode#*
\expanded#*
\ifincsname#*
\ifpdfabsdim#*
\ifpdfabsnum#*
\ifpdfprimitive#*
\knaccode#*
\knbccode#*
\knbscode#*
\leftmarginkern#*
\letterspacefont#*
\lpcode#*
\partokencontext#*
\partokenname#*
\pdfadjustinterwordglue#*
\pdfadjustspacing#*
\pdfannot#*
\pdfappendkern#*
\pdfcatalog{action spec}#*
\pdfcolorstack#*
\pdfcolorstackinit#*
\pdfcompresslevel#*
\pdfcopyfont#*
\pdfcreationdate#*
\pdfdecimaldigits#*
\pdfdest#*
\pdfdestmargin#*
\pdfdraftmode#*
\pdfeachlinedepth#*
\pdfeachlineheight#*
\pdfelapsedtime#*
\pdfendlink#*
\pdfendthread#*
\pdfescapehex{string}#*
\pdfescapename{string}#*
\pdfescapestring{string}#*
\pdffakespace#*
\pdffiledump#*
\pdffilemoddate{file}#*
\pdffilesize{file}#*
\pdffirstlineheight#*
\pdffontattr#*
\pdffontexpand#*
\pdffontname#*
\pdffontobjnum#*
\pdffontsize#*
\pdfforcepagebox#*
\pdfgamma#*
\pdfgentounicode#*
\pdfglyphtounicode{glyphname}{codepoint}#*
\pdfhorigin#*
\pdfignoreddimen#*
\pdfimageapplygamma#*
\pdfimagegamma#*
\pdfimagehicolor#*
\pdfimageresolution#*
\pdfincludechars#*
\pdfinclusioncopyfonts#*
\pdfinclusionerrorlevel#*
\pdfinfo{info}
\pdfinfoomitdate#*
\pdfinsertht#*
\pdfinterwordspaceoff#*
\pdfinterwordspaceon#*
\pdflastannot#*
\pdflastlinedepth#*
\pdflastlink#*
\pdflastmatch#*
\pdflastobj#*
\pdflastxform#*
\pdflastximage#*
\pdflastximagecolordepth#*
\pdflastximagepages#*
\pdflastxpos#*
\pdflastypos#*
\pdflinkmargin#*
\pdfliteral{literal}#*
\pdfmajorversion#*
\pdfmapfile{file}#*
\pdfmapline{map spec}#*
\pdfmatch#*
\pdfmdfivesum#*
\pdfminorversion#*
\pdfmovechars#*
\pdfnames{action spec}#*
\pdfnobuiltintounicode#*
\pdfnoligatures#*
\pdfnormaldeviate#*
\pdfobj{object type spec}#*
\pdfobjcompresslevel#*
\pdfomitcharset#*
\pdfomitinfodict#*
\pdfomitprocset#*
\pdfoutline#*
\pdfoutput#*
\pdfpageattr{attributes}#*
\pdfpagebox#*
\pdfpageheight#*
\pdfpageref#*
\pdfpageresources{resources}#*
\pdfpagesattr{attributes}#*
\pdfpagewidth#*
\pdfpkmode#*
\pdfpkresolution#*
\pdfprependkern#*
\pdfprimitive#*
\pdfprotrudechars#*
\pdfpxdimen#*
\pdfrandomseed#*
\pdfrefobj#*
\pdfrefxform#*
\pdfrefximage#*
\pdfresettimer#*
\pdfrestore#*
\pdfretval#*
\pdfrunninglinkoff#*
\pdfrunninglinkon#*
\pdfsave#*
\pdfsavepos#*
\pdfsetmatrix{matrix}#*
\pdfsetrandomseed#*
\pdfshellescape#*
\pdfsnaprefpoint#*
\pdfsnapy#*
\pdfsnapycomp#*
\pdfspacefont#*
\pdfstartlink#*
\pdfstartthread#*
\pdfstrcmp{string1}{string2}#*
\pdfsuppressptexinfo#*
\pdfsuppresswarningdupdest#*
\pdfsuppresswarningdupmap#*
\pdfsuppresswarningpagegroup#*
\pdftexbanner#*
\pdftexrevision#*
\pdftexversion#*
\pdfthread#*
\pdfthreadmargin#*
\pdftracingfonts#*
\pdftrailer{text%plain}#*
\pdftrailerid{text%plain}#*
\pdfunescapehex{string}#*
\pdfuniformdeviate#*
\pdfuniqueresname#*
\pdfvorigin#*
\pdfxform#*
\pdfxformname#*
\pdfximage{file}#*
\pdfximagebbox#*
\quitvmode#*
\rightmarginkern#*
\rpcode#*
\shbscode#*
\showstream#*
\stbscode#*
\synctex#*
\tagcode#*
\tracingstacklevels#*

# miscellany
\allocationnumber#*
\bfdefault#*
\counterwithin{counter}{within-counter}#*
\counterwithout{counter}{within-counter}#*
\emforce#*
\eminnershape#*
\emreset#*
\extrafloats{number}#*
\familydefault#*
\fill#*
\hideoutput#*
\IeC#*
\ignorespacesafterend#*
\itdefault#*
\kill#*
\loggingall#*
\loggingoutput#*
\ltcmddate#S
\ltcmdhooksdate#S
\ltcmdhooksversion#S
\ltcmdversion#S
\ltfilehookdate#S
\ltfilehookversion#S
\lthooksdate#S
\lthooksversion#S
\ltmarksdate#S
\ltmarksversion#S
\ltmetadate#S
\ltmetaversion#S
\ltparadate#S
\ltparaversion#S
\ltpropertiesdate#S
\ltpropertiesversion#S
\ltshipoutdate#S
\ltshipoutversion#S
\ltsocketsdate#S
\ltsocketsversion#S
\mathalpha#*
\mathgroup#*
\mathhexbox#*
\mddefault#*
\nobreakdashes#*
\nobreakspace#*
\normalsfcodes#*
\numberline{number}#*
\poptabs#*
\pushtabs#*
\requestedLaTeXdate#*
\rmdefault#*
\rmsubstdefault#*
\scdefault#*
\secdef{star cmd}{unstar cmd}#*
\seriesdefault#*
\sfdefault#*
\sfsubstdefault#*
\shapedefault#*
\showoutput#*
\showoverfull#*
\sldefault#*
\sscdefault#*
\swdefault#*
\symletters#*
\symoperators#*
\tencirc#*
\tencircw#*
\tenln#*
\tenlnw#*
\textcompsubstdefault#*
\TextOrMath{text content}{math content}#*
\tmspace{arg1}{arg2}{arg3}#*
\tracingnone#*
\ttdefault#*
\ttsubstdefault#*
\ulcdefault#*
\unitlength#*
\updefault#*
