# scrbase package
# Matthew Bertucci 2022/05/17 for v3.36

#include:scrlfile
#include:keyval
#include:scrlogo

\KOMAScriptVersion#*
\rloop{arg}#*
\IfLTXAtLeastTF{date}{then code}{else code}#*

\DefineFamily{family}#*
\DefineFamilyMember{family}#*
\DefineFamilyMember[member]{family}#*
\DefineFamilyKey{family}{key%plain}{action}#*
\DefineFamilyKey[member]{family}{key%plain}{action}#*
\DefineFamilyKey[member]{family}{key%plain}[default]{action}#*
\RelaxFamilyKey{family}{key%plain}#*
\RelaxFamilyKey[member]{family}{key%plain}#*
\FamilyKeyState#*
\FamilyKeyStateUnknown#*
\FamilyKeyStateUnknownValue#*
\FamilyKeyStateNeedValue#*
\FamilyKeyStateProcessed#*
\FamilyOfKey#*
\FamilyMemberOfKey#*
\FamilyProcessOptions{family}#*
\FamilyProcessOptions[member]{family}#*

\AtEndOfFamilyOptions{action}#*
\AtEndOfFamilyOptions*{action}#*
\IfArgIsEmpty{arg}{then code}{else code}#*
\XdivY{dividend}{divisor}#*
\XmodY{dividend}{divisor}#*
\Ifundefinedorrelax{name}{then code}{else code}#*
\Ifnotundefined{name}{then code}{else code}#*
\Ifstr{string1}{string2}{then code}{else code}#*
\Ifstrstart{string1}{string2}{then code}{else code}#*
\Ifislengthprimitive{expression}{then code}{else code}#*
\Ifisdimen{string}{then code}{else code}#*
\Ifisskip{expression}{then code}{else code}#*
\Ifiscount{count}{then code}{else code}#*
\Ifisdimexpr{expression}{then code}{else code}#*
\Ifisglueexpr{expression}{then code}{else code}#*
\Ifisnumexpr{expression}{then code}{else code}#*
\Ifisdefchar{arg}{then code}{else code}#*
\Ifiscounter{counter}{then code}{else code}#*
\Ifisinteger{expression}{then code}{else code}#*
\Ifisdimension{expression}{then code}{else code}#*
\Ifisglue{expression}{then code}{else code}#*
\Ifnumber{string}{then code}{else code}#*
\Ifintnumber{string}{then code}{else code}#*
\Ifdimen{string}{then code}{else code}#*
\Ifpdfoutput{then code}{else code}#*
\Ifpsoutput{then code}{else code}#*
\Ifdvioutput{then code}{else code}#*
\IfRTL{then code}{else code}#*
\IfLTR{then code}{else code}#*
\PackageInfoNoLine{package}{information%text}#*
\ClassInfoNoLine{class}{information%text}#*
\IfActiveMkBoth{then code}{else code}#*

\BeforeFamilyProcessOptions{family}{code}#*
\BeforeFamilyProcessOptions[member]{family}{code}#*
\FamilyExecuteOptions{family}{options list}#*
\FamilyExecuteOptions[member]{family}{options list}#*
\FamilyOptions{family}{options list}#*
\FamilyOption{family}{option}{value list}#*
\FamilyUnknownKeyValue{family}{key%plain}{value}{value list}#*
\FamilyElseValues#*
\FamilyBoolKey{family}{key%plain}{switch name}#*
\FamilyBoolKey[member]{family}{key%plain}{switch name}#*
\FamilySetBool{family}{key%plain}{switch name}{value}#*
\FamilyInverseBoolKey{family}{key%plain}{switch name}#*
\FamilyInverseBoolKey[member]{family}{key%plain}{switch name}#*
\FamilySetInverseBool{family}{key%plain}{switch name}{value}#*
\FamilyCounterKey{family}{key%plain}{counter}#*
\FamilyCounterKey[member]{family}{key%plain}{counter}#*
\FamilyCounterKey[member]{family}{key%plain}[default]{counter}#*
\FamilySetCounter{family}{key%plain}{counter}{value}#*
\FamilyCounterMacroKey{family}{key%plain}{macro%cmd}#*d
\FamilyCounterMacroKey{family}{key%plain}[default]{macro%cmd}#Sd
\FamilyCounterMacroKey[member]{family}{key%plain}{macro%cmd}#*d
\FamilyCounterMacroKey[member]{family}{key%plain}[default]{macro%cmd}#*d
\FamilySetCounterMacro{family}{key%plain}{macro%cmd}{value}#*d
\FamilyLengthKey{family}{key%plain}{length}#*
\FamilyLengthKey[member]{family}{key%plain}{length}#*
\FamilyLengthKey[member]{family}{key%plain}[default]{length}#*
\FamilySetLength{family}{key%plain}{length}{value}#*
\FamilyLengthMacroKey{family}{key%plain}{macro%cmd}#*d
\FamilyLengthMacroKey{family}{key%plain}[default]{macro%cmd}#Sd
\FamilyLengthMacroKey[member]{family}{key%plain}{macro%cmd}#*d
\FamilyLengthMacroKey[member]{family}{key%plain}[default]{macro%cmd}#*d
\FamilySetLengthMacro{family}{key%plain}{macro%cmd}{value}#*d
\FamilyUseLengthMacroKey{family}{key%plain}{macro%cmd}#*d
\FamilyUseLengthMacroKey{family}{key%plain}[default]{macro%cmd}#Sd
\FamilyUseLengthMacroKey[member]{family}{key%plain}{macro%cmd}#*d
\FamilyUseLengthMacroKey[member]{family}{key%plain}[default]{macro%cmd}#*d
\FamilySetUseLengthMacro{family}{key%plain}{macro%cmd}{value}#*d
\FamilyNumericalKey{family}{key%plain}{macro%cmd}{value list}#*d
\FamilyLengthMacroKey{family}{key%plain}[default]{macro%cmd}{value list}#Sd
\FamilyLengthMacroKey[member]{family}{key%plain}{macro%cmd}{value list}#*d
\FamilyLengthMacroKey[member]{family}{key%plain}[default]{macro%cmd}{value list}#*d
\FamilySetNumerical{family}{key%plain}{macro%cmd}{value list}{value}#*d
\FamilyStringKey{family}{key%plain}{macro%cmd}#*d
\FamilyStringKey{family}{key%plain}[default]{macro%cmd}#Sd
\FamilyStringKey[member]{family}{key%plain}{macro%cmd}#*d
\FamilyStringKey[member]{family}{key%plain}[default]{macro%cmd}#*d
\FamilyCSKey{family}{key%plain}{csname}#*
\FamilyLengthKey[member]{family}{key%plain}{csname}#*
\FamilyLengthKey[member]{family}{key%plain}[default]{csname}#*

\ForDoHook{specification}{command}#*
\SplitDoHook{specifier}{head macro%cmd}{remainder macro%cmd}#*d
\ExecuteDoHook{specifier}#*
\AddtoDoHook{name}{command}#*
\AddtoOneTimeDoHook{name}{command}#*

\defcaptionname{language list}{term%cmd}{definition}#*d
\defcaptionname*{language list}{term%cmd}{definition}#*d
\providecaptionname{language list}{term%cmd}{definition}#*d
\providecaptionname*{language list}{term%cmd}{definition}#*d
\newcaptionname{language list}{term%cmd}{definition}#*d
\newcaptionname*{language list}{term%cmd}{definition}#*d
\renewcaptionname{language list}{term%cmd}{definition}#*
\renewcaptionname*{language list}{term%cmd}{definition}#*

# deprecated
\ifnotundefined#S
\ifislengthprimitive#S
\ifisdefchar#S
\ifstr#S
\ifstrstart#S
\ifisdimen#S
\ifisskip#S
\ifiscount#S
\ifisdimexpr#S
\ifisglueexpr#S
\ifisnumexpr#S
\ifiscounter#S
\ifisinteger#S
\ifisdimension#S
\ifisglue#S
\ifnumber#S
\ifintnumber#S
\ifdimen#S
\ifpdfoutput#S
\ifpsoutput#S
\ifdvioutput#S
