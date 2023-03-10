# memhangul-x package
# Matthew Bertucci 2023/03/09 for v23.03

## default to luatex
#include:luatexko
#include:xob-font
#include:xob-dotemph
## uncomment following line for xetex
## #include:xetexko-var
## uncomment following line for pdflatex
## #include:cjkutf8-ko
#include:hyperref
#include:memhfixc
#include:memhangul-common
#include:memucs-setspace

#keyvals:\usepackage/memhangul-x#c
interworddefault
nosetspace
quotespacing
nonfrench
hanja
mathdisp
arabicfront
hangulpagestyle
pdfbookmark
polyglossia
babelhangul
babelvacant
gremph
itemph
latinquote
oldhangul
manualfontspec
nowinname
unfonts
nounfonts
nanum
hcr
noto
figtabcapt
cjk
dhucs
uset1font
usedotemph
#endkeyvals

#ifOption:polyglossia
#include:polyglossia
\sethangulfont{font name}
\sethangulfont{font name}[font features]
\hangulfont#*
\hangulfonttt#*
#endif

#ifOption:babelhangul
#include:babel
#endif

#ifOption:interworddefault
#include:memucs-interword-x
#endif

\HUGE
\kscntformat{level}{before}{title%text}
\regremph
\ungremph

\DisabledOption{option}#S
\ifKOTEXCJK#*
\KOTEXCJKfalse#*
\KOTEXCJKtrue#*
\marginparswitchfalse#*
\marginparswitchtrue#*
\memucsinterwordchapterskiphook#*
\memucsinterwordhook#*
\nosetspace#*
\reversemarginfalse#*
\reversemargintrue#*
\setxxxlength{arg1}{arg2}#*
\subappendixname#*
