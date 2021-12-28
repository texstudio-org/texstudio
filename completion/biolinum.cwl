# biolinum package
# Matthew Bertucci 12/26/2021 for v5.3.0

#include:ifxetex
#include:ifluatex
#include:xkeyval
#include:textcomp
#include:fontenc
#include:fontaxes

#keyvals:\usepackage/biolinum#c
sfdefault
type1
nofontspec
lining
nf
lf
oldstyle
osf
sflining
sflf
sfoldstyle
sfosf
osfss
tabular
t
p
sftabular
sft
sfproportional
sfp
scaled=%<factor%>
scale=%<factor%>
defaultfeatures={%<fontspec features%>}
#endkeyvals

\biolinum#n
\biolinumOsF#n
\biolinumLF#n
\biolinumkey#*n
\sufigures#n
\textsu{text}#n
\textsuperior{text}#*n
\oldstylenums{text}#n
\liningnums{text}#*n
\oldstylenumsf{text}#n
\liningnumsf{text}#n
\tabularnums{text}#*n
\proportionalnums{text}#*n
\tabularnumsf{text}#n
\proportionalnumsf{text}#n
\DeclareTextGlyphY{type}{name}{number}#*n
\biolinumGlyph{glyph name}#n
\biolinumKeyGlyph{glyph name}#n

# from LKey.tex
\LKey{letter or digit}#n
\LKeyPad{digit}#n
\LKeyF{digit}#n
\LKeyAltF{digit}#n
\LKeyStrgAltF{digit}#n
\LKeyCtrlAltF{digit}#n
\LKeyStrgX{letter or digit}#n
\LKeyCtrlX{letter or digit}#n
\LKeyShiftX{letter or digit}#n
\LKeyAltX{letter or digit}#n
\LKeyAltGrX{letter or digit}#n
\LKeyShiftStrgX{letter or digit}#n
\LKeyShiftCtrlX{letter or digit}#n
\LKeyShiftAltX{letter or digit}#n
\LKeyShiftAltGrX{letter or digit}#n
\LKeyStrgAltX{letter or digit}#n
\LKeyCtrlAltX{letter or digit}#n
\LKeyStrgAltEnt#n
\LKeyCtrlAltEnt#n
\LKeyReset#n
\LKeyTux#n
\LKeyWin#n
\LKeyMenu#n
\LKeyStrg#n
\LKeyCtrl#n
\LKeyAlt#n
\LKeyAltGr#n
\LKeyShift#n
\LKeyTab#n
\LKeyEnter#n
\LKeyCapsLock#n
\LKeyPos#n
\LKeyEntf#n
\LKeyEinf#n
\LKeyLeer#n
\LKeyEsc#n
\LKeyEnde#n
\LKeyCommand#n
\LKeyOptionKey#n
\LKeyBack#n
\LKeyUp#n
\LKeyDown#n
\LKeyLeft#n
\LKeyRight#n
\LKeyPgUp#n
\LKeyPgDown#n
\LKeyAt#n
\LKeyFn#n
\LKeyHome#n
\LKeyDel#n
\LKeySpace#n
\LKeyScreenUp#n
\LKeyScreenDown#n
\LKeyIns#n
\LKeyEnd#n
\LKeyGNU#n
\LKeyPageUp#n
\LKeyPageDown#n
\LMouseEmpty#n
\LMouseN#n
\LMouseL#n
\LMouseM#n
\LMouseR#n
\LMouseLR#n
\LMouseIIEmpty#n
\LMouseIIN#n
\LMouseIIL#n
\LMouseIIR#n
\LMouseIILR#n