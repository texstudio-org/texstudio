# latex mode: LaTeX commands (package level)
# dani/2006-02-18
# muzimuzhi/8 Jul 2019
# commands with big Letters and others
\AtBeginDocument{code}#*
\AtEndDocument{code}#*
\AtEndOfClass{code}#*
\AtEndOfPackage{code}#*
\CheckCommand{cmd}[args][default]{def}#*
\CheckCommand{cmd}[args]{def}#*
\CheckCommand{cmd}{def}#*
\CheckCommand*{cmd}[args][default]{def}#*
\CheckCommand*{cmd}[args]{def}#*
\CheckCommand*{cmd}{def}#*
\ClassError{class name}{error text}{help text}#*
\ClassInfo{class name}{info text}#*
\ClassInfoNoLine{class name}{info text}
\ClassWarning{class name}{warning text}#*
\ClassWarningNoLine{class name}{warning text}#*
\CurrentOption#*
\DeclareFixedFont{cmd}{encoding}{family}{series}{shape}{size}#*d
\DeclareFontEncoding{encoding}{text-settings}{math-settings}#*
\DeclareFontEncodingDefaults{text-settings}{math-settings}#*
\DeclareFontFamily{encoding}{family}{loading-settings}#*
\DeclareFontShape{encoding}{family}{series}{shape}{loading-info}{loading-settings}#*
\DeclareMathAccent{cmd}{type}{sym-font}{slot}#*d
\DeclareMathAlphabet{math-alph}{encoding}{family}{series}{shape}#*
\DeclareMathDelimiter{cmd}{type}{sym-font-1}{slot-1}{sym-font-2}{slot-2}#*d
\DeclareMathRadical{cmd}{sym-font-1}{slot-1}{sym-font-2}{slot-2}#*d
\DeclareMathSizes{t-size}{mt-size}{s-size}{ss-size}#*
\DeclareMathSymbol{symbol}{type}{sym-font}{slot}#*d
\DeclareMathVersion{version}#*
\DeclareOldFontCommand{cmd}{text-switch}{math-switch}#*
\DeclareOption*{code}#*
\DeclareOption{option}{code}#*
\DeclareRobustCommand{cmd}[args][default]{def}#*d
\DeclareRobustCommand{cmd}[args]{def}#*d
\DeclareRobustCommand{cmd}{def}#*d
\DeclareRobustCommand*{cmd}[args][default]{def}#*d
\DeclareRobustCommand*{cmd}[args]{def}#*d
\DeclareRobustCommand*{cmd}{def}#*d
\DeclareSizeFunction{name}{code}#*
\DeclareSymbolFont{sym-font}{encoding}{family}{series}{shape}#*
\DeclareSymbolFontAlphabet{math-alph}{sym-font}#*
\DeclareTextAccent{def}{encoding}{character}#*
\DeclareTextCommand{cmd}{encoding%definition}[num][default]{definition}#*d
\DeclareTextComposite{def}{encoding}{character}{character}#*
\DeclareTextCompositeCommand{cmd}{encoding%definition}{letter%definition}{definition}#*d
\DeclareTextFontCommand{cmd}{font-switches%definition}#*d
\DeclareTextSymbol{def}{encoding}{code}#*
\ExecuteOptions{optionlist}#*
\IfFileExists{file}{then}{else}#*
\InputIfFileExists{file}{then}{else}#*
\LastDeclaredEncoding#*
\LoadClass[optionlist]{class}#*u
\LoadClass[optionlist]{class}[release]#*u
\LoadClass{class}#*u
\LoadClass{class}[release]#*u
\LoadClassWithOptions{class}#*u
\LoadClassWithOptions{class}[release]#*u
\NeedsTeXFormat{format}#*
\NeedsTeXFormat{format}[release]#*
\OptionNotUsed#*
\PackageError{package name}{error text}{help text}#*
\PackageInfo{package name}{info text}#*
\PackageInfoNoLine{package name}{info text}#*
\PackageWarning{package name}{warning text}#*
\PackageWarningNoLine{package name}{warning text}#*
\PassOptionsToClass{optionlist}{class}#*
\PassOptionsToPackage{optionlist}{package}#*
\ProcessOptions#*
\ProcessOptions*#*
\ProvidesClass{name}#*
\ProvidesClass{name}[release info]#*
\ProvidesFile{name}#*
\ProvidesFile{name}[release info]#*
\ProvidesPackage{name}#*
\ProvidesPackage{name}[release info]#*
\ProvideTextCommand{cmd}{encoding}[num][default]{definition}#*
\RequirePackage[optionlist]{package}#*u
\RequirePackage[optionlist]{package}[release]#*u
\RequirePackage{package}#u
\RequirePackage{package}[release]#*u
\RequirePackageWithOptions{package}#*u
\RequirePackageWithOptions{package}[release]#*u
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
\newfont{cmd}{fontname}#*
# counter representative
\thechapter#*
\theenumi#*
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
\numberline#* 

# miscellany
\allocationnumber
\fill
\tracingfonts
\unitlength
