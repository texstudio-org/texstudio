# PJLlang package
# Matthew Bertucci 12/30/2021

#include:kvoptions
#include:etoolbox
#include:iftex
#include:fontenc
#include:inputenc
#include:babel
#include:silence
#include:setspace

#keyvals:\usepackage/PJLlang#c
polyglossia#true,false
EN
english
English
FR
french
French
DE
german
ngerman
German
IT
italian
Italian
PT
portuguese
Portuguese
BR
brazilian
Brazilian
ES
spanish
Spanish
CN
chinese
Chinese
schinese
SChinese
simplifiedchinese
SimplifiedChinese
TC
tchinese
TChinese
traditionalchinese
TraditionalChinese
JP
japanese
Japanese
RU
russian
Russian
#endkeyvals

\englishABBR#*
\frenchABBR#*
\ngermanABBR#*
\italianABBR#*
\portugueseABBR#*
\brazilianABBR#*
\spanishABBR#*
\schineseABBR#*
\tchineseABBR#*
\japaneseABBR#*
\russianABBR#*

\StrToABBR{string}#*
\StrToTYPE{string}#*

\AddLanguageSetting{code}
\AddLanguageSetting(language){code}

\PJLsetlinespacing{dimen%l}#*
\PJLsetCJKlinespacing{dimen%l}#*
\PJLsetparindent{dimen%l}#*
\PJLsetCJKparindent{dimen%l}#*

\UseLanguageCORE{language}#*
\UseLanguage{language}
\UseOtherLanguage{language}{content%text}

\bibname#S
\frenchpartname#S
\ord#S
\proofname#S

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