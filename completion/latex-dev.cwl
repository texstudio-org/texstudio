# latex mode: LaTeX commands (package level)
# dani/2006-02-18
# muzimuzhi/8 Jul 2019
# Matthew Bertucci 10/21/2021

# commands with big Letters and others
\AddEverypageHook{code}#*
\AddThispageHook{code}#*
\AddToHook{hook}{label}{code}#*
\AddToHookNext{hook}{code}#*
\AfterEndEnvironment[label]{code}#*
\AfterEndEnvironment{code}#*
\AtBeginDocument{code}#*
\AtBeginDvi{code}#*
\AtBeginEnvironment[label]{code}#*
\AtBeginEnvironment{code}#*
\AtBeginShipout{code}#*
\AtBeginShipoutAddToBox{code}#*
\AtBeginShipoutAddToBoxForeground{code}#*
\AtBeginShipoutBox#*
\AtBeginShipoutDiscard
\AtBeginShipoutFirst{code}#*
\AtBeginShipoutInit
\AtBeginShipoutNext{code}#*
\AtBeginShipoutOriginalShipout#*
\AtBeginShipoutUpperLeft{code}#*
\AtBeginShipoutUpperLeftForeground{code}#*
\AtEndDocument{code}#*
\AtEndDvi{code}#*
\AtEndEnvironment[label]{code}#*
\AtEndEnvironment{code}#*
\AtEndOfClass{code}#*
\AtEndOfPackage{code}#*
\AtNextShipout{code}#*
\BeforeBeginEnvironment[label]{code}#*
\BeforeBeginEnvironment{code}#*
\BeforeClearDocument{code}#*
\BooleanFalse
\BooleanTrue
\CheckCommand*{cmd}[args][default]{def}#*
\CheckCommand*{cmd}[args]{def}#*
\CheckCommand*{cmd}{def}#*
\CheckCommand{cmd}[args][default]{def}#*
\CheckCommand{cmd}[args]{def}#*
\CheckCommand{cmd}{def}#*
\CheckEncodingSubset{text cmd}{encoding}{error}{subset id}{symbol}#*
\ClassError{class name}{error text}{help text}#*
\ClassInfo{class name}{info text}#*
\ClassWarning{class name}{warning text}#*
\ClassWarningNoLine{class name}{warning text}#*
\ClearHookRule{hook}{label1}{label2}#*
\CurrentFile#*
\CurrentFilePath#*
\CurrentFilePathUsed#*
\CurrentFileUsed#*
\CurrentOption#*
\DebugHooksOff#*
\DebugHooksOn#*
\DebugShipoutsOff#*
\DebugShipoutsOn#*
\DeclareCommandCopy{cmd}{def}#d
\DeclareCurrentRelease{name}{date}#*
\DeclareDefaultHookRule{label1}{relation}{label2}#*
\DeclareDocumentCommand{cmd}{args}{def}#d
\DeclareDocumentEnvironment{envname}{args}{begdef}{enddef}#N
\DeclareEmphSequence{font cmd list}#*
\DeclareEncodingSubset{encoding}{family}{subset number}#*
\DeclareErrorFont{encoding}{family}{series}{shape}{size}#*
\DeclareExpandableDocumentCommand{cmd}{args}{def}#*d
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
\DisableHook{hook}#*
\DiscardShipoutBox#*
\EndIncludeInRelease#*
\EndModuleRelease#*
\EveryShipout{code}#*
\ExecuteOptions{optionlist}#*
\ExplSyntaxOff#*
\ExplSyntaxOn#*
\GenericError{continuation}{message%text}{help location%text}{help info%text}#*
\GenericInfo{continuation}{message%text}#*
\GenericWarning{continuation}{message%text}#*
\GetDocumentCommandArgSpec{cmd}#*
\GetDocumentEnvironmentArgSpec{envname}#*
\IfBooleanF{arg}{falseCode}
\IfBooleanT{arg}{trueCode}
\IfBooleanTF{arg}{trueCode}{falseCode}
\IfClassAtLeastTF{date}{true code}{false code}#*
\IfFileExists{file}{then}{else}#*
\IfFontSeriesContextTF{face}{true code}{false code}#*
\IfFormatAtLeastTF{date}{true code}{false code}#*
\IfHookEmptyTF{hook}{true code}{false code}#*
\IfNoValueF{arg}{ValueCode}
\IfNoValueT{arg}{-NoValue-Code}
\IfNoValueTF{arg}{-NoValue-Code}{ValueCode}
\IfPackageAtLeastTF{date}{true code}{false code}#*
\IfTargetDateBefore{date}{before code}{after code}#*
\IncludeInRelease{date}{command}{description}#*
\IndentBox#*
\InputIfFileExists{file}{then}{else}#*
\LastDeclaredEncoding#*
\LoadClass[optionlist]{class}#*u
\LoadClass[optionlist]{class}[release]#*u
\LoadClass{class}#*u
\LoadClass{class}[release]#*u
\LoadClassWithOptions{class}#*u
\LoadClassWithOptions{class}[release]#*u
\LoadFontDefinitionFile{encoding}{family}#*
\LogHook#*
\MakeRobust{cmd}#*
\MessageBreak#*
\NeedsTeXFormat{format}#*
\NeedsTeXFormat{format}[release]#*
\NewCommandCopy{cmd}{def}#d
\NewDocumentCommand{cmd}{args}{def}#d
\NewDocumentEnvironment{envname}{args}{begdef}{enddef}#N
\NewExpandableDocumentCommand{cmd}{args}{def}#*d
\NewHook{hook}#*
\NewMirroredHookPair{hook1}{hook2}#*
\NewModuleRelease{date}{name}#*
\NewReversedHook{hook}#*
\OmitIndent#*
\OptionNotUsed#*
\PackageError{package name}{error text}{help text}#*
\PackageInfo{package name}{info text}#*
\PackageWarning{package name}{warning text}#*
\PackageWarningNoLine{package name}{warning text}#*
\PassOptionsToClass{optionlist}{class}#*
\PassOptionsToPackage{optionlist}{package}#*
\PopDefaultHookLabel#*
\PreviousTotalPages#*
\ProcessedArgument#*
\ProcessList{list}{cmd}#*
\ProcessOptions#*
\ProcessOptions*#*
\ProvideDocumentCommand{cmd}{args}{def}#d
\ProvideDocumentEnvironment{envname}{args}{begdef}{enddef}#N
\ProvideExpandableDocumentCommand{cmd}{args}{def}#*d
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
\RemoveFromHook{hook}{label}#*
\RenewCommandCopy{cmd}{def}#d
\RenewDocumentCommand{cmd}{args}{def}#d
\RenewDocumentEnvironment{envname}{args}{begdef}{enddef}#N
\RenewExpandableDocumentCommand{cmd}{args}{def}#*d
\RequirePackage[optionlist]{package}#*u
\RequirePackage[optionlist]{package}[release]#*u
\RequirePackage{package}#u
\RequirePackage{package}[release]#*u
\RequirePackageWithOptions{package}#*u
\RequirePackageWithOptions{package}[release]#*u
\ReverseBoolean#*
\SetDefaultHookLabel{default label}#*
\SetMathAlphabet{math-alph%cmd}{version}{encoding}{family}{series}{shape}#*d
\SetSymbolFont{sym-font}{version}{encoding}{family}{series}{shape}#*
\ShipoutBox#*
\ShipoutBoxDepth#*
\ShipoutBoxHeight#*
\ShipoutBoxWidth#*
\ShowCommand{cmd}#*
\ShowDocumentCommandArgSpec{cmd}#*
\ShowDocumentEnvironmentArgSpec{envname}#*
\ShowHook{hook}#*
\SplitArgument{number}{tokens}#*
\SplitList{tokens}#*
\TextSymbolUnavailable{arg}#*
\TrimSpaces#*
\UndeclareTextCommand{cmd}{encoding}#*
\UseHook{hook}#*
\UseLegacyTextSymbols#*
\UseOneTimeHook{hook}#*
\UseRawInputEncoding#*
\UseTextAccent{encoding}{cmd}{text}#*
\UseTextSymbol{encoding}{cmd}#*

# counter, lengths and dimens
\setcounter{counter}{value}#*
\setlanguage{language}#*
\setlength{\gnat}{length}#*
\setpapersize{layout}#*
\settodepth{\gnat}{text}#*
\settoheight{\gnat}{text}#*
\settowidth{\gnat}{text}#*
\addto#*
\addtocontents{file}{text}#*
\addtocounter{counter}{value}#*
\addtolength{\gnat}{length}#*
\addtoversion#*
\addvspace{length}#*
\deffootnote[width}{indention}{par indention}{definition}#*
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
\thechapter#*
\theenumi#*
\theenumii#*
\theenumiii#*
\theenumiv#*
\theequation#*
\thefigure#*
\thefootnote#*
\thefootnotemark#*
\thehours#*
\theminutes#*
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
\bottomnumber#*
\dblfigrule#*
\dblfloatpagefraction#*
\dblfloatsep#*
\dbltextfloatsep#*
\dbltopfraction#*
\dbltopnumber#*
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
\topnumber#*
\topsep#*L
\totalheight#*L
\totalnumber#*
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
\columnwidth#*L
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
\footheight#*L
\hideskip#*

# pdftex specials
\pdfoutput#*
\pdfadjustspacing#*
\pdfcompresslevel#*
\pdfdecimaldigits#*
\pdfmovechars#*
\pdfimageresolution#*
\pdfpkresolution#*
\pdfhorigin#*
\pdfvorigin#*
\pdfpageheight#*
\pdfpagewidth#*
\pdflinkmargin#*
\pdfthreadmargin#*
\pdfminorversion#*
\pdfgentounicode#*
\pdfmapfile{file}#*
\numberline#*

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
\itdefault#*
\loggingall#*
\loggingoutput#* 
\mathalpha#*
\mathgroup#*
\mathhexbox{number}{expr%formula}{expr%formula}#*
\mddefault#*
\nobreakdashes#*
\nobreakspace#*
\normalsfcodes#*
\poptabs#*
\pushtabs#*
\requestedLaTeXdate#*
\rmdefault#*
\rmsubstdefault#*
\scdefault#*
\seriesdefault#*
\sfdefault#*
\sfsubstdefault#*
\shapedefault#*
\showoutput#*
\showoverfull#*
\sldefault#*
\sscdefault#*
\swdefault#*
\textcompsubstdefault#*
\TextOrMath{text content}{math content}#*
\tmspace{arg1}{arg2}{arg3}#*
\tracefloats#*
\tracefloatsoff#*
\tracefloatvals#*
\tracingfonts#*
\tracingnone#*
\ttdefault#*
\ttsubstdefault#*
\ulcdefault#*
\unitlength#*
\updefault#*
